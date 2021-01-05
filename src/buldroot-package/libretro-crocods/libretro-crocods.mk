################################################################################
#
# CROCODS
#
################################################################################
# Version.: Commits on Jan 2, 2021
LIBRETRO_CROCODS_VERSION = e1be0baf9e359b5034baa57f1230a70bc4294700
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
