#!/bin/bash
###
### Batocera.PLUS
### Alexxandre Freire dos Santos
###

GPU_DATABASE_LAST=/opt/Nvidia/supported-gpus-last.dat
GPU_DATABASE_V390=/opt/Nvidia/supported-gpus-v390.dat
GPU_DATABASE_V340=/opt/Nvidia/supported-gpus-v340.dat

DEVICE_ID="$(lspci -nd10de::0300 | egrep -o "[[:xdigit:]]{4}:[[:xdigit:]]{4}" | cut -d ":" -f 2 | sed '/^$/d' | head -n 1)"

if grep -iqF "${DEVICE_ID}" ${GPU_DATABASE_LAST}
then
    DRIVER_VER=last
elif grep -iqF "${DEVICE_ID}" ${GPU_DATABASE_V390}
then
    DRIVER_VER=v390
elif grep -iqF "${DEVICE_ID}" ${GPU_DATABASE_V340}
then
    DRIVER_VER=v340
else
    exit 0
fi

DEVICE_HIBRID_ID="$(lspci -d8086::0300)"

if [ "${DEVICE_HIBRID_ID}" ] && [ "${DEVICE_ID}" ]
then
    echo "${DRIVER_VER} hybrid"
else
    echo ${DRIVER_VER}
fi

exit 0
