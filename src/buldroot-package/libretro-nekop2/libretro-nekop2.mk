################################################################################
#
# NEKOP2
#
################################################################################
# Version.: Commits on Jan 10, 2021
LIBRETRO_NEKOP2_VERSION = cc25d911e2246a2377e02290a4a2fc344bb03bc2
LIBRETRO_NEKOP2_SITE = $(call github,libretro,libretro-meowPC98,$(LIBRETRO_NEKOP2_VERSION))
LIBRETRO_NEKOP2_LICENSE = GPLv3

define LIBRETRO_NEKOP2_BUILD_CMDS
	$(TARGET_CONFIGURE_OPTS) $(MAKE) CXX="$(TARGET_CXX)" CC="$(TARGET_CC)" -C $(@D)/libretro -f Makefile.libretro target="libretro" platform=unix
endef

define LIBRETRO_NEKOP2_INSTALL_TARGET_CMDS
	$(INSTALL) -D $(@D)/libretro/nekop2_libretro.so \
		$(TARGET_DIR)/usr/lib/libretro/nekop2_libretro.so
endef

$(eval $(generic-package))
