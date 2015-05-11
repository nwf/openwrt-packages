/* aklog.c: get krb5-based rxkad tokens for kAFS
 *
 * Copyright (C) 2008,2012 Chaskiel Grundman. All Rights Reserved.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version
 * 2 of the License, or (at your option) any later version.
 *
 * build with gcc -o aklog-kafs aklog-kafs.c des-mini.c -lkrb5 -lkeyutils \
 *            -lgcrypt
 *
 * Based on code:
 * Copyright (C) 2007 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 */

#define _XOPEN_SOURCE 500
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <keyutils.h>
#include <gcrypt.h>
#include <krb5.h>

#ifdef USING_HEIMDAL
#define CREDS_ENCTYPE(c) (c)->session.keytype
#define CREDS_KEYLEN(c) (c)->session.keyvalue.length
#define CREDS_KEYDATA(c) (c)->session.keyvalue.data
#else
#define CREDS_ENCTYPE(c) (c)->keyblock.enctype
#define CREDS_KEYLEN(c) (c)->keyblock.length
#define CREDS_KEYDATA(c) (c)->keyblock.contents
#endif
struct rxrpc_key_sec2_v1 {
        uint32_t        kver;                   /* key payload interface version */
        uint16_t        security_index;         /* RxRPC header security index */
        uint16_t        ticket_length;          /* length of ticket[] */
        uint32_t        expiry;                 /* time at which expires */
        uint32_t        kvno;                   /* key version number */
        uint8_t         session_key[8];         /* DES session key */
        uint8_t         ticket[0];              /* the encrypted ticket */
};

#define RXKAD_TKT_TYPE_KERBEROS_V5              256
#define OSERROR(X, Y) do { if ((long)(X) == -1) { perror(Y); exit(1); } } while(0)
#define KRBERROR(X, Y) do { if ((X) != 0) { const char *msg = krb5_get_error_message(k5_ctx, (X)); fprintf(stderr, "%s: %s\n", (Y), msg); krb5_free_error_message(k5_ctx, msg); exit(1); } } while(0)

#include "des-mini.h"

static int compress_parity_bits(void *in, void *out, size_t *bytes) {

  size_t i, j;
  unsigned char *s, *sb, *d, t;
  if (*bytes % 8)
    return 1;
  s=sb=in;
  sb+=7;
  d=out;

  for (i=0; i<(*bytes)/8; i++) {
    for (j=0; j<7; j++) {
      t=*s++ & 0xfe; /* high 7 bits from this byte */
      t |= (*sb >> (j+1)) & 0x01; /* low bit is the xth bit of the 8th byte in this group */
      *d++=t;
    }
    s++; /* skip byte used to fill in parity bits */
    sb+=8; /* next block */
  }
  *bytes=d-(unsigned char *)out;
  return 0;
}

static int compute_session_key(void *out, int enctype, size_t keylen, 
			       void *keydata) {
  gcry_md_hd_t md;
  unsigned char *mdtmp;
  DES_cblock keytmp;
  int i;
  unsigned char ctr;
  unsigned char L[4];
  char label[]="rxkad";

  if (gcry_md_open(&md, GCRY_MD_MD5, GCRY_MD_FLAG_HMAC))
    return 1;
  if (gcry_md_setkey(md, keydata, keylen)) {
    gcry_md_close(md);
    return 1;
  }
  L[0]=0;
  L[1]=0;
  L[2]=0;
  L[3]=64;
  for (i=1; i< 256; i++) {
    ctr=i & 0xFF;
    gcry_md_write(md, &ctr, 1);
    gcry_md_write(md, label, strlen(label)+1); /* write the null too */
    gcry_md_write(md, L, 4);
    mdtmp=gcry_md_read(md, 0);
    if (!mdtmp) {
      gcry_md_close(md);
      return 1;
    }
    memcpy(keytmp, mdtmp, DES_CBLOCK_LEN);
    DES_set_odd_parity(&keytmp);
    if (!DES_is_weak_key(&keytmp)) {
      memcpy(out, keytmp, DES_CBLOCK_LEN);
      gcry_md_close(md);
      return 0;
    }
    gcry_md_reset(md);
  }
  gcry_md_close(md);
  return 1;
}

static int convert_key(void *out, int enctype, size_t keylen, 
			       void *keydata) {
  char tdesbuf[24];
  
  switch (enctype) {
  case ENCTYPE_DES_CBC_CRC:
  case ENCTYPE_DES_CBC_MD4:
  case ENCTYPE_DES_CBC_MD5:
    if (keylen != 8)
      return 1;
    
    /* Extract session key */
    memcpy(out, keydata, 8);
    break;
  case ENCTYPE_NULL:
  case 4:
  case 6:
  case 8:
  case 9:
  case 10:
  case 11:
  case 12:
  case 13:
  case 14:
  case 15:
    return 1;
    /*In order to become a "Cryptographic Key" as specified in
     * SP800-108, it must be indistinguishable from a random bitstring. */
  case 5:
  case 7:
  case ENCTYPE_DES3_CBC_SHA1:
    if (keylen > 24)
      return 1;
    if (compress_parity_bits(keydata, tdesbuf, &keylen))
      return 1;
    keydata=tdesbuf;
    /* FALLTHROUGH */
  default:
    if (enctype < 0)
      return 1;
    if (keylen < 7)
      return 1;
    return compute_session_key(out, enctype, keylen, keydata);
  }
  return 0;
}

int main(int argc, char **argv) {
  char *cell, *realm, *p;
  int ret, mode;
  size_t plen;
  struct rxrpc_key_sec2_v1 *payload;
  char description[256];
  key_serial_t dest_keyring, sessring, usessring;
  krb5_error_code kresult;
  krb5_context k5_ctx;
  krb5_ccache cc;
  krb5_creds search_cred, *creds;

  if (argc < 3) {
    fprintf(stderr, "Usage: aklog cell realm\n");
    exit(1);
  }
  cell=argv[1];
  realm=argv[2];

  kresult=krb5_init_context(&k5_ctx);
  if (kresult) { fprintf(stderr, "krb5_init_context failed\n"); exit(1); }
  kresult=krb5_allow_weak_crypto(k5_ctx, 1);
  KRBERROR(kresult, "Enabling weak crypto (DES) use");
  kresult = krb5_cc_default(k5_ctx, &cc);
  KRBERROR(kresult, "Getting credential cache");

  memset(&search_cred, 0, sizeof(krb5_creds));

  kresult = krb5_cc_get_principal(k5_ctx, cc, &search_cred.client);
  KRBERROR(kresult, "Getting client principal");

  for (mode=0;mode < 2;mode++) {
    kresult = krb5_build_principal(k5_ctx, &search_cred.server,
				   strlen(realm), realm, "afs",
				   mode ? NULL : cell, NULL);
    KRBERROR(kresult, "Building server principal name");
    kresult = krb5_get_credentials(k5_ctx, 0, cc, &search_cred, &creds);
    if (kresult == 0)
      break;
    krb5_free_principal(k5_ctx, search_cred.server);
    search_cred.server=NULL;
  }
  KRBERROR(kresult, "Getting tickets");

  plen = sizeof(*payload) + creds->ticket.length;
  payload = calloc(1, plen + 4);
  if (!payload) {
    perror("calloc");
    exit(1);
  }
  
  /* use version 1 of the key data interface */
  payload->kver           = 1;
  payload->security_index = 2;
  payload->ticket_length  = creds->ticket.length;
  payload->expiry         = creds->times.endtime;
  payload->kvno           = RXKAD_TKT_TYPE_KERBEROS_V5;
  if (convert_key(payload->session_key, CREDS_ENCTYPE(creds),
		  CREDS_KEYLEN(creds), CREDS_KEYDATA(creds))) {
    fprintf(stderr, "session key could not be converted to a suitable DES key\n");
    exit(1);
  }
  memcpy(payload->ticket, creds->ticket.data, creds->ticket.length);

  /* if the session keyring is not set (i.e. using the uid session keyring),
     then the kernel will instantiate a new session keyring if any keys are
     added to KEY_SPEC_SESSION_KEYRING! Since we exit immediately, that
     keyring will be orphaned. So, add the key to KEY_SPEC_USER_SESSION_KEYRING
     in that case */
  dest_keyring=KEY_SPEC_SESSION_KEYRING;
  sessring=keyctl_get_keyring_ID(KEY_SPEC_SESSION_KEYRING, 0);
  usessring=keyctl_get_keyring_ID(KEY_SPEC_USER_SESSION_KEYRING, 0);
  if (sessring == usessring)
     dest_keyring=KEY_SPEC_USER_SESSION_KEYRING;
  snprintf(description, 255, "afs@%s", cell);
  p=&description[4];
  while(*p) {
     if (isalpha(*p) && islower(*p)) *p=toupper(*p);
     p++;
  }

  ret = add_key("rxrpc", description, payload, plen, dest_keyring);
  OSERROR(ret, "add_key");

  krb5_free_creds(k5_ctx, creds);
  krb5_free_cred_contents(k5_ctx, &search_cred);
  krb5_cc_close(k5_ctx, cc);
  krb5_free_context(k5_ctx);
  exit(0);
}
