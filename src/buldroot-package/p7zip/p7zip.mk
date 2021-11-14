################################################################################
#
# p7zip
#
################################################################################

P7ZIP_VERSION = 17.04
P7ZIP_SITE = $(call github,jinfeihan57,p7zip,v$(P7ZIP_VERSION))
P7ZIP_LICENSE = LGPL-2.1+ with unRAR restriction
P7ZIP_LICENSE_FILES = DOC/License.txt
P7ZIP_CPE_ID_VENDOR = 7-zip
P7ZIP_DEPENDENCIES = wxwidgets tiff

define P7ZIP_BUILD_CMDS
    $(TARGET_MAKE_ENV) \
    PATH="$(HOST_DIR)/x86_64-buildroot-linux-gnu/sysroot/usr/bin:$$PATH" \
    $(MAKE) CC="$(TARGET_CC)" \
            ALLFLAGS_C="$(TARGET_CFLAGS)" \
            CXX="$(TARGET_CXX)" \
            ALLFLAGS_CPP="$(TARGET_CXXFLAGS)" \
            LDFLAGS="$(TARGET_LDFLAGS)" \
            -C $(@D) 7z 7zr 7za 7zG 7zFM sfx lzham
endef

define P7ZIP_INSTALL_TARGET_CMDS
    $(foreach i, 7z 7zr 7za 7zCon.sfx 7z.so 7zG 7zFM_do_not_use Codecs/Rar.so Codecs/Lzham.so,
        $(INSTALL) -D -m 0755 $(@D)/bin/$(i) $(TARGET_DIR)/usr/lib/p7zip/$(i)
    )
    mv -f $(TARGET_DIR)/usr/lib/p7zip/7zFM_do_not_use $(TARGET_DIR)/usr/lib/p7zip/7zFM

    mkdir -p $(TARGET_DIR)/usr/bin

    $(foreach i, 7z 7zr 7za 7zG 7zFM,
        echo '#!/bin/sh'                       >  $(TARGET_DIR)/usr/bin/$(i)
        echo "exec /usr/lib/p7zip/$(i) \"$@\"" >> $(TARGET_DIR)/usr/bin/$(i)
        chmod 755                                 $(TARGET_DIR)/usr/bin/$(i)
    )

    cp -rf $(@D)/GUI/Lang   $(TARGET_DIR)/usr/lib/p7zip/Lang
    cp -rf $(@D)/DOC/MANUAL $(TARGET_DIR)/usr/lib/p7zip/help
endef

$(eval $(generic-package))
