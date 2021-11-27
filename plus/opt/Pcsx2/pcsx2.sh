#!/bin/bash
###
### Batocera.PLUS
###
################################################################################

readonly CORE="${1}"
readonly P1GUID="${2}"
readonly ROM="${3}"

readonly PCSX2_DIR="$(dirname ${0})"

################################################################################

## Exit game (hotkey + start)

function exitHotkeyStart()
{
    if [ -z "${P1GUID}" ]
    then
        return 1
    fi

    local BOTOES="$(${PCSX2_DIR}/getHotkeyStart ${P1GUID})"
    local BOTAO_HOTKEY=$(echo "${BOTOES}" | cut -d ' ' -f 1)
    local BOTAO_START=$(echo  "${BOTOES}" | cut -d ' ' -f 2)

    if [ "${BOTAO_HOTKEY}" ] && [ "${BOTAO_START}" ]
    then
        # Impede que o xjoykill seja encerrado enquanto o jogo está em execução.
        while :
        do
            nice -n 20 xjoykill -hotkey ${BOTAO_HOTKEY} -start ${BOTAO_START} -kill "${PCSX2_DIR}/killpcsx2"
            if ! [ "$(pidof PCSX2)" ]
            then
                break
            fi
            sleep 5
        done &
    fi
}

################################################################################

## CLOSE XJOYKILL

function killXjoyKill()
{
    if [ "$(pidof -s xjoykill)" ]
    then
       killall -9 xjoykill
    fi
}

################################################################################

exitHotkeyStart

if [ "${CORE}" == 'pcsx-mainline' ]
then
    /opt/Pcsx2/pcsx2-mainline/pcsx2.sh "${ROM}"
elif [ "${CORE}" == 'pcsx2-legacy' ]
then
    /opt/Pcsx2/pcsx2-legacy/pcsx2.sh "${ROM}"
fi

killXjoyKill

################################################################################

exit 0
