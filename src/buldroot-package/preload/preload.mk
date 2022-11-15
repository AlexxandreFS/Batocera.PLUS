################################################################################
#
# PRELOAD
#
################################################################################

PRELOAD_VERSION = 0.6.4
PRELOAD_SOURCE = preload-$(PRELOAD_VERSION).tar.gz
PRELOAD_SITE = https://sourceforge.net/projects/preload/files
PRELOAD_LICENSE = GPL-2.0
PRELOAD_DEPENDENCIES = host-pkgconf

TARGET_CONFIGURE_OPTS += GLIB_CFLAGS="-lglib-2.0"

define PRELOAD_CONFIGURE_CMDS
	cd $(@D); ./configure \
        --prefix=/usr \
        --sbindir=/usr/bin \
        --sysconfdir=/etc \
        --localstatedir=/userdata/system/.config/preload
endef

define PRELOAD_BUILD_CMDS
	$(TARGET_CONFIGURE_OPTS) $(MAKE) -C $(@D)
endef

define PRELOAD_INSTALL_TARGET_CMDS
	$(INSTALL) -m 0755 -D $(@D)/src/preload      $(TARGET_DIR)/usr/bin/preload
	$(INSTALL) -m 0655 -D $(@D)/src/preload.conf $(TARGET_DIR)/etc/preload.conf
endef

$(eval $(generic-package))
