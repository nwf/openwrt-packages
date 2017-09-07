#
# Copyright (C) 2017 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=pcimem
PKG_VERSION:=0.0
PKG_RELEASE:=1

PKG_SOURCE_URL:=git://github.com/billfarrow/pcimem.git
PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION)-$(PKG_RELEASE).tar.xz
PKG_SOURCE_VERSION:=1971bfb3895107119a7b50310040cbf219570118
PKG_SOURCE_SUBDIR:=$(PKG_NAME)-$(PKG_VERSION)-$(PKG_RELEASE)
PKG_BUILD_DIR:=$(BUILD_DIR)/$(PKG_NAME)-$(PKG_VERSION)-$(PKG_RELEASE)

PKG_LICENSE:=GPLv2

include $(INCLUDE_DIR)/package.mk

define Package/pcimem
  CATEGORY:=Utilities
  TITLE:=Simple program to read & write to a PCI memory-mapped resource from userspace
  URL:=https://github.com/billfarrow/pcimem
  DEPENDS:=
endef

define Package/pcimem/description
  The pcimem application provides a simple method of reading and writing
  to memory registers on a PCI card.
endef

define Build/Compile
	$(TARGET_CC) $(TARGET_CFLAGS) $(TARGET_CPPFLAGS) \
		-o $(PKG_BUILD_DIR)/pcimem \
		$(PKG_BUILD_DIR)/pcimem.c
endef

define Package/pcimem/install
	$(INSTALL_DIR) $(1)/usr/sbin
	$(CP) $(PKG_BUILD_DIR)/pcimem $(1)/usr/sbin
endef

$(eval $(call BuildPackage,pcimem))
