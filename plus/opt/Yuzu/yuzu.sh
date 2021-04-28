#!/bin/bash
###
### Batocera.PLUS
### Alexxandre Freire dos Santos
###

HOME_DIR="${HOME}/configs/yuzu"
SAVE_DIR=/userdata/saves/switch
BIOS_DIR=/userdata/bios/yuzu

P1GUID="${2}"

export HOME="${HOME_DIR}"
export XDG_DATA_HOME="${SAVE_DIR}"
export QT_QPA_PLATFORM=xcb

mkdir -p "${HOME_DIR}"
mkdir -p "${SAVE_DIR}/yuzu"

# Keys

if [ ! -e "${SAVE_DIR}/yuzu/keys" ] && [ -d "${BIOS_DIR}/keys" ]
then
    mkdir -p "${SAVE_DIR}/yuzu"
    ln -s "${BIOS_DIR}/keys" "${SAVE_DIR}/yuzu/keys"
fi


# Exit game (hotkey + start)

if [ "${P1GUID}" ]
then
    BOTOES="$(/opt/Yuzu/getHotkeyStart "${P1GUID}")"
    BOTAO_HOTKEY="$(echo "${BOTOES}" | cut -d ' ' -f 1)"
    BOTAO_START="$(echo "${BOTOES}"  | cut -d ' ' -f 2)"

    if [ "${BOTAO_HOTKEY}" ] && [ "${BOTAO_START}" ]; then
        # Impede que o xjoykill seja encerrado enquanto o jogo está em execução.
        while : ; do
            nice -n 20 xjoykill -hotkey "${BOTAO_HOTKEY}" -start "${BOTAO_START}" -kill /opt/Yuzu/killyuzu
            if ! [ "$(pidof yuzu)" ]; then
                  break
            fi
            sleep 5
        done &
    fi
fi

# Exec emulator.

if [ -e "${1}" ]
then
    /opt/Yuzu/yuzu -f -g "${1}"
else
    # APPS (F1)
    /opt/Yuzu/yuzu
fi

kill -9 xjoykill

exit 0