################################################################################
#
# vkd3d
#
################################################################################
# Version 1.2
VKD3D_VERSION = 56cd4a94d541707959ce7677af6d1a34739e5579
VKD3D_SITE = git://source.winehq.org/git/vkd3d

# Commit on Jun 2, 2020 (proton_5.0)
#VKD3D_VERSION = e6857939e7de69da02dfb277a0482905c133b1c3
#VKD3D_SITE = $(call github,ValveSoftware,vkd3d,$(VKD3D_VERSION))

VKD3D_LICENSE = LGPL-2.1+
VKD3D_LICENSE_FILES = COPYING.LIB LICENSE
VKD3D_DEPENDENCIES = host-bison host-flex host-wine spirv-headers host-libtool vulkan-headers vulkan-loader

VKD3D_CONF_ENV += WIDL="$(BUILD_DIR)/host-wine-$(WINE_VERSION)/tools/widl/widl"

VKD3D_CONF_OPTS = --disable-tests --with-sysroot=$(STAGING_DIR)

VKD3D_AUTORECONF = YES
VKD3D_INSTALL_STAGING = YES

$(eval $(autotools-package))
