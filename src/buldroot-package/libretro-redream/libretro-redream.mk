################################################################################
#
# REDREAM
#
################################################################################
# Version.: Commits on Jun 7, 2020
LIBRETRO_REDREAM_VERSION = bf4d812daf326c56e99208a4c30acae1475fd701
LIBRETRO_REDREAM_SITE = $(call github,libretro,retrodream,$(LIBRETRO_REDREAM_VERSION))
LIBRETRO_REDREAM_LICENSE="GPLv3"

define LIBRETRO_REDREAM_BUILD_CMDS
        CFLAGS="$(TARGET_CFLAGS)" CXXFLAGS="$(TARGET_CXXFLAGS)" $(MAKE) CXX="$(TARGET_CXX)" \
		CC="$(TARGET_CC)" AR="$(TARGET_AR)" -C $(@D)/deps/libretro/ -f Makefile platform="$(LIBRETRO_PLATFORM)"
endef

define LIBRETRO_REDREAM_INSTALL_TARGET_CMDS
	$(INSTALL) -D $(@D)/deps/libretro/retrodream_libretro.so \
		$(TARGET_DIR)/usr/lib/libretro/redream_libretro.so
endef

$(eval $(generic-package))
