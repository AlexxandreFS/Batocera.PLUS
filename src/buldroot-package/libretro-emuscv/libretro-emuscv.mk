################################################################################
#
# LIBRETRO_EMUSCV
#
################################################################################
# Version.: Commits on Jan 2, 2021
LIBRETRO_EMUSCV_VERSION = 8821c14035b15473e658109ceb8afe9831d15f4e
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

