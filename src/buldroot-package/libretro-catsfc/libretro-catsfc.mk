################################################################################
#
# CATSFC
#
################################################################################
# Version.: Feb 14, 2021
LIBRETRO_CATSFC_VERSION = 218be8ef543fc25a603f20a2a3ee79fc7cdad611
LIBRETRO_CATSFC_SITE = $(call github,libretro,snes9x2005,$(LIBRETRO_CATSFC_VERSION))
LIBRETRO_CATSFC_LICENSE="Non-commercial"

define LIBRETRO_CATSFC_BUILD_CMDS
	CFLAGS="$(TARGET_CFLAGS)" CXXFLAGS="$(TARGET_CXXFLAGS)" $(MAKE) CXX="$(TARGET_CXX)" CC="$(TARGET_CC)" -C $(@D) platform="$(LIBRETRO_PLATFORM)"
endef

define LIBRETRO_CATSFC_INSTALL_TARGET_CMDS
	$(INSTALL) -D $(@D)/snes9x2005_libretro.so \
		$(TARGET_DIR)/usr/lib/libretro/catsfc_libretro.so
endef

$(eval $(generic-package))
