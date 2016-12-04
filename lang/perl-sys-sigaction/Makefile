#
# Copyright (C) 2015 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=perl-sys-sigaction
PKG_VERSION:=0.21
PKG_RELEASE:=1

PKG_SOURCE_URL:=http://search.cpan.org/CPAN/authors/id/L/LB/LBAXTER
PKG_SOURCE:=Sys-SigAction-$(PKG_VERSION).tar.gz
PKG_MD5SUM:=68a8f727b2763945dd06552899e3e8e4

PKG_BUILD_DIR:=$(BUILD_DIR)/perl/Sys-SigAction-$(PKG_VERSION)

include $(INCLUDE_DIR)/package.mk
include ../perl/perlmod.mk

define Package/perl-sys-sigaction
  SUBMENU:=Perl
  SECTION:=lang
  CATEGORY:=Languages
  TITLE:=Sys::SigAction module
  URL:=http://search.cpan.org/~lbaxter/Sys-SigAction/lib/Sys/SigAction.pm
  DEPENDS:=perl +perlbase-base +perlbase-essential
endef

define Build/Configure
        $(call perlmod/Configure,,)
endef

define Build/Compile
        $(call perlmod/Compile,,)
endef

define Package/perl-sys-sigaction/install
        $(call perlmod/Install,$(1), auto/Sys/SigAction Sys/SigAction.pm Sys/SigAction)
endef


$(eval $(call BuildPackage,perl-sys-sigaction))
