################################################################################
#
# LIBRETRO_EASYRPG_PLAYER
#
################################################################################
# Version.: Commits on Dec 23, 2020
LIBRETRO_EASYRPG_PLAYER_VERSION = 7767965ad25f898fbfe8afeec75802ffca8fb317
LIBRETRO_EASYRPG_PLAYER_SITE = https://github.com/EasyRPG/Player.git
LIBRETRO_EASYRPG_PLAYER_SITE_METHOD = git
LIBRETRO_EASYRPG_PLAYER_GIT_SUBMODULES=y
LIBRETRO_EASYRPG_PLAYER_LICENSE = MIT
LIBRETRO_EASYRPG_PLAYER_DEPENDENCIES = libretro-easyrpg-liblcf

LIBRETRO_EASYRPG_PLAYER_CONF_OPTS  = -DPLAYER_TARGET_PLATFORM=libretro
LIBRETRO_EASYRPG_PLAYER_CONF_OPTS += -DCMAKE_BUILD_TYPE=Release
LIBRETRO_EASYRPG_PLAYER_CONF_OPTS += -DBUILD_SHARED_LIBS=ON
LIBRETRO_EASYRPG_PLAYER_CONF_OPTS += -DCMAKE_POSITION_INDEPENDENT_CODE=ON

define LIBRETRO_EASYRPG_PLAYER_INSTALL_TARGET_CMDS
	$(INSTALL) -D $(@D)/easyrpg_libretro.so \
		$(TARGET_DIR)/usr/lib/libretro/easyrpg_libretro.so
endef

$(eval $(cmake-package))
