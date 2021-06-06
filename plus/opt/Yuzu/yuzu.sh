#!/bin/bash
###
### Batocera.PLUS
### Alexandre Freire dos Santos
###
################################################################################

### DIRECTORIES, FILES AND PARAMETERS

YUZU_DIR="$(dirname ${0})"

HOME_DIR="${HOME}/configs/yuzu"
SAVE_DIR=/userdata/saves/switch
BIOS_DIR=/userdata/bios/yuzu

ROM="${1}"
CORE="${2}"
P1GUID="${3}"

################################################################################

### NINTENDO SWITCH KEYS

if [ ! -e "${SAVE_DIR}/yuzu/keys" ] && [ -d "${BIOS_DIR}/keys" ]
then
    mkdir -p "${SAVE_DIR}/yuzu"
    ln -s "${BIOS_DIR}/keys" "${SAVE_DIR}/yuzu/keys"
fi

################################################################################

### MOUSE POINTER

mouse-pointer on

################################################################################

### FIRST RUN

if ! [ -e "${HOME_DIR}/.config/yuzu/qt-config.ini" ]
then
    mkdir -p "${HOME_DIR}/.config/yuzu"

    (echo '[UI]'
     echo 'calloutFlags=1'
     echo 'calloutFlags\default=false'
     echo 'confirmClose=false\n'
     echo 'confirmClose\default=false') > "${HOME_DIR}/.config/yuzu/qt-config.ini"	
fi

################################################################################

### EXIT GAME (hotkey + start)

if [ "${P1GUID}" ]
then
    BOTOES="$(${YUZU_DIR}/getHotkeyStart ${P1GUID})"
    BOTAO_HOTKEY=$(echo "${BOTOES}" | cut -d ' ' -f 1)
    BOTAO_START=$(echo  "${BOTOES}" | cut -d ' ' -f 2)

    if [ "${BOTAO_HOTKEY}" ] && [ "${BOTAO_START}" ]
    then
        # Impede que o xjoykill seja encerrado enquanto o jogo está em execução.
        while :
        do
            nice -n 20 xjoykill -hotkey ${BOTAO_HOTKEY} -start ${BOTAO_START} -kill "${YUZU_DIR}/killyuzu"
            if ! [ "$(pidof yuzu yuzu-mainline yuzu-early-access)" ]
            then
                break
            fi
            sleep 5
        done &
    fi
fi

################################################################################

### WORKING PATHS 

mkdir -p "${HOME_DIR}"
mkdir -p "${SAVE_DIR}/yuzu"

export HOME="${HOME_DIR}"
export XDG_DATA_HOME="${SAVE_DIR}"
export QT_QPA_PLATFORM=xcb

export LD_LIBRARY_PATH="${YUZU_DIR}/lib:${LD_LIBRARY_PATH}"

#https://github.com/yuzu-emu/yuzu/issues/6388
#https://github.com/yuzu-emu/yuzu/issues/6343
#https://github.com/yuzu-emu/yuzu-mainline/commit/648bef235ea7a7eb183c6aac52bdd63f921b7b22#diff-1e7de1ae2d059d21e1dd75d5812d5a34b0222cef273b7c3a2af62eb747f9d20a
export SDL_JOYSTICK_HIDAPI=0

################################################################################

### EXEC EMULATOR

if [ -e "${ROM}" ]
then
    if [ "${CORE}" == 'auto' ]
    then
        "${YUZU_DIR}/yuzu"    -f -g "${ROM}"
    else
        "${YUZU_DIR}/${CORE}" -f -g "${ROM}"
    fi
else
    # APPS (F1)
    "${YUZU_DIR}/yuzu" "${@}"
fi

################################################################################

### CLOSE xjoykill

if [ "$(pidof xjoykill)" ]
then
    killall -9 xjoykill
fi

exit 0