# Copyright 2017-2018 Stan Grishin (stangri@melmac.net)
# TLD optimization written by Dirk Brenken (dev@brenken.org)
# This is free software, licensed under the GNU General Public License v3.

include $(TOPDIR)/rules.mk

PKG_NAME:=simple-adblock
PKG_VERSION:=1.8.3
PKG_RELEASE:=13
PKG_MAINTAINER:=Stan Grishin <stangri@melmac.net>
PKG_LICENSE:=GPL-3.0-or-later

include $(INCLUDE_DIR)/package.mk

define Package/simple-adblock
	SECTION:=net
	CATEGORY:=Network
	TITLE:=Simple AdBlock Service
	DEPENDS:=+jshn +jsonfilter
	PKGARCH:=all
endef

define Package/simple-adblock/description
Simple adblock script to block ad or abuse/malware domains with DNSMASQ or Unbound.
Script supports local/remote list of domains and hosts-files for both black- and white-listing.
Please see https://github.com/openwrt/packages/blob/master/net/simple-adblock/files/README.md for more information.

endef

define Package/simple-adblock/conffiles
/etc/config/simple-adblock
endef

define Build/Prepare
	mkdir -p $(PKG_BUILD_DIR)/files/
	$(CP) ./files/simple-adblock.init $(PKG_BUILD_DIR)/files/simple-adblock.init
	sed -i "s|^\(PKG_VERSION\).*|\1='$(PKG_VERSION)-$(PKG_RELEASE)'|" $(PKG_BUILD_DIR)/files/simple-adblock.init
endef

define Build/Configure
endef

define Build/Compile
endef

define Package/simple-adblock/install
	$(INSTALL_DIR) $(1)/etc/init.d
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/files/simple-adblock.init $(1)/etc/init.d/simple-adblock
	$(INSTALL_DIR) $(1)/etc/config
	$(INSTALL_CONF) ./files/simple-adblock.conf $(1)/etc/config/simple-adblock
	$(INSTALL_DIR) $(1)/tmp
	$(INSTALL_CONF) ./files/simple-adblock.conf.update $(1)/tmp/simple-adblock.conf.update
	$(INSTALL_DIR) $(1)/etc/hotplug.d/iface
	$(INSTALL_BIN) ./files/simple-adblock.hotplug $(1)/etc/hotplug.d/iface/80-simple-adblock
endef

define Package/simple-adblock/postinst
	#!/bin/sh
	# check if we are on real system
	if [ -z "$${IPKG_INSTROOT}" ]; then
		sed -f /tmp/simple-adblock.conf.update -i /etc/config/simple-adblock || true
		/etc/init.d/simple-adblock enable
	fi
	exit 0
endef

define Package/simple-adblock/prerm
	#!/bin/sh
	# check if we are on real system
	if [ -z "$${IPKG_INSTROOT}" ]; then
		echo "Stopping service and removing rc.d symlink for simple-adblock"
		/etc/init.d/simple-adblock stop || true
		/etc/init.d/simple-adblock killcache || true
		/etc/init.d/simple-adblock disable || true
	fi
	exit 0
endef

$(eval $(call BuildPackage,simple-adblock))
