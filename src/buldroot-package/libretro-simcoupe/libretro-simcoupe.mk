################################################################################
#
# SIMCOUPE
#
################################################################################
# Version.: Commits on Aug 17, 2019
LIBRETRO_SIMCOUPE_VERSION = c28046241ac6a4d79e55326b6e354dc02f92fa34
LIBRETRO_SIMCOUPE_SITE = $(call github,libretro,libretro-simcoupe,$(LIBRETRO_SIMCOUPE_VERSION))
LIBRETRO_SIMCOUPE_LICENSE = GPLv2

define LIBRETRO_SIMCOUPE_BUILD_CMDS
	CFLAGS="$(TARGET_CFLAGS)" \
    CXXFLAGS="$(TARGET_CXXFLAGS)"\
    $(MAKE) CXX="$(TARGET_CXX)" \
            CC="$(TARGET_CC)" \
		    -C $(@D) -f Makefile
endef

define LIBRETRO_SIMCOUPE_INSTALL_TARGET_CMDS
	$(INSTALL) -D $(@D)/libretro-simcp.so \
		$(TARGET_DIR)/usr/lib/libretro/libretro-simcp.so
endef

$(eval $(generic-package))
