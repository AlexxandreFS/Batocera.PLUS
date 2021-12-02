#!/bin/bash
###
### Batocera.PLUS
### Alexandre Freire dos Santos
###
################################################################################

readonly ROM="${1}"
readonly PCSX2_DIR="$(dirname ${0})"

################################################################################

## MAIN

function main()
{
    populate

    if [ -e "${ROM}" ]
    then
        execByES
    else
        execByF1
    fi
}

################################################################################

## DEFAULT CONFIG

function populate()
{
    if ! [ -e "${HOME}/../system/configs/pcsx2-legacy/PCSX2_ui.ini" ]
    then
        cat << '        EOF' > "${HOME}/../system/configs/pcsx2-legacy/PCSX2_ui.ini"
            [Filenames]
            BIOS=scph39001.bin

            [ProgramLog]
            Visible=disabled

            [GSWindow]
            AspectRatio=4:3
        EOF
    fi

    if ! [ -e "${HOME}/../system/configs/pcsx2-legacy/GS.ini" ]
    then
        cat << '        EOF' > "${HOME}/../system/configs/pcsx2-legacy/GS.ini"
            vsync = 0
            upscale_multiplier = 1
            MaxAnisotropy = 0
        EOF
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
        --fullboot \
        --gs=${PCSX2_DIR}/plugins/libGSdx.so \
        "${ROM}" > $HOME/logs/pcsx2-legacy.log 2>&1
}

################################################################################

## Executa o emulador pelo aplicativo no menu F1.

function execByF1()
{
    ${PCSX2_DIR}/PCSX2 \
        --gs=${PCSX2_DIR}/plugins/libGSdx.so \
        "${@}" > $HOME/logs/pcsx2-legacy.log 2>&1
}

################################################################################

main && exit 0
