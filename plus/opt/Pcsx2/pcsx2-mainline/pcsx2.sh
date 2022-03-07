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
CUSTOM="${6}"
API="${7}"         #graphic API

EMU_DIR='/opt/Pcsx2/pcsx2-mainline'
SAVE_DIR='/userdata/saves/ps2'
CONFIG_DIR="${HOME}/configs/pcsx2-mainline"

################################################################################

### EXPORTS

export LD_LIBRARY_PATH="${EMU_DIR}/lib:${LD_LIBRARY_PATH}"

export GDK_PIXBUF_MODULEDIR='/usr/lib/gdk-pixbuf-2.0/2.10.0/loaders'
export GDK_PIXBUF_MODULE_FILE='/usr/lib/gdk-pixbuf-2.0/2.10.0/loaders.cache'

export GSETTINGS_SCHEMA_DIR="${EMU_DIR}/pcsx2_rc/glib-2.0/schemas"

export GDK_BACKEND=x11

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

### CREATE CUSTOM INI FOLDER

function createcustom()
{
  local CUSTOMINIPATCH="${SAVE_DIR}/custom/$(basename "${ROM%.*}")"
  
  if [ ! "$(ls -A "${CUSTOMINIPATCH}" 2> /dev/null)" ]
  then
      mkdir -p "${CUSTOMINIPATCH}"

       if ! [ -e "${CUSTOMINIPATCH}/PCSX2_vm.ini" ]; then
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
           echo 'vu1Instant=enabled') > "${CUSTOMINIPATCH}/PCSX2_vm.ini"
       fi

       if ! [ -e "${CUSTOMINIPATCH}/PCSX2_ui.ini" ]; then
          (echo 'PresetIndex=1'
           echo '[Filenames]'
           echo 'BIOS=scph39001.bin'
           echo '[ProgramLog]'
           echo 'Visible=disabled'
           echo '[GSWindow]'
           echo 'AspectRatio=4:3'
           echo '[MemoryCards]'
           echo 'Slot1_Enable=enabled'
           echo ''Slot1_Filename="$(basename "${ROM%.*}")".ps2'') > "${CUSTOMINIPATCH}/PCSX2_ui.ini"
       fi

       if ! [ -e "${CUSTOMINIPATCH}/GS.ini" ]; then
          (echo 'vsync = 0'
           echo 'upscale_multiplier = 1'
           echo 'MaxAnisotropy = 0'
           echo 'UserHacks = 0') > "${CUSTOMINIPATCH}/GS.ini"
       fi
  
       if ! [ -e "${CUSTOMINIPATCH}/PAD.ini" ]; then
          (echo 'first_time_wizard = 0'
           echo 'options = 1') > "${CUSTOMINIPATCH}/PAD.ini"
       fi
  fi
}

################################################################################

### PERGAME CONFIG

if [ "${CUSTOM}" == '1' ]; then    
    if ! [ -e "${SAVE_DIR}/custom/$(basename "${ROM%.*}")" ]
    then
        createcustom
    fi
    CUSTOM_INIS="${SAVE_DIR}/custom/$(basename "${ROM%.*}")"
fi

#echo "${CUSTOM_INIS}" >> "${HOME}/../PARAMETROS.TXT"

################################################################################

### GRAPHICS API

case ${API} in
    12) sed -i s/'^Renderer =.*/Renderer = 12/'  "${CONFIG_DIR}/GS.ini" ;;
    13) sed -i s/'^Renderer =.*/Renderer = 13/'  "${CONFIG_DIR}/GS.ini" ;;
    14) sed -i s/'^Renderer =.*/Renderer = 14/'  "${CONFIG_DIR}/GS.ini" ;;
    *)  sed -i s/'^Renderer =.*/Renderer = -1/'  "${CONFIG_DIR}/GS.ini"
esac


################################################################################

### RUN

if [ -e "${ROM}" ] && [ -e "${CUSTOM_INIS}" ]
then
    ${EMU_DIR}/PCSX2 --nogui --fullscreen --cfgpath="${CUSTOM_INIS}" \
          ${FULLBOOT} "${ROM}" > ${HOME}/logs/pcsx2-mainline.log 2>&1
elif [ -e "${ROM}" ]
then
    ${EMU_DIR}/PCSX2 --nogui --fullscreen ${FULLBOOT} \
        "${ROM}" > ${HOME}/logs/pcsx2-mainline.log 2>&1
else
    ${EMU_DIR}/PCSX2 > "${HOME}/logs/pcsx2-mainline.log" 2>&1
fi

################################################################################

exit 0
