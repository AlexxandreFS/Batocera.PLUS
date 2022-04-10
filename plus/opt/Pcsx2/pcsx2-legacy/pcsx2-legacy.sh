#!/bin/bash
###
### Batocera.PLUS
### Alexandre Freire dos Santos
### Editado por: Sérgio de Carvalho Júnior
###
################################################################################

readonly ROM="${1}"
readonly FULLBOOT="${2}"
readonly CUSTOM="${3}"
readonly PCSX2_DIR="$(dirname ${0})"
CONFIG_DIR="${HOME}/../system/configs/pcsx2-legacy"
SAVE_DIR='/userdata/saves/ps2'

################################################################################

## MAIN

function main()
{
    if [ "${ROM}" == 'populate' ]
    then
        populate
        return 0
    fi

    if [ -e "${ROM}" ]
    then	
        case $CUSTOM in
           auto|0) execByES ;;
                1) execByEScustom ;;
                2) execByF1custom ;;
                *) exit 0
        esac
    else
        execByF1
    fi
}

################################################################################

## DEFAULT CONFIG

function populate()
{
    mkdir -p "${CONFIG_DIR}"

    if ! [ -e "${CONFIG_DIR}/PCSX2_ui.ini" ]
    then
        (echo '[Filenames]'
         echo 'BIOS=scph39001.bin'
         echo ''
         echo '[ProgramLog]'
         echo 'Visible=disabled'
         echo ''
         echo '[GSWindow]'
         echo 'AspectRatio=4:3'
         echo '[MemoryCards]'
         echo 'Slot1_Enable=enabled'
         echo 'Slot1_Filename=Mcd001.ps2') > "${CONFIG_DIR}/PCSX2_ui.ini"
    fi

    if [ "${CUSTOM}" == '1' ] || [ "${CUSTOM}" == '2' ]; then
        sed -i "s|^Slot1_Filename=.*|Slot1_Filename=$(basename "${ROM%.*}")".ps2"|" "${CONFIG_DIR}/PCSX2_ui.ini"
    fi

    if ! [ -e "${CONFIG_DIR}/GSdx.ini" ]
    then
        (echo 'vsync = 0'
         echo 'upscale_multiplier = 1'
         echo 'MaxAnisotropy = 0') > "${CONFIG_DIR}/GSdx.ini"
    fi
}

################################################################################

## Cria um tema com fundo de tela preto.
## Este tema corrige o problema com as bordas de tela branca.
## Este bug foi corrigido nas versões recentes do PCSX2.

function makeTheme()
{
    local THEME_NAME=Pcsx2-Adwaita-Black
    local THEME_DIR=/usr/share/themes/${THEME_NAME}

    export GTK_THEME=${THEME_NAME}

    mkdir -p ${THEME_DIR}/gtk-3.0

    cat << '    EOF' > ${THEME_DIR}/gtk-3.0/gtk.css
        @import url("resource:///org/gtk/libgtk/theme/Adwaita/gtk-contained-dark.css");
        .background {background-color: #000000}
    EOF

    (sleep 1; rm -r ${THEME_DIR}/gtk-3.0) &
}

################################################################################

## Executa o emulador pelo Emulationstation

function execByES()
{
    makeTheme

    ${PCSX2_DIR}/PCSX2 \
        --portable \
        --nogui \
        --fullscreen \
        ${FULLBOOT} \
        --gs=${PCSX2_DIR}/plugins/libGSdx.so \
        "${ROM}" > $HOME/logs/pcsx2-legacy.log 2>&1
}

################################################################################

## Executa o emulador pelo aplicativo no menu F1.

function execByF1()
{
    makeTheme

    ${PCSX2_DIR}/PCSX2 \
        --gs=${PCSX2_DIR}/plugins/libGSdx.so \
        "${@}" > $HOME/logs/pcsx2-legacy.log 2>&1
}

################################################################################

## Executa o emulador pelo Emulationstation com uma configuração custom

function execByEScustom()
{
    CONFIG_DIR="${SAVE_DIR}/custom-legacy/$(basename "${ROM%.*}")"

    if ! [ -d "${CONFIG_DIR}" ]
    then
        populate
    fi

    makeTheme

    ${PCSX2_DIR}/PCSX2 \
        --portable \
        --nogui \
        --fullscreen \
		--cfgpath="${CONFIG_DIR}" \
        --gs=${PCSX2_DIR}/plugins/libGSdx.so \
        "${ROM}" > $HOME/logs/pcsx2-legacy.log 2>&1
}

################################################################################

## Executa o emulador pelo aplicativo no menu F1 com uma configuração customizada.

function execByF1custom()
{
    CONFIG_DIR="${SAVE_DIR}/custom-legacy/$(basename "${ROM%.*}")"

    if ! [ -d "${CONFIG_DIR}" ]
    then
        populate
    fi

    makeTheme

    ${PCSX2_DIR}/PCSX2 \
        --gs=${PCSX2_DIR}/plugins/libGSdx.so \
		--cfgpath="${CONFIG_DIR}" \
         "${ROM}" > $HOME/logs/pcsx2-legacy.log 2>&1
}

################################################################################

main && exit 0
