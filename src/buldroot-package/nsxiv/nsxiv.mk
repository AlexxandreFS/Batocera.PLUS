################################################################################
#
# NSXIV
#
################################################################################
# Version.: Commits on Jun 11, 2022
NSXIV_VERSION = 4c6d26bef4d5e7ca9554a485751ea7306ae4b9d0
NSXIV_SITE = https://codeberg.org/nsxiv/nsxiv.git
NSXIV_SITE_METHOD = git
NSXIV_LICENSE = GPLv2
NSXIV_DEPENDENCIES = imlib2

# Precisa tivar a compilação da lib imlib2 com suporte ao X para não dar erro na
# na compilação deste pacote
# BR2_PACKAGE_IMLIB2_X veja imlib2.mk 
#
# HAVE_LIBFONTS=0 Desativa a barra de status.
#

define NSXIV_BUILD_CMDS
	$(MAKE) CXX="$(TARGET_CXX)" CC="$(TARGET_CC)" -C $(@D) HAVE_LIBEXIF=0 HAVE_LIBWEBP=0 HAVE_LIBFONTS=0
endef

define NSXIV_INSTALL_TARGET_CMDS
	$(INSTALL) -D $(@D)/nsxiv $(TARGET_DIR)/usr/bin/nsxiv
endef

$(eval $(generic-package))