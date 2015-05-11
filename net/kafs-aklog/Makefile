#
# Copyright (C) 2014 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=kafs-aklog
PKG_RELEASE=1-kdf
PKG_LICENSE:=GPLv2
PKG_MAINTAINER:=Nathaniel Wesley Filardo <nwf@cs.jhu.edu>

PKG_BUILD_DIR := $(BUILD_DIR)/$(PKG_NAME)
include $(INCLUDE_DIR)/package.mk

define Package/kafs-aklog
  SECTION:=net
  CATEGORY:=Network
  SUBMENU:=Filesystem
  TITLE:=kafs-aklog
  DEPENDS:=+libkeyutils +krb5-libs +libgcrypt +kmod-fs-afs
endef

define Build/Prepare
	$(CP) ./files/* $(PKG_BUILD_DIR)/
endef

TARGET_CFLAGS+=-I$(STAGING_DIR)/usr/include/krb5

define Package/kafs-aklog/install
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/aklog-kafs-kdf $(1)/usr/bin
endef

$(eval $(call BuildPackage,kafs-aklog))
