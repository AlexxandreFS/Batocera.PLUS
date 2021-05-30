#!/bin/bash
###
### Batocera.PLUS
### Alexxandre Freire dos Santos
###
################################################################################

### DIRECTORIES, FILES AND PARAMETERS

YUZU_DIR="$(dirname ${0})"

HOME_DIR="${HOME}/configs/yuzu"
SAVE_DIR=/userdata/saves/switch
BIOS_DIR=/userdata/bios/yuzu

ROM="${1}"
P1GUID="${2}"

################################################################################

### NINTENDO SWITCH KEYS

if [ ! -e "${SAVE_DIR}/yuzu/keys" ] && [ -d "${BIOS_DIR}/keys" ]
then
    mkdir -p "${SAVE_DIR}/yuzu"
    ln -s "${BIOS_DIR}/keys" "${SAVE_DIR}/yuzu/keys"
fi

################################################################################

### EXIT GAME (hotkey + start)

if [ "${P1GUID}" ]
then
    BOTOES="$(${YUZU_DIR}/Yuzu/getHotkeyStart ${P1GUID})"
    BOTAO_HOTKEY=$(echo "${BOTOES}" | cut -d ' ' -f 1)
    BOTAO_START=$(echo "${BOTOES}"  | cut -d ' ' -f 2)

    if [ "${BOTAO_HOTKEY}" ] && [ "${BOTAO_START}" ]
    then
        # Impede que o xjoykill seja encerrado enquanto o jogo está em execução.
        while :
        do
            nice -n 20 xjoykill -hotkey ${BOTAO_HOTKEY} -start ${BOTAO_START} -kill "${YUZU_DIR}/killyuzu"
            if ! [ "$(pidof yuzu)" ]
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

################################################################################

### EXEC EMULATOR

if [ -e "${ROM}" ]
then
    "${YUZU_DIR}/yuzu" -f -g "${ROM}"
else
    # APPS (F1)
    "${YUZU_DIR}/yuzu"
fi

################################################################################

### CLOSE xjoykill

if [ "$(pidof xjoykill)" ]
then
    killall -9 xjoykill
fi

exit 0