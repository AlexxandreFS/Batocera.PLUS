################################################################################
#
# LIBRETRO_EASYRPG_LIBLCF
#
################################################################################
# Version.: Commits on Nov 9, 2020
LIBRETRO_EASYRPG_LIBLCF_VERSION = 8bdca2e87e521308c1fe6dced9eed64d2c7bf715
LIBRETRO_EASYRPG_LIBLCF_SITE = https://github.com/EasyRPG/liblcf.git
LIBRETRO_EASYRPG_LIBLCF_SITE_METHOD = git
LIBRETRO_EASYRPG_LIBLCF_GIT_SUBMODULES=y
LIBRETRO_EASYRPG_LIBLCF_INSTALL_STAGING = YES
LIBRETRO_EASYRPG_LIBLCF_EASYRPG_LICENSE = MIT
LIBRETRO_EASYRPG_LIBLCF_DEPENDENCIES = icu

LIBRETRO_EASYRPG_LIBLCF_CONF_OPTS += -DCMAKE_BUILD_TYPE=Release

$(eval $(cmake-package))
