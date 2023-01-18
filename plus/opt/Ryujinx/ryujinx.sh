#!/bin/bash
##
## Batocera.PLUS
##
## Código escrito por: Sérgio de Carvalho Júnior
## Colaborador: Alexandre Freire dos Santos
##
## https://discord.com/channels/410208534861447168/790357964749406249/855828176215080960
## https://unix.stackexchange.com/questions/57658/how-to-utilize-xdg-directories-and-paths-in-bash
## https://darthsternie.net/switch-firmwares/
## https://github.com/Ryujinx/Ryujinx/wiki/Ryujinx-Setup-&-Configuration-Guide
## https://emulation.gametechwiki.com/index.php/Shader_caches

################################################################################

### DIRECTORIES, FILES AND PARAMETERS

ROM="${1}"
RENDER="${2}"

RYUJINX_DIR=/opt/Ryujinx
SAVE_DIR=/userdata/saves/switch
BIOS_DIR="${HOME}/../bios/switch"

export LD_LIBRARY_PATH="${RYUJINX_DIR}/lib:${LD_LIBRARY_PATH}"
export XDG_CONFIG_HOME="${SAVE_DIR}"
#export GSETTINGS_SCHEMA_DIR=${RYUJINX_DIR}/gschemas

export DOTNET_SYSTEM_GLOBALIZATION_INVARIANT=1

################################################################################

### CREATE DIRS AND LINKS

function createDirs()
{
    if ! [ -d "${SAVE_DIR}/Ryujinx" ]; then
        # make config dir
        mkdir -p "${SAVE_DIR}/Ryujinx/system" \  # keys folder
                 "${SAVE_DIR}/Ryujinx/bis/system/Contents/registered"
        cp -f "${RYUJINX_DIR}/default_config/Config.json" "${SAVE_DIR}/Ryujinx"
    fi

    # create keys dir
    if [ -f "${BIOS_DIR}/keys/prod.keys" ] && [ -f "${BIOS_DIR}/keys/title.keys" ]; then
        rm -rf "${SAVE_DIR}/Ryujinx/system/"*
        ln -sf "${BIOS_DIR}/keys/"* "${SAVE_DIR}/Ryujinx/system"
    else
        rm -rf "${SAVE_DIR}/Ryujinx/system/"*
    fi
}

################################################################################

### FIRMWARE CHECK

function TextLocalization()
{
   case ${LANG%.*} in
      pt_BR) MSG[1]='\n NENHUM FIRMWARE FOI INSTALADO, INSTALE ANTES DE EXECUTAR O JOGO. \n' ;;
      es_ES) MSG[1]='\n NO SE HA INSTALADO FIRMWARE, INSTALAR ANTES DE EJECUTAR UN JUEGO. \n' ;;
      *)     MSG[1]='\n NO FIRMWARE HAS BEEN INSTALLED, INSTALL BEFORE RUN A GAME. \n'
   esac

   if [ ${LANG%.*} == 'pt_BR' ] || [ ${LANG%.*} == 'es_ES' ]; then
       sed -i 's/"language_code":.*/"language_code": "'"${LANG%.*}"'",/' "${SAVE_DIR}/Ryujinx/Config.json"
   else
       sed -i 's/"language_code":.*/"language_code": "'"${LANG%.*}"'",/' "${SAVE_DIR}/Ryujinx/Config.json"
   fi

}

function FirmwareWarning()
{
   yad --form \
       --title='WARNING' \
       --window-icon='/usr/share/icons/batocera/ryujinx.png' \
       --text=''"${MSG[1]}"'' \
       --undecorated \
       --text-align=center \
       --on-top \
       --fixed \
       --center \
       --no-escape \
       --timeout=3 \
       --no-buttons &

   exit 0
}

if [ -z "$(ls -A "${SAVE_DIR}/Ryujinx/bis/system/Contents/registered" 2> /dev/null)" ] && [ -e "${ROM}" ]; then
    TextLocalization
    FirmwareWarning
fi

################################################################################

### CHECK DIRS

createDirs

################################################################################

### LOCALIZATION

TextLocalization

################################################################################

if [ "${RENDER}" != 'vulkan' ]; then
    sed -i 's/"graphics_backend":.*/"graphics_backend": "OpenGl",/' "${SAVE_DIR}/Ryujinx/Config.json"
else
    sed -i 's/"graphics_backend":.*/"graphics_backend": "Vulkan",/' "${SAVE_DIR}/Ryujinx/Config.json"
fi

################################################################################

### FIX SOME SETTINGS

sed -i 's/"check_updates_on_start":.*/"check_updates_on_start": false,/'         "${SAVE_DIR}/Ryujinx/Config.json"
sed -i 's/"enable_discord_integration":.*/"enable_discord_integration": false,/' "${SAVE_DIR}/Ryujinx/Config.json"
sed -i 's/"show_confirm_exit":.*/"show_confirm_exit": false,/'                   "${SAVE_DIR}/Ryujinx/Config.json"
sed -i 's/"audio_backend":.*/"audio_backend": "OpenAl",/'                        "${SAVE_DIR}/Ryujinx/Config.json"

################################################################################

### EXECUTION

if [ -e "${ROM}" ]; then
   ${MANGOHUD_CMD}  ${RYUJINX_DIR}/publish/Ryujinx --fullscreen "${ROM}"
else
   ${RYUJINX_DIR}/publish/Ryujinx
fi

################################################################################

exit 0
