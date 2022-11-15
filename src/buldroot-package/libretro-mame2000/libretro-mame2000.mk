################################################################################
#
# MAME2000
#
################################################################################
# Version.: Commits on Feb 21, 2021
LIBRETRO_MAME2000_VERSION = a027d41d33a1e7547a568a83ab5bc9024aa15a97
LIBRETRO_MAME2000_SITE = $(call github,libretro,mame2000-libretro,$(LIBRETRO_MAME2000_VERSION))
LIBRETRO_MAME2000_LICENSE = MAME

ifeq ($(BR2_x86_64),y)
	LIBRETRO_MAME2000_EXTRA_ARGS += PTR64=1 ARM=0 LCPU=x86_64
endif

define LIBRETRO_MAME2000_BUILD_CMDS
	mkdir -p $(@D)/obj/mame/cpu/ccpu
	$(TARGET_CONFIGURE_OPTS) $(MAKE) CXX="$(TARGET_CXX)" CC="$(TARGET_CC)" LD="$(TARGET_CC)" -C $(@D)/ -f Makefile platform="$(LIBRETRO_PLATFORM)" $(LIBRETRO_MAME2000_EXTRA_ARGS)
endef

define LIBRETRO_MAME2000_INSTALL_TARGET_CMDS
	$(INSTALL) -D $(@D)/mame2000_libretro.so \
		$(TARGET_DIR)/usr/lib/libretro/mame037_libretro.so

	# Bios
    # Need to think of another way to use these files.
    # They take up a lot of space on tmpfs.
	mkdir -p $(TARGET_DIR)/usr/share/batocera/datainit/bios/mame2000/samples
	$(INSTALL) -D $(@D)/metadata/* \
		$(TARGET_DIR)/usr/share/batocera/datainit/bios/mame2000
endef

$(eval $(generic-package))
