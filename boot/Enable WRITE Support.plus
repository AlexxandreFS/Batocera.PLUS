#!/bin/sh
###
### Batocera.PLUS
###
### Ativa o suporte para escrita na partição de boot. (mount -o remount,rw /boot)
### Este script só funciona com o sistema em execução, ao abrir o script escolha a opção executar.
###
### Enables support for writing to the boot partition. (mount -o remount,rw /boot)
### This script only works with the system running, when opening the script choose the option run.
###

BOOT_DIR='/boot'

TMP_FILE="$(mktemp -p "${BOOT_DIR}" 2> /dev/null)"

if [ "${TMP_FILE}" ]; then
    rm -f "${TMP_FILE}"

    yad --form \
        --title='Enable WRITE support' \
        --window-icon='/usr/share/icons/Adwaita/64x64/places/user-home-symbolic.symbolic.png' \
        --text='\n  Write support is already active on this unit!  \n' \
        --button=gtk-ok \
        --fixed \
        --center
else
    yad --form \
        --title='Enable WRITE support' \
        --window-icon='/usr/share/icons/Adwaita/64x64/places/user-home-symbolic.symbolic.png' \
        --text='\n  Enable write support on this unit?  \n' \
        --fixed \
        --center

    if [ "${?}" == '0' ]; then
        if mount -o remount,rw ${BOOT_DIR}; then
            TMP_FILE="$(mktemp -p "${BOOT_DIR}" 2> /dev/null)"

            if [ "${TMP_FILE}" ]; then
                rm -f "${TMP_FILE}"

                yad --form \
                    --title='Enable WRITE support' \
                    --window-icon='/usr/share/icons/Adwaita/64x64/places/user-home-symbolic.symbolic.png' \
                    --text='\n  Write support has been enabled on this unit!  \n' \
                    --button=gtk-ok \
                    --fixed \
                    --center
            else
                yad --form \
                    --title='Enable WRITE support' \
                    --window-icon='/usr/share/icons/Adwaita/64x64/places/user-home-symbolic.symbolic.png' \
                    --text='\n  Could not activate write support on this unit.  \n' \
                    --button=gtk-ok \
                    --fixed \
                    --center
            fi
        fi
    fi
fi

exit 0
