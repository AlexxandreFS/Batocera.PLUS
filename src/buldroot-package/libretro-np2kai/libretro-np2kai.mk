################################################################################
#
# LIBRETRO NP2KAI
#
################################################################################
# Version.: Commits on Apr 1, 2020
LIBRETRO_NP2KAI_VERSION = 9f7a8168270bc5cc8b060965a0d6c21e0a1c60de
LIBRETRO_NP2KAI_SITE = $(call github,AZO234,NP2kai,$(LIBRETRO_NP2KAI_VERSION))
LIBRETRO_NP2KAI_LICENSE = MIT

define LIBRETRO_NP2KAI_BUILD_CMDS
	CFLAGS="$(TARGET_CFLAGS)" \
	CXXFLAGS="$(TARGET_CXXFLAGS)" \
	LDFLAGS="$(TARGET_LDFLAGS)" \
	$(MAKE) CXX="$(TARGET_CXX)" \
            CC="$(TARGET_CC)" \
            platform="$(LIBRETRO_PLATFORM)" \
           -C $(@D)/sdl2 -f Makefile 
endef

define LIBRETRO_NP2KAI_INSTALL_TARGET_CMDS
	$(INSTALL) -D $(@D)/sdl2/np2kai_libretro.so \
		$(TARGET_DIR)/usr/lib/libretro/np2kai_libretro.so
endef

$(eval $(generic-package))

################################################################################

#define LIBRETRO_NP2KAI_LINE_ENDINGS_FIXUP
#	# DOS2UNIX Makefile.libretro - patch system does not support different line endings
#	sed -i -E -e "s|\r$$||g" $(@D)/sdl2/Makefile.libretro
#endef
#LIBRETRO_NP2KAI_PRE_PATCH_HOOKS += LIBRETRO_NP2KAI_LINE_ENDINGS_FIXUP


