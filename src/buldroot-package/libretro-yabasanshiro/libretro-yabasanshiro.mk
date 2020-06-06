################################################################################
#
# YABASANSHIRO
#
################################################################################
# Version.: Commits on Apr 27, 2020
LIBRETRO_YABASANSHIRO_VERSION = 7ae0de7abc378f6077aff0fd365ab25cff58b055
LIBRETRO_YABASANSHIRO_SITE = $(call github,libretro,yabause,$(LIBRETRO_YABASANSHIRO_VERSION))
LIBRETRO_YABASANSHIRO_LICENSE = GPLv2

define LIBRETRO_YABASANSHIRO_BUILD_CMDS
	CFLAGS="$(TARGET_CFLAGS)" CXXFLAGS="$(TARGET_CXXFLAGS)" \
         $(MAKE) CXX="$(TARGET_CXX)" \
         CC="$(TARGET_CC)" \
         LD="$(TARGET_LD)" \
         RANLIB="$(TARGET_RANLIB)" \
         AR="$(TARGET_AR)" \
         -C $(@D)/yabause/src/libretro -f Makefile platform="$(LIBRETRO_PLATFORM)"
endef

define LIBRETRO_YABASANSHIRO_INSTALL_TARGET_CMDS
	$(INSTALL) -D $(@D)/yabause/src/libretro/yabasanshiro_libretro.so \
		$(TARGET_DIR)/usr/lib/libretro/yabasanshiro_libretro.so
endef

$(eval $(generic-package))
