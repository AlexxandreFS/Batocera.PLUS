#!/bin/bash
###
### Batocera.PLUS
### Alexxandre Freire dos Santos
###
### Install Nvidia driver
###

### PATH

DRIVER_DIR="$(dirname $0)"
XORG_CONF_IN=${DRIVER_DIR}/hybrid-nvidia-xorg.conf
XORG_CONF_OUT=/usr/share/X11/xorg.conf.d/10-nvidia-drm-outputclass.conf
CONFIG_FILE=/boot/batocera-boot.conf
DRIVER_VERSION=$(grep -E "^[ ]*nvidia-driver[ ]*=" ${CONFIG_FILE} | cut -d '=' -f 2 | xargs)

case ${DRIVER_VERSION} in
    auto|true)
        DRIVER_DIR="${DRIVER_DIR}/${1}"
        ;;
    last)
        DRIVER_DIR="${DRIVER_DIR}/last"
        ;;
    390)
        DRIVER_DIR="${DRIVER_DIR}/v390"
        ;;
    340)
        DRIVER_DIR="${DRIVER_DIR}/v340"
        ;;
    *)
        exit 0
esac

### DISABLE NOUVEAU DRIVER

ln -s ${DRIVER_DIR}/../nvidia-modprobe.conf \
      /etc/modprobe.d/nvidia-driver.conf

ln -s ${DRIVER_DIR}/../nvidia-config.desktop \
      /usr/share/applications/nvidia-config.desktop


### CREATE FOLDERS

DIRS=$(find ${DRIVER_DIR} -type d | sed "s|${DRIVER_DIR}||")

for DIR in ${DIRS[*]}
do
    mkdir -p ${DIR}
done


### LINK FILES

FILES=$(find ${DRIVER_DIR} -type f | sed "s|${DRIVER_DIR}||")

for FILE in ${FILES[*]}
do
    ln -sf ${DRIVER_DIR}${FILE} ${FILE}
done


### COPY LINKS

LINKS=$(find ${DRIVER_DIR} -type l | sed "s|${DRIVER_DIR}||")

for LINK in ${LINKS[*]}
do
    cp -df ${DRIVER_DIR}${LINK} ${LINK}
done


### LOAD MODULES

KERNEL_VERSION="$(uname -r)"

for i in nvidia.ko \
         nvidia-modeset.ko \
         nvidia-uvm.ko \
         nvidia-drm.ko
do
    if [ -e "/lib/modules/${KERNEL_VERSION}/extra/${i}" ]
    then
        modprobe ${i}
    fi
done


### HYBRID NVIDIA

if ! [ "$(lspci -d8086::0300)" ]
then
    exit 0
fi

function convert()
{
    local A=$(echo "${1}" | cut -d ':' -f 1)
    local B=$(echo "${1}" | cut -d ':' -f 2)
    local C=$(echo "${1}" | cut -d ':' -f 3)

    local OA=$(printf "%d" "0x${A}")
    local OB=$(printf "%d" "0x${B}")
    local OC=$(printf "%d" "0x${C}")

    echo -n "${OA}:${OB}:${OC}"
}

BUSID=$(lspci | grep -E 'controller: NVIDIA' | cut -d ' ' -f 1 | sed s/[.]/:/g)

if [ -z "${BUSID}" ]
then
    exit 1
fi

PCIID="PCI:$(convert "${BUSID}")"

cp  -f "${XORG_CONF_IN}"    "${XORG_CONF_OUT}"
sed -i "s/%PCIID%/${PCIID}/" ${XORG_CONF_OUT}

exit 0
