#!/bin/bash
##
## Batocera.PLUS
##
## Código escrito por: Sérgio de Carvalho Júnior
## Supervisão: Alexandre Freire dos Santos
##
################################################################################

### DIRECTORIES, FILES AND PARAMETERS

ROM="${1}"
P1GUID="${2}"
RESOLUTION="${3}"  #videomode
WIDESCREEN="${4}"  #ratio
BOOTANIM="${5}"    #fullboot
I_RES="${6}"       #internal_resolution
A_FILT="${7}"      #anisotropic_filtering
VSYNC="${8}"       #vsync

EMU_DIR='/opt/Pcsx2/pcsx2-mainline'
SAVE_DIR='/userdata/saves/ps2/pcsx2-mainline'

#echo "${ROM}" "${P1GUID}" "${RESOLUTION}" "${WIDESCREEN}" "${BOOTANIM}" "${I_RES}" "${A_FILT}" "${VSYNC}" > "${HOME}/../PARAMETROS.TXT"

#exit 0

### EXPORTS

export LD_LIBRARY_PATH="${EMU_DIR}/lib:${EMU_DIR}:${LD_LIBRARY_PATH}"
export GDK_PIXBUF_MODULEDIR='/usr/lib/gdk-pixbuf-2.0/2.10.0/loaders'
export GDK_PIXBUF_MODULE_FILE='/usr/lib/gdk-pixbuf-2.0/2.10.0/loaders.cache'
export GDK_BACKEND=x11
export GSETTINGS_SCHEMA_DIR="${EMU_DIR}/schemas"

################################################################################

function CreateDirs()
{
 # Create folders to batocera.linux pcsx2
 mkdir -p "${HOME}/configs/PCSX2/cheats" \
          "${HOME}/configs/PCSX2/cheats_ws" \
          "${HOME}/configs/PCSX2/inis" \
          "${HOME}/configs/PCSX2/logs" \
          "${HOME}/configs/PCSX2/memcards"

# Create folders to batocera.plus pcsx2
 mkdir -p "${SAVE_DIR}/inis" \
          "${SAVE_DIR}/snaps" \
          "${SAVE_DIR}/sstates"

 touch "${SAVE_DIR}/inis/PCSX2_ui.ini"
 echo '[Filenames]'        >> "${SAVE_DIR}/inis/PCSX2_ui.ini"
 echo 'BIOS=scph39001.bin' >> "${SAVE_DIR}/inis/PCSX2_ui.ini"
 echo '[ProgramLog]'       >> "${SAVE_DIR}/inis/PCSX2_ui.ini"
 echo 'Visible=disabled'   >> "${SAVE_DIR}/inis/PCSX2_ui.ini"
 echo '[GSWindow]'         >> "${SAVE_DIR}/inis/PCSX2_ui.ini"
 echo 'AspectRatio=4:3'    >> "${SAVE_DIR}/inis/PCSX2_ui.ini"

 touch "${SAVE_DIR}/inis/GS.ini"
 echo 'vsync = 0'              >> "${SAVE_DIR}/inis/GS.ini"
 echo 'upscale_multiplier = 1' >> "${SAVE_DIR}/inis/GS.ini"
 echo 'MaxAnisotropy = 0'      >> "${SAVE_DIR}/inis/GS.ini"
}

################################################################################

if [ ! "$(ls -A "${SAVE_DIR}" 2> /dev/null)" ] || [ ! "$(ls -A "${HOME}/configs/PCSX2"  2> /dev/null)" ]; then
   CreateDirs
fi

################################################################################

# per-game config

mkdir -p "${SAVE_DIR}/custon-configs/$(basename "${ROM%.*}" )"

################################################################################

### FULLBOOT

if [ "${BOOTANIM}" == '1' ] || [ "${BOOTANIM}" == 'auto' ]; then
   FULLBOOT='--fullboot'
fi

################################################################################

### WIDESCREEN

case "${WIDESCREEN}" in
    4/3|1/1|16/15|3/2|3/4|4/4|5/4|6/5|7/9|8/7|auto|custom|squarepixel)
        sed -i s/'^AspectRatio=.*/AspectRatio=4:3/'  "${SAVE_DIR}/inis/PCSX2_ui.ini" ;;
    16/9|19/12|19/14|2/1|21/9|30/17|32/9|4/1|8/3)
        sed -i s/'^AspectRatio=.*/AspectRatio=16:9/' "${SAVE_DIR}/inis/PCSX2_ui.ini" ;;
esac

################################################################################

### VSYNC

if [ "${VSYNC}" == '1' ] || [ "${VSYNC}" == 'auto' ]; then
   sed -i s/'^vsync =.*/vsync = 1 /' "${SAVE_DIR}/inis/GS.ini"
else
   sed -i s/'^vsync =.*/vsync = 0 /' "${SAVE_DIR}/inis/GS.ini"
fi

################################################################################

### INTERNAL RESOLUTION

if [ "${I_RES}" != 'auto' ]; then
   sed -i s/'^upscale_multiplier =.*/upscale_multiplier = '"${I_RES}"'/' "${SAVE_DIR}/inis/GS.ini"
else
   sed -i s/'^upscale_multiplier =.*/upscale_multiplier = 1 /' "${SAVE_DIR}/inis/GS.ini"
fi

################################################################################

### ANISOTROPIC FILTERING

if [ "${A_FILT}" != 'auto' ]; then
   sed -i s/'^MaxAnisotropy =.*/MaxAnisotropy = '"${A_FILT}"'/' "${SAVE_DIR}/inis/GS.ini"
else
   sed -i s/'^MaxAnisotropy =.*/MaxAnisotropy = 0 /' "${SAVE_DIR}/inis/GS.ini"
fi

################################################################################

### RUN

# $EMU_DIR/bin/PCSX2

if [ -e "${ROM}" ]; then
   $MANGOHUD_CMD $EMU_DIR/PCSX2 --fullscreen --nogui $FULLBOOT "${ROM}"
else
   $EMU_DIR/PCSX2
fi

################################################################################

exit 0
