#!/bin/bash
###
### Batocera.PLUS
###
################################################################################

CORE="${1}"
P1GUID="${2}"
ROM="${3}"
RATIO="${4}"
VIDEOMODE="${5}"
FULLBOOT="${6}"
INTERNALRESOLUTION="${7}"
ANISOTROPIC_FILTERING="${8}"
VSYNC="${9}"
WSCRH="${10}"
SPEEDHACKS="${11}"
CUSTOM="${12}"
API="${13}"

PCSX2_DIR="$(dirname ${0})"
PCSX2_SAVE_DIR="/userdata/saves/ps2"
PCSX2_UI_FILE="${HOME}/configs/${CORE}/PCSX2_ui.ini"
PCSX2_VM_FILE="${HOME}/configs/${CORE}/PCSX2_vm.ini"
PCSX2_GS_FILE="${HOME}/configs/${CORE}/GS.ini"

if [ "${CORE}" == 'pcsx2-legacy' ]
then
    PCSX2_GS_FILE="${HOME}/configs/${CORE}/GSdx.ini"
fi

if [ "${CORE}" == 'PCSX2' ]
then
   PCSX2_GS_FILE="${HOME}/configs/${CORE}/inis/GSdx.ini"
   PCSX2_VM_FILE="${HOME}/configs/${CORE}/inis/PCSX2_vm.ini"
   PCSX2_UI_FILE="${HOME}/configs/${CORE}/inis/PCSX2_ui.ini"
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

### POPULATE

function populate()
{
    local INDEX=''

    mkdir -p "${PCSX2_SAVE_DIR}/pcsx2/Slot 1" \
             "${PCSX2_SAVE_DIR}/pcsx2/Slot 2" \
             "${PCSX2_SAVE_DIR}/sstates" \
             "${PCSX2_SAVE_DIR}/cheats" \
             "${PCSX2_SAVE_DIR}/cheats_ws" \
			 "${PCSX2_SAVE_DIR}/memcards" \
             "${PCSX2_SAVE_DIR}/textures" \
             "${HOME}/configs/${CORE}" \
             "${HOME}/.cache/pcsx2_cache"

    /opt/Pcsx2/pcsx2/pcsx2.sh
	/opt/Pcsx2/pcsx2-mainline/pcsx2.sh 'fristrun'

    for INDEX in {1..2}
    do
        touch "${PCSX2_SAVE_DIR}/pcsx2/Slot ${INDEX}/Shared Memory Card (8 MB).ps2"

        if ! [ -e "${PCSX2_SAVE_DIR}/memcards/Mcd00${INDEX}.ps2" ]
        then
            ln -s "${PCSX2_SAVE_DIR}/pcsx2/Slot ${INDEX}/Shared Memory Card (8 MB).ps2" \
                  "${PCSX2_SAVE_DIR}/memcards/Mcd00${INDEX}.ps2"
        fi
    done
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

### GAME RATION (WIDESCREEN)

case "${RATIO}" in
    4/3|1/1|16/15|3/2|3/4|4/4|5/4|6/5|7/9|8/7|auto|custom|squarepixel)
        sed -i 's/^[ ]*AspectRatio=.*/AspectRatio=4:3/'  "${PCSX2_UI_FILE}"
        ;;
    16/9|19/12|19/14|2/1|21/9|30/17|32/9|4/1|8/3)
        sed -i 's/^[ ]*AspectRatio=.*/AspectRatio=16:9/' "${PCSX2_UI_FILE}"
        ;;
esac

################################################################################

### RESOLUTION

if [ "${VIDEOMODE}" == 'auto' ]
then
    sed -i "s/^[ ]*WindowSize=.*/WindowSize=640,480/"          "${PCSX2_UI_FILE}"
else
    sed -i "s/^[ ]*WindowSize=.*/WindowSize=${VIDEOMODE/x/,}/" "${PCSX2_UI_FILE}"
fi

################################################################################

### FULLBOOT

if [ "${FULLBOOT}" == '1' ] || [ "${FULLBOOT}" == 'auto' ]
then
    FULLBOOT='--fullboot'
else
    FULLBOOT=''
fi

################################################################################

### INTERNAL RESOLUTION

if [ "${INTERNALRESOLUTION}" == 'auto' ] || [ "${INTERNALRESOLUTION}" == '0' ]
then
    INTERNALRESOLUTION=1
fi

### Fix for pcsx2-mainline split screen on high resolutions (only for pcsx2-mainline)
if [ "${CORE}" == 'pcsx2-mainline' ] && [ "${INTERNALRESOLUTION}" -gt 1 ]
then
    sed -i "s/^[ ]*UserHacks[ ]*=.*/UserHacks = 1 /" "${PCSX2_GS_FILE}"
    sed -i "s/^[ ]*UserHacks_align_sprite_X[ ]*=.*/UserHacks_align_sprite_X = 1 /" "${PCSX2_GS_FILE}"
elif [ "${CORE}" == 'pcsx2-mainline' ]
then
    sed -i "s/^[ ]*UserHacks[ ]*=.*/UserHacks = 0 /" "${PCSX2_GS_FILE}"
    sed -i "s/^[ ]*UserHacks_align_sprite_X[ ]*=.*/UserHacks_align_sprite_X = 0 /" "${PCSX2_GS_FILE}"
fi

sed -i "s/^[ ]*upscale_multiplier[ ]*=.*/upscale_multiplier = ${INTERNALRESOLUTION}/" "${PCSX2_GS_FILE}"

################################################################################

### ANISOTROPIC FILTERING

if [ "${ANISOTROPIC_FILTERING}" == 'auto' ]
then
    ANISOTROPIC_FILTERING=0
fi

sed -i "s/^[ ]*MaxAnisotropy[ ]*=.*/MaxAnisotropy = ${ANISOTROPIC_FILTERING}/" "${PCSX2_GS_FILE}"

################################################################################

### VSYNC

if [ "${VSYNC}" == 'auto' ]
then
    VSYNC=1
fi

if [ "${CORE}" == 'pcsx2-mainline' ]
then
    sed -i "s/^[ ]*VsyncEnable[ ]*=.*/VsyncEnable = ${VSYNC}/" "${PCSX2_VM_FILE}"
fi

sed -i "s/^[ ]*vsync[ ]*=.*/vsync = ${VSYNC}/" "${PCSX2_GS_FILE}"

################################################################################

### SPEED HACKS

case ${SPEEDHACKS} in
  safest)
        sed -i s/'^EnablePresets=.*/EnablePresets=enabled/'  "${PCSX2_UI_FILE}"
        sed -i s/'^PresetIndex=.*/PresetIndex=0/'            "${PCSX2_UI_FILE}"
        sed -i s/'^vsync =.*/vsync = 1/'                     "${PCSX2_GS_FILE}"
        sed -i s/'^VsyncEnable=.*/VsyncEnable = 1/'          "${PCSX2_VM_FILE}"
        ;;
  default|auto)
        sed -i s/'^EnablePresets=.*/EnablePresets=enabled/'  "${PCSX2_UI_FILE}"
        sed -i s/'^PresetIndex=.*/PresetIndex=1/'            "${PCSX2_UI_FILE}"
        sed -i s/'^vsync =.*/vsync = 1/'                     "${PCSX2_GS_FILE}"
        sed -i s/'^VsyncEnable=.*/VsyncEnable = 1/'          "${PCSX2_VM_FILE}"
        ;;
  balanced)
        sed -i s/'^EnablePresets=.*/EnablePresets=enabled/'  "${PCSX2_UI_FILE}"
        sed -i s/'^PresetIndex=.*/PresetIndex=2/'            "${PCSX2_UI_FILE}"
        sed -i s/'^vsync =.*/vsync = 1/'                     "${PCSX2_GS_FILE}"
        sed -i s/'^VsyncEnable=.*/VsyncEnable = 1/'          "${PCSX2_VM_FILE}"
        ;;
  aggressive)
        sed -i s/'^EnablePresets=.*/EnablePresets=disabled/' "${PCSX2_UI_FILE}"
        sed -i s/'UserHacks =.*/UserHacks = 1/'              "${PCSX2_GS_FILE}"
        sed -i s/'^vsync =.*/vsync = 0/'                     "${PCSX2_GS_FILE}"
        sed -i s/'^VsyncEnable=.*/VsyncEnable = 0/'          "${PCSX2_VM_FILE}"
        sed -i s/'^EECycleRate=.*/EECycleRate=-1/'           "${PCSX2_VM_FILE}"
        sed -i s/'^EECycleSkip=.*/EECycleSkip=0/'            "${PCSX2_VM_FILE}"
        sed -i s/'^fastCDVD=.*/fastCDVD=disabled/'           "${PCSX2_VM_FILE}"
        sed -i s/'^IntcStat=.*/IntcStat=enabled/'            "${PCSX2_VM_FILE}"
        sed -i s/'^WaitLoop=.*/WaitLoop=enabled/'            "${PCSX2_VM_FILE}"
        sed -i s/'^vuFlagHack=.*/vuFlagHack=enabled/'        "${PCSX2_VM_FILE}"
        sed -i s/'^vuThread=.*/vuThread=enabled/'            "${PCSX2_VM_FILE}"
        sed -i s/'^vu1Instant=.*/vu1Instant=enabled/'        "${PCSX2_VM_FILE}"
        ;;
  vaggressive)
        sed -i s/'^EnablePresets=.*/EnablePresets=disabled/' "${PCSX2_UI_FILE}"
        sed -i s/'UserHacks =.*/UserHacks = 1/'              "${PCSX2_GS_FILE}"
        sed -i s/'^vsync =.*/vsync = 0/'                     "${PCSX2_GS_FILE}"
		sed -i s/'^VsyncEnable=.*/VsyncEnable = 0/'          "${PCSX2_VM_FILE}"
        sed -i s/'^EECycleRate=.*/EECycleRate=-2/'           "${PCSX2_VM_FILE}"
        sed -i s/'^EECycleSkip=.*/EECycleSkip=0/'            "${PCSX2_VM_FILE}"
        sed -i s/'^fastCDVD=.*/fastCDVD=disabled/'           "${PCSX2_VM_FILE}"
        sed -i s/'^IntcStat=.*/IntcStat=enabled/'            "${PCSX2_VM_FILE}"
        sed -i s/'^WaitLoop=.*/WaitLoop=enabled/'            "${PCSX2_VM_FILE}"
        sed -i s/'^vuFlagHack=.*/vuFlagHack=enabled/'        "${PCSX2_VM_FILE}"
        sed -i s/'^vuThread=.*/vuThread=enabled/'            "${PCSX2_VM_FILE}"
        sed -i s/'^vu1Instant=.*/vu1Instant=enabled/'        "${PCSX2_VM_FILE}"
        ;;
  mharmful)
        sed -i s/'^EnablePresets=.*/EnablePresets=disabled/' "${PCSX2_UI_FILE}"
        sed -i s/'UserHacks =.*/UserHacks = 1/'              "${PCSX2_GS_FILE}"
        sed -i s/'^vsync =.*/vsync = 0/'                     "${PCSX2_GS_FILE}"
		sed -i s/'^VsyncEnable=.*/VsyncEnable = 0/'          "${PCSX2_VM_FILE}"
        sed -i s/'^EECycleRate=.*/EECycleRate=1/'            "${PCSX2_VM_FILE}"
        sed -i s/'^EECycleSkip=.*/EECycleSkip=1/'            "${PCSX2_VM_FILE}"
        sed -i s/'^fastCDVD=.*/fastCDVD=disabled/'           "${PCSX2_VM_FILE}"
        sed -i s/'^IntcStat=.*/IntcStat=enabled/'            "${PCSX2_VM_FILE}"
        sed -i s/'^WaitLoop=.*/WaitLoop=enabled/'            "${PCSX2_VM_FILE}"
        sed -i s/'^vuFlagHack=.*/vuFlagHack=enabled/'        "${PCSX2_VM_FILE}"
        sed -i s/'^vuThread=.*/vuThread=enabled/'            "${PCSX2_VM_FILE}"
        sed -i s/'^vu1Instant=.*/vu1Instant=enabled/'        "${PCSX2_VM_FILE}"
        ;;
esac

################################################################################

### GRAPHICS API

### Only change API if custom config is not enabled
if [ "${CORE}" == 'pcsx2-mainline' ] && [ "${CUSTOM}" != '1' ]
then
    case ${API} in
        12) sed -i s/'^Renderer =.*/Renderer = 12/'  "${PCSX2_GS_FILE}" ;; # Vulkan
        13) sed -i s/'^Renderer =.*/Renderer = 13/'  "${PCSX2_GS_FILE}" ;; # OpenGL
        14) sed -i s/'^Renderer =.*/Renderer = 14/'  "${PCSX2_GS_FILE}" ;; # Software
        *)  sed -i s/'^Renderer =.*/Renderer = -1/'  "${PCSX2_GS_FILE}"    # Automatic
    esac
fi

################################################################################

### WIDE SCREEN HACK

if [ "${WSCRH}" == '0' ] || [ "${WSCRH}" == 'auto' ]
then
    WSCRH=disabled
else
    WSCRH=enabled
fi

sed -i "s/^[ ]*EnableWideScreenPatches=.*/EnableWideScreenPatches=${WSCRH}/" "${PCSX2_VM_FILE}"

################################################################################

### MAIN

populate

case ${CORE} in
    pcsx2-mainline)
                    exitHotkeyStart
                    ${MANGOHUD_CMD} /opt/Pcsx2/pcsx2-mainline/pcsx2.sh \
                       "${ROM}"                "${FULLBOOT}" \
                       "${CUSTOM}"
                    ;;
    pcsx2-legacy)
                    exitHotkeyStart
                        ${MANGOHUD_CMD} /opt/Pcsx2/pcsx2-legacy/pcsx2.sh \
                        "${ROM}"                "${FULLBOOT}"
                    ;;
    PCSX2)
                    /usr/bin/batocera-config-pcsx2
                    ;;
    *)
                    exit 1

esac

killXjoyKill

################################################################################

exit 0
