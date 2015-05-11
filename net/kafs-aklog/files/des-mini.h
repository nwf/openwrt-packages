#ifndef DES_MINI_H
#define DES_MINI_H

#define DES_CBLOCK_LEN 8
#define DES_KEY_SZ 8

typedef unsigned char DES_cblock[DES_CBLOCK_LEN];
extern void DES_set_odd_parity(DES_cblock *key);
extern int DES_is_weak_key(DES_cblock *key);
#endif
