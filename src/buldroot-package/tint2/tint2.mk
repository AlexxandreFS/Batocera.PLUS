################################################################################
#
# DOLPHIN EMU
#
################################################################################
# Version: Commits on Jun 27, 2020
TINT2_VERSION = 5b3f9c4662babaff4d396618efb384a3967ae8e9
TINT2_SITE = https://gitlab.com/o9000/tint2.git
TINT2_SITE_METHOD= git
TINT2_LICENSE = GPLv2
TINT2_LICENSE_FILES = COPYING
TINT2_INSTALL_TARGET = YES
TINT2_SUPPORTS_IN_SOURCE_BUILD = NO

TINT2_DEPENDENCIES = imlib2

TINT2_CONF_OPTS  = -DENABLE_SN=OFF
TINT2_CONF_OPTS += -DENABLE_RSVG=OFF
TINT2_CONF_OPTS += -DTINT2_WITH_POST_BUILD_UNITTEST=OFF
TINT2_CONF_OPTS += -DTINT2_WITH_TESTS=OFF
TINT2_CONF_OPTS += -DTINT2_WITH_STRICT_ISO=OFF
 
$(eval $(cmake-package))
