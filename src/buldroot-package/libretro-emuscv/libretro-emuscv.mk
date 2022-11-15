################################################################################
#
# LIBRETRO_EMUSCV
#
################################################################################
# Version.: Commits on Mar 4, 2021
LIBRETRO_EMUSCV_VERSION = ad6df67ea1fca6b3e6dfca951cc9d0b27e22f62a
LIBRETRO_EMUSCV_SITE = https://gitlab.com/MaaaX-EmuSCV/libretro-emuscv.git
LIBRETRO_EMUSCV_SITE_METHOD = git
LIBRETRO_EMUSCV_LICENSE = GPL3

define LIBRETRO_EMUSCV_BUILD_CMDS
	CFLAGS="$(TARGET_CFLAGS)" CXXFLAGS="$(TARGET_CXXFLAGS)" \
		$(MAKE) CXX="$(TARGET_CXX)" CC="$(TARGET_CC)" -C $(@D)/ -f Makefile.libretro platform="unix"
endef

define LIBRETRO_EMUSCV_INSTALL_TARGET_CMDS
	$(INSTALL) -D $(@D)/emuscv_libretro.so \
		$(TARGET_DIR)/usr/lib/libretro/emuscv_libretro.so
endef

$(eval $(generic-package))

