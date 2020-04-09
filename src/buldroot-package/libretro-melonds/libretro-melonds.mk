################################################################################
#
# LIBRETRO MELONDS
#
################################################################################
# Version.: Commits on Sep 12, 2019
LIBRETRO_MELONDS_VERSION = 42c1acd5c47dcda17288dcb64ea4adb8e13b8732
LIBRETRO_MELONDS_SITE = $(call github,libretro,melonds,$(LIBRETRO_MELONDS_VERSION))
LIBRETRO_MELONDS_LICENSE = GPLv3

define LIBRETRO_MELONDS_BUILD_CMDS
	CFLAGS="$(TARGET_CFLAGS)" \
	CXXFLAGS="$(TARGET_CXXFLAGS)" \
	LDFLAGS="$(TARGET_LDFLAGS)" \
	$(MAKE) CXX="$(TARGET_CXX)" \
            CC="$(TARGET_CC)" \
            platform="$(LIBRETRO_PLATFORM)" \
           -C $(@D)/ -f Makefile
endef

define LIBRETRO_MELONDS_INSTALL_TARGET_CMDS
	$(INSTALL) -D $(@D)/melonds_libretro.so \
		$(TARGET_DIR)/usr/lib/libretro/melonds_libretro.so
endef

$(eval $(generic-package))

