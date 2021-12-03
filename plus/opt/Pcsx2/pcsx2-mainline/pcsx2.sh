#!/bin/bash
##
## Batocera.PLUS
##
## Código escrito por: Sérgio de Carvalho Júnior
## Supervisão: Alexandre Freire dos Santos
## https://forums.pcsx2.net/Thread-PCSX2-Widescreen-Game-Patches?pid=271674#pid271674
## https://www.mediafire.com/file/j48lgoeeli5evve/PCSX_Cheats_Pack_v1.1_-_Mateus_Auri.rar/file
################################################################################

### DIRECTORIES, FILES AND PARAMETERS

ROM="${1}"
RESOLUTION="${2}"  #videomode
WIDESCREEN="${3}"  #ratio
BOOTANIM="${4}"    #fullboot
I_RES="${5}"       #internal_resolution
A_FILT="${6}"      #anisotropic_filtering
WSCRH="${7}"       #widescreen hack
PRESET="${8}"      #speed hacks

echo "${ROM}" "${RESOLUTION}" "${WIDESCREEN}" "${BOOTANIM}" "${I_RES}" "${A_FILT}" "${WSCRH}" "${PRESET}" > "${HOME}/../PARAMETROS.TXT"

#exit 0

EMU_DIR='/opt/Pcsx2/pcsx2-mainline'
SAVE_DIR='/userdata/saves/ps2'
CONFIG_DIR="${HOME}/configs/pcsx2-mainline"

### EXPORTS

export LD_LIBRARY_PATH="${EMU_DIR}/lib:${EMU_DIR}:${LD_LIBRARY_PATH}"
export GDK_PIXBUF_MODULEDIR='/usr/lib/gdk-pixbuf-2.0/2.10.0/loaders'
export GDK_PIXBUF_MODULE_FILE='/usr/lib/gdk-pixbuf-2.0/2.10.0/loaders.cache'
export GDK_BACKEND=x11
export GSETTINGS_SCHEMA_DIR="${EMU_DIR}/schemas"

################################################################################

function CreateDirs()
{
 # Create folders to batocera.plus pcsx2
 mkdir -p "${HOME}/logs/pcsx2-mainline"
 DIRS='memcards cheats cheats_ws sstates-mainline custom-inis-mainline'
 for i in ${DIRS}; do
   if [ ! -e "${SAVE_DIR}/${i}" ]; then
      mkdir -p "${SAVE_DIR}/${i}"
   fi 
 done
 
 # Memcards from pcsx2 libretro
 if [ -f "${SAVE_DIR}/pcsx2/slot1/Shared Memory Card (8 MB).ps2" ] ; then
     ln -s "${SAVE_DIR}/pcsx2/slot1/Shared Memory Card (8 MB).ps2" "${SAVE_DIR}/pcsx2/memcards/Mcd001.ps2"
 else
     touch "${SAVE_DIR}/pcsx2/slot1/Shared Memory Card (8 MB).ps2"
     ln -s "${SAVE_DIR}/pcsx2/slot1/Shared Memory Card (8 MB).ps2" "${SAVE_DIR}/pcsx2/memcards/Mcd001.ps2"
 fi
 
 if [ -f "${SAVE_DIR}/pcsx2/slot2/Shared Memory Card (8 MB).ps2" ] ; then
     ln -s "${SAVE_DIR}/pcsx2/slot2/Shared Memory Card (8 MB).ps2" "${SAVE_DIR}/pcsx2/memcards/Mcd002.ps2"
 else
     touch "${SAVE_DIR}/pcsx2/slot2/Shared Memory Card (8 MB).ps2"
     ln -s "${SAVE_DIR}/pcsx2/slot2/Shared Memory Card (8 MB).ps2" "${SAVE_DIR}/pcsx2/memcards/Mcd002.ps2"
 fi
 
}

function CreateInis()
{
 mkdir -p "${CONFIG_DIR}"
 
 touch "${CONFIG_DIR}/PCSX2_ui.ini"
 echo 'PresetIndex=1'      >> "${CONFIG_DIR}/PCSX2_ui.ini"
 echo '[Filenames]'        >> "${CONFIG_DIR}/PCSX2_ui.ini"
 echo 'BIOS=scph39001.bin' >> "${CONFIG_DIR}/PCSX2_ui.ini"
 echo '[ProgramLog]'       >> "${CONFIG_DIR}/PCSX2_ui.ini"
 echo 'Visible=disabled'   >> "${CONFIG_DIR}/PCSX2_ui.ini"
 echo '[GSWindow]'         >> "${CONFIG_DIR}/PCSX2_ui.ini"
 echo 'AspectRatio=4:3'    >> "${CONFIG_DIR}/PCSX2_ui.ini"

 touch "${CONFIG_DIR}/GS.ini"
 echo 'vsync = 0'              >> "${CONFIG_DIR}/GS.ini"
 echo 'upscale_multiplier = 1' >> "${CONFIG_DIR}/GS.ini"
 echo 'MaxAnisotropy = 0'      >> "${CONFIG_DIR}/GS.ini"
 echo 'UserHacks = 0'          >> "${CONFIG_DIR}/GS.ini"

 touch "${CONFIG_DIR}/PCSX2_vm.ini"
 echo '[EmuCore]'                        >> "${CONFIG_DIR}/PCSX2_vm.ini"
 echo 'EnableWideScreenPatches=disabled' >> "${CONFIG_DIR}/PCSX2_vm.ini"
 echo '[EmuCore/Speedhacks]'             >> "${CONFIG_DIR}/PCSX2_vm.ini"
 echo 'EECycleRate=0'                    >> "${CONFIG_DIR}/PCSX2_vm.ini"
 echo 'EECycleSkip=0'                    >> "${CONFIG_DIR}/PCSX2_vm.ini"
 echo 'fastCDVD=disabled'                >> "${CONFIG_DIR}/PCSX2_vm.ini"
 echo 'IntcStat=enabled'                 >> "${CONFIG_DIR}/PCSX2_vm.ini"
 echo 'WaitLoop=enabled'                 >> "${CONFIG_DIR}/PCSX2_vm.ini"
 echo 'vuFlagHack=enabled'               >> "${CONFIG_DIR}/PCSX2_vm.ini"
 echo 'vuThread=disabled'                >> "${CONFIG_DIR}/PCSX2_vm.ini"
 echo 'vu1Instant=enabled'               >> "${CONFIG_DIR}/PCSX2_vm.ini"

 touch "${CONFIG_DIR}/PAD.ini"
 echo 'first_time_wizard = 0'  >> "${CONFIG_DIR}/PAD.ini"
 echo 'options = 1'            >> "${CONFIG_DIR}/PAD.ini"
}

################################################################################

if [ ! "$(ls -A "${HOME}/configs/pcsx2-mainline"  2> /dev/null)" ]; then
   CreateInis
fi

if [ ! "$(ls -A "${SAVE_DIR}/custom-inis-mainline" 2> /dev/null)" ]; then
   CreateDirs
fi

################################################################################

### PERGAME CONFIG

if [ "${CUSTOM}" == '1' ]; then
   if [ ! "$(ls -A "${HOME}/configs/pcsx2-mainline"  2> /dev/null)" ]; then
      CreateDirs
      CreateInis
   fi
   GAME_NAME="${SAVE_DIR}/custom-inis-mainline/$(basename "${ROM%.*}" )"
   mkdir -p "${SAVE_DIR}/custom-inis-mainline/$(basename "${ROM%.*}" )"
   cp -r -f "${HOME}/configs/pcsx2-mainline/"* "${SAVE_DIR}/custom-inis-mainline/${GAME_NAME}"
   INIS="--cfgpath ${SAVE_DIR}/custom-inis-mainline/${GAME_NAME}"
fi

################################################################################

### FULLBOOT

if [ "${BOOTANIM}" == '1' ] || [ "${BOOTANIM}" == 'auto' ]; then
   FULLBOOT='--fullboot'
fi

################################################################################

### WIDESCREEN

case "${WIDESCREEN}" in
    4/3|1/1|16/15|3/2|3/4|4/4|5/4|6/5|7/9|8/7|auto|custom|squarepixel)
        sed -i s/'^AspectRatio=.*/AspectRatio=4:3/'  "${CONFIG_DIR}/PCSX2_ui.ini" ;;
    16/9|19/12|19/14|2/1|21/9|30/17|32/9|4/1|8/3)
        sed -i s/'^AspectRatio=.*/AspectRatio=16:9/' "${CONFIG_DIR}/PCSX2_ui.ini" ;;
esac

################################################################################

### VSYNC

if [ "${VSYNC}" == '1' ] || [ "${VSYNC}" == 'auto' ]; then
   sed -i s/'^vsync =.*/vsync = 1/' "${CONFIG_DIR}/GS.ini"
else
   sed -i s/'^vsync =.*/vsync = 0/' "${CONFIG_DIR}/GS.ini"
fi

################################################################################

### INTERNAL RESOLUTION

if [ "${I_RES}" != 'auto' ]; then
   sed -i s/'^upscale_multiplier =.*/upscale_multiplier = '"${I_RES}"'/' "${CONFIG_DIR}/GS.ini"
else
   sed -i s/'^upscale_multiplier =.*/upscale_multiplier = 1/' "${CONFIG_DIR}/GS.ini"
fi

################################################################################

### WIDE SCREEN HACK

if [ "${WSCRH}" == '0' ] || [ "${WSCRH}" == 'auto' ]; then
   sed -i s/'^EnableWideScreenPatches=.*/EnableWideScreenPatches=disabled/' "${CONFIG_DIR}/PCSX2_vm.ini"
else
   sed -i s/'^EnableWideScreenPatches=.*/EnableWideScreenPatches=enabled/' "${CONFIG_DIR}/PCSX2_vm.ini"
fi

################################################################################

### ANISOTROPIC FILTERING

if [ "${A_FILT}" != 'auto' ]; then
   sed -i s/'^MaxAnisotropy =.*/MaxAnisotropy = '"${A_FILT}"'/' "${CONFIG_DIR}/GS.ini"
else
   sed -i s/'^MaxAnisotropy =.*/MaxAnisotropy = 0/' "${CONFIG_DIR}/GS.ini"
fi

################################################################################

### SPEED HACKS

case ${PRESET} in
   safest)
      sed -i s/'^EnablePresets=.*/EnablePresets=enabled/' "${CONFIG_DIR}/PCSX2_ui.ini"
      sed -i s/'^PresetIndex=.*/PresetIndex=0/'           "${CONFIG_DIR}/PCSX2_ui.ini"
      sed -i s/'^vsync =.*/vsync = 1/'                    "${CONFIG_DIR}/GS.ini"
      ;;
   default|auto)
      sed -i s/'^EnablePresets=.*/EnablePresets=enabled/' "${CONFIG_DIR}/PCSX2_ui.ini"
      sed -i s/'^PresetIndex=.*/PresetIndex=1/'           "${CONFIG_DIR}/PCSX2_ui.ini"
      sed -i s/'^vsync =.*/vsync = 1/'                    "${CONFIG_DIR}/GS.ini"
      ;;
   balanced)
      sed -i s/'^EnablePresets=.*/EnablePresets=enabled/' "${CONFIG_DIR}/PCSX2_ui.ini"
      sed -i s/'^PresetIndex=.*/PresetIndex=2/'           "${CONFIG_DIR}/PCSX2_ui.ini"
      sed -i s/'^vsync =.*/vsync = 1/'                    "${CONFIG_DIR}/GS.ini"
      ;;
   aggressive)
      sed -i s/'^EnablePresets=.*/EnablePresets=disabled/' "${CONFIG_DIR}/PCSX2_ui.ini"
      sed -i s/'UserHacks =.*/UserHacks = 1/'              "${CONFIG_DIR}/GS.ini"
      sed -i s/'^vsync =.*/vsync = 0/'                     "${CONFIG_DIR}/GS.ini"
      sed -i s/'^EECycleRate=.*/EECycleRate=-1/'           "${CONFIG_DIR}/PCSX2_vm.ini"
      sed -i s/'^EECycleSkip=.*/EECycleSkip=0/'            "${CONFIG_DIR}/PCSX2_vm.ini"
      sed -i s/'^fastCDVD=.*/fastCDVD=disabled/'           "${CONFIG_DIR}/PCSX2_vm.ini"
      sed -i s/'^IntcStat=.*/IntcStat=enabled/'            "${CONFIG_DIR}/PCSX2_vm.ini"
      sed -i s/'^WaitLoop=.*/WaitLoop=enabled/'            "${CONFIG_DIR}/PCSX2_vm.ini"
      sed -i s/'^vuFlagHack=.*/vuFlagHack=enabled/'        "${CONFIG_DIR}/PCSX2_vm.ini"
      sed -i s/'^vuThread=.*/vuThread=enabled/'            "${CONFIG_DIR}/PCSX2_vm.ini"
      sed -i s/'^vu1Instant=.*/vu1Instant=enabled/'        "${CONFIG_DIR}/PCSX2_vm.ini"
      ;;
   vaggressive)
      sed -i s/'^EnablePresets=.*/EnablePresets=disabled/' "${CONFIG_DIR}/PCSX2_ui.ini"
      sed -i s/'UserHacks =.*/UserHacks = 1/'              "${CONFIG_DIR}/GS.ini"
      sed -i s/'^vsync =.*/vsync = 0/'                     "${CONFIG_DIR}/GS.ini"
      sed -i s/'^EECycleRate=.*/EECycleRate=-2/'           "${CONFIG_DIR}/PCSX2_vm.ini"
      sed -i s/'^EECycleSkip=.*/EECycleSkip=0/'            "${CONFIG_DIR}/PCSX2_vm.ini"
      sed -i s/'^fastCDVD=.*/fastCDVD=disabled/'           "${CONFIG_DIR}/PCSX2_vm.ini"
      sed -i s/'^IntcStat=.*/IntcStat=enabled/'            "${CONFIG_DIR}/PCSX2_vm.ini"
      sed -i s/'^WaitLoop=.*/WaitLoop=enabled/'            "${CONFIG_DIR}/PCSX2_vm.ini"
      sed -i s/'^vuFlagHack=.*/vuFlagHack=enabled/'        "${CONFIG_DIR}/PCSX2_vm.ini"
      sed -i s/'^vuThread=.*/vuThread=enabled/'            "${CONFIG_DIR}/PCSX2_vm.ini"
      sed -i s/'^vu1Instant=.*/vu1Instant=enabled/'        "${CONFIG_DIR}/PCSX2_vm.ini"
      ;;
   mharmful)
      sed -i s/'^EnablePresets=.*/EnablePresets=disabled/' "${CONFIG_DIR}/PCSX2_ui.ini"
      sed -i s/'UserHacks =.*/UserHacks = 1/'              "${CONFIG_DIR}/GS.ini"
      sed -i s/'^vsync =.*/vsync = 0/'                     "${CONFIG_DIR}/GS.ini"
      sed -i s/'^EECycleRate=.*/EECycleRate=1/'            "${CONFIG_DIR}/PCSX2_vm.ini"
      sed -i s/'^EECycleSkip=.*/EECycleSkip=1/'            "${CONFIG_DIR}/PCSX2_vm.ini"
      sed -i s/'^fastCDVD=.*/fastCDVD=disabled/'           "${CONFIG_DIR}/PCSX2_vm.ini"
      sed -i s/'^IntcStat=.*/IntcStat=enabled/'            "${CONFIG_DIR}/PCSX2_vm.ini"
      sed -i s/'^WaitLoop=.*/WaitLoop=enabled/'            "${CONFIG_DIR}/PCSX2_vm.ini"
      sed -i s/'^vuFlagHack=.*/vuFlagHack=enabled/'        "${CONFIG_DIR}/PCSX2_vm.ini"
      sed -i s/'^vuThread=.*/vuThread=enabled/'            "${CONFIG_DIR}/PCSX2_vm.ini"
      sed -i s/'^vu1Instant=.*/vu1Instant=enabled/'        "${CONFIG_DIR}/PCSX2_vm.ini"
      ;;
esac

################################################################################
### RUN

if [ -e "${ROM}" ]; then
   $MANGOHUD_CMD $EMU_DIR/PCSX2 \
        --nogui \
        --fullscreen \
        $FULLBOOT \
        "${ROM}" > $HOME/logs/pcsx2-mainline.log 2>&1
else
   $EMU_DIR/PCSX2 > $HOME/logs/pcsx2-mainline.log 2>&1
fi

################################################################################

exit 0
