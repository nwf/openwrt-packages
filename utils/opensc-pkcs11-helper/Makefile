#
# Copyright (C) 2011-2014 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=opensc-pkcs11-helper
PKG_VERSION:=1.29.0
PKG_RELEASE:=1
PKG_LICENSE:=LGPL-2.1+
PKG_LICENSE_FILES:=COPYING

PKG_RELEASE=$(PKG_SOURCE_VERSION)

PKG_SOURCE_PROTO:=git
PKG_SOURCE_URL:=https://github.com/OpenSC/pkcs11-helper.git
PKG_SOURCE_SUBDIR:=$(PKG_NAME)-$(PKG_VERSION)
PKG_SOURCE_VERSION:=2306f896c2f3c147792300155316fd65825aabad
PKG_MIRROR_HASH:=967c621a3d92bf64c308b2da172b3ac8989bca8cc9076c95baa122626f872694
PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.gz
# PKG_BUILD_DEPENDS:=+libopensc +libressl
PKG_FIXUP:=libtool

PKG_INSTALL:=1

include $(INCLUDE_DIR)/package.mk

define Package/opensc-pkcs11-helper
  SECTION:=libs
  CATEGORY:=Libraries
  TITLE:=OpenSC helper for PKCS11
  URL:=https://github.com/OpenSC/OpenSC/wiki
  DEPENDS:=+libopensc +libopenssl +libpthread
  MENU:=1
endef

define Package/opensc-pkcs11-helper/description
  OpenSC's PKCS11 application helper library
endef

define Build/InstallDev
	$(INSTALL_DIR) $(1)/usr/include/pkcs11-helper-1.0
	$(CP) $(PKG_INSTALL_DIR)/usr/include/pkcs11-helper-1.0/* $(1)/usr/include/pkcs11-helper-1.0/
	$(INSTALL_DIR) $(1)/usr/lib
	$(CP) $(PKG_INSTALL_DIR)/usr/lib/libpkcs11-helper.{a,so}* $(1)/usr/lib/
	$(INSTALL_DIR) $(1)/usr/lib/pkgconfig
	$(CP) $(PKG_INSTALL_DIR)/usr/lib/pkgconfig/*.pc $(1)/usr/lib/pkgconfig/
endef

define Package/opensc-pkcs11-helper/install
	$(INSTALL_DIR) $(1)/usr/lib
	$(CP) $(PKG_INSTALL_DIR)/usr/lib/libpkcs11-helper.so* $(1)/usr/lib/
endef

CONFIGURE_ARGS += \
  --enable-crypto-engine-openssl \
  --disable-crypto-engine-gnutls \
  --disable-crypto-engine-nss \
  --disable-crypto-engine-polarssl \
  --disable-crypto-engine-mbedtls \
  --disable-crypto-engine-cryptoapi

$(eval $(call BuildPackage,opensc-pkcs11-helper))
