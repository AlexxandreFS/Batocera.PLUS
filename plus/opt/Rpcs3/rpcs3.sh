#!/bin/bash
###
### Batocera.PLUS
### Sérgio de Carvalho Júnior
### Alexandre Freire dos Santos
################################################################################

### DIRECTORIES, FILES AND PARAMETERS

GAME="${1}"

MAINLINE_DIR=/opt/Rpcs3
MAINLINE_SAVE_DIR="${HOME}/../saves/ps3"
RPCS3_CONFIG_DIR="${HOME}/configs/rpcs3"
MAINLINE_CACHE_DIR="${HOME}/../saves/rpcs3_mainline"

if [ "$(pidof rpcs3)" ]; then
    echo ' RPCS3 launcher já está em execução'
    exit 1
fi

################################################################################

### FUNCTIONS

function CreateFolders()
{
    mkdir -p "${MAINLINE_SAVE_DIR}/.config/rpcs3/GuiConfigs" \
             "${MAINLINE_SAVE_DIR}/.config/rpcs3/dev_hdd0/home/00000001" \
             "${MAINLINE_SAVE_DIR}/dev_hdd0/home/00000001/savedata" \
             "${MAINLINE_SAVE_DIR}/dev_hdd0/home/00000001/trophy" \
             "${MAINLINE_SAVE_DIR}/dev_hdd0/home/00000001/exdata" \
             "${MAINLINE_SAVE_DIR}/dev_hdd0/game" \
             "${MAINLINE_SAVE_DIR}/dev_flash" \
             "${MAINLINE_CACHE_DIR}"

    ln -sf "${MAINLINE_SAVE_DIR}/dev_hdd0/home/00000001/savedata" "${MAINLINE_SAVE_DIR}/.config/rpcs3/dev_hdd0/home/00000001"
    ln -sf "${MAINLINE_SAVE_DIR}/dev_hdd0/home/00000001/trophy"   "${MAINLINE_SAVE_DIR}/.config/rpcs3/dev_hdd0/home/00000001"
    ln -sf "${MAINLINE_SAVE_DIR}/dev_hdd0/home/00000001/exdata"   "${MAINLINE_SAVE_DIR}/.config/rpcs3/dev_hdd0/home/00000001"
    ln -sf "/usr/share/rpcs3/GuiConfigs/"*                        "${MAINLINE_SAVE_DIR}/.config/rpcs3/GuiConfigs"
    ln -sf "${MAINLINE_SAVE_DIR}/dev_hdd0/game"                   "${MAINLINE_SAVE_DIR}/.config/rpcs3/dev_hdd0/"
    ln -sf /usr/share/rpcs3/Icons                                 "${MAINLINE_SAVE_DIR}/.config/rpcs3"
    ln -sf "${MAINLINE_SAVE_DIR}/dev_flash"                       "${MAINLINE_SAVE_DIR}/.config/rpcs3"
}

function CreateConfigs()
{
    if [ ! -f "${MAINLINE_SAVE_DIR}/.config/rpcs3/GuiConfigs/CurrentSettings.ini" ]; then
       (echo '[GameList]'
        echo 'hidden_list=@Invalid()'
        echo 'iconColor=@Variant(\0\0\0\x43\x1\xff\xff\xf0\xf0\xf0\xf0\xf0\xf0\0\0)'
        echo 'marginFactor=0.09'
        echo 'textFactor=2'
        echo '[Localization]'
        echo 'language=en'
        echo '[Meta]'
        echo 'checkUpdateStart=false'
        echo 'currentStylesheet=Skyline'
        echo 'showDebugTab=true'
        echo 'useRichPresence=false'
        echo 'discordState='
        echo '[Logger]'
        echo 'level=4'
        echo 'stack=true'
        echo '[main_window]'
        echo 'confirmationBoxExitGame=false'
        echo 'infoBoxEnabledInstallPUP=false'
        echo 'infoBoxEnabledWelcome=false'
        echo 'lastExplorePathPUP=/userdata/system/../bios') > "${MAINLINE_SAVE_DIR}/.config/rpcs3/GuiConfigs/CurrentSettings.ini"
    fi

    if [ ! -f "${MAINLINE_SAVE_DIR}/.config/rpcs3/config.yml" ]; then
       (echo 'Miscellaneous:'
        echo '  Exit RPCS3 when process finishes: true'
        echo '  Start games in fullscreen mode: true') > "${MAINLINE_SAVE_DIR}/.config/rpcs3/config.yml"
    fi
}

function TextLocalization()
{
    local SYSTEM_LANG="$(echo "${LANG}" | cut -d '.' -f 1)"

    case ${SYSTEM_LANG} in
        pt_BR)
            MSG[1]='\n NENHUMA CONFIGURAÇÃO DE CONTROLE FOI FEITA, FAÇA UMA ANTES DE EXECUTAR O JOGO. \n'
            MSG[2]='\n NENHUM FIRMWARE FOI INSTALADO, INSTALE ANTES DE EXECUTAR O JOGO. \n'
            MSG[3]='\n ESCOLHA UMA OPÇÃO. \n'
            ;;
        es_ES)
            MSG[1]='\n NO SE HAN REALIZADO AJUSTES DE CONTROL, HAGA UNO ANTES DE EJECUTAR EL JUEGO. \n'
            MSG[2]='\n NO SE HA INSTALADO FIRMWARE, INSTALAR ANTES DE EJECUTAR UN JUEGO. \n'
            MSG[3]='\n ESCOGE UNA OPCIÓN. \n'
            ;;
        *)
            MSG[1]='\n NO CONTROLLER CONFIG HAS BEEN MADE, MAKE ONE BEFORE RUN A GAME.\n'
            MSG[2]='\n NO FIRMWARE HAS BEEN INSTALLED, INSTALL BEFORE RUN A GAME. \n'
            MSG[3]='\n CHOOSE A OPTION. \n'
    esac
}

function ControllerWarning()
{
    yad --form \
        --title='WARNING' \
        --window-icon='/usr/share/icons/batocera/rpcs3.png' \
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

function FirmwareWarning()
{
    yad --form \
        --title='WARNING' \
        --window-icon='/usr/share/icons/batocera/rpcs3.png' \
        --text=''"${MSG[2]}"'' \
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

function choseEmu()
{
    yad --form \
        --title='RPCS3 CONFIGURATOR' \
        --window-icon='/usr/share/icons/batocera/rpcs3.png' \
        --text=''"${MSG[3]}"'' \
        --text-align=center \
        --button='RPCS3:0' \
        --button='RPCS3-MAINLINE:1' \
        --fixed \
        --center \
        --close-on-unfocus

    case ${?} in
        0) exec /usr/bin/batocera-config-rpcs3 ;;
        1) GUI='1' ;;
        *) exit 0
    esac
}

################################################################################

### CALL HELP

if [ "${GAME}" == '--help' ]; then
    echo
    echo ' Linha de comando:'
    echo ' rpcs3.sh [ROM]'
    echo
    echo ' ROM          = Caminho do jogo até a pasta do jogo'
    echo

    exit 0
else
    echo
    echo ' RPCS3 launcher for Batocera.PLUS'
    echo
fi

################################################################################

### MENU

if [ ! -e "${GAME}" ] && [ ! -e "${P1GUID}" ]; then
    TextLocalization
    choseEmu
fi

################################################################################

### BUILD FOLDERS AND FILES

# new install
if [ ! "$(ls -A "${MAINLINE_SAVE_DIR}/.config/rpcs3" 2> /dev/null)" ] ||
   [ ! "$(ls -A "${MAINLINE_CACHE_DIR}"              2> /dev/null)" ] ||
   [ ! "$(ls -l "${RPCS3_CONFIG_DIR}"                2> /dev/null)" ]; then
    CreateFolders
    CreateConfigs
fi

# no controller config found warning
if [ ! -f "${MAINLINE_SAVE_DIR}/.config/rpcs3/config_input.yml" ] && [ "${GAME}" ]; then
    TextLocalization
    ControllerWarning
fi

# no firmware found warning
if [ -z "${MAINLINE_SAVE_DIR}/.config/rpcs3/dev_flash/vsh" ] && [ "${GAME}" ]; then
    TextLocalization
    FirmwareWarning
fi

################################################################################

### FORCE SETTINGS

sed -i 's/confirmationBoxExitGame=.*/confirmationBoxExitGame=false/'                   "${MAINLINE_SAVE_DIR}/.config/rpcs3/GuiConfigs/CurrentSettings.ini"
sed -i 's/Exit RPCS3 when process finishes:.*/Exit RPCS3 when process finishes: true/' "${MAINLINE_SAVE_DIR}/.config/rpcs3/config.yml"
sed -i 's/Start games in fullscreen mode:.*/Start games in fullscreen mode: true/'     "${MAINLINE_SAVE_DIR}/.config/rpcs3/config.yml"

################################################################################

### EXPORTS

export HOME="${MAINLINE_SAVE_DIR}"
export LD_LIBRARY_PATH="${MAINLINE_DIR}/lib:${LD_LIBRARY_PATH}"
export XDG_CACHE_HOME="${MAINLINE_CACHE_DIR}"
export XDG_RUNTIME_DIR=/tmp/runtime-root
export QT_PLUGIN_PATH="${MAINLINE_DIR}/plugins"
export QT_QPA_PLATFORM=xcb

################################################################################

### RUN

if [ -e "${GAME}" ]; then
    ${MANGOHUD_CMD} "${MAINLINE_DIR}/bin/rpcs3" "${GAME}/PS3_GAME/USRDIR/EBOOT.BIN" --no-gui
elif [ "${GUI}" ]; then
    "${MAINLINE_DIR}/bin/rpcs3"
fi

exit 0
