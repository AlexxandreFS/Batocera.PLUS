################################################################################
#
# BSNES
#
################################################################################
# Version.: Commits on Mar 4, 2021
# Batocera.PLUS Start
LIBRETRO_BSNES_VERSION = 73b275a7d0fadcc777e1b344093687c84d02eddd
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
