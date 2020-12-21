################################################################################
#
# LIBRETRO NP2KAI
#
################################################################################
# Version.: Commits on Nov 29, 2020
LIBRETRO_NP2KAI_VERSION = 1c9eb5c62f8474c9deec81aad9502701775ad993
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

################################################################################

#define LIBRETRO_NP2KAI_LINE_ENDINGS_FIXUP
#	# DOS2UNIX Makefile.libretro - patch system does not support different line endings
#	sed -i -E -e "s|\r$$||g" $(@D)/sdl2/Makefile.libretro
#endef
#LIBRETRO_NP2KAI_PRE_PATCH_HOOKS += LIBRETRO_NP2KAI_LINE_ENDINGS_FIXUP


