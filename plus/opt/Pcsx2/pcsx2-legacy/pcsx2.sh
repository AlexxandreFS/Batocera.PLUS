#!/bin/bash
###
### Batocera.PLUS
### Alexandre Freire dos Santos
###
################################################################################

readonly ROM="${2}"
readonly P1GUID="${1}"

readonly PCSX2_DIR=/opt/Pcsx2/pcsx2-legacy

################################################################################

## MAIN

function main()
{
    makeFolders

    if [ -e "${ROM}" ]
    then
        execByES
    else
        execByF1
    fi
}

################################################################################

## Cria algumas pastas usadas pelo pcsx2

function makeFolders()
{
    mkdir -p ${HOME}/configs/pcsx2-legacy /
             ${HOME}/../saves/ps2/pcsx2-legacy/sstates \
             ${HOME}/../saves/userdata/saves/ps2/pcsx2/Slot 1 \
             ${HOME}/../saves/userdata/saves/ps2/pcsx2/Slot 2

    touch "${HOME}/../saves/userdata/saves/ps2/pcsx2/Slot 1/Shared Memory Card (8 MB).ps2" \
          "${HOME}/../saves/userdata/saves/ps2/pcsx2/Slot 2/Shared Memory Card (8 MB).ps2"
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

    exitHotkeyStart

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

## Exit game (hotkey + start)

function exitHotkeyStart()
{
    if [ -z "${P1GUID}" ]
    then
        return 1
    fi

    local BOTOES="$(${PCSX2_DIR}/../getHotkeyStart ${P1GUID})"
    local BOTAO_HOTKEY=$(echo "${BOTOES}" | cut -d ' ' -f 1)
    local BOTAO_START=$(echo  "${BOTOES}" | cut -d ' ' -f 2)

    if [ "${BOTAO_HOTKEY}" ] && [ "${BOTAO_START}" ]
    then
        # Impede que o xjoykill seja encerrado enquanto o jogo está em execução.
        while :
        do
            nice -n 20 xjoykill -hotkey ${BOTAO_HOTKEY} -start ${BOTAO_START} -kill "${PCSX2_DIR}/../killpcsx2"
            if ! [ "$(pidof PCSX2)" ]
            then
                break
            fi
            sleep 5
        done &
    fi
}

################################################################################

main && exit 0
