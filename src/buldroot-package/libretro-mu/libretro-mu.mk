################################################################################
#
# LIBRETRO_MU
#
################################################################################
# Version.: Commits on Jan 2, 2021
LIBRETRO_MU_VERSION = e140a25c5b0d32682f107bc769f3ae78603a4187
LIBRETRO_MU_SITE = $(call github,libretro,Mu,$(LIBRETRO_MU_VERSION))
LIBRETRO_MU_LICENSE = Unknown

define LIBRETRO_MU_BUILD_CMDS
    CFLAGS="$(TARGET_CFLAGS)" CXXFLAGS="$(TARGET_CXXFLAGS)" \
		$(MAKE) -C $(@D)/libretroBuildSystem -f Makefile.libretro platform="linux_x86_64"
endef

define LIBRETRO_MU_INSTALL_TARGET_CMDS
	$(INSTALL) -D $(@D)/libretroBuildSystem/mu_libretro.linux_x86_64.so \
		$(TARGET_DIR)/usr/lib/libretro/mu_libretro.so
endef

$(eval $(generic-package))

