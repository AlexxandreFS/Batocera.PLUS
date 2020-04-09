################################################################################
#
# METEOR
#
################################################################################
# Version.: Commits on Sep 12, 2019
LIBRETRO_METEOR_VERSION = 3d21e3b5a7596918bee0fcaca5752ae76624c05e
LIBRETRO_METEOR_SITE = $(call github,libretro,meteor-libretro,$(LIBRETRO_METEOR_VERSION))
LIBRETRO_METEOR_LICENSE="GPLv3"


define LIBRETRO_METEOR_BUILD_CMDS
	CFLAGS="$(TARGET_CFLAGS)" CXXFLAGS="$(TARGET_CXXFLAGS)" \
	$(MAKE) CXX="$(TARGET_CXX)" CC="$(TARGET_CC)" LD="$(TARGET_LD)" AR="$(TARGET_AR)" RANLIB="$(TARGET_RANLIB)" -C $(@D)/libretro platform="$(LIBRETRO_PLATFORM)"
endef

define LIBRETRO_METEOR_INSTALL_TARGET_CMDS
	$(INSTALL) -D $(@D)/libretro/meteor_libretro.so \
		$(TARGET_DIR)/usr/lib/libretro/meteor_libretro.so
endef

$(eval $(generic-package))
