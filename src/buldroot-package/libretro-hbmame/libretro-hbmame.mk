##########################################################™™######################
#
# HBMAME
#
################################################################################
# Version: Commits on Mar 29, 2020 (0.220)
LIBRETRO_HBMAME_VERSION = c63ab69a853440ddb5cd0d50a00e8850c12757b8
LIBRETRO_HBMAME_SITE = $(call github,libretro,hbmame-libretro,$(LIBRETRO_HBMAME_VERSION))
LIBRETRO_HBMAME_LICENSE = MAME

ifeq ($(BR2_x86_64),y)
	LIBRETRO_HBMAME_EXTRA_ARGS += PTR64=1 LIBRETRO_CPU=x86_64 PLATFORM=x86_64
endif

ifeq ($(BR2_i386),y)
	LIBRETRO_HBMAME_EXTRA_ARGS += PTR64=0 LIBRETRO_CPU=x86 PLATFORM=x86
endif

ifeq ($(BR2_arm),y)
	LIBRETRO_HBMAME_EXTRA_ARGS += PTR64=0 LIBRETRO_CPU=arm PLATFORM=arm
	LIBRETRO_HBMAME_ARCHOPTS += -D__arm__
endif

ifeq ($(BR2_ENABLE_DEBUG),y)
	LIBRETRO_HBMAME_EXTRA_ARGS += SYMBOLS=1 SYMLEVEL=2 OPTIMIZE=0
endif

define LIBRETRO_HBMAME_BUILD_CMDS
	# create some dirs while with parallelism, sometimes it fails because this directory is missing
	mkdir -p $(@D)/build/libretro/obj/x64/libretro/src/osd/libretro/libretro-internal

	$(MAKE) -C $(@D)/ -f Makefile.libretro     \
        TARGET=hbmame                          \
        CONFIG=libretro                        \
        RETRO=1                                \
        OSD="retro"                            \
        OS=linux                               \
        TARGETOS=linux                         \

        NO_USE_MIDI=0                          \
        NO_USE_PORTAUDIO=0                     \
		DEBUG=0                                \

        OPENMP=1                               \
        REGENIE=1                              \
        NOWERROR=1                             \
        VERBOSE=1                              \
        PYTHON_EXECUTABLE=python2              \

		OVERRIDE_CC="$(TARGET_CC)"             \
        OVERRIDE_CXX="$(TARGET_CXX)"           \
		OVERRIDE_LD="$(TARGET_LD)"             \
        RANLIB="$(TARGET_RANLIB)"              \
        AR="$(TARGET_AR)"                      \

		ARCHOPTS="$(LIBRETRO_HBMAME_ARCHOPTS)" \
		$(LIBRETRO_HBMAME_EXTRA_ARGS)
endef

define LIBRETRO_HBMAME_INSTALL_TARGET_CMDS
	$(INSTALL) -D $(@D)/hbmame_libretro.so \
		$(TARGET_DIR)/usr/lib/libretro/hbmame_libretro.so
endef

$(eval $(generic-package))
