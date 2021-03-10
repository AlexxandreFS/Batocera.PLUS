################################################################################
#
# FBA_CPS1
#
################################################################################
# Version.: Commits on Jan 9, 2021
LIBRETRO_FBALPHA2012_CPS1_VERSION = 358bc96fa42bc7a6c4d9f03d3ad11baeefc85e36
LIBRETRO_FBALPHA2012_CPS1_SITE = $(call github,libretro,fbalpha2012_cps1,$(LIBRETRO_FBALPHA2012_CPS1_VERSION))
LIBRETRO_FBALPHA2012_CPS1_LICENSE = Non-commercial

define LIBRETRO_FBALPHA2012_CPS1_BUILD_CMDS
	$(TARGET_CONFIGURE_OPTS) $(MAKE) -C $(@D)/ -f makefile.libretro
endef

define LIBRETRO_FBALPHA2012_CPS1_INSTALL_TARGET_CMDS
	$(INSTALL) -D $(@D)/fbalpha2012_cps1_libretro.so \
		$(TARGET_DIR)/usr/lib/libretro/fbalpha2012_cps1_libretro.so
endef

$(eval $(generic-package))
