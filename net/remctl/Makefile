#
# Copyright (C) 2015 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.

include $(TOPDIR)/rules.mk

PKG_NAME:=remctl
PKG_VERSION:=3.9
PKG_RELEASE:=1
PKG_LICENSE:=Various

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.gz
PKG_SOURCE_URL:=http://archives.eyrie.org/software/kerberos/
PKG_MD5SUM:=71ac5a1b1f6ac7145a8a47ecbf3f1864

PKG_MAINTAINER:=Nathaniel Wesley Filardo <nwf@cs.jhu.edu>

include $(INCLUDE_DIR)/package.mk

define Package/remctl
  SECTION:=net
  CATEGORY:=Network
  TITLE:=Kerberized Remote Control
  URL:=http://www.eyrie.org/~eagle/software/remctl/
  DEPENDS:=+krb5-libs +libevent2
endef

# Work around broken tests which fail in cross-compilation
# inet_ntoa manifests as a compilation failure, the others are just... sigh.
CONFIGURE_VARS += \
  rra_cv_func_inet_ntoa_works=yes \
  rra_cv_func_snprintf_works=yes \
  rra_cv_func_getaddrinfo_addrconfig_works=yes \
  rra_cv_in6_are_addr_equal_broken=no

define Package/remctl/install
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/client/remctl $(1)/usr/bin/
	$(INSTALL_DIR) $(1)/usr/sbin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/server/remctld $(1)/usr/sbin/
endef

$(eval $(call BuildPackage,remctl))
