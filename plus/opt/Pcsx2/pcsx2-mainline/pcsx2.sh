#!/bin/bash
##
## Batocera.PLUS
##
## Código escrito por: Sérgio de Carvalho Júnior
## Supervisão: Alexandre Freire dos Santos
##
## https://forums.pcsx2.net/Thread-PCSX2-Widescreen-Game-Patches?pid=271674#pid271674
## https://www.mediafire.com/file/j48lgoeeli5evve/PCSX_Cheats_Pack_v1.1_-_Mateus_Auri.rar/file
##
################################################################################

### DIRECTORIES, FILES AND PARAMETERS

ROM="${1}"
FULLBOOT="${2}"
I_RES="${3}"       #internal_resolution
A_FILT="${4}"      #anisotropic_filtering
WSCRH="${5}"       #widescreen hack
PRESET="${6}"      #speed hacks

EMU_DIR='/opt/Pcsx2/pcsx2-mainline'
SAVE_DIR='/userdata/saves/ps2'
CONFIG_DIR="${HOME}/configs/pcsx2-mainline"

################################################################################

### EXPORTS

export LD_LIBRARY_PATH="${EMU_DIR}/lib:${EMU_DIR}:${LD_LIBRARY_PATH}"
export GDK_PIXBUF_MODULEDIR='/usr/lib/gdk-pixbuf-2.0/2.10.0/loaders'
export GDK_PIXBUF_MODULE_FILE='/usr/lib/gdk-pixbuf-2.0/2.10.0/loaders.cache'
export GDK_BACKEND=x11
export GSETTINGS_SCHEMA_DIR="${EMU_DIR}/schemas"

################################################################################

### DEFAULT CONFIG

function createInis()
{
    mkdir -p "${CONFIG_DIR}"

    if ! [ -e "${CONFIG_DIR}/PCSX2_vm.ini" ]; then
        (echo '[EmuCore]'
         echo 'EnableWideScreenPatches=disabled'
         echo '[EmuCore/Speedhacks]'
         echo 'EECycleRate=0'
         echo 'EECycleSkip=0'
         echo 'fastCDVD=disabled'
         echo 'IntcStat=enabled'
         echo 'WaitLoop=enabled'
         echo 'vuFlagHack=enabled'
         echo 'vuThread=disabled'
         echo 'vu1Instant=enabled') > "${CONFIG_DIR}/PCSX2_vm.ini"
    fi

    if ! [ -e "${CONFIG_DIR}/PCSX2_ui.ini" ]; then
        (echo 'PresetIndex=1'
         echo '[Filenames]'
         echo 'BIOS=scph39001.bin'
         echo '[ProgramLog]'
         echo 'Visible=disabled'
         echo '[GSWindow]'
         echo 'AspectRatio=4:3') > "${CONFIG_DIR}/PCSX2_ui.ini"
    fi

    if ! [ -e "${CONFIG_DIR}/GS.ini" ]; then
        (echo 'vsync = 1'
         echo 'upscale_multiplier = 1'
         echo 'MaxAnisotropy = 0'
         echo 'UserHacks = 0') > "${CONFIG_DIR}/GS.ini"
    fi

    if ! [ -e "${CONFIG_DIR}/PAD.ini" ]; then
        (echo 'first_time_wizard = 0'
         echo 'options = 1') > "${CONFIG_DIR}/PAD.ini"
    fi
}

################################################################################

### PERGAME CONFIG

createInis

if [ "${CUSTOM}" == '1' ]; then
    PGAME="$(basename "${ROM%.*}")"
    mkdir -p "${SAVE_DIR}/inis-custom-pcsx2-mainline/${PGAME}"

    cp -rf "${HOME}/configs/pcsx2-mainline/"* "${SAVE_DIR}/inis-custom-pcsx2-mainline/${PGAME}"
    CUSTOM_INIS="--cfgpath ${SAVE_DIR}/inis-custom-pcsx2-mainline/${PGAME}"
fi

################################################################################

### VSYNC

if [ "${VSYNC}" == '1' ] || [ "${VSYNC}" == 'auto' ]; then
    sed -i 's/^vsync =.*/vsync = 1/' "${CONFIG_DIR}/GS.ini"
else
    sed -i 's/^vsync =.*/vsync = 0/' "${CONFIG_DIR}/GS.ini"
fi

################################################################################

### WIDE SCREEN HACK

if [ "${WSCRH}" == '0' ] || [ "${WSCRH}" == 'auto' ]; then
    sed -i 's/^EnableWideScreenPatches=.*/EnableWideScreenPatches=disabled/' "${CONFIG_DIR}/PCSX2_vm.ini"
else
    sed -i 's/^EnableWideScreenPatches=.*/EnableWideScreenPatches=enabled/'  "${CONFIG_DIR}/PCSX2_vm.ini"
fi

################################################################################

### ANISOTROPIC FILTERING

if [ "${A_FILT}" != 'auto' ]; then
    sed -i 's/^MaxAnisotropy =.*/MaxAnisotropy = '"${A_FILT}"'/' "${CONFIG_DIR}/GS.ini"
else
    sed -i 's/^MaxAnisotropy =.*/MaxAnisotropy = 0/'             "${CONFIG_DIR}/GS.ini"
fi

################################################################################

### SPEED HACKS

case ${PRESET} in
    safest)
        sed -i 's/^EnablePresets=.*/EnablePresets=enabled/'  "${CONFIG_DIR}/PCSX2_ui.ini"
        sed -i 's/^PresetIndex=.*/PresetIndex=0/'            "${CONFIG_DIR}/PCSX2_ui.ini"
        sed -i 's/UserHacks =.*/UserHacks = 0/'              "${CONFIG_DIR}/GS.ini"
        sed -i 's/^vsync =.*/vsync = 1/'                     "${CONFIG_DIR}/GS.ini"
        ;;
    default|auto)
        sed -i 's/^EnablePresets=.*/EnablePresets=enabled/'  "${CONFIG_DIR}/PCSX2_ui.ini"
        sed -i 's/^PresetIndex=.*/PresetIndex=1/'            "${CONFIG_DIR}/PCSX2_ui.ini"
        sed -i 's/UserHacks =.*/UserHacks = 1/'              "${CONFIG_DIR}/GS.ini"
        sed -i 's/^vsync =.*/vsync = 1/'                     "${CONFIG_DIR}/GS.ini"
        ;;
    balanced)
        sed -i 's/^EnablePresets=.*/EnablePresets=enabled/'  "${CONFIG_DIR}/PCSX2_ui.ini"
        sed -i 's/^PresetIndex=.*/PresetIndex=2/'            "${CONFIG_DIR}/PCSX2_ui.ini"
        sed -i 's/UserHacks =.*/UserHacks = 1/'              "${CONFIG_DIR}/GS.ini"
        sed -i 's/^vsync =.*/vsync = 1/'                     "${CONFIG_DIR}/GS.ini"
        ;;
    aggressive)
        sed -i 's/^EnablePresets=.*/EnablePresets=disabled/' "${CONFIG_DIR}/PCSX2_ui.ini"
        sed -i 's/^EECycleRate=.*/EECycleRate=-1/'           "${CONFIG_DIR}/PCSX2_vm.ini"
        sed -i 's/^EECycleSkip=.*/EECycleSkip=0/'            "${CONFIG_DIR}/PCSX2_vm.ini"
        sed -i 's/^fastCDVD=.*/fastCDVD=disabled/'           "${CONFIG_DIR}/PCSX2_vm.ini"
        sed -i 's/^IntcStat=.*/IntcStat=enabled/'            "${CONFIG_DIR}/PCSX2_vm.ini"
        sed -i 's/^WaitLoop=.*/WaitLoop=enabled/'            "${CONFIG_DIR}/PCSX2_vm.ini"
        sed -i 's/^vuFlagHack=.*/vuFlagHack=enabled/'        "${CONFIG_DIR}/PCSX2_vm.ini"
        sed -i 's/^vuThread=.*/vuThread=enabled/'            "${CONFIG_DIR}/PCSX2_vm.ini"
        sed -i 's/^vu1Instant=.*/vu1Instant=enabled/'        "${CONFIG_DIR}/PCSX2_vm.ini"
        sed -i 's/UserHacks =.*/UserHacks = 1/'              "${CONFIG_DIR}/GS.ini"
        sed -i 's/^vsync =.*/vsync = 1/'                     "${CONFIG_DIR}/GS.ini"
        ;;
    vaggressive)
        sed -i 's/^EnablePresets=.*/EnablePresets=disabled/' "${CONFIG_DIR}/PCSX2_ui.ini"
        sed -i 's/^EECycleRate=.*/EECycleRate=-2/'           "${CONFIG_DIR}/PCSX2_vm.ini"
        sed -i 's/^EECycleSkip=.*/EECycleSkip=0/'            "${CONFIG_DIR}/PCSX2_vm.ini"
        sed -i 's/^fastCDVD=.*/fastCDVD=disabled/'           "${CONFIG_DIR}/PCSX2_vm.ini"
        sed -i 's/^IntcStat=.*/IntcStat=enabled/'            "${CONFIG_DIR}/PCSX2_vm.ini"
        sed -i 's/^WaitLoop=.*/WaitLoop=enabled/'            "${CONFIG_DIR}/PCSX2_vm.ini"
        sed -i 's/^vuFlagHack=.*/vuFlagHack=enabled/'        "${CONFIG_DIR}/PCSX2_vm.ini"
        sed -i 's/^vuThread=.*/vuThread=enabled/'            "${CONFIG_DIR}/PCSX2_vm.ini"
        sed -i 's/^vu1Instant=.*/vu1Instant=enabled/'        "${CONFIG_DIR}/PCSX2_vm.ini"
        sed -i 's/UserHacks =.*/UserHacks = 1/'              "${CONFIG_DIR}/GS.ini"
        sed -i 's/^vsync =.*/vsync = 1/'                     "${CONFIG_DIR}/GS.ini"
        ;;
    mharmful)
        sed -i 's/^EnablePresets=.*/EnablePresets=disabled/' "${CONFIG_DIR}/PCSX2_ui.ini"
        sed -i 's/^EECycleRate=.*/EECycleRate=1/'            "${CONFIG_DIR}/PCSX2_vm.ini"
        sed -i 's/^EECycleSkip=.*/EECycleSkip=1/'            "${CONFIG_DIR}/PCSX2_vm.ini"
        sed -i 's/^fastCDVD=.*/fastCDVD=disabled/'           "${CONFIG_DIR}/PCSX2_vm.ini"
        sed -i 's/^IntcStat=.*/IntcStat=enabled/'            "${CONFIG_DIR}/PCSX2_vm.ini"
        sed -i 's/^WaitLoop=.*/WaitLoop=enabled/'            "${CONFIG_DIR}/PCSX2_vm.ini"
        sed -i 's/^vuFlagHack=.*/vuFlagHack=enabled/'        "${CONFIG_DIR}/PCSX2_vm.ini"
        sed -i 's/^vuThread=.*/vuThread=enabled/'            "${CONFIG_DIR}/PCSX2_vm.ini"
        sed -i 's/^vu1Instant=.*/vu1Instant=enabled/'        "${CONFIG_DIR}/PCSX2_vm.ini"
        sed -i 's/UserHacks =.*/UserHacks = 1/'              "${CONFIG_DIR}/GS.ini"
        sed -i 's/^vsync =.*/vsync = 0/'                     "${CONFIG_DIR}/GS.ini"
        ;;
esac

################################################################################

### RUN

if [ -e "${ROM}" ]; then
    ${EMU_DIR}/PCSX2 \
        --nogui \
        --fullscreen \
        ${FULLBOOT} \
        ${CUSTOM_INIS} \
        "${ROM}" > ${HOME}/logs/pcsx2-mainline.log 2>&1
else
    ${EMU_DIR}/PCSX2 > "${HOME}/logs/pcsx2-mainline.log" 2>&1
fi

################################################################################

exit 0
