################################################################################
#
# JGMENU
#
################################################################################
JGMENU_VERSION = b8adff9af4d825c499ef050c700e056f6a7bddb9
JGMENU_SITE = $(call github,johanmalm,jgmenu,$(JGMENU_VERSION))
JGMENU_DEPENDENCIES = host-libxml2

define JGMENU_CONFIGURE_CMDS
	cd $(@D); PATH="$(HOST_DIR)/bin:$$PATH" ./configure --with-gtktheme --with-pmenu --prefix=$(TARGET_DIR)/usr
endef

define JGMENU_BUILD_CMDS
	$(TARGET_CONFIGURE_OPTS) $(MAKE) -C  $(@D)
endef

define JGMENU_INSTALL_TARGET_CMDS
	$(TARGET_CONFIGURE_OPTS) $(MAKE) -C  $(@D) install
	$(SED) "s|$(TARGET_DIR)||g" $(TARGET_DIR)/usr/bin/jgmenu_run
endef

$(eval $(generic-package))
