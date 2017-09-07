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

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION)-$(PKG_RELEASE).tar.xz
PKG_SOURCE_URL:=https://github.com/billfarrow/pcimem.git
PKG_SOURCE_PROTO:=git
PKG_SOURCE_VERSION:=09724edb1783a98da2b7ae53c5aaa87493aabc9b
PKG_MIRROR_HASH:=bf132ca30836b8665e6946f6fb53d149d8945c97c09dc7bb94cbce7f42d013f3
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
