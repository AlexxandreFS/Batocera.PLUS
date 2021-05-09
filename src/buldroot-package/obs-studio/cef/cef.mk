################################################################################
#
# CEF
#
################################################################################

CEF_VERSION = 4280
CEF_SOURCE = cef_binary_$(CEF_VERSION)_linux64.tar.bz2
CEF_SITE = https://cdn-fastly.obsproject.com/downloads
CEF_LICENSE = GPLv2
CEF_CONF_OPTS += -DCMAKE_BUILD_TYPE=Release

define CEF_INSTALL_TARGET_CMDS
    echo
endef

$(eval $(cmake-package))

