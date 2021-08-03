################################################################################
#
# YABAUSE
#
################################################################################
# Version.: Commits on Jul 28, 2021
LIBRETRO_YABAUSE_VERSION = 5c2038a2baf906dfaba01ad4da219ca74d613e9f
LIBRETRO_YABAUSE_SITE = $(call github,libretro,yabause,$(LIBRETRO_YABAUSE_VERSION))
LIBRETRO_YABAUSE_LICENSE = GPLv2

define LIBRETRO_YABAUSE_BUILD_CMDS
	CFLAGS="$(TARGET_CFLAGS)" CXXFLAGS="$(TARGET_CXXFLAGS)" \
        $(MAKE) CXX="$(TARGET_CXX)" CC="$(TARGET_CC)" LD="$(TARGET_CXX)" RANLIB="$(TARGET_RANLIB)" AR="$(TARGET_AR)" -C $(@D)/yabause/src/libretro -f Makefile platform="$(LIBRETRO_PLATFORM)"
endef

define LIBRETRO_YABAUSE_INSTALL_TARGET_CMDS
	$(INSTALL) -D $(@D)/yabause/src/libretro/yabause_libretro.so \
		$(TARGET_DIR)/usr/lib/libretro/yabause_libretro.so
endef

$(eval $(generic-package))
