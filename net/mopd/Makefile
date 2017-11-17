#
# Copyright (C) 2017 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=mopd
PKG_VERSION:=2.5.3
PKG_RELEASE:=1

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.gz
PKG_SOURCE_PROTO:=git
PKG_SOURCE_URL:=https://github.com/qu1j0t3/mopd.git
PKG_SOURCE_VERSION:=41275e0b29e6c63c9a9bd319b7068fb967440418

PKG_MAINTAINER:=nwf
PKG_LICENSE:=BSD

include $(INCLUDE_DIR)/package.mk

define Package/mopd
  SECTION:=net
  CATEGORY:=Network
  DEPENDS:=$(PKG_DEFAULT_DEPENDS)
  TITLE:=MOP tools
  URL:=https://github.com/qu1j0t3/mopd
endef

define Package/mopd/description
DEC Maintenance Operation Protocol support
endef

define Package/mopd/install
	$(INSTALL_DIR) $(1)/usr/sbin	
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/mopd/mopd $(1)/usr/sbin/mopd
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/mopchk/mopchk $(1)/usr/sbin/mopchk
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/moptrace/moptrace $(1)/usr/sbin/moptrace
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/mopprobe/mopprobe $(1)/usr/sbin/mopprobe
endef

$(eval $(call BuildPackage,mopd))
