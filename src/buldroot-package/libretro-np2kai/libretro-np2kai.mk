################################################################################
#
# LIBRETRO NP2KAI
#
################################################################################
# Version.: Commits on Feb 11, 2021
LIBRETRO_NP2KAI_VERSION = 3e8fedc7c1c6f68faa26589187512474a766ee9e
LIBRETRO_NP2KAI_SITE = https://github.com/AZO234/NP2kai
LIBRETRO_NP2KAI_SITE_METHOD=git
LIBRETRO_NP2KAI_GIT_SUBMODULES=YES
LIBRETRO_NP2KAI_LICENSE = MIT

define LIBRETRO_NP2KAI_BUILD_CMDS

    ln -s $(DL_DIR)/libretro-np2kai/git/.git $(@D)

	CFLAGS="$(TARGET_CFLAGS)" \
	CXXFLAGS="$(TARGET_CXXFLAGS)" \
	LDFLAGS="$(TARGET_LDFLAGS)" \
	$(MAKE) CXX="$(TARGET_CXX)" \
            CC="$(TARGET_CC)" \
            platform="$(LIBRETRO_PLATFORM)" \
           -C $(@D)/sdl -f Makefile.libretro
endef

define LIBRETRO_NP2KAI_INSTALL_TARGET_CMDS
	$(INSTALL) -D $(@D)/sdl/np2kai_libretro.so \
		$(TARGET_DIR)/usr/lib/libretro/np2kai_libretro.so
endef

$(eval $(generic-package))

