################################################################################
#
# OBS_STUDIO
#
################################################################################
# Version.: Commits on May 2, 2021
OBS_STUDIO_VERSION = 091bdb9832513803e6390d4e06924422f01b23b4
OBS_STUDIO_SITE = https://github.com/obsproject/obs-studio.git
OBS_STUDIO_SITE_METHOD=git
OBS_STUDIO_GIT_SUBMODULES=YES
OBS_STUDIO_LICENSE = GPLv2
OBS_STUDIO_SUPPORTS_IN_SOURCE_BUILD = NO
OBS_STUDIO_DEPENDENCIES = qt5base qt5svg qt5x11extras libcurl speexdsp mbedtls jack2 luajit libv4l fdk-aac jansson host-swig vlc

OBS_STUDIO_CONF_OPTS += -DCMAKE_BUILD_TYPE=Release
OBS_STUDIO_CONF_OPTS += -DOBS_VERSION_OVERRIDE=27.0RC3-Batocera.PLUS
OBS_STUDIO_CONF_OPTS += -DCMAKE_INSTALL_PREFIX="/opt/Obs-Studio"
OBS_STUDIO_CONF_OPTS += -DUNIX_STRUCTURE=0
OBS_STUDIO_CONF_OPTS += -DTHREADS_PTHREAD_ARG=ON
OBS_STUDIO_CONF_OPTS += -DDISABLE_PULSEAUDIO=ON
OBS_STUDIO_CONF_OPTS += -DENABLE_WAYLAND=OFF
OBS_STUDIO_CONF_OPTS += -DENABLE_PIPEWIRE=OFF

OBS_STUDIO_CONF_OPTS += -DBUILD_BROWSER=OFF
#OBS_STUDIO_DEPENDENCIES += cef
#OBS_STUDIO_CONF_OPTS += -DCEF_ROOT_DIR="../../cef-4280"

OBS_STUDIO_CONF_ENV += LDFLAGS=-lpthread

$(eval $(cmake-package))

