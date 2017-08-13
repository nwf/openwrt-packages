#
# Copyright (C) 2017 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=direwolf
PKG_VERSION:=1.4
PKG_RELEASE:=1

PKG_SOURCE:=$(PKG_VERSION).tar.gz
PKG_SOURCE_URL:=https://github.com/wb2osz/$(PKG_NAME)/archive/$(PKG_VERSION)/
PKG_HASH:=49e831c207261272f252433a542069ecaba5dad813a5b9efca6802021c295a3a

PKG_INSTALL:=1

PKG_MAINTAINER:=Nathaniel Wesley Filardo <nwfilardo@gmail.com>
PKG_LICENSE:=GPL-2.0
PKG_LICENSE_FILES:=COPYING

include $(INCLUDE_DIR)/package.mk

define Package/direwolf
SECTION:=sound
CATEGORY:=Sound
TITLE:=direwolf soundcard modem/TNC and APRS codec
URL:=https://github.com/wb2osz/direwolf
DEPENDS:=+alsa-lib
endef

define Package/direwolf/description
  direwolf is a soundcard-based modem/TNC with integrated APRS codec.

  Building this package requires libasound2-dev on the host!
endef

TARGET_CFLAGS += $(FPIC)
TARGET_LDFLAGS += -Wl,-rpath-link,$(STAGING_DIR)/usr/lib

define Build/Compile
	CFLAGS="$(HOST_CFLAGS)" \
	LDFLAGS="$(HOST_LDFLAGS)" \
	$(MAKE) $(PKG_JOBS) -C $(PKG_BUILD_DIR) -f Makefile.linux \
		CC="$(HOSTCC)" \
		gen_fff

	CFLAGS="$(TARGET_CFLAGS)" \
	LDFLAGS="$(TARGET_LDFLAGS)" \
	$(MAKE) $(PKG_JOBS) -C $(PKG_BUILD_DIR) -f Makefile.linux \
		CC="$(TARGET_CC)" \
		direwolf
endef

define Build/Install
endef

define Package/direwolf/install
	$(INSTALL_DIR) $(1)/usr/bin
	$(CP) $(PKG_BUILD_DIR)/direwolf $(1)/usr/bin
endef

$(eval $(call BuildPackage,direwolf))
