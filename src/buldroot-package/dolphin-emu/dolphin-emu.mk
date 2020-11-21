################################################################################
#
# DOLPHIN EMU
#
################################################################################
# Version: Commits on Nov 9, 2020
# Dolphin
DOLPHIN_EMU_VERSION = 43e2f0e88f80686c2b76dcba4241a7be64e7bf55
DOLPHIN_EMU_SITE = $(call github,dolphin-emu,dolphin,$(DOLPHIN_EMU_VERSION))

# Version: Commits on Oct 26, 2020
# Ishiiruka
#DOLPHIN_EMU_VERSION = abaa23cadcccccb1ac23d1169a6d428db7b9b3f4
#DOLPHIN_EMU_SITE = $(call github,Tinob,Ishiiruka,$(DOLPHIN_EMU_VERSION))
#DOLPHIN_EMU_DEPENDENCIES += wxwidgets

DOLPHIN_EMU_LICENSE = GPLv2+
DOLPHIN_EMU_DEPENDENCIES += libevdev ffmpeg zlib libpng lzo libusb libcurl bluez5_utils hidapi xz host-xz libenet bzip2
DOLPHIN_EMU_SUPPORTS_IN_SOURCE_BUILD = NO

ifeq ($(BR2_PACKAGE_BATOCERA_TARGET_X86_64),y)
DOLPHIN_EMU_DEPENDENCIES += xserver_xorg-server qt5base
endif
ifeq ($(BR2_PACKAGE_BATOCERA_TARGET_ODROIDN2)$(BR2_PACKAGE_BATOCERA_TARGET_VIM3),y)
DOLPHIN_EMU_DEPENDENCIES += libdrm
endif

DOLPHIN_EMU_CONF_OPTS  = -DTHREADS_PTHREAD_ARG=ON
DOLPHIN_EMU_CONF_OPTS += -DUSE_DISCORD_PRESENCE=OFF
DOLPHIN_EMU_CONF_OPTS += -DBUILD_SHARED_LIBS=OFF
DOLPHIN_EMU_CONF_OPTS += -DENABLE_EGL=ON
DOLPHIN_EMU_CONF_OPTS += -DENABLE_PULSEAUDIO=OFF
DOLPHIN_EMU_CONF_OPTS += -DUSE_SHARED_ENET=ON
DOLPHIN_EMU_CONF_OPTS += -DDISTRIBUTOR='Batocera.PLUS'

ifeq ($(BR2_PACKAGE_BATOCERA_TARGET_ODROIDN2)$(BR2_PACKAGE_BATOCERA_TARGET_VIM3),y)
DOLPHIN_EMU_CONF_OPTS += -DENABLE_QT=OFF
DOLPHIN_EMU_CONF_OPTS += -DENABLE_LTO=ON
endif

$(eval $(cmake-package))
