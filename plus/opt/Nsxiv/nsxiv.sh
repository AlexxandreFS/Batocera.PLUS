#!/bin/bash
###
### Batocera.PLUS
### Alexandre Freire dos Santos
###
################################################################################

### USER CONFIG

# Disable status bar
#EXTRA_PARM='-b'

# Only one instance
#ONE_INSTANCE=FALSE

################################################################################

### PATH

IMG_FILE="${1}"
IMG_DIR="$(dirname "${IMG_FILE}")/"
APP_DIR="$(dirname ${0})"

export XDG_CONFIG_HOME="${APP_DIR}/xdg_config_home"
export LC_ALL=C

################################################################################

### SHOWS OTHER IMAGES IN THE FORDER

if [ "$(ls -1 "${IMG_DIR}" | grep -iE '\.(jpe?g|png|gif|svg|webp|tiff|heif|avif|ico|bmp)$' | wc -l)" == '1' ]
then
    unset IMG_DIR
fi

################################################################################

### MAX AND MIN WINDOW SIZE

IMG_RES=$(file -bp "${IMG_FILE}" | grep -Eo ",[ ][[:digit:]]+ *x+ *[[:digit:]]+" | tail -n 1 | tr -d ', ')
SCR_RES=$(batocera-resolution currentMode)

if [ -z "${IMG_RES}" ]
then
    IMG_RES=${SCR_RES}
fi

IMG_RES_X=$(echo ${IMG_RES} | cut -d 'x' -f 1)
IMG_RES_Y=$(echo ${IMG_RES} | cut -d 'x' -f 2)

SCR_RES_X=$(echo ${SCR_RES} | cut -d 'x' -f 1)
SCR_RES_Y=$(echo ${SCR_RES} | cut -d 'x' -f 2)

MIN_RES_X=640
MIN_RES_Y=480
MIN_RES=${MIM_RES_X}x${MIN_RES_Y}

MAX_RES_X=$((${SCR_RES_X} / 16 * 14))
MAX_RES_Y=$((${SCR_RES_Y} /  9 *  8))
MAX_RES=${MAX_RES_X}x${MAX_RES_Y}

if [ "${IMG_RES_X}" -gt "${MAX_RES_X}" ]   || [ "${IMG_RES_Y}" -gt "${MAX_RES_Y}" ]
then
    IMG_RES=${MAX_RES_X}x${MAX_RES_Y}
elif [ "${IMG_RES_X}" -le "${MIN_RES_X}" ] || [ "${IMG_RES_Y}" -le "${MIN_RES_Y}" ]
then
    IMG_RES=${MIN_RES_X}x${MIN_RES_Y}
fi

################################################################################

### ONLY ONE INSTANCE

if [ "${ONE_INSTANCE}" != 'FALSE' ]
then
    if [ "$(pidof -s nsxiv)" ]
    then
        killall -15 nsxiv
    fi
fi

################################################################################

exec "${APP_DIR}/nsxiv" -pqg ${IMG_RES} ${EXTRA_PARM} "${IMG_FILE}" "${IMG_DIR}"
