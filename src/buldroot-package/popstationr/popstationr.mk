################################################################################
#
# POPSTATIONR
#
################################################################################
POPSTATIONR_VERSION = ef89ca8147c856972cb139218e5885da52c4f4ed
POPSTATIONR_SITE = $(call github,pseiler,popstationr,$(POPSTATIONR_VERSION))
POPSTATIONR_DEPENDENCIES = zlib

define POPSTATIONR_BUILD_CMDS
	$(TARGET_CONFIGURE_OPTS) $(MAKE) CC="$(TARGET_CC)" -C  $(@D)
endef

define POPSTATIONR_INSTALL_TARGET_CMDS
	$(INSTALL) -m 0755 -D $(@D)/popstationr $(TARGET_DIR)/usr/bin/popstationr
endef

$(eval $(generic-package))
