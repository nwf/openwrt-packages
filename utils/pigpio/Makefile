# Based on Brandon Low's work at https://groups.google.com/forum/#!msg/bup-list/HIeue2eiIKc/gmPpUururMoJ

include $(TOPDIR)/rules.mk

PKG_NAME:=pigpio
PKG_VERSION:=58
PKG_REV:=2bd75cd1c4c698e8281ddbea8834ed7d7c58396a
PKG_RELEASE:=1

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.gz
PKG_SOURCE_URL:=git://github.com/joan2937/pigpio
PKG_SOURCE_SUBDIR:=$(PKG_NAME)-$(PKG_VERSION)
PKG_SOURCE_VERSION:=$(PKG_REV)
PKG_SOURCE_PROTO:=git

include $(INCLUDE_DIR)/package.mk

define Package/pigpio
  SECTION:=utils
  CATEGORY:=Utilities
  TITLE:=Pi GPIO library and daemon
  DEPENDS:=@TARGET_brcm2708 +librt +libpthread
  URL:=http://github.com/joan2937/pigpio
endef

define Package/pigpio/description
  pigpio is a C library for the Raspberry which allows control of the General Purpose Input Outputs (GPIO).

  This package contains the core C library, pigpiod daemon, and pigs CLI tool.
endef

# Nothing necessary
define Build/Configure
endef

define Build/Compile
	$(MAKE) -C $(PKG_BUILD_DIR) \
		$(TARGET_CONFIGURE_OPTS) \
		CFLAGS="$(TARGET_CFLAGS)" \
		LDFLAGS="$(TARGET_LDFLAGS)" \
	libpigpio.so pigpiod pigs
endef

define Package/pigpio/install
	$(INSTALL_DIR) $(1)/usr/lib
	$(CP) $(PKG_BUILD_DIR)/libpigpio.so $(1)/usr/lib/
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/pigs $(1)/usr/bin/
	$(INSTALL_DIR) $(1)/usr/sbin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/pigpiod $(1)/usr/sbin/
endef

$(eval $(call BuildPackage,pigpio))
