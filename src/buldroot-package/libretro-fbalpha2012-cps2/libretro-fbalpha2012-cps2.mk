################################################################################
#
# FBA_CPS2
#
################################################################################
# Version.: Commits on Jan 9, 2021
LIBRETRO_FBALPHA2012_CPS2_VERSION = bb4545430e6992f877b0a00065ee8a6c51a137d3
LIBRETRO_FBALPHA2012_CPS2_SITE = $(call github,libretro,fbalpha2012_cps2,$(LIBRETRO_FBALPHA2012_CPS2_VERSION))
LIBRETRO_FBALPHA2012_CPS2_LICENSE = Non-commercial

define LIBRETRO_FBALPHA2012_CPS2_BUILD_CMDS
	$(TARGET_CONFIGURE_OPTS) $(MAKE) -C $(@D)/ -f makefile.libretro
endef

define LIBRETRO_FBALPHA2012_CPS2_INSTALL_TARGET_CMDS
	$(INSTALL) -D $(@D)/fbalpha2012_cps2_libretro.so \
		$(TARGET_DIR)/usr/lib/libretro/fbalpha2012_cps2_libretro.so
endef

$(eval $(generic-package))
