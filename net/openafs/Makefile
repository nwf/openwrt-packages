include $(TOPDIR)/rules.mk
include $(INCLUDE_DIR)/kernel.mk

PKG_NAME:=openafs

PKG_SOURCE_URL=git://git.openafs.org/openafs.git
PKG_SOURCE_PROTO=git
PKG_SOURCE_VERSION=d7211350eec18b30e9ccf30f5e95fb58162c637d
PKG_SOURCE_SUBDIR:=$(PKG_NAME)-$(PKG_SOURCE_VERSION)

PKG_VERSION:=git
PKG_RELEASE:=5
PKG_MAINTAINER=Nathaniel Wesley Filardo <nwfilardo@gmail.com>

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION)-src.tar.bz2

PKG_LICENSE:=IPL-1.0
PKG_LICENSE_FILES:=COPYING

HOST_BUILD_PARALLEL:=1
PKG_BUILD_PARALLEL:=1

PKG_BUILD_DEPENDS+=$(PKG_NAME)/host	# our own cross-tools

HOST_BUILD_DIR:=$(BUILD_DIR_HOST)/openafs-$(PKG_SOURCE_VERSION)
PKG_BUILD_DIR:=$(BUILD_DIR)/openafs-$(PKG_SOURCE_VERSION)

# If someone wants to take a stab at making this build a release rather than master...
#PKG_VERSION:=1.6.21
#HOST_BUILD_DIR:=$(BUILD_DIR_HOST)/openafs-$(PKG_VERSION)
#PKG_BUILD_DIR:=$(BUILD_DIR)/openafs-$(PKG_VERSION)
#PKG_SOURCE_URL:=https://www.openafs.org/dl/$(PKG_NAME)/$(PKG_VERSION)/
#PKG_HASH:=ba9c1f615edd53b64fc271ad369c49a816acedca70cdd090975033469a84118f

include $(INCLUDE_DIR)/host-build.mk
include $(INCLUDE_DIR)/package.mk

HOST_CONFIGURE_ARGS+= \
	--disable-fuse-client \
	--enable-pthreaded-ubik \
	--enable-supergroups \
	--disable-kernel-module

define Host/Prepare
	$(call Host/Prepare/Default)
	(cd $(HOST_BUILD_DIR); ./regen.sh -q)
endef

define Host/Compile
	$(call Host/Compile/Default, config comerr rxgen)
endef

define Host/Install
	$(INSTALL_DIR) $(STAGING_DIR_HOST)/afsbin
	$(INSTALL_BIN) $(HOST_BUILD_DIR)/src/config/config     $(STAGING_DIR_HOST)/afsbin/
	$(INSTALL_BIN) $(HOST_BUILD_DIR)/src/comerr/compile_et $(STAGING_DIR_HOST)/afsbin/
	$(INSTALL_BIN) $(HOST_BUILD_DIR)/src/rxgen/rxgen       $(STAGING_DIR_HOST)/afsbin/
endef


define Build/Prepare
	$(Build/Prepare/Default)
	(cd $(PKG_BUILD_DIR); ./regen.sh -q)
endef

CONFIGURE_ARGS+= \
	--with-crosstools-dir=$(STAGING_DIR_HOST)/afsbin \
	--disable-fuse-client \
	--enable-pthreaded-ubik \
	--enable-supergroups

# Have to do the ac_cv_path_ thing for PATH_CPP because $(TARGET_CC)
# may not contain a / if we're using ccache.
#
# It does not hurt to set CROSS_COMPILE and ARCH even if we are not
# building the kernel module.
#
CONFIGURE_VARS+= \
	ac_cv_path_PATH_CPP="$(TARGET_CROSS)cpp" \
	CROSS_COMPILE="$(TARGET_CROSS)" \
	ARCH="$(LINUX_KARCH)"

MAKE_VARS+= \
	CROSS_COMPILE="$(TARGET_CROSS)" \
	ARCH="$(LINUX_KARCH)"


define Build/Compile
	$(call Build/Compile/Default, $(OPENAFS_BUILD_TARGETS))
endef

define Package/openafs/common
	URL:=https://www.openafs.org
endef

define Package/openafs-solib
  SECTION:=net
  CATEGORY:=Network
  TITLE:=OpenAFS Libraries
  DEPENDS:=+libpthread +krb5-libs +libcomerr
  $(call Package/openafs/common)
endef

define Package/openafs-libs/description
  OpenAFS dynamic-link libraries
endef

ifdef CONFIG_PACKAGE_openafs-solib
  OPENAFS_BUILD_TARGETS+=hcrypto roken
endif

define Package/openafs-solib/install
	$(INSTALL_DIR) $(1)/usr/lib
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/src/crypto/hcrypto/.libs/libafshcrypto*.so* $(1)/usr/lib/
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/src/roken/.libs/librokenafs*.so* $(1)/usr/lib/
endef


define Package/openafs-bosserver
  SECTION:=net
  CATEGORY:=Network
  TITLE:=OpenAFS Basic OverSeer server and client
  DEPENDS:=+libpthread +krb5-libs +libcomerr +openafs-solib

  $(call Package/openafs/common)
endef

define Package/openafs-bosserver/description
  OpenAFS process supervisor server and client
endef

ifdef CONFIG_PACKAGE_openafs-bosserver
  OPENAFS_BUILD_TARGETS+=bozo
endif

define Package/openafs-bosserver/install
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/src/bozo/bos $(1)/usr/bin/
	$(INSTALL_DIR) $(1)/usr/sbin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/src/bozo/bosserver $(1)/usr/sbin/
	$(INSTALL_DIR) $(1)/etc/init.d
	$(INSTALL_BIN) ./files/openafs-server.init $(1)/etc/init.d/openafs-server
	$(INSTALL_DIR) $(1)/etc/openafs/server
endef


define Package/openafs-dbservers
  SECTION:=net
  CATEGORY:=Network
  TITLE:=OpenAFS Cell Database Servers
  DEPENDS:=+libpthread +krb5-libs +libcomerr +openafs-solib
  $(call Package/openafs/common)
endef

define Package/openafs-dbservers/description
  OpenAFS Database Servers (VLDB, PRDB)
endef

ifdef CONFIG_PACKAGE_openafs-dbservers
  OPENAFS_BUILD_TARGETS+=tvlserver tptserver
endif

define Package/openafs-dbservers/install
	$(INSTALL_DIR) $(1)/usr/sbin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/src/tvlserver/vldb_check $(1)/usr/sbin/
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/src/tptserver/db_verify $(1)/usr/sbin/prdb_check
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/src/tptserver/pt_util $(1)/usr/sbin/
	$(INSTALL_DIR) $(1)/usr/lib/openafs
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/src/tptserver/ptserver $(1)/usr/lib/openafs/
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/src/tvlserver/vlserver $(1)/usr/lib/openafs/
endef


define Package/openafs-dafileserver
  SECTION:=net
  CATEGORY:=Network
  TITLE:=OpenAFS Demand-Attach File Server and subordinates
  DEPENDS:=+libpthread +krb5-libs +libcomerr +openafs-solib +openafs-bosserver
  $(call Package/openafs/common)
endef

define Package/openafs-dafileserver/description
  OpenAFS Demand Attach File Server, volser, and salvager
endef

ifdef CONFIG_PACKAGE_openafs-dafileserver
  OPENAFS_BUILD_TARGETS+=dviced dvolser tsalvaged vol volser
endif

define Package/openafs-dafileserver/install
	$(INSTALL_DIR) $(1)/usr/sbin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/src/vol/volinfo              $(1)/usr/sbin/
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/src/volser/voldump           $(1)/usr/sbin/
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/src/volser/restorevol        $(1)/usr/sbin/
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/src/dviced/state_analyzer    $(1)/usr/sbin/
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/src/tsalvaged/dafssync-debug $(1)/usr/sbin/
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/src/tsalvaged/salvsync-debug $(1)/usr/sbin/
	$(INSTALL_DIR) $(1)/usr/lib/openafs
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/src/dvolser/davolserver      $(1)/usr/lib/openafs/
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/src/dviced/dafileserver      $(1)/usr/lib/openafs/
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/src/tsalvaged/dasalvager     $(1)/usr/lib/openafs/
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/src/tsalvaged/salvageserver  $(1)/usr/lib/openafs/
endef


define Package/openafs-utils
  SECTION:=net
  CATEGORY:=Network
  TITLE:=OpenAFS Userland Programs
  DEPENDS:=+libpthread +krb5-libs +libcomerr +openafs-solib
  $(call Package/openafs/common)
endef

define Package/openafs-utils/description
  OpenAFS Userland Programs: fs, pts, vos, tokens, pagsh, aklog, unlog, rxdebug, udebug
endef

ifdef CONFIG_PACKAGE_openafs-utils
  OPENAFS_BUILD_TARGETS+=aklog log tptserver tvolser venus
endif

define Package/openafs-utils/install
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/src/aklog/aklog              $(1)/usr/bin/
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/src/venus/fs                 $(1)/usr/bin/
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/src/log/pagsh                $(1)/usr/bin/
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/src/tptserver/pts            $(1)/usr/bin/
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/src/log/tokens               $(1)/usr/bin/
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/src/log/unlog                $(1)/usr/bin/
	$(INSTALL_DIR) $(1)/usr/sbin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/src/tvolser/vos              $(1)/usr/sbin/
endef


define Package/openafs-utils-debug
  SECTION:=net
  CATEGORY:=Network
  TITLE:=OpenAFS Userland Debugging Programs
  DEPENDS:=+openafs-solib
  $(call Package/openafs/common)
endef

define Package/openafs-utils-debug/description
  OpenAFS Userland Programs: rxdebug, udebug
endef

ifdef CONFIG_PACKAGE_openafs-utils-debug
  OPENAFS_BUILD_TARGETS+=rxdebug tubik
endif

define Package/openafs-utils-debug/install
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/src/tubik/udebug             $(1)/usr/bin/
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/src/rxdebug/rxdebug          $(1)/usr/bin/
endef


define Package/openafs-client
  SECTION:=net
  CATEGORY:=Network
  TITLE:=OpenAFS Client Cache Manager
  DEPENDS:=+libpthread +krb5-libs +libcomerr +openafs-solib +kmod-openafs-client
  $(call Package/openafs/common)
endef

define Package/openafs-client/description
  OpenAFS Client Cache Manager
endef

ifdef CONFIG_PACKAGE_openafs-client
  OPENAFS_BUILD_TARGETS+=afsd venus
endif

define Package/openafs-client/install
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/src/venus/cmdebug            $(1)/usr/bin/
	$(INSTALL_DIR) $(1)/usr/sbin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/src/afsd/afsd                $(1)/usr/sbin/
	$(INSTALL_DIR) $(1)/etc/init.d
	$(INSTALL_BIN) ./files/openafs.init $(1)/etc/init.d/openafs
	$(INSTALL_DIR) $(1)/etc/openafs
	$(INSTALL_DATA) ./files/cacheinfo $(1)/etc/openafs/
	$(INSTALL_DATA) ./files/CellServDB $(1)/etc/openafs/
	echo 'acm.jhu.edu' > $(1)/etc/openafs/ThisCell
endef


define KernelPackage/openafs-client
	SUBMENU:=$(FS_MENU)
	TITLE:=OpenAFS kernel modules
	DEPENDS:=+@KERNEL_KEYS
	### AUTOLOAD:=$(call AutoLoad,50,libafs)
	FILES:= \
		$(PKG_BUILD_DIR)/src/libafs/MODLOAD-$(LINUX_VERSION)-*/libafs.$(LINUX_KMOD_SUFFIX)
endef

ifneq ($(CONFIG_PACKAGE_kmod-openafs-client),)
  OPENAFS_BUILD_TARGETS+=libafs
  CONFIGURE_ARGS+= --enable-kernel-module \
                   --with-linux-kernel-headers=$(LINUX_DIR)
else
  CONFIGURE_ARGS+= --disable-kernel-module
endif

define KernelPackage/openafs-client/install
	$(INSTALL_DIR) $(1)/lib/modules/$(LINUX_VERSION)
endef

$(eval $(call HostBuild))
$(eval $(call BuildPackage,openafs-solib))
$(eval $(call BuildPackage,openafs-bosserver))
$(eval $(call BuildPackage,openafs-dbservers))
$(eval $(call BuildPackage,openafs-dafileserver))
$(eval $(call BuildPackage,openafs-utils))
$(eval $(call BuildPackage,openafs-utils-debug))
$(eval $(call BuildPackage,openafs-client))
$(eval $(call KernelPackage,openafs-client))
