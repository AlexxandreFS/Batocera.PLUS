################################################################################
#
# CROCODS
#
################################################################################
# Version.: Commits on Jan 7, 2021
LIBRETRO_CROCODS_VERSION = 922368cef684c691f51baf8b8338721497dbfef8
LIBRETRO_CROCODS_SITE = $(call github,libretro,libretro-crocods,$(LIBRETRO_CROCODS_VERSION))
LIBRETRO_CROCODS_LICENSE = MIT

define LIBRETRO_CROCODS_BUILD_CMDS
	CFLAGS="$(TARGET_CFLAGS)" CXXFLAGS="$(TARGET_CXXFLAGS)" \
    $(MAKE) -C $(@D) -f Makefile \
    platform="unix" \
    CXX="$(TARGET_CXX)" \
    CC="$(TARGET_CC)" \
    LD="$(TARGET_CXX)" \
    RANLIB="$(TARGET_RANLIB)" \
    AR="$(TARGET_AR)"
endef

define LIBRETRO_CROCODS_INSTALL_TARGET_CMDS
	$(INSTALL) -D $(@D)/crocods_libretro.so \
		$(TARGET_DIR)/usr/lib/libretro/crocods_libretro.so
endef

$(eval $(generic-package))
