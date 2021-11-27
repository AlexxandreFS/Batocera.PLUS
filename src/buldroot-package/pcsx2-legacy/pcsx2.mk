################################################################################
#
# PCSX2
#
################################################################################

### Batocera.PLUS Start
# Commits on Apr 10, 2021
PCSX2_VERSION = 87daea8a06ec2197443548ed49e27c6404a2cdb2
### Batocera.PLUS Stop

PCSX2_SITE = https://github.com/pcsx2/pcsx2.git
PCSX2_LICENSE = GPLv2 GPLv3 LGPLv2.1 LGPLv3
PCSX2_DEPENDENCIES = xserver_xorg-server alsa-lib freetype zlib libpng wxwidgets libaio portaudio libsoundtouch sdl2 libpcap yaml-cpp libgtk3 libsamplerate fmt

PCSX2_SITE_METHOD = git
PCSX2_GIT_SUBMODULES = YES

PCSX2_CONF_OPTS += -DCMAKE_BUILD_TYPE=Release
PCSX2_CONF_OPTS += -DXDG_STD=TRUE
PCSX2_CONF_OPTS += -DSDL2_API=TRUE
PCSX2_CONF_OPTS += -DDISABLE_PCSX2_WRAPPER=1
PCSX2_CONF_OPTS += -DPACKAGE_MODE=FALSE
PCSX2_CONF_OPTS += -DwxWidgets_CONFIG_EXECUTABLE="$(STAGING_DIR)/usr/bin/wx-config"
PCSX2_CONF_OPTS += -DPCSX2_TARGET_ARCHITECTURES=x86_64
PCSX2_CONF_OPTS += -DENABLE_TESTS=OFF
PCSX2_CONF_OPTS += -DUSE_SYSTEM_YAML=ON
PCSX2_CONF_OPTS += -DEXTRA_PLUGINS=TRUE
#PCSX2_CONF_OPTS += -DwxUSE_UNICODE=0
#PCSX2_CONF_OPTS += -DwxUSE_UNICODE_UTF8=0
PCSX2_CONF_OPTS += -DBUILD_SHARED_LIBS=ON
PCSX2_CONF_OPTS += -DDISABLE_ADVANCE_SIMD=ON
PCSX2_CONF_OPTS += -DUSE_VTUNE=OFF

### Batocera.PLUS Start
#PCSX2_CONF_OPTS += -DARCH_FLAG="-mfxsr -O3 -march=native -ffast-math -pipe"
### Batocera.PLUS Stop

# https://github.com/PCSX2/pcsx2/blob/51ceec74a351bd25a1066ec2c02c2aa3f8c813f4/cmake/BuildParameters.cmake#L215
# PCSX2_CONF_OPTS += -DARCH_FLAG="-msse -msse2 -mfxsr -mxsave -march=x86_64"


### Batocera.PLUS Start
define PCSX2_INSTALL_TARGET_CMDS
	mkdir -p                                $(TARGET_DIR)/opt/Pcsx2-legacy/plugins
	cp -pr $(@D)/plugins/GSdx/libGSdx*      $(TARGET_DIR)/opt/Pcsx2-legacy/plugins
	cp -pr $(@D)/bin/*                      $(TARGET_DIR)/opt/Pcsx2-legacy
	$(INSTALL) -m 0755 -D $(@D)/pcsx2/PCSX2 $(TARGET_DIR)/opt/Pcsx2-legacy/PCSX2
endef
### Batocera.PLUS Stop


$(eval $(cmake-package))
