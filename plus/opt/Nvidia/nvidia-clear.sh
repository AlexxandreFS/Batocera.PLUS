#!/bin/bash
###
### Batocera.PLUS
### Alexandre Freire dos Santos
###
### Remove todos os arquivos adicionados pelo driver da nvidia.
###

KERNEL_VERSION="$(uname -r)"

if ! [ -f '/lib/modules/${KERNEL_VERSION}/extra/nvidia.ko" ]
    exit 0
fi

NVIDIA_VERSION="$(modinfo /lib/modules/${KERNEL_VERSION}/extra/nvidia.ko | grep -E '^version: ' | awk '{print $2}')"

NVIDIA_FILES=(
    /lib/modules/${KERNEL_VERSION}/extra/nvidia-drm.ko
    /lib/modules/${KERNEL_VERSION}/extra/nvidia-modeset.ko
    /lib/modules/${KERNEL_VERSION}/extra/nvidia-uvm.ko
    /lib/modules/${KERNEL_VERSION}/extra/nvidia.ko

    /lib32/libEGL_nvidia.so
    /lib32/libEGL_nvidia.so.0
    /lib32/libEGL_nvidia.so.${NVIDIA_VERSION}
    /lib32/libGLESv1_CM_nvidia.so
    /lib32/libGLESv1_CM_nvidia.so.1
    /lib32/libGLESv1_CM_nvidia.so.${NVIDIA_VERSION}
    /lib32/libGLESv2_nvidia.so
    /lib32/libGLESv2_nvidia.so.2
    /lib32/libGLESv2_nvidia.so.${NVIDIA_VERSION}
    /lib32/libGLX_nvidia.so
    /lib32/libGLX_nvidia.so.0
    /lib32/libGLX_nvidia.so.${NVIDIA_VERSION}
    /lib32/libnvidia-eglcore.so
    /lib32/libnvidia-eglcore.so.${NVIDIA_VERSION}
    /lib32/libnvidia-glcore.so
    /lib32/libnvidia-glcore.so.${NVIDIA_VERSION}
    /lib32/libnvidia-glsi.so
    /lib32/libnvidia-glsi.so.${NVIDIA_VERSION}
    /lib32/libnvidia-ml.so
    /lib32/libnvidia-ml.so.1
    /lib32/libnvidia-ml.so.${NVIDIA_VERSION}
    /lib32/libnvidia-tls.so
    /lib32/libnvidia-tls.so.${NVIDIA_VERSION}
    /lib32/libvdpau_nvidia.so
    /lib32/libvdpau_nvidia.so.1
    /lib32/libvdpau_nvidia.so.${NVIDIA_VERSION}

    /usr/lib/libEGL_nvidia.so
    /usr/lib/libEGL_nvidia.so.0
    /usr/lib/libEGL_nvidia.so.${NVIDIA_VERSION}
    /usr/lib/libGLESv1_CM_nvidia.so
    /usr/lib/libGLESv1_CM_nvidia.so.1
    /usr/lib/libGLESv1_CM_nvidia.so.${NVIDIA_VERSION}
    /usr/lib/libGLESv2_nvidia.so
    /usr/lib/libGLESv2_nvidia.so.2
    /usr/lib/libGLESv2_nvidia.so.${NVIDIA_VERSION}
    /usr/lib/libGLX_nvidia.so
    /usr/lib/libGLX_nvidia.so.0
    /usr/lib/libGLX_nvidia.so.${NVIDIA_VERSION}
    /usr/lib/libnvidia-eglcore.so
    /usr/lib/libnvidia-eglcore.so.${NVIDIA_VERSION}
    /usr/lib/libnvidia-glcore.so
    /usr/lib/libnvidia-glcore.so.${NVIDIA_VERSION}
    /usr/lib/libnvidia-glsi.so
    /usr/lib/libnvidia-glsi.so.${NVIDIA_VERSION}
    /usr/lib/libnvidia-ml.so
    /usr/lib/libnvidia-ml.so.1
    /usr/lib/libnvidia-ml.so.${NVIDIA_VERSION}
    /usr/lib/libnvidia-tls.so
    /usr/lib/libnvidia-tls.so.${NVIDIA_VERSION}
    /usr/lib/libvdpau_nvidia.so
    /usr/lib/libvdpau_nvidia.so.1
    /usr/lib/libvdpau_nvidia.so.${NVIDIA_VERSION}

    /usr/lib/xorg/modules/drivers/nvidia_drv.so

    /usr/share/glvnd/egl_vendor.d/10_nvidia.json
    /usr/share/vulkan/implicit_layer.d/nvidia_layers.json
    /usr/share/X11/xorg.conf.d/10-nvidia-drm-outputclass.conf

    # Batocera.PLUS only
    #/usr/bin/nvidia-settings
    #/usr/lib/libnvidia-gtk2.so.${NVIDIA_VERSION}
    #/usr/share/nvidia/nvidia-application-profiles-${NVIDIA_VERSION}-key-documentation
    #/usr/share/nvidia/nvidia-application-profiles-${NVIDIA_VERSION}-rc
    /usr/share/applications/nvidia-config.desktop

    #/usr/lib/libnvidia-encode.so.${NVIDIA_VERSION}
    #/usr/lib/libnvcuvid.so.1
)

NVIDIA_FILES_LAST=(
    /usr/lib/libnvidia-egl-wayland.so
    /usr/lib/libnvidia-egl-wayland.so.1
    /usr/lib/libnvidia-egl-wayland.so.1.1.5

    /usr/lib/xorg/modules/extensions/libglxserver_nvidia.so
    /usr/lib/xorg/modules/extensions/libglxserver_nvidia.so.1
    /usr/lib/xorg/modules/extensions/libglxserver_nvidia.so.${NVIDIA_VERSION}

    /usr/share/vulkan/icd.d/nvidia_icd.i686.json
    /usr/share/vulkan/icd.d/nvidia_icd.x86_64.json

    /lib32/libnvidia-glvkspirv.so
    /lib32/libnvidia-glvkspirv.so.${NVIDIA_VERSION}
    /usr/lib/libnvidia-glvkspirv.so
    /usr/lib/libnvidia-glvkspirv.so.${NVIDIA_VERSION}
)

NVIDIA_FILES_390=(

    /usr/lib/libnvidia-egl-wayland.so
    /usr/lib/libnvidia-egl-wayland.so.1
    /usr/lib/libnvidia-egl-wayland.so.1.0.2

    /usr/lib/xorg/modules/extensions/libglx.so
    /usr/lib/xorg/modules/extensions/libglx.so.1
    /usr/lib/xorg/modules/extensions/libglx.so.${NVIDIA_VERSION}

    /usr/share/vulkan/icd.d/nvidia_icd.json

    /usr/lib/xorg/modules/libnvidia-wfb.so.${NVIDIA_VERSION}
)

for FILE in ${NVIDIA_FILES[@]} ${NVIDIA_FILES_LAST[@]} ${NVIDIA_FILES_390[@]}
do
    if [ -e ${FILE} ]
    then
        rm ${FILE}
    fi
done

exit 0
