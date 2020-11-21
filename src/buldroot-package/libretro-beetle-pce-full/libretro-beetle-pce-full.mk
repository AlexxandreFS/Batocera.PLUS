################################################################################
#
# BEETLE_PCE_FULL
#
################################################################################
# Version.: Commits on Nov 10, 2020
LIBRETRO_BEETLE_PCE_FULL_VERSION = 7e834dc9831eb10a80e2a928d5c5de6a7e5fd5ef
LIBRETRO_BEETLE_PCE_FULL_SITE = $(call github,libretro,beetle-pce-libretro,$(LIBRETRO_BEETLE_PCE_FULL_VERSION))
LIBRETRO_BEETLE_PCE_FULL_LICENSE = GPLv2

define LIBRETRO_BEETLE_PCE_FULL_BUILD_CMDS
	CFLAGS="$(TARGET_CFLAGS)" CXXFLAGS="$(TARGET_CXXFLAGS)" \
	$(MAKE) CXX="$(TARGET_CXX)" CC="$(TARGET_CC)" LD="$(TARGET_CXX)" AR="$(TARGET_AR)" RANLIB="$(TARGET_RANLIB)" -C $(@D) platform="$(LIBRETRO_PLATFORM)"
endef

define LIBRETRO_BEETLE_PCE_FULL_INSTALL_TARGET_CMDS
	$(INSTALL) -D $(@D)/mednafen_pce_libretro.so \
		$(TARGET_DIR)/usr/lib/libretro/mednafen_pce_libretro.so
endef

$(eval $(generic-package))
