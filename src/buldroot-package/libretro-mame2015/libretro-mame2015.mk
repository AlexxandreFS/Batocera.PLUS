################################################################################
#
# MAME2015
#
################################################################################
# Version.: Commits on Dec 21, 2020
LIBRETRO_MAME2015_VERSION = ef41361dc9c88172617f7bbf6cd0ead4516a3c3f
LIBRETRO_MAME2015_SITE = $(call github,libretro,mame2015-libretro,$(LIBRETRO_MAME2015_VERSION))
LIBRETRO_MAME2015_LICENSE="MAME"

#LIBRETRO_MAME2015_EXTRA_ARGS = VRENDER=soft emulator

ifeq ($(BR2_x86_64),y)
	LIBRETRO_MAME2015_EXTRA_ARGS += PTR64=1 ARM_ENABLED=0 LCPU=x86_64
endif

define LIBRETRO_MAME2015_BUILD_CMDS
	#mkdir -p $(@D)/obj/mame/cpu/ccpu
	$(TARGET_CONFIGURE_OPTS) $(MAKE) CXX="$(TARGET_CXX)" CC="$(TARGET_CC)" LD="$(TARGET_CC)" -C $(@D)/ -f Makefile platform="$(LIBRETRO_PLATFORM)" $(LIBRETRO_MAME2015_EXTRA_ARGS)
endef

define LIBRETRO_MAME2015_INSTALL_TARGET_CMDS
	$(INSTALL) -D $(@D)/mame2015_libretro.so \
		$(TARGET_DIR)/usr/lib/libretro/mame0160_libretro.so

	# Bios
    # Need to think of another way to use these files.
    # They take up a lot of space on tmpfs.
	mkdir -p $(TARGET_DIR)/usr/share/batocera/datainit/bios/mame2015/samples
	$(INSTALL) -D $(@D)/metadata/* \
		$(TARGET_DIR)/usr/share/batocera/datainit/bios/mame2015
endef

$(eval $(generic-package))
