################################################################################
#
# LIBRETRO RACE
#
################################################################################
# Version.: Commits on Sep 12, 2019
LIBRETRO_RACE_VERSION = fc41e50aeff2be5c9d5c70757a2d77c4ecf13ef1
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

