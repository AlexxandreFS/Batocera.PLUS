################################################################################
#
# BSNES
#
################################################################################
# Version.: Commits on Nov 12, 2020
# Batocera.PLUS Start
LIBRETRO_BSNES_VERSION = 67d8586720c114cfbd44ac6c8eeb3f00492184ab
LIBRETRO_BSNES_SITE = $(call github,bsnes-emu,bsnes,$(LIBRETRO_BSNES_VERSION))
LIBRETRO_BSNES_LICENSE = GPLv3
# Batocera.PLUS End

define LIBRETRO_BSNES_BUILD_CMDS
	$(TARGET_CONFIGURE_OPTS) $(MAKE) CXX="$(TARGET_CXX)" CC="$(TARGET_CC)" -C $(@D)/bsnes -f GNUmakefile target="libretro" platform=linux local=false
endef

define LIBRETRO_BSNES_INSTALL_TARGET_CMDS
	$(INSTALL) -D $(@D)/bsnes/out/bsnes_libretro.so \
		$(TARGET_DIR)/usr/lib/libretro/bsnes_libretro.so
endef

$(eval $(generic-package))
