#!/bin/bash
###
### Batocera.PLUS
### Alexxandre Freire dos Santos
###

### SET DRIVER FOLDER

if [ -z "${1}" ]
then
    DRIVER_VERSION=$(/opt/Nvidia/auto-detect.sh)

    if [ -z "${DRIVER_VERSION}" ]
    then
        exit 1
    else
        DRIVER_DIR=/opt/Nvidia/${DRIVER_VERSION}
    fi
else
    DRIVER_DIR=/opt/Nvidia/${1}
fi


### UNINSTALL OLD DRIVER

${DRIVER_DIR}/../uninstall.sh


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

ln -s ${DRIVER_DIR}/../nvidia-modprobe.conf \
      /etc/modprobe.d/nvidia-driver.conf

ln -s ${DRIVER_DIR}/../nvidia-config.desktop \
      /usr/share/applications/nvidia-config.desktop


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
        insmod "/lib/modules/${KERNEL_VERSION}/extra/${i}"
    fi
done

exit 0
