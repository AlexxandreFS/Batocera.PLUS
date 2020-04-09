################################################################################
#
# MAME2016
#
################################################################################
# Version.: Commits on Feb 7, 2020
LIBRETRO_MAME2016_VERSION = 02987af9b81a9c3294af8fb9d5a34f9826a2cf4d
LIBRETRO_MAME2016_SITE = $(call github,libretro,mame2016-libretro,$(LIBRETRO_MAME2016_VERSION))
LIBRETRO_MAME2016_LICENSE="MAME"

# x86
ifeq ($(BR2_x86_i586),y)
	LIBRETRO_MAME2016_PLATFORM = PTR64=0
endif

# x86_64
ifeq ($(BR2_x86_64),y)
	LIBRETRO_MAME2016_PLATFORM = PTR64=1
endif

define LIBRETRO_MAME2016_BUILD_CMDS
        mkdir -p "$(@D)/3rdparty/genie/build/gmake.linux/obj/Release/src/host"
	mkdir -p "$(@D)/build/gmake/libretro/obj/x64/libretro/src/osd/retro"
	CFLAGS="$(TARGET_CFLAGS)" CXXFLAGS="$(TARGET_CXXFLAGS)" \
        $(MAKE) CXX="$(TARGET_CXX)" CC="$(TARGET_CC)" LD="$(TARGET_LD)" RANLIB="$(TARGET_RANLIB)" AR="$(TARGET_AR)" -C $(@D)/ -f Makefile.libretro $(LIBRETRO_MAME2016_PLATFORM) platform="$(LIBRETRO_PLATFORM)"
endef

define LIBRETRO_MAME2016_INSTALL_TARGET_CMDS
	$(INSTALL) -D $(@D)/mame2016_libretro.so \
		$(TARGET_DIR)/usr/lib/libretro/mame0174_libretro.so
endef

$(eval $(generic-package))
