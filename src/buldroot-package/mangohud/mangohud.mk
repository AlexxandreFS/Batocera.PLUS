################################################################################
#
# MangoHud
#
################################################################################
# Version: Commits from Mar 20th, 2021
MANGOHUD_VERSION = 1f41b4aac9a43f451b7ab6218a47dad674e44b64
MANGOHUD_SITE = https://github.com/flightlessmango/MangoHud.git
MANGOHUD_SITE_METHOD = git

MANGOHUD_DEPENDENCIES = libdrm xserver_xorg-server vulkan-headers

MANGOHUD_CONF_OPTS  = -Duse_system_vulkan=enabled
MANGOHUD_CONF_OPTS += -Dwith_xnvctrl=disabled
MANGOHUD_CONF_OPTS += -Dvkdatadir=$(STAGING_DIR)/usr/share 

$(eval $(meson-package))
