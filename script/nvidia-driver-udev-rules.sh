#!/bin/bash
###
### Batocera.PLUS
### Alexandre Freire dos Santos
###
################################################################################

# USER CONFIG

SUPPORTED_GPUS_JSON="${1}"
UDEV_RULES="${2}"

#SUPPORTED_GPUS_JSON='/userdata/downloads/build-nvidia-driver-rules/supported-gpus.json'
#UDEV_RULES='/userdata/downloads/build-nvidia-driver-rules/01-nvidia-driver.rules'

################################################################################

# SANITY

if [ "${#}" != '2' ]
then
    exit 1
fi

if ! [ -e "${SUPPORTED_GPUS_JSON}" ]
then
    echo "not found: ${SUPPORTED_GPUS_JSON}"
    exit 3
fi

if ! [ -d "$(dirname ${UDEV_RULES})" ]
then
    echo "not found: ${SUPPORTED_GPUS_JSON}"
    exit 5
fi

################################################################################

# CREATE VIDEO CARD LIST

INDEX=0

GPU_INFO=''
GPU_ID=''

DRIVER_LAST=''
DRIVER_V470=''
DRIVER_V390=''
DRIVER_V340=''

SUPPORTED_GPUS_JSON="$(cat "${SUPPORTED_GPUS_JSON}")"

rm -f "${UDEV_RULES}"

while :
do
    GPU_INFO=$(printf '%s' "${SUPPORTED_GPUS_JSON}" | jq .chips[${INDEX}])

    if [ "${GPU_INFO}" == 'null' ]
    then
        break
    fi

    GPU_ID=$(echo ${GPU_INFO} | grep '"devid"' | cut -d '"' -f 4 | tr 'A-Z' 'a-z')

    if echo ${GPU_INFO} | grep -q '"legacybranch":'
    then
        if echo ${GPU_INFO} | grep -q '"470.xx"'
        then
            DRIVER_V470="${DRIVER_V470} ${GPU_ID}"
        elif echo ${GPU_INFO} | grep -q '"390.xx"'
        then
            DRIVER_V390="${DRIVER_V390} ${GPU_ID}"
        elif echo ${GPU_INFO} | grep -q '"340.xx"'
        then
            DRIVER_V340="${DRIVER_V340} ${GPU_ID}"
        fi
    else
        DRIVER_LAST="${DRIVER_LAST} ${GPU_ID}"
    fi

    echo -en "\r\033[0KGPU: ${INDEX} | ${GPU_ID}"

    let INDEX++
done

echo

DRIVER_LAST="$(printf '%s\n' ${DRIVER_LAST} | sort | uniq)"
DRIVER_V470="$(printf '%s\n' ${DRIVER_V470} | sort | uniq)"
DRIVER_V390="$(printf '%s\n' ${DRIVER_V390} | sort | uniq)"
DRIVER_V340="$(printf '%s\n' ${DRIVER_V340} | sort | uniq)"

################################################################################

# HEADER

echo -n '#
# Batocera.PLUS
# Alexandre Freire dos Santos
#
# Database:
# https://download.nvidia.com/XFree86/Linux-x86_64/510.60.02/README/supportedchips.html
#
ACTION=="add", SUBSYSTEM=="pci", ATTRS{vendor}=="0x10de", ATTR{class}=="0x030000", GOTO="nvidia"
ACTION=="add", SUBSYSTEM=="pci", ATTRS{vendor}=="0x10de", ATTR{class}=="0x030200", GOTO="nvidia"
GOTO="exit"

LABEL="nvidia"
' > "${UDEV_RULES}"

################################################################################

# BODY

for DRIVER in ${DRIVER_LAST}
do
    echo "ATTRS{device}==\"${DRIVER}\", GOTO=\"nvidia_last\"" >> "${UDEV_RULES}"
done

for DRIVER in ${DRIVER_V470}
do
    echo "ATTRS{device}==\"${DRIVER}\", GOTO=\"nvidia_v470\"" >> "${UDEV_RULES}"
done

for DRIVER in ${DRIVER_V390}
do
    echo "ATTRS{device}==\"${DRIVER}\", GOTO=\"nvidia_v390\"" >> "${UDEV_RULES}"
done

for DRIVER in ${DRIVER_V340}
do
    echo "ATTRS{device}==\"${DRIVER}\", GOTO=\"nvidia_v340\"" >> "${UDEV_RULES}"
done

################################################################################

# FOOTER

echo -n 'GOTO="exit"

LABEL="nvidia_last"
RUN+="/opt/Nvidia/install.sh last"
GOTO="exit"

LABEL="nvidia_v470"
RUN+="/opt/Nvidia/install.sh v470"
GOTO="exit"

LABEL="nvidia_v390"
RUN+="/opt/Nvidia/install.sh v390"
GOTO="exit"

LABEL="nvidia_v340"
RUN+="/opt/Nvidia/install.sh v340"
GOTO="exit"

LABEL="exit"
' >> "${UDEV_RULES}"

################################################################################

exit 0
