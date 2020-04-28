################################################################################
#
# LIBRETRO_SMSPLUS_GX
#
################################################################################
# Version.: Commits on Apr 20, 2020
LIBRETRO_SMSPLUS_GX_VERSION = a656bc26c3178dfda4ae9e05e18496ed93788f7b
LIBRETRO_SMSPLUS_GX_SITE = $(call github,libretro,smsplus-gx,$(LIBRETRO_SMSPLUS_GX_VERSION))
LIBRETRO_SMSPLUS_GX_LICENSE = Non-commercial

LIBRETRO_SMSPLUS_GX_PLATFORM = $(LIBRETRO_PLATFORM)

define LIBRETRO_SMSPLUS_GX_BUILD_CMDS
	CFLAGS="$(TARGET_CFLAGS)" CXXFLAGS="$(TARGET_CXXFLAGS)" \
    $(MAKE) CXX="$(TARGET_CXX)" CC="$(TARGET_CC)" \
    -C $(@D) -f Makefile.libretro platform="$(LIBRETRO_SMSPLUS_GX_PLATFORM)"
endef

define LIBRETRO_SMSPLUS_GX_INSTALL_TARGET_CMDS
	$(INSTALL) -D $(@D)/smsplus_libretro.so \
		$(TARGET_DIR)/usr/lib/libretro/smsplus_libretro.so
endef

$(eval $(generic-package))
