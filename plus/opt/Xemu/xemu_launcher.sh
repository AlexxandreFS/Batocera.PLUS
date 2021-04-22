#!/bin/bash
##
## Batocera.PLUS
##
## Código escrito por: Sérgio de Carvalho Júnior
## 
################################################################################

# external variables
ROM="${1}"
P1GUID="${2}"
P2GUID="${3}"
P3GUID="${4}"
P4GUID="${5}"
RESOLUTION="${6}"
SCALING="${7}"

#local variables
BIOS='/userdata/bios'
SAVES='/userdata/saves/xbox'
FILES='/opt/Xemu'
export XDG_CONFIG_HOME="${HOME}/configs/xemu"

# "batocera.files"
function CreateConfigs()
{    
   # copy the hdd if it doesn't exist
   if [ ! -d "${HOME}/../saves/xbox/xbox_hdd.qcow2" ]; then
       mkdir -p "${HOME}/../saves/xbox"
       cp -f  "${FILES}/xbox_hdd.qcow2" "${HOME}/../saves/xbox"
   fi
   
   # save the ini file
   if [ ! -f "${HOME}/configs/xemu/xemu.ini" ]; then
       mkdir -p "${HOME}/configs/xemu"
       touch "${HOME}/configs/xemu/xemu.ini"
   
       # Fill system section
       echo '[system]'                                             >> "${HOME}/configs/xemu/xemu.ini"
       echo 'flash_path = '"${BIOS}/Complex_4627.bin"''            >> "${HOME}/configs/xemu/xemu.ini"
       echo 'bootrom_path = '"${BIOS}/mcpx_1.0.bin"''              >> "${HOME}/configs/xemu/xemu.ini"
       echo 'hdd_path = '"${SAVES}/xbox_hdd.qcow2"''               >> "${HOME}/configs/xemu/xemu.ini"
       echo 'eeprom_path = '"${SAVES}/xbox/xemu_eeprom.bin"''      >> "${HOME}/configs/xemu/xemu.ini"
       echo 'dvd_path = '                                          >> "${HOME}/configs/xemu/xemu.ini"
       echo 'memory = 64'                                          >> "${HOME}/configs/xemu/xemu.ini"
       echo 'shortanim = false'                                    >> "${HOME}/configs/xemu/xemu.ini"
       echo 'hard_fpu = true'                                      >> "${HOME}/configs/xemu/xemu.ini"

       # Fill audio section
       echo '[audio]'                                              >> "${HOME}/configs/xemu/xemu.ini"
       echo 'use_dsp = false'                                      >> "${HOME}/configs/xemu/xemu.ini"

       # Fill display section
       echo '[display]'                                            >> "${HOME}/configs/xemu/xemu.ini"
       echo 'scale = scale'                                        >> "${HOME}/configs/xemu/xemu.ini"
       echo 'ui_scale = 1'                                         >> "${HOME}/configs/xemu/xemu.ini"

       # Fill input section
       echo '[input]'                                              >> "${HOME}/configs/xemu/xemu.ini"
       echo 'controller_1_guid = '"${P1GUID}"''                    >> "${HOME}/configs/xemu/xemu.ini"
       echo 'controller_2_guid = '"${P2GUID}"''                    >> "${HOME}/configs/xemu/xemu.ini"
       echo 'controller_3_guid = '"${P3GUID}"''                    >> "${HOME}/configs/xemu/xemu.ini"
       echo 'controller_4_guid = '"${P4GUID}"''                    >> "${HOME}/configs/xemu/xemu.ini"

       # Fill network section
       echo '[network]'                                            >> "${HOME}/configs/xemu/xemu.ini"
       echo 'enabled = false'                                      >> "${HOME}/configs/xemu/xemu.ini"
       echo 'backend = user'                                       >> "${HOME}/configs/xemu/xemu.ini"
       echo 'local_addr = 0.0.0.0:9368'                            >> "${HOME}/configs/xemu/xemu.ini"
       echo 'remote_addr = 1.2.3.4:9368'                           >> "${HOME}/configs/xemu/xemu.ini"

       # Fill misc section
       echo '[misc]'                                               >> "${HOME}/configs/xemu/xemu.ini"
       echo 'user_token = '                                        >> "${HOME}/configs/xemu/xemu.ini"
   fi
}

# Create config dirs and files
if [ ! "$(ls -A "${HOME}/../saves/xbox/xbox_hdd.qcow2" 2> /dev/null)" ] || [ ! "$(ls -A "${HOME}/configs/xemu/xemu.ini"  2> /dev/null)" ]; then
    CreateConfigs
fi

# hotkey
BOTOES="$(/opt/Xemu/getHotkeyStart "${P1GUID}")"
BOTAO_HOTKEY="$(echo "${BOTOES}" | cut -d ' ' -f 1)"
BOTAO_START="$(echo "${BOTOES}"  | cut -d ' ' -f 2)"

if [ "${BOTAO_HOTKEY}" ] && [ "${BOTAO_START}" ]; then
    # Impede que o xjoykill seja encerrado enquanto o jogo está em execução.
    while : ; do
        nice -n 20 xjoykill -hotkey "${BOTAO_HOTKEY}" -start "${BOTAO_START}" -kill /opt/Xemu/killxemu
        if ! [ "$(pidof xemu)" ]; then
              break
        fi
        sleep 5
    done &
fi

# resolution
RES_START="$(batocera-resolution currentResolution)"
if [ "${RESOLUTION}" != 'auto' ]; then
    batocera-resolution setMode "${RESOLUTION}"
fi

# scale
case $SCALING in
        center)  sed -i "s|^scale = .*|scale = ${SCALING}|"   "${HOME}/configs/xemu/xemu.ini" ;;
        scale)   sed -i "s|^scale = .*|scale = ${SCALING}|"   "${HOME}/configs/xemu/xemu.ini" ;;
        stretch) sed -i "s|^scale = .*|scale = ${SCALING}|"   "${HOME}/configs/xemu/xemu.ini" ;;
        *)       sed -i "s|^scale = .*|scale = scale|"        "${HOME}/configs/xemu/xemu.ini" ;;
esac

# launch game
sed -i "s|^dvd_path = .*|dvd_path = ${ROM}|"                        "${HOME}/configs/xemu/xemu.ini"
sed -i "s|^controller_1_guid = .*|controller_1_guid = ${P1GUID}|"   "${HOME}/configs/xemu/xemu.ini"
sed -i "s|^controller_2_guid = .*|controller_2_guid = ${P2GUID}|"   "${HOME}/configs/xemu/xemu.ini"
sed -i "s|^controller_3_guid = .*|controller_3_guid = ${P3GUID}|"   "${HOME}/configs/xemu/xemu.ini"
sed -i "s|^controller_4_guid = .*|controller_4_guid = ${P4GUID}|"   "${HOME}/configs/xemu/xemu.ini"

xemu -config_path "${HOME}/configs/xemu/xemu.ini"

# restore resolution if changed
RES_STOP="$(batocera-resolution currentResolution)"
if [ "${RES_START}" != "${RES_STOP}" ]; then
    batocera-resolution setMode "${RES_START}"
fi

exit 0
