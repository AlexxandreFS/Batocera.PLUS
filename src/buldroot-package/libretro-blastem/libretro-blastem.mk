################################################################################
#
# LIBRETRO BLASTEM
#
################################################################################
# Version.: Commits on Jun 20, 2019
LIBRETRO_BLASTEM_VERSION = 4206da1f986ecda199c82d4a2404eff904397f55
LIBRETRO_BLASTEM_SITE = $(call github,libretro,blastem,$(LIBRETRO_BLASTEM_VERSION))
LIBRETRO_BLASTEM_LICENSE = GPLv3

LIBRETRO_BLASTEM_CONF_OPTS  = target="libretro"
LIBRETRO_BLASTEM_CONF_OPTS += platform=linux


define LIBRETRO_BLASTEM_BUILD_CMDS
	CFLAGS="$(TARGET_CFLAGS)" \
    CXXFLAGS="$(TARGET_CXXFLAGS)" \
    $(MAKE) CXX="$(TARGET_CXX)" CC="$(TARGET_CC)" -C $(@D)/ -f Makefile.libretro $(LIBRETRO_BLASTEM) 
endef

define LIBRETRO_BLASTEM_INSTALL_TARGET_CMDS
	$(INSTALL) -D $(@D)/blastem_libretro.so \
		$(TARGET_DIR)/usr/lib/libretro/blastem_libretro.so
endef

$(eval $(generic-package))
