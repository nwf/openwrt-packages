#
# Copyright (C) 2009-2013 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=lua-cqueues
PKG_SOURCE_VERSION:=36b4b8cf1d8d3e3224cab04357dda3a633c7f0ff
PKG_VERSION:=20171014
PKG_RELEASE:=1

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.bz2
PKG_SOURCE_URL:=https://github.com/wahern/cqueues.git
PKG_SOURCE_PROTO:=git
PKG_SOURCE_SUBDIR:=$(PKG_NAME)-$(PKG_VERSION)

include $(INCLUDE_DIR)/package.mk

define Package/lua-cqueues
  SUBMENU:=Lua
  SECTION:=lang
  CATEGORY:=Languages
  TITLE:=Lua CQueues
  URL:=http://25thandclement.com/~william/projects/cqueues.html
  MAINTAINER:=Nathaniel Wesley Filardo <nwfilardo@gmail.com>
  DEPENDS:=+lua +libopenssl +librt +libpthread
endef

define Package/lua-cqueues/description
  Continuation Queues: Embeddable asynchronous networking, threading, and
  notification framework for Lua on Unix.
endef

define Build/Configure
endef

define Build/Compile
	$(MAKE) -C $(PKG_BUILD_DIR)/ \
		ALL_LDFLAGS="$(TARGET_LDFLAGS)" \
		CC="$(TARGET_CC) $(TARGET_CFLAGS) $(TARGET_CPPFLAGS) -fPIC -std=gnu99" \
		LD="$(TARGET_CROSS)ld -shared" \
		all5.1
endef


define Package/lua-cqueues/install
	$(INSTALL_DIR) $(1)/usr/lib/lua
	$(MAKE) -C $(PKG_BUILD_DIR)/ \
		lua51path=$(1)/usr/lib/lua lua51cpath=$(1)/usr/lib/lua \
		install5.1
endef

$(eval $(call BuildPackage,lua-cqueues))
