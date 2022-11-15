################################################################################
#
# FBA
#
################################################################################
# Version.: Commits on Feb 21, 2021
LIBRETRO_FBALPHA2012_VERSION = a292dacd7249b3d8c1178d5c52c54d60f8099323
LIBRETRO_FBALPHA2012_SITE = $(call github,libretro,fbalpha2012,$(LIBRETRO_FBALPHA2012_VERSION))
LIBRETRO_FBALPHA2012_LICENSE = Non-commercial

define LIBRETRO_FBALPHA2012_BUILD_CMDS
	$(TARGET_CONFIGURE_OPTS) \
    FORMAT=libretro \
    $(MAKE) -C $(@D)/svn-current/trunk -f makefile.libretro
endef

define LIBRETRO_FBALPHA2012_INSTALL_TARGET_CMDS
	$(INSTALL) -D $(@D)/svn-current/trunk/fbalpha2012_libretro.so \
		$(TARGET_DIR)/usr/lib/libretro/fbalpha2012_libretro.so
endef

$(eval $(generic-package))
