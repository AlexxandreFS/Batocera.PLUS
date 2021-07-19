################################################################################
#
# batocera-nvidia-driver-304
#
################################################################################
# Patch https://github.com/jorgem-seq/NVIDIA-Linux-304.137-patches
BATOCERA_NVIDIA_DRIVER_VERSION = 304.137
BATOCERA_NVIDIA_DRIVER_SUFFIX = $(if $(BR2_x86_64),_64)
BATOCERA_NVIDIA_DRIVER_SITE = http://download.nvidia.com/XFree86/Linux-x86$(BATOCERA_NVIDIA_DRIVER_SUFFIX)/$(BATOCERA_NVIDIA_DRIVER_VERSION)
BATOCERA_NVIDIA_DRIVER_SOURCE = NVIDIA-Linux-x86$(BATOCERA_NVIDIA_DRIVER_SUFFIX)-$(BATOCERA_NVIDIA_DRIVER_VERSION).run
BATOCERA_NVIDIA_DRIVER_LICENSE = NVIDIA Software License
BATOCERA_NVIDIA_DRIVER_LICENSE_FILES = LICENSE
BATOCERA_NVIDIA_DRIVER_REDISTRIBUTE = NO
#BATOCERA_NVIDIA_DRIVER_INSTALL_STAGING = YES
BATOCERA_NVIDIA_DRIVER_DEPENDENCIES = mesa3d xlib_libX11 xlib_libXext libglvnd

################################################################################

# Batocera.PLUS install dir  
INSTALL_DIR = $(TARGET_DIR)/opt/Nvidia/v340

################################################################################

define BATOCERA_NVIDIA_DRIVER_EXTRACT_CMDS
    $(SHELL) $(BATOCERA_NVIDIA_DRIVER_DL_DIR)/$(BATOCERA_NVIDIA_DRIVER_SOURCE) --extract-only --target $(@D)/tmp-extract
    chmod u+w -R $(@D)
    ln -s Makefile.kbuild $(@D)/tmp-extract/kernel/Makefile
    mv $(@D)/tmp-extract/* $(@D)/tmp-extract/.manifest $(@D)
    rm -rf $(@D)/tmp-extract
endef

################################################################################

# Build and install the kernel modules if needed
ifeq ($(BR2_PACKAGE_BATOCERA_NVIDIA_DRIVER_MODULE),y)
    BATOCERA_NVIDIA_DRIVER_MODULE_MAKE_OPTS = \
        SYSSRC="$(LINUX_DIR)" \
        SYSOUT="$(LINUX_DIR)" \
        IGNORE_CC_MISMATCH=1

    BATOCERA_NVIDIA_DRIVER_MODULE_SUBDIRS = kernel

    $(eval $(kernel-module))
endif

################################################################################

define BATOCERA_NVIDIA_DRIVER_INSTALL_TARGET_CMDS

    # 64bit libraries
    $(INSTALL) -D -m 0644 $(@D)/libGL.so.$(BATOCERA_NVIDIA_DRIVER_VERSION)                   $(INSTALL_DIR)/usr/lib/libGL.so.$(BATOCERA_NVIDIA_DRIVER_VERSION)
    ln -sf libGL.so.$(BATOCERA_NVIDIA_DRIVER_VERSION)                                        $(INSTALL_DIR)/usr/lib/libGL.so
    ln -sf libGL.so.$(BATOCERA_NVIDIA_DRIVER_VERSION)                                        $(INSTALL_DIR)/usr/lib/libGL.so.1

    $(INSTALL) -D -m 0644 $(@D)/libnvidia-glcore.so.$(BATOCERA_NVIDIA_DRIVER_VERSION)        $(INSTALL_DIR)/usr/lib/libnvidia-glcore.so.$(BATOCERA_NVIDIA_DRIVER_VERSION)
    ln -sf libnvidia-glcore.so.$(BATOCERA_NVIDIA_DRIVER_VERSION)                             $(INSTALL_DIR)/usr/lib/libnvidia-glcore.so
    ln -sf libnvidia-glcore.so.$(BATOCERA_NVIDIA_DRIVER_VERSION)                             $(INSTALL_DIR)/usr/lib/libnvidia-glcore.so.1

    $(INSTALL) -D -m 0644 $(@D)/libXvMCNVIDIA.so.$(BATOCERA_NVIDIA_DRIVER_VERSION)           $(INSTALL_DIR)/usr/lib/libXvMCNVIDIA.so.$(BATOCERA_NVIDIA_DRIVER_VERSION)
    ln -sf libXvMCNVIDIA.so.$(BATOCERA_NVIDIA_DRIVER_VERSION)                                $(INSTALL_DIR)/usr/lib/libXvMCNVIDIA.so
    ln -sf libXvMCNVIDIA.so.$(BATOCERA_NVIDIA_DRIVER_VERSION)                                $(INSTALL_DIR)/usr/lib/libXvMCNVIDIA.so.1
    ln -sf libXvMCNVIDIA.so.$(BATOCERA_NVIDIA_DRIVER_VERSION)                                $(INSTALL_DIR)/usr/lib/libXvMCNVIDIA_dynamic.so
    ln -sf libXvMCNVIDIA.so.$(BATOCERA_NVIDIA_DRIVER_VERSION)                                $(INSTALL_DIR)/usr/lib/libXvMCNVIDIA_dynamic.so.1

    $(INSTALL) -D -m 0644 $(@D)/libnvidia-ml.so.$(BATOCERA_NVIDIA_DRIVER_VERSION)            $(INSTALL_DIR)/usr/lib/libnvidia-ml.so.$(BATOCERA_NVIDIA_DRIVER_VERSION)
    ln -sf libnvidia-ml.so.$(BATOCERA_NVIDIA_DRIVER_VERSION)                                 $(INSTALL_DIR)/usr/lib/libnvidia-ml.so
    ln -sf libnvidia-ml.so.$(BATOCERA_NVIDIA_DRIVER_VERSION)                                 $(INSTALL_DIR)/usr/lib/libnvidia-ml.so.1

    $(INSTALL) -D -m 0644 $(@D)/libvdpau_nvidia.so.$(BATOCERA_NVIDIA_DRIVER_VERSION)         $(INSTALL_DIR)/usr/lib/libvdpau_nvidia.so.$(BATOCERA_NVIDIA_DRIVER_VERSION)
    ln -sf libvdpau_nvidia.so.$(BATOCERA_NVIDIA_DRIVER_VERSION)                              $(INSTALL_DIR)/usr/lib/libvdpau_nvidia.so
    ln -sf libvdpau_nvidia.so.$(BATOCERA_NVIDIA_DRIVER_VERSION)                              $(INSTALL_DIR)/usr/lib/libvdpau_nvidia.so.1

    $(INSTALL) -D -m 0644 $(@D)/libnvidia-wfb.so.$(BATOCERA_NVIDIA_DRIVER_VERSION)           $(INSTALL_DIR)/usr/lib/xorg/modules/libnvidia-wfb.so.$(BATOCERA_NVIDIA_DRIVER_VERSION)

    $(INSTALL) -D -m 0644 $(@D)/libglx.so.$(BATOCERA_NVIDIA_DRIVER_VERSION)                  $(INSTALL_DIR)/usr/lib/xorg/modules/extensions/libglx.so.$(BATOCERA_NVIDIA_DRIVER_VERSION)
    ln -sf libglx.so.$(BATOCERA_NVIDIA_DRIVER_VERSION)                                       $(INSTALL_DIR)/usr/lib/xorg/modules/extensions/libglx.so
    ln -sf libglx.so.$(BATOCERA_NVIDIA_DRIVER_VERSION)                                       $(INSTALL_DIR)/usr/lib/xorg/modules/extensions/libglx.so.1

    $(INSTALL) -D -m 0644 $(@D)/libnvidia-tls.so.$(BATOCERA_NVIDIA_DRIVER_VERSION)           $(INSTALL_DIR)/usr/lib/libnvidia-tls.so.$(BATOCERA_NVIDIA_DRIVER_VERSION)
    ln -sf libnvidia-tls.so.$(BATOCERA_NVIDIA_DRIVER_VERSION)                                $(INSTALL_DIR)/usr/lib/libnvidia-tls.so

    $(INSTALL) -D -m 0644 $(@D)/tls/libnvidia-tls.so.$(BATOCERA_NVIDIA_DRIVER_VERSION)       $(INSTALL_DIR)/usr/lib/tls/libnvidia-tls.so.$(BATOCERA_NVIDIA_DRIVER_VERSION)
    ln -sf libnvidia-tls.so.$(BATOCERA_NVIDIA_DRIVER_VERSION)                                $(INSTALL_DIR)/usr/lib/tls/libnvidia-tls.so
    ln -sf libnvidia-tls.so.$(BATOCERA_NVIDIA_DRIVER_VERSION)                                $(INSTALL_DIR)/usr/lib/tls/libnvidia-tls.so.1

    $(INSTALL) -D -m 0644 $(@D)/nvidia_drv.so                                                $(INSTALL_DIR)/usr/lib/xorg/modules/drivers/nvidia_drv.so

    # 32bit libraries
    $(INSTALL) -D -m 0644 $(@D)/32/libGL.so.$(BATOCERA_NVIDIA_DRIVER_VERSION)                $(INSTALL_DIR)/lib32/libGL.so.$(BATOCERA_NVIDIA_DRIVER_VERSION)
    ln -sf libGL.so.$(BATOCERA_NVIDIA_DRIVER_VERSION)                                        $(INSTALL_DIR)/lib32/libGL.so
    ln -sf libGL.so.$(BATOCERA_NVIDIA_DRIVER_VERSION)                                        $(INSTALL_DIR)/lib32/libGL.so.1

    $(INSTALL) -D -m 0644 $(@D)/32/libnvidia-glcore.so.$(BATOCERA_NVIDIA_DRIVER_VERSION)     $(INSTALL_DIR)/lib32/libnvidia-glcore.so.$(BATOCERA_NVIDIA_DRIVER_VERSION)
    ln -sf libnvidia-glcore.so.$(BATOCERA_NVIDIA_DRIVER_VERSION)                             $(INSTALL_DIR)/lib32/libnvidia-glcore.so

    $(INSTALL) -D -m 0644 $(@D)/32/libnvidia-ml.so.$(BATOCERA_NVIDIA_DRIVER_VERSION)         $(INSTALL_DIR)/lib32/libnvidia-ml.so.$(BATOCERA_NVIDIA_DRIVER_VERSION)
    ln -sf libnvidia-ml.so.$(BATOCERA_NVIDIA_DRIVER_VERSION)                                 $(INSTALL_DIR)/lib32/libnvidia-ml.so
    ln -sf libnvidia-ml.so.$(BATOCERA_NVIDIA_DRIVER_VERSION)                                 $(INSTALL_DIR)/lib32/libnvidia-ml.so.1

    $(INSTALL) -D -m 0644 $(@D)/32/libvdpau_nvidia.so.$(BATOCERA_NVIDIA_DRIVER_VERSION)      $(INSTALL_DIR)/lib32/libvdpau_nvidia.so.$(BATOCERA_NVIDIA_DRIVER_VERSION)
    ln -sf libvdpau_nvidia.so.$(BATOCERA_NVIDIA_DRIVER_VERSION)                              $(INSTALL_DIR)/lib32/libvdpau_nvidia.so
    ln -sf libvdpau_nvidia.so.$(BATOCERA_NVIDIA_DRIVER_VERSION)                              $(INSTALL_DIR)/lib32/libvdpau_nvidia.so.1

    $(INSTALL) -D -m 0644 $(@D)/32/libnvidia-tls.so.$(BATOCERA_NVIDIA_DRIVER_VERSION)        $(INSTALL_DIR)/lib32/libnvidia-tls.so.$(BATOCERA_NVIDIA_DRIVER_VERSION)
    ln -sf libnvidia-tls.so.$(BATOCERA_NVIDIA_DRIVER_VERSION)                                $(INSTALL_DIR)/lib32/libnvidia-tls.so

    $(INSTALL) -D -m 0644 $(@D)/32/tls/libnvidia-tls.so.$(BATOCERA_NVIDIA_DRIVER_VERSION)    $(INSTALL_DIR)/lib32/tls/libnvidia-tls.so.$(BATOCERA_NVIDIA_DRIVER_VERSION)
    ln -sf libnvidia-tls.so.$(BATOCERA_NVIDIA_DRIVER_VERSION)                                $(INSTALL_DIR)/lib32/tls/libnvidia-tls.so
    ln -sf libnvidia-tls.so.$(BATOCERA_NVIDIA_DRIVER_VERSION)                                $(INSTALL_DIR)/lib32/tls/libnvidia-tls.so.1

    # Config files
    $(INSTALL) -D -m 0644 $(BR2_EXTERNAL_BATOCERA_PATH)/package/batocera/gpu/batocera-nvidia-driver/10-nvidia-drm-outputclass.conf $(INSTALL_DIR)/usr/share/X11/xorg.conf.d/10-nvidia-drm-outputclass.conf
endef

define BATOCERA_NVIDIA_DRIVER_MODULES_INSTALL
    # Kernel modules
    $(INSTALL) -D -m 0644 $(TARGET_DIR)/lib/modules/$(LINUX_VERSION)/extra/nvidia.ko         $(INSTALL_DIR)/lib/modules/$(LINUX_VERSION)/extra/nvidia.ko
    $(INSTALL) -D -m 0644 $(TARGET_DIR)/lib/modules/$(LINUX_VERSION)/modules.alias           $(INSTALL_DIR)/lib/modules/$(LINUX_VERSION)/modules.alias
    $(INSTALL) -D -m 0644 $(TARGET_DIR)/lib/modules/$(LINUX_VERSION)/modules.alias.bin       $(INSTALL_DIR)/lib/modules/$(LINUX_VERSION)/modules.alias.bin
    $(INSTALL) -D -m 0644 $(TARGET_DIR)/lib/modules/$(LINUX_VERSION)/modules.dep             $(INSTALL_DIR)/lib/modules/$(LINUX_VERSION)/modules.dep
    $(INSTALL) -D -m 0644 $(TARGET_DIR)/lib/modules/$(LINUX_VERSION)/modules.dep.bin         $(INSTALL_DIR)/lib/modules/$(LINUX_VERSION)/modules.dep.bin
    $(INSTALL) -D -m 0644 $(TARGET_DIR)/lib/modules/$(LINUX_VERSION)/modules.symbols         $(INSTALL_DIR)/lib/modules/$(LINUX_VERSION)/modules.symbols
    $(INSTALL) -D -m 0644 $(TARGET_DIR)/lib/modules/$(LINUX_VERSION)/modules.symbols.bin     $(INSTALL_DIR)/lib/modules/$(LINUX_VERSION)/modules.symbols.bin
endef

BATOCERA_NVIDIA_DRIVER_POST_INSTALL_TARGET_HOOKS += BATOCERA_NVIDIA_DRIVER_MODULES_INSTALL

################################################################################

$(eval $(generic-package))
