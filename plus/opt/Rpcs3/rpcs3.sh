#!/bin/bash
###
###
###
###
################################################################################

### DIRECTORIES, FILES AND PARAMETERS

GAME="${1}"
P1GUID="${2}"

RPCS3_DIR=/opt/Rpcs3
HOME_DIR="${HOME}/configs/rpcs3"
SAVE_DIR=/userdata/saves

################################################################################
### FUNCTIONS

function xdg-mime() { :; }

function CreateFolders()
{
   mkdir -p "${HOME_DIR}/.config/rpcs3/GuiConfigs" \
            "${HOME_DIR}/.config/rpcs3/dev_hdd0/home/00000001" \
            "${HOME_DIR}/dev_hdd0/home/00000001/savedata" \
            "${HOME_DIR}/dev_hdd0/home/00000001/trophy" \
            "${HOME_DIR}/dev_hdd0/home/00000001/exdata" \
            "${HOME_DIR}/dev_flash" \
            "${SAVE_DIR}/rpcs3"

   ln -sf "${HOME_DIR}/dev_hdd0/home/00000001/savedata" "${HOME_DIR}/.config/rpcs3/dev_hdd0/home/00000001"
   ln -sf "${HOME_DIR}/dev_hdd0/home/00000001/trophy" "${HOME_DIR}/.config/rpcs3/dev_hdd0/home/00000001"
   ln -sf "${HOME_DIR}/dev_hdd0/home/00000001/exdata" "${HOME_DIR}/.config/rpcs3/dev_hdd0/home/00000001"
   ln -sf "${HOME_DIR}/dev_flash" "${HOME_DIR}/.config/rpcs3"
}

function CreateConfigs()
{
   touch "${HOME_DIR}/.config/rpcs3/GuiConfigs/CurrentSettings.ini" \
         "${HOME_DIR}/.config/rpcs3/config.yml"

   echo '[GameList]' >> "${HOME_DIR}/.config/rpcs3/GuiConfigs/CurrentSettings.ini"
   echo 'hidden_list=@Invalid()' >> "${HOME_DIR}/.config/rpcs3/GuiConfigs/CurrentSettings.ini"
   echo 'iconColor=@Variant(\0\0\0\x43\x1\xff\xff\xf0\xf0\xf0\xf0\xf0\xf0\0\0)' >> "${HOME_DIR}/.config/rpcs3/GuiConfigs/CurrentSettings.ini"
   echo 'marginFactor=0.09' >> "${HOME_DIR}/.config/rpcs3/GuiConfigs/CurrentSettings.ini"
   echo 'textFactor=2' >> "${HOME_DIR}/.config/rpcs3/GuiConfigs/CurrentSettings.ini"
   echo '[Localization]' >> "${HOME_DIR}/.config/rpcs3/GuiConfigs/CurrentSettings.ini"
   echo 'language=en' >> "${HOME_DIR}/.config/rpcs3/GuiConfigs/CurrentSettings.ini"
   echo '[Meta]' >> "${HOME_DIR}/.config/rpcs3/GuiConfigs/CurrentSettings.ini"
   echo 'showDebugTab=true' >> "${HOME_DIR}/.config/rpcs3/GuiConfigs/CurrentSettings.ini"
   echo 'useRichPresence=true' >> "${HOME_DIR}/.config/rpcs3/GuiConfigs/CurrentSettings.ini"
   echo 'discordState=' >> "${HOME_DIR}/.config/rpcs3/GuiConfigs/CurrentSettings.ini"
   echo '[Logger]' >> "${HOME_DIR}/.config/rpcs3/GuiConfigs/CurrentSettings.ini"
   echo 'level=4' >> "${HOME_DIR}/.config/rpcs3/GuiConfigs/CurrentSettings.ini"
   echo 'stack=true' >> "${HOME_DIR}/.config/rpcs3/GuiConfigs/CurrentSettings.ini"
   echo '[main_window]' >> "${HOME_DIR}/.config/rpcs3/GuiConfigs/CurrentSettings.ini"
   echo 'confirmationBoxExitGame=false' >> "${HOME_DIR}/.config/rpcs3/GuiConfigs/CurrentSettings.ini"
   echo 'infoBoxEnabledInstallPUP=false' >> "${HOME_DIR}/.config/rpcs3/GuiConfigs/CurrentSettings.ini"
   echo 'infoBoxEnabledWelcome=false' >> "${HOME_DIR}/.config/rpcs3/GuiConfigs/CurrentSettings.ini"
   echo 'lastExplorePathPUP=/userdata/system/../bios' >> "${HOME_DIR}/.config/rpcs3/GuiConfigs/CurrentSettings.ini"

   echo 'Audio:' >> "${HOME_DIR}/.config/rpcs3/config.yml"
   echo '  Audio Channels: Downmix to Stereo' >> "${HOME_DIR}/.config/rpcs3/config.yml"
   echo '  Renderer: ALSA' >> "${HOME_DIR}/.config/rpcs3/config.yml"
   echo 'Core:' >> "${HOME_DIR}/.config/rpcs3/config.yml"
   echo '  PPU Decoder: Recompiler (LLVM)' >> "${HOME_DIR}/.config/rpcs3/config.yml"
   echo '  PPU LLVM Accurate Vector NaN values: true' >> "${HOME_DIR}/.config/rpcs3/config.yml"
   echo '  SPU Decoder: Recompiler (LLVM)' >> "${HOME_DIR}/.config/rpcs3/config.yml"
   echo 'Miscellaneous:' >> "${HOME_DIR}/.config/rpcs3/config.yml"
   echo '  Exit RPCS3 when process finishes: true' >> "${HOME_DIR}/.config/rpcs3/config.yml"
   echo '  Start games in fullscreen mode: true' >> "${HOME_DIR}/.config/rpcs3/config.yml"
   echo 'Video:' >> "${HOME_DIR}/.config/rpcs3/config.yml"
   echo '  Frame limit: 60' >> "${HOME_DIR}/.config/rpcs3/config.yml"
   echo '  Renderer: Vulkan' >> "${HOME_DIR}/.config/rpcs3/config.yml"
}

function ControllerWarning()
{
   yad --form \
   --title='WARNING' \
   --window-icon='/usr/share/icons/batocera/vpinball.png' \
   --text='\n NO CONTROLLER CONFIG HAS BEEN MADE, MAKE ONE BEFORE RUN A GAME.\n' \
   --undecorated \
   --on-top \
   --fixed \
   --center \
   --no-escape \
   --timeout=3 \
   --no-buttons &
   exit 0
}

function FimwareWarning()
{
   yad --form \
   --title='WARNING' \
   --window-icon='/usr/share/icons/batocera/vpinball.png' \
   --text='\n NO FIRMWARE HAS BEEN INSTALLED, INSTALL BEFORE RUN A GAME.\n' \
   --undecorated \
   --on-top \
   --fixed \
   --center \
   --no-escape \
   --timeout=3 \
   --no-buttons &
   exit 0

}

################################################################################
### EXPORTS

export HOME="${HOME_DIR}"
export LD_LIBRARY_PATH="${RPCS3_DIR}/lib:${LD_LIBRARY_PATH}"
export QT_QPA_PLATFORM=xcb
export QT_PLUGIN_PATH="${RPCS3_DIR}/plugins"
export XDG_RUNTIME_DIR=/run/root
export XDG_CACHE_HOME="${SAVE_DIR}"
export -f xdg-mime

################################################################################
### DIR CHANGE DETECTION

if [ ! "$(ls -A "${HOME_DIR}/.config/rpcs3" 2> /dev/null)" ] || [ ! "$(ls -A "${SAVE_DIR}/rpcs3"  2> /dev/null)" ]; then
   CreateFolders
   CreateConfigs
fi

if [ ! -f "${HOME_DIR}/.config/rpcs3/config_input.yml" ] && [ "${GAME}" != '' ]; then
   ControllerWarning
fi

if [ ! -f "${SAVE_DIR}/rpcs3/cache/ppu-ogZ9XMwLZb70cCsiaswxN1kKG5ts-libpngenc.sprx/v3-kusa-GUaqd0R8vrnMWoH17WjSzY-00000s-haswell.obj.gz" ] && [ "${GAME}" != '' ]; then
   FimwareWarning
fi

################################################################################
### HOTKEY

if [ "${P1GUID}" != '' ]; then
   BOTOES="$(/opt/Wine/getHotkeyStart "${P1GUID}")"
   BOTAO_HOTKEY="$(echo "${BOTOES}" | cut -d ' ' -f 1)"
   BOTAO_START="$(echo "${BOTOES}"  | cut -d ' ' -f 2)"

   if [ "${BOTAO_HOTKEY}" ] && [ "${BOTAO_START}" ]; then
      # Impede que o xjoykill seja encerrado enquanto o jogo está em execução.
      while : ; do
         nice -n 20 xjoykill -hotkey "${BOTAO_HOTKEY}" -start "${BOTAO_START}" -kill /opt/Rpcs3/killrpcs3
         if ! [ "$(pidof rpcs3)" ]; then
            break
         fi
         sleep 5
      done &
   fi

fi

################################################################################
### RUN

if [ "${GAME}" != '' ]; then
   "${RPCS3_DIR}/bin/rpcs3" "${GAME}/PS3_GAME/USRDIR/EBOOT.BIN"
else
   "${RPCS3_DIR}/bin/rpcs3"
fi


################################################################################
### CLOSE XJOYKILL

if [ "$(pidof -s xjoykill)" ]; then
   killall -9 xjoykill
fi

exit 0
