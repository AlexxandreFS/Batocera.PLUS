################################################################################
#
# GENESISPLUSGX_WIDE
#
################################################################################
# Version.: Commits on Mar 9, 2021
LIBRETRO_GENESISPLUSGX_WIDE_VERSION = 767113a4a81f618f25ed8119ef1d9dc53af9a44c
LIBRETRO_GENESISPLUSGX_WIDE_SITE = $(call github,libretro,Genesis-Plus-GX-Wide,$(LIBRETRO_GENESISPLUSGX_WIDE_VERSION))
LIBRETRO_GENESISPLUSGX_WIDE_LICENSE = Non-commercial

LIBRETRO_GENESISPLUSGX_WIDE_PLATFORM = $(LIBRETRO_PLATFORM)

ifeq ($(BR2_PACKAGE_BATOCERA_TARGET_ROCKPRO64),y)
	LIBRETRO_GENESISPLUSGX_WIDE_PLATFORM += rockpro64
endif

ifeq ($(BR2_PACKAGE_BATOCERA_TARGET_ODROIDN2),y)
	LIBRETRO_GENESISPLUSGX_WIDE_PLATFORM += CortexA73_G12B
endif

define LIBRETRO_GENESISPLUSGX_WIDE_BUILD_CMDS
	$(TARGET_CONFIGURE_OPTS) $(MAKE) CXX="$(TARGET_CXX)" CC="$(TARGET_CC)" -C $(@D) -f Makefile.libretro platform="$(LIBRETRO_GENESISPLUSGX_WIDE_PLATFORM)"
endef

define LIBRETRO_GENESISPLUSGX_WIDE_INSTALL_TARGET_CMDS
	$(INSTALL) -D $(@D)/genesis_plus_gx_wide_libretro.so \
		$(TARGET_DIR)/usr/lib/libretro/genesisplusgx_wide_libretro.so
endef

$(eval $(generic-package))
