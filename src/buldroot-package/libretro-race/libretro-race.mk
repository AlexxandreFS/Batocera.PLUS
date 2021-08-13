################################################################################
#
# LIBRETRO RACE
#
################################################################################
# Version.: Commits on Aug 2, 2021
LIBRETRO_RACE_VERSION = f40270b04a297880ff425bb9347c98726a02eded
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

