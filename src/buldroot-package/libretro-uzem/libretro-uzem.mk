################################################################################
#
# LIBRETRO_UZEM
#
################################################################################
# Version.: Commits on Jan 8, 2021
LIBRETRO_UZEM_VERSION = 1c4fe15dcfa821ff578f3d373162bc29bd4f90ff
LIBRETRO_UZEM_SITE = $(call github,libretro,libretro-uzem,$(LIBRETRO_UZEM_VERSION))
LIBRETRO_CROCODS_LICENSE = Unknown

define LIBRETRO_UZEM_BUILD_CMDS
		$(MAKE) CXX="$(TARGET_CXX)" CC="$(TARGET_CC)" -C $(@D) -f Makefile
endef

define LIBRETRO_UZEM_INSTALL_TARGET_CMDS
	$(INSTALL) -D $(@D)/uzem_libretro.so \
		$(TARGET_DIR)/usr/lib/libretro/uzem_libretro.so
endef

$(eval $(generic-package))
