################################################################################
#
# LIBRETRO-KRONOS
#
################################################################################
# Version.: Commits on May 14, 2020
# Ultima versão
# Não precisa do patch 000-fix-cue.patch
#LIBRETRO_KRONOS_VERSION = a66f55a88b092f9aaff6814329fbd3d3c8460dc0

# Version.: Commits on Feb 22, 2020
# Versão mais antiga que funciona 100%
# Precisa do patch 000-fix-cue.patch para corrigir problemas com alguns arquivos .cue
LIBRETRO_KRONOS_VERSION = 7fe1ac0c6234180fe1bd50a897d8e49f61b6e8e6

LIBRETRO_KRONOS_VERSION = a66f55a88b092f9aaff6814329fbd3d3c8460dc0
LIBRETRO_KRONOS_SITE = $(call github,libretro,yabause,$(LIBRETRO_KRONOS_VERSION))
LIBRETRO_KRONOS_LICENSE = BSD-3-Clause

define LIBRETRO_KRONOS_BUILD_CMDS
	$(TARGET_CONFIGURE_OPTS) $(MAKE) CXX="$(TARGET_CXX)" CC="$(TARGET_CC)" \
    -C $(@D)/yabause/src/libretro -f Makefile platform="$(LIBRETRO_PLATFORM)" RTHREADS=1
endef

define LIBRETRO_KRONOS_INSTALL_TARGET_CMDS
	$(INSTALL) -D $(@D)/yabause/src/libretro/kronos_libretro.so \
		$(TARGET_DIR)/usr/lib/libretro/kronos_libretro.so
endef

$(eval $(generic-package))
