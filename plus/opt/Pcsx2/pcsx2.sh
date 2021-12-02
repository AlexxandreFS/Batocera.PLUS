#!/bin/bash
###
### Batocera.PLUS
###
################################################################################

readonly CORE="${1}"
readonly P1GUID="${2}"
readonly ROM="${3}"

RESOLUTION="${4}"  #videomode
WIDESCREEN="${5}"  #ratio
BOOTANIM="${6}"    #fullboot
I_RES="${7}"       #internal_resolution
A_FILT="${8}"      #anisotropic_filtering
WSCRH="${9}"       #widescreen hack
SPEEDHACKS="${10}" #speedhacks

readonly PCSX2_DIR="$(dirname ${0})"
readonly PCSX2_SAVE_DIR='/userdata/saves/ps2'

################################################################################

function guiChoseEmu()
{
    local LANG="$(batocera-settings -command load -key system.language)"

    case ${LANG} in
        pt_BR) MSG[1]='\n ESCOLHA UMA OPÇÃO. \n' ;;
        es_ES) MSG[1]='\n ESCOGE UNA OPCIÓN. \n' ;;
        *)     MSG[1]='\n CHOOSE A OPTION. \n'
    esac

    yad --form \
        --title='PCSX2 CONFIGURATOR' \
        --window-icon='/usr/share/icons/batocera/pcsx2.png' \
        --text=''"${MSG[1]}"'' \
        --text-align=center \
        --button='PCSX2:0' \
        --button='PCSX2-LEGACY:1' \
        --button='PCSX2-MAINLINE:2' \
        --fixed \
        --center \
        --close-on-unfocus

    case ${?} in
        0) /usr/bin/batocera-config-pcsx2     ;;
        1) /opt/Pcsx2/pcsx2-legacy/pcsx2.sh   ;;
        2) /opt/Pcsx2/pcsx2-mainline/pcsx2.sh ;;
        *) return 0
    esac
}

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
    mkdir -p "${HOME}/configs/${CORE}"

    mkdir -p "${PCSX2_SAVE_DIR}/pcsx2/Slot 1" \
             "${PCSX2_SAVE_DIR}/pcsx2/Slot 2" \
             "${PCSX2_SAVE_DIR}/sstates" \
             "${PCSX2_SAVE_DIR}/cheats" \
             "${PCSX2_SAVE_DIR}/cheats_ws" \
             "${PCSX2_SAVE_DIR}/inis-custom-${CORE}"

    touch    "${PCSX2_SAVE_DIR}/pcsx2/Slot 1/Shared Memory Card (8 MB).ps2" \
             "${PCSX2_SAVE_DIR}/pcsx2/Slot 2/Shared Memory Card (8 MB).ps2"
}

################################################################################

### MAIN

populate

if [ -e "${ROM}" ]
then
    exitHotkeyStart

    if [ "${CORE}" == 'pcsx2-mainline' ]
    then
        /opt/Pcsx2/pcsx2-mainline/pcsx2.sh \
            "${ROM}" \
            "${P1GUID}" \
            "${RESOLUTION}" \
            "${WIDESCREEN}" \
            "${BOOTANIM}" \
            "${I_RES}" \
            "${A_FILT}" \
            "${WSCRH}" \
            "${SPEEDHACKS}"
    else
        /opt/Pcsx2/pcsx2-legacy/pcsx2.sh "${ROM}"
    fi

    killXjoyKill
else
    guiChoseEmu
fi

################################################################################

exit 0
