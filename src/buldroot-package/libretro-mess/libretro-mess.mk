##########################################################™™######################
#
# LIBRETRO MESS
#
################################################################################
# Version: Commits on Apr 1, 2020 
LIBRETRO_MESS_VERSION = d3d9afd0b59d1ae7afa8e14404c100394243137c
LIBRETRO_MESS_SITE = $(call github,libretro,mame,$(LIBRETRO_MESS_VERSION))
LIBRETRO_MESS_LICENSE = MAME

LIBRETRO_MESS_EXTRA_ARGS += PTR64=1 LIBRETRO_CPU=x86_64 PLATFORM=x86_64

define LIBRETRO_MESS_BUILD_CMDS
	# create some dirs while with parallelism, sometimes it fails because this directory is missing
	mkdir -p $(@D)/build/libretro/obj/x64/libretro/src/osd/libretro/libretro-internal

	$(MAKE) -C $(@D)/ \
        OPENMP=1 \
        REGENIE=0 \
        VERBOSE=0 \
        NOWERROR=1 \
        PYTHON_EXECUTABLE=python2 \
		CONFIG=libretro \
        LIBRETRO_OS="unix" \
        ARCH="" PROJECT="" \
        ARCHOPTS="$(LIBRETRO_MAME_ARCHOPTS)" \
		DISTRO="debian-stable" \
        OVERRIDE_CC="$(TARGET_CC)" \
        OVERRIDE_CXX="$(TARGET_CXX)" \
		OVERRIDE_LD="$(TARGET_LD)" \
        RANLIB="$(TARGET_RANLIB)" \
        AR="$(TARGET_AR)" \
		$(LIBRETRO_MAME_EXTRA_ARGS) \
        CROSS_BUILD=1 \
        TARGET="mame" \
        SUBTARGET="mess" \
        RETRO=1 \
		OSD="retro" \
        DEBUG=0
endef

define LIBRETRO_MESS_INSTALL_TARGET_CMDS
	$(INSTALL) -D $(@D)/mess_libretro.so \
		$(TARGET_DIR)/usr/lib/libretro/mess_libretro.so
endef

$(eval $(generic-package))
