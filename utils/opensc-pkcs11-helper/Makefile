#
# Copyright (C) 2011-2014 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=opensc-pkcs11-helper
PKG_VERSION:=20170729
PKG_RELEASE:=1
PKG_LICENSE:=LGPL-2.1+
PKG_LICENSE_FILES:=COPYING

PKG_RELEASE=$(PKG_SOURCE_VERSION)

PKG_SOURCE_PROTO:=git
PKG_SOURCE_URL:=https://github.com/OpenSC/pkcs11-helper.git
PKG_SOURCE_SUBDIR:=$(PKG_NAME)-$(PKG_VERSION)
PKG_SOURCE_VERSION:=febfaa5b928ca2a66de03303334653c8e3b24a90
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
	$(CP) $(PKG_INSTALL_DIR)/usr/lib/libpkcs11-helper.{a,so}* $(1)/usr/lib/
endef

CONFIGURE_ARGS += \
  --enable-crypto-engine-openssl \
  --disable-crypto-engine-gnutls \
  --disable-crypto-engine-nss \
  --disable-crypto-engine-polarssl \
  --disable-crypto-engine-mbedtls \
  --disable-crypto-engine-cryptoapi

$(eval $(call BuildPackage,opensc-pkcs11-helper))
