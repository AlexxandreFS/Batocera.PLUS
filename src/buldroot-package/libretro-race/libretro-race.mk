################################################################################
#
# LIBRETRO RACE
#
################################################################################
# Version.: Commits on Mar 4, 2021
LIBRETRO_RACE_VERSION = f2cec67d9bb4ae7e67f6a3127c7b81fd2178a0e8
LIBRETRO_RACE_SITE = $(call github,libretro,RACE,$(LIBRETRO_RACE_VERSION))
LIBRETRO_MELONDS_LICENSE = GPL

define LIBRETRO_RACE_BUILD_CMDS
	CFLAGS="$(TARGET_CFLAGS)" \
	CXXFLAGS="$(TARGET_CXXFLAGS)" \
	LDFLAGS="$(TARGET_LDFLAGS)" \
	$(MAKE) CXX="$(TARGET_CXX)" \
            CC="$(TARGET_CC)" \
            platform="$(LIBRETRO_PLATFORM)" \
           -C $(@D)/ -f Makefile
endef

define LIBRETRO_RACE_INSTALL_TARGET_CMDS
	$(INSTALL) -D $(@D)/race_libretro.so \
		$(TARGET_DIR)/usr/lib/libretro/race_libretro.so
endef

$(eval $(generic-package))

