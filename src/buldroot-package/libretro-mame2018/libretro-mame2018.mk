##########################################################™™######################
#
# MAME2018
#
################################################################################
# Version: Commits on Jul 8, 2018 (0.199)
LIBRETRO_MAME2018_VERSION = 2339ff121bcba95c354ae353f9d07e1b8b892dba
LIBRETRO_MAME2018_SITE = $(call github,Zoltan45,mame-mkp,$(LIBRETRO_MAME2018_VERSION))
LIBRETRO_MAME2018_LICENSE = MAME
# install in staging for debugging (gdb)
LIBRETRO_MAME2018_INSTALL_STAGING=YES

ifeq ($(BR2_x86_64),y)
	LIBRETRO_MAME2018_EXTRA_ARGS += PTR64=1 LIBRETRO_CPU=x86_64 PLATFORM=x86_64
endif

ifeq ($(BR2_i386),y)
	LIBRETRO_MAME2018_EXTRA_ARGS += PTR64=0 LIBRETRO_CPU=x86 PLATFORM=x86
endif

ifeq ($(BR2_arm),y) 
	LIBRETRO_MAME2018_EXTRA_ARGS += PTR64=0 LIBRETRO_CPU=arm PLATFORM=arm
	# workaround for asmjit broken build system (arm backend is not public)
	LIBRETRO_MAME2018_ARCHOPTS += -D__arm__ -DASMJIT_BUILD_X86
endif

ifeq ($(BR2_aarch64),y)
	LIBRETRO_MAME2018_EXTRA_ARGS += PTR64=1 LIBRETRO_CPU= PLATFORM=arm64
	# workaround for asmjit broken build system (arm backend is not public)
	LIBRETRO_MAME2018_ARCHOPTS += -D__aarch64__ -DASMJIT_BUILD_X86
endif

ifeq ($(BR2_ENABLE_DEBUG),y)
	LIBRETRO_MAME2018_EXTRA_ARGS += SYMBOLS=1 SYMLEVEL=2 OPTIMIZE=0
endif

define LIBRETRO_MAME2018_BUILD_CMDS
	# create some dirs while with parallelism, sometimes it fails because this directory is missing
	mkdir -p $(@D)/build/libretro/obj/x64/libretro/src/osd/libretro/libretro-internal

	$(MAKE) -j3 -C $(@D)/ -f Makefile.libretro OPENMP=1 REGENIE=1 VERBOSE=1 NOWERROR=1 PYTHON_EXECUTABLE=python2            \
		CONFIG=libretro LIBRETRO_OS="unix" ARCH="" PROJECT="" ARCHOPTS="$(LIBRETRO_MAME2018_ARCHOPTS)" \
		DISTRO="debian-stable" OVERRIDE_CC="$(TARGET_CC)" OVERRIDE_CXX="$(TARGET_CXX)"             \
		OVERRIDE_LD="$(TARGET_LD)" RANLIB="$(TARGET_RANLIB)" AR="$(TARGET_AR)"                     \
		$(LIBRETRO_MAME2018_EXTRA_ARGS) CROSS_BUILD=1 TARGET="mame" SUBTARGET="mame" RETRO=1         \
		OSD="sdl" DEBUG=0
endef

define LIBRETRO_MAME2018_INSTALL_TARGET_CMDS
	$(INSTALL) -D $(@D)/mame_libretro.so \
		$(TARGET_DIR)/usr/lib/libretro/mame0199_libretro.so
endef

define LIBRETRO_MAME2018_INSTALL_STAGING_CMDS
	$(INSTALL) -D $(@D)/mame_libretro.so \
		$(STAGING_DIR)/usr/lib/libretro/mame0199_libretro.so
endef

$(eval $(generic-package))
