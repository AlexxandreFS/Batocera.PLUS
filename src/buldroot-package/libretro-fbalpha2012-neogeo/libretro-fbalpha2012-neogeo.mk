################################################################################
#
# FBA_NEOGEO
#
################################################################################
# Version.: Commits on Jan 9, 2021
LIBRETRO_FBALPHA2012_NEOGEO_VERSION = ac3f5b204166df0d1da482c52f3c2f449623ffcf
LIBRETRO_FBALPHA2012_NEOGEO_SITE = $(call github,libretro,fbalpha2012_neogeo,$(LIBRETRO_FBALPHA2012_NEOGEO_VERSION))
LIBRETRO_FBALPHA2012_NEOGEO_LICENSE = Non-commercial

define LIBRETRO_FBALPHA2012_NEOGEO_BUILD_CMDS
	$(TARGET_CONFIGURE_OPTS) $(MAKE) -C $(@D)/ -f makefile.libretro
endef

define LIBRETRO_FBALPHA2012_NEOGEO_INSTALL_TARGET_CMDS
	$(INSTALL) -D $(@D)/fbalpha2012_neogeo_libretro.so \
		$(TARGET_DIR)/usr/lib/libretro/fbalpha2012_neogeo_libretro.so
endef

$(eval $(generic-package))
