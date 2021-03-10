################################################################################
#
# LIBRETRO PLAY
#
################################################################################

# Version.: Commits on Mar 8, 2021
LIBRETRO_PLAY_VERSION = 88f26b01d78e51ea7a6e61fa795461fd706ff4e3
LIBRETRO_PLAY_SITE = https://github.com/jpd002/Play-.git
LIBRETRO_PLAY_SITE_METHOD = git
LIBRETRO_PLAY_GIT_SUBMODULES = YES
LIBRETRO_PLAY_LICENSE = Play!
LIBRETRO_PLAY_DEPENDENCIES = xserver_xorg-server qt5base qt5x11extras
LIBRETRO_PLAY_SUPPORTS_IN_SOURCE_BUILD = NO

LIBRETRO_PLAY_CONF_OPTS  = -DBUILD_LIBRETRO_CORE=ON
LIBRETRO_PLAY_CONF_OPTS += -DCMAKE_BUILD_TYPE=Release
LIBRETRO_PLAY_CONF_OPTS += -DUSE_QT=OFF

define LIBRETRO_PLAY_INSTALL_TARGET_CMDS
	$(INSTALL) -D $(@D)/buildroot-build/Source/ui_libretro/play_libretro.so \
		$(TARGET_DIR)/usr/lib/libretro/play_libretro.so
endef

$(eval $(cmake-package))
