#!/bin/bash

XORG_CONF_IN=/opt/Nvidia/hybrid-nvidia-xorg.conf
XORG_CONF_OUT=/usr/share/X11/xorg.conf.d/10-nvidia-drm-outputclass.conf

function convert()
{
    A=$(echo "${1}" | cut -d ':' -f 1)
    B=$(echo "${1}" | cut -d ':' -f 2)
    C=$(echo "${1}" | cut -d ':' -f 3)

    OA=$(printf "%d" "0x${A}")
    OB=$(printf "%d" "0x${B}")
    OC=$(printf "%d" "0x${C}")

    echo -n "${OA}:${OB}:${OC}"
}

BUSID=$(lspci | grep -E 'controller: NVIDIA' | cut -d ' ' -f 1 | sed s/[.]/:/g)

if [ -z "${BUSID}" ]
then
    exit 0
fi

BID=$(convert "${BUSID}")
PCIID="PCI:${BID}"

cp  -f "${XORG_CONF_IN}"    "${XORG_CONF_OUT}"
sed -i "s/%PCIID%/${PCIID}/" ${XORG_CONF_OUT}

exit 0
