#!/bin/bash
###
### Batocera.PLUS
###
################################################################################

readonly CORE="${1}"
readonly P1GUID="${2}"
readonly ROM="${3}"

readonly RESOLUTION="${4}"  #videomode
readonly WIDESCREEN="${5}"  #ratio
readonly BOOTANIM="${6}"    #fullboot
readonly I_RES="${7}"       #internal_resolution
readonly A_FILT="${8}"      #anisotropic_filtering
readonly WSCRH="${9}"       #widescreen hack
readonly SPEEDHACKS="${10}" #speedhacks

readonly PCSX2_DIR="$(dirname ${0})"
readonly PCSX2_SAVE_DIR='/userdata/saves/ps2'

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

### POPULATE

function populate()
{
    local INDEX=''

    mkdir -p "${HOME}/configs/pcsx2-mainline" \
             "${HOME}/configs/pcsx2-legacy"

    mkdir -p "${PCSX2_SAVE_DIR}/pcsx2/Slot 1" \
             "${PCSX2_SAVE_DIR}/pcsx2/Slot 2" \
             "${PCSX2_SAVE_DIR}/sstates-mainline" \
             "${PCSX2_SAVE_DIR}/sstates-legacy" \
             "${PCSX2_SAVE_DIR}/cheats" \
             "${PCSX2_SAVE_DIR}/cheats_ws" \
             "${PCSX2_SAVE_DIR}/memcards" \
             "${PCSX2_SAVE_DIR}/inis-custom-pcsx2-mainline"

    for INDEX in {1..2}
    do
        touch "${PCSX2_SAVE_DIR}/pcsx2/slot ${INDEX}/Shared Memory Card (8 MB).ps2"

        if ! [ -e "${PCSX2_SAVE_DIR}/memcards/Mcd00${INDEX}.ps2" ]
        then
            ln -s "${PCSX2_SAVE_DIR}/pcsx2/Slot ${INDEX}/Shared Memory Card (8 MB).ps2" \
                  "${PCSX2_SAVE_DIR}/memcards/Mcd00${INDEX}.ps2"
        fi
    done
}

################################################################################

### MAIN

populate

if [ "${CORE}" == 'pcsx2-mainline' ]
then
    exitHotkeyStart
    /opt/Pcsx2/pcsx2-mainline/pcsx2.sh \
        "${ROM}" \
        "${RESOLUTION}" \
        "${WIDESCREEN}" \
        "${BOOTANIM}" \
        "${I_RES}" \
        "${A_FILT}" \
        "${WSCRH}" \
        "${SPEEDHACKS}"
elif [ "${CORE}" == 'pcsx2-legacy' ]
then
    exitHotkeyStart
    /opt/Pcsx2/pcsx2-legacy/pcsx2.sh "${ROM}"
else
    exit 1
fi

killXjoyKill

################################################################################

exit 0
