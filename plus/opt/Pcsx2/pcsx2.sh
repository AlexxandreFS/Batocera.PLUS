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

if [ "${CORE}" == 'pcsx2-legacy' ] || [ "${CORE}" == 'auto' ]
then
    PCSX2_GS_FILE="${HOME}/configs/${CORE}/GSdx.ini"
fi

if [ "${CORE}" == 'PCSX2' ]
then
   PCSX2_GS_FILE="${HOME}/configs/${CORE}/inis/GSdx.ini"
   PCSX2_VM_FILE="${HOME}/configs/${CORE}/inis/PCSX2_vm.ini"
   PCSX2_UI_FILE="${HOME}/configs/${CORE}/inis/PCSX2_ui.ini"
fi

GAME_CONTROLLER_DATABASE_FILE="${HOME}/../bios/gamecontrollerdb.txt"

################################################################################

### POPULATE ALL PCSX2 STANDALONE

mkdir -p "${PCSX2_SAVE_DIR}/pcsx2/Slot 1" \
         "${PCSX2_SAVE_DIR}/pcsx2/Slot 2" \
         "${PCSX2_SAVE_DIR}/sstates" \
         "${PCSX2_SAVE_DIR}/cheats" \
         "${PCSX2_SAVE_DIR}/cheats_ws" \
         "${PCSX2_SAVE_DIR}/memcards" \
         "${PCSX2_SAVE_DIR}/textures" \
         "${HOME}/configs/${CORE}" \
         "${HOME}/.cache/pcsx2_cache"

"${PCSX2_DIR}/pcsx2-mainline/pcsx2-mainline.sh" 'populate'
"${PCSX2_DIR}/pcsx2-legacy/pcsx2-legacy.sh"     'populate'
"${PCSX2_DIR}/pcsx2/pcsx2-pcsx2.sh"             'populate'


for INDEX in {1..2}
do
    touch "${PCSX2_SAVE_DIR}/pcsx2/Slot ${INDEX}/Shared Memory Card (8 MB).ps2"

    if ! [ -e "${PCSX2_SAVE_DIR}/memcards/Mcd00${INDEX}.ps2" ]
    then
        ln -s "${PCSX2_SAVE_DIR}/pcsx2/Slot ${INDEX}/Shared Memory Card (8 MB).ps2" \
              "${PCSX2_SAVE_DIR}/memcards/Mcd00${INDEX}.ps2"
    fi
done

################################################################################

### ASPECT RATION (WIDESCREEN)

case "${RATIO}" in
    4/3|auto)
        sed -i 's/^[ ]*AspectRatio=.*/AspectRatio=4:3/'     "${PCSX2_UI_FILE}"
        ;;
    16/9)
        sed -i 's/^[ ]*AspectRatio=.*/AspectRatio=16:9/'    "${PCSX2_UI_FILE}"
        ;;
    stretch)
        sed -i 's/^[ ]*AspectRatio=.*/AspectRatio=Stretch/' "${PCSX2_UI_FILE}"
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

if [ "${INTERNALRESOLUTION}" == 'auto' ] || 
   [ "${INTERNALRESOLUTION}" == '0' ]    ||
   [ "${INTERNALRESOLUTION}" == '' ]
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

sed -i "s/^[ ]*VsyncEnable[ ]*=.*/VsyncEnable = ${VSYNC}/" "${PCSX2_VM_FILE}"
sed -i "s/^[ ]*vsync[ ]*=.*/vsync = ${VSYNC}/"             "${PCSX2_GS_FILE}"

################################################################################

### SPEED HACKS

case ${SPEEDHACKS} in
    safest)
        sed -i s/'^EnablePresets=.*/EnablePresets=enabled/'  "${PCSX2_UI_FILE}"
        sed -i s/'^PresetIndex=.*/PresetIndex=0/'            "${PCSX2_UI_FILE}"
        ;;
    default|auto)
        sed -i s/'^EnablePresets=.*/EnablePresets=enabled/'  "${PCSX2_UI_FILE}"
        sed -i s/'^PresetIndex=.*/PresetIndex=1/'            "${PCSX2_UI_FILE}"
        ;;
    balanced)
        sed -i s/'^EnablePresets=.*/EnablePresets=enabled/'  "${PCSX2_UI_FILE}"
        sed -i s/'^PresetIndex=.*/PresetIndex=2/'            "${PCSX2_UI_FILE}"
        ;;
    aggressive)
        sed -i s/'^EnablePresets=.*/EnablePresets=disabled/' "${PCSX2_UI_FILE}"
        sed -i s/'UserHacks =.*/UserHacks = 1/'              "${PCSX2_GS_FILE}"
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
        12) sed -i s/'^Renderer =.*/Renderer = 12/' "${PCSX2_GS_FILE}" ;; # Vulkan
        13) sed -i s/'^Renderer =.*/Renderer = 13/' "${PCSX2_GS_FILE}" ;; # OpenGL
        14) sed -i s/'^Renderer =.*/Renderer = 14/' "${PCSX2_GS_FILE}" ;; # Software
        *)  sed -i s/'^Renderer =.*/Renderer = -1/' "${PCSX2_GS_FILE}"    # Automatic
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

### SDL GAME CONTROLLER DATABASE

if [ -e "${GAME_CONTROLLER_DATABASE_FILE}" ]; then
    #export SDL_GAMECONTROLLERCONFIG="$(grep -E ',# Linux,$' ${GAME_CONTROLLER_DATABASE_FILE})"
    ln -sf "${GAME_CONTROLLER_DATABASE_FILE}" "${PCSX2_DIR}/pcsx2-mainline/pcsx2_rc/PCSX2/resources/game_controller_db.txt"
else
    ln -sf /usr/share/batocera/datainit/bios/gamecontrollerdb.txt "${PCSX2_DIR}/pcsx2-mainline/pcsx2_rc/PCSX2/resources/game_controller_db.txt"
fi

################################################################################

### MAIN

case ${CORE} in
    pcsx2-mainline)
        exitHotkeyStart
        ${MANGOHUD_CMD} /opt/Pcsx2/pcsx2-mainline/pcsx2-mainline.sh "${ROM}" "${FULLBOOT}" "${CUSTOM}"
        ;;
    pcsx2-legacy|auto)
        exitHotkeyStart
        ${MANGOHUD_CMD} /opt/Pcsx2/pcsx2-legacy/pcsx2-legacy.sh     "${ROM}" "${FULLBOOT}" "${CUSTOM}"
        ;;
    PCSX2)
        /usr/bin/batocera-config-pcsx2
        ;;
    *)
        exit 1
esac

################################################################################

exit 0
