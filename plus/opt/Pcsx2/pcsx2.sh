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

################################################################################

function TextLocalization()
{
   LANG="$(batocera-settings -command load -key system.language)"
   case $LANG in
      pt_BR) MSG[1]='\n ESCOLHA UMA OPÇÃO. \n' ;;
      es_ES) MSG[1]='\n ESCOGE UNA OPCIÓN. \n' ;;
      *)     MSG[1]='\n CHOOSE A OPTION. \n'
   esac
}

function choseEmu()
{
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
      0) GUI='0' ;;
      1) GUI='1' ;;
      2) GUI='2' ;;
      *) exit 0
   esac
}

################################################################################

if [ ! -e "${ROM}" ]; then
    TextLocalization
    choseEmu
    case ${GUI} in
        0) /usr/bin/batocera-config-pcsx2 ;;
        1) /opt/Pcsx2/pcsx2-legacy/pcsx2.sh ;;
        2) /opt/Pcsx2/pcsx2-mainline/pcsx2.sh ;;
    esac
fi


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

if [ "${CORE}" == 'pcsx2-mainline' ]
then
    /opt/Pcsx2/pcsx2-mainline/pcsx2.sh \
            "${ROM}" "${P1GUID}" "${RESOLUTION}" "${WIDESCREEN}" "${BOOTANIM}" "${I_RES}" \
            "${A_FILT}" "${WSCRH}" "${SPEEDHACKS}"
elif [ "${CORE}" == 'pcsx2-legacy' ]
then
    /opt/Pcsx2/pcsx2-legacy/pcsx2.sh "${ROM}"
fi

killXjoyKill

################################################################################

exit 0
