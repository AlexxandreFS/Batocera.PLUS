################################################################################
#
# QUICKNES
#
################################################################################
# Version.: Commits on Oct 19, 2020
LIBRETRO_QUICKNES_VERSION = 55d47ca526e7d8585e321b9d99cc2ac3796bd230
LIBRETRO_QUICKNES_SITE = $(call github,libretro,QuickNES_Core,$(LIBRETRO_QUICKNES_VERSION))
LIBRETRO_QUICKNES_LICENSE="LGPLv2.1+"

define LIBRETRO_QUICKNES_BUILD_CMDS
	CFLAGS="$(TARGET_CFLAGS)" CXXFLAGS="$(TARGET_CXXFLAGS)" $(MAKE) CXX="$(TARGET_CXX)" CC="$(TARGET_CC)" -C $(@D)/ -f Makefile platform="$(LIBRETRO_PLATFORM)"
endef

define LIBRETRO_QUICKNES_INSTALL_TARGET_CMDS
	$(INSTALL) -D $(@D)/quicknes_libretro.so \
		$(TARGET_DIR)/usr/lib/libretro/quicknes_libretro.so
endef

$(eval $(generic-package))
