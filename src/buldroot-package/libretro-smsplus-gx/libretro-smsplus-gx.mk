################################################################################
#
# LIBRETRO_SMSPLUS_GX
#
################################################################################
# Version.: Commits on Jan 24, 2021
LIBRETRO_SMSPLUS_GX_VERSION = 0345f1f20b0344cd6d8ad25bf7580123e3623c06
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
