################################################################################
#
# vkbasalt
#
################################################################################
# Version: Commits from Jul 3, 2023
VKBASALT_VERSION = 0.3.2.10
VKBASALT_SOURCE = vkBasalt-$(VKBASALT_VERSION).tar.gz
VKBASALT_SITE = https://github.com/DadSchoorse/vkBasalt/releases/download/v$(VKBASALT_VERSION)
VKBASALT_DEPENDENCIES = libdrm xserver_xorg-server vulkan-headers

$(eval $(meson-package))
