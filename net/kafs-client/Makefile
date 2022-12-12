include $(TOPDIR)/rules.mk

PKG_NAME:=kafs-client
PKG_VERSION:=0.5
PKG_RELEASE:=1

PKG_SOURCE_PROTO:=git
PKG_SOURCE_URL:=git://git.infradead.org/users/dhowells/kafs-client.git
PKG_SOURCE_VERSION:=c7d868e8b343ff04b8fa9ab7cb00e80375002d32
PKG_MIRROR_HASH:=58a960ae76242dfdfdcac0ef1f51223269d8cb66fe8dd760ce510997d80760a9

PKG_LICENSE:=GPL-2.0
PKG_LICENSE_FILES:=LICENSE

PKG_BUILD_PARALLEL:=1

include $(INCLUDE_DIR)/package.mk

define Package/kafs-client
	SECTION:=net
	CATEGORY:=Network
	SUBMENU:=Filesystem
	DEPENDS:=+keyutils +krb5-libs +kmod-fs-afs
	TITLE:=kafs client library
	URL:=http://git.infradead.org/users/dhowells/kafs-client.git
endef

define Package/kafs-client/description
kAFS utilities
endef

define Build/Compile
	$(MAKE) -C $(PKG_BUILD_DIR)/src \
		$(TARGET_CONFIGURE_OPTS) \
		CFLAGS="$(TARGET_CFLAGS)"
endef

define Build/InstallDev
	$(INSTALL_DIR) $(1)/usr/include/kafs
	$(CP) $(PKG_BUILD_DIR)/src/include/kafs/*.h $(1)/usr/include/kafs/
endef

define Package/kafs-client/install
	$(INSTALL_DIR) $(1)/afs

	$(INSTALL_DIR) $(1)/etc
	$(INSTALL_DIR) $(1)/etc/kafs
	$(INSTALL_DIR) $(1)/etc/kafs/client.d
	$(INSTALL_DATA) $(PKG_BUILD_DIR)/conf/client.conf $(1)/etc/kafs/

	$(INSTALL_DIR) $(1)/etc/request-key.d
	$(INSTALL_DATA) $(PKG_BUILD_DIR)/conf/kafs_dns.conf \
	    $(1)/etc/request-key.d/

	$(INSTALL_DIR) $(1)/usr/share/kafs
	$(INSTALL_DATA) $(PKG_BUILD_DIR)/conf/cellservdb.conf \
	    $(1)/usr/share/kafs/

	$(INSTALL_DIR) $(1)/usr/lib
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/src/lib*.so* $(1)/usr/lib/

	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/src/aklog-kafs $(1)/usr/bin/

	$(INSTALL_DIR) $(1)/usr/sbin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/src/kafs-check-config $(1)/usr/sbin/

	$(INSTALL_DIR) $(1)/usr/libexec
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/src/kafs-preload $(1)/usr/libexec/
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/src/kafs-dns $(1)/usr/libexec/
endef

$(eval $(call BuildPackage,kafs-client))
