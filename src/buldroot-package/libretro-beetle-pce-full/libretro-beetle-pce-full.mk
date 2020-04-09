################################################################################
#
# BEETLE_PCE_FULL
#
################################################################################
# Version.: Commits on Mar 19, 2020 
LIBRETRO_BEETLE_PCE_FULL_VERSION = a54a259bb6f26ffca438a2e2ddda27a67d424981
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
