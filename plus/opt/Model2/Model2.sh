#!/bin/sh
##
## Batocera.PLUS
##
## Código escrito por: Sérgio de Carvalho Júnior
## Colaborador: Alexandre Freire dos Santos
## 
## Linha de comando:
## Model2.sh [ROM] [CORE] [RESOLUTION] [WIDESCREEN] [ANTIALIASING] [VSYNC] [ANISOTROPICFILTER] [DRAWCROSS] [RUMBLE] [P1GUID]
##
## ROM = Caminho do jogo até o .zip do jogo
## CORE = singlecore, multicore ou auto
## RESULUTION = auto ou algo que respeite a regra XXXXxXXXX ex: [1920x1080]
## WIDESCREEN = 4/3|1/1|16/15|3/2|3/4|4/4|5/4|6/5|7/9|8/7|16/9|19/12|19/14|2/1|21/9|30/17|32/9|4/1|8/3|auto|custom|squarepixel
## ANTIALIASING = auto, on ou off
## VSYNC = auto, on ou off
## ANISOTROPICFILTER = bilinear, trilinear, auto ou off
## DRAWCROSS = on, off ou auto
## RUMBLE = on, off ou auto
## PIGUID = parâmetro do emulatorlauncher.sh

################################################################################

### PARÂMETROS

JOGO="${1}"
CORE="${2}"
RESOLUTION="${3}"
WIDESCREEN="${4}"
ANTIALIASING="${5}"
VSYNC="${6}"
ANISOTROPICFILTER="${7}"
DRAWCROSS="${8}"
RUMBLE="${9}"
P1GUID="${10}"

################################################################################

### CAMINHOS

MODEL2_DIR='/opt/Model2'
MODEL2="${HOME}/configs/model2"
SAVE="${HOME}/../saves/model2"

################################################################################


### HELP

function help()
{
    echo ' Sega Model 2 launcher for Batocera.PLUS'
    echo
    echo ' Codigo escrito por: Sergio de Carvalho Junior'
    echo ' Colaborador: Alexandre Freire dos Santos'
    echo
    echo ' Linha de comando:'
    echo ' Model2.sh [ROM] [CORE] [RESOLUTION] [WIDESCREEN] [ANTIALIASING] [VSYNC] [ANISOTROPICFILTER] [DRAWCROSS] [RUMBLE] [P1GUID]'
    echo
    echo ' ROM               = Caminho do jogo até o .zip do jogo'
    echo ' CORE              = singlecore, multicore ou auto'
    echo ' RESULUTION        = auto ou algo que respeite a regra XXXXxXXXX ex: [1920x1080]'
    echo ' WIDESCREEN        = 4/3|1/1|16/15|3/2|3/4|4/4|5/4|6/5|7/9|8/7|16/9|19/12|19/14|2/1|21/9|30/17|32/9|4/1|8/3|auto|custom|squarepixel'
    echo ' ANTIALIASING      = auto, on ou off'
    echo ' VSYNC             = auto, on ou off'
    echo ' ANISOTROPICFILTER = bilinear, trilinear, auto ou off'
    echo ' DRAWCROSS         = on, off ou auto'
    echo ' RUMBLE            = on, off ou auto'
    echo ' PIGUID            = parâmetro do emulatorlauncher.sh'
    echo
}

if [ "${JOGO}" == '--help' ]; then
    help
    exit 0
fi

################################################################################

### NÃO EXECUTA O EMULADOR DUAS VEZES

# Executa o Model2/Wine se não estiver sendo executado
if [ "$(pidof emulator.exe)" ] || [ "$(pidof emulator_multicpu.exe)" ]; then
    echo ' Sega Model 2 launcher já esta sendo executado'
    exit 1
fi

################################################################################

### LAUNCHER INFO

echo ' Sega Model 2 launcher for Batocera.PLUS'
echo
echo ' Código escrito por: Sérgio de Carvalho Junior'
echo ' Colaborador: Alexandre Freire dos Santos'
echo


################################################################################

### INSTALAÇÃO DO MODEL2

if [ ! "$(ls -A "${MODEL2}" 2> /dev/null)" ] || [ ! "$(ls -A "${SAVE}"  2> /dev/null)" ]; then
    # Montando o model2 em "system/configs/model2"
    mkdir -p "${SAVE}"                                    "${MODEL2}" || exit $?
    cp -f  "${MODEL2_DIR}/emulator/emulator.exe"          "${MODEL2}" || exit $?
    cp -f  "${MODEL2_DIR}/emulator/emulator_multicpu.exe" "${MODEL2}" || exit $?
    cp -f  "${MODEL2_DIR}/emulator/Emulator.ini"          "${MODEL2}" || exit $?

    # Montando o model2 em "share/save/model2"
    cp -rf "${MODEL2_DIR}/emulator/CFG"                   "${SAVE}"   || exit $?
    cp -rf "${MODEL2_DIR}/emulator/NVDATA"                "${SAVE}"   || exit $?
    cp -rf "${MODEL2_DIR}/emulator/scripts"               "${SAVE}"   || exit $?

    # Criando links simbólicos para "system/configs/model2"
    ln -s  "${SAVE}/"* "$MODEL2"
fi

################################################################################

### WIDESCREEN

case "${WIDESCREEN}" in
    4/3|1/1|16/15|3/2|3/4|4/4|5/4|6/5|7/9|8/7|auto|custom|squarepixel)
        sed -i s/'^WideScreenWindow=.*/WideScreenWindow=0/' "${MODEL2}/Emulator.ini"
        ;;
    16/9|19/12|19/14|2/1|21/9|30/17|32/9|4/1|8/3)
        sed -i s/'^WideScreenWindow=.*/WideScreenWindow=1/' "${MODEL2}/Emulator.ini"
        ;;
esac

################################################################################

### RESOLUÇÃO

RES_START="$(batocera-resolution currentMode)"

if [ "${RESOLUTION}" == 'auto' ]; then
    XRES="$(echo "${RES_START}" | cut -d 'x' -f 1)"
    YRES="$(echo "${RES_START}" | cut -d 'x' -f 2)"

    sed -i 's/^FullScreenWidth=.*/FullScreenWidth='"${XRES}"'/'   "${MODEL2}/Emulator.ini"
    sed -i 's/^FullScreenHeight=.*/FullScreenHeight='"${YRES}"'/' "${MODEL2}/Emulator.ini"
else
    XRES="$(echo "${RESOLUTION}" | cut -d 'x' -f 1)"
    YRES="$(echo "${RESOLUTION}" | cut -d 'x' -f 2)"

    sed -i 's/^FullScreenWidth=.*/FullScreenWidth='"${XRES}"'/'   "${MODEL2}/Emulator.ini"
    sed -i 's/^FullScreenHeight=.*/FullScreenHeight='"${YRES}"'/' "${MODEL2}/Emulator.ini"
fi

################################################################################

### ANTIALIASING

if [ "${ANTIALIASING}" == 'auto' ] || [ "${ANTIALIASING}" == 'on' ]; then
    sed -i s/'^FSAA=.*/FSAA=1/' "${MODEL2}/Emulator.ini"
else
    sed -i s/'^FSAA=.*/FSAA=0/' "${MODEL2}/Emulator.ini"
fi

################################################################################

### ANISOTROPICFILTER

if [ "${ANISOTROPICFILTER}" == 'bilinear' ]; then
    sed -i s/'^Bilinear=.*/Bilinear=1/'   "${MODEL2}/Emulator.ini"
    sed -i s/'^Trilinear=.*/Trilinear=0/' "${MODEL2}/Emulator.ini"
elif [ "${ANISOTROPICFILTER}" == 'trilinear' ]; then
    sed -i s/'^Bilinear=.*/Bilinear=0/'   "${MODEL2}/Emulator.ini"
    sed -i s/'^Trilinear=.*/Trilinear=1/'    "${MODEL2}/Emulator.ini"
else
    sed -i s/'^Bilinear=.*/Bilinear=0/'   "${MODEL2}/Emulator.ini"
    sed -i s/'^Trilinear=.*/Trilinear=0/' "${MODEL2}/Emulator.ini"
fi

################################################################################

### VSYNC

if [ "${VSYNC}" == 'auto' ] || [ "${VSYNC}" == 'on' ]; then
    sed -i s/'^ForceSync=.*/ForceSync=1/' "${MODEL2}/Emulator.ini"
else
    sed -i s/'^ForceSync=.*/ForceSync=0/' "${MODEL2}/Emulator.ini"
fi

################################################################################

### FORCE FEEDBACK

if [ "${RUMBLE}" == 'auto' ] || [ "${RUMBLE}" == 'on' ]; then
    sed -i s/'^EnableFF=.*/EnableFF=1/'             "${MODEL2}/Emulator.ini"
    sed -i s/'^Force Feedback=.*/Force Feedback=1/' "${MODEL2}/Emulator.ini"
else
    sed -i s/'^EnableFF=.*/EnableFF=0/'             "${MODEL2}/Emulator.ini"
    sed -i s/'^Force Feedback=.*/Force Feedback=0/' "${MODEL2}/Emulator.ini"
fi

################################################################################

### DRAWCROSS

# Para jogos de tiro, seria interessante portar o demulshooter
if [ "${DRAWCROSS}" == 'on' ]; then
    mouse-pointer on
    sed -i s/'^DrawCross=.*/DrawCross=1/' "${MODEL2}/Emulator.ini"
    sed -i s/'^RawDevP1=.*/RawDevP1=0/'   "${MODEL2}/Emulator.ini"
    sed -i s/'^RawDevP2=.*/RawDevP2=1/'   "${MODEL2}/Emulator.ini"
else
    sed -i s/'^DrawCross=.*/DrawCross=0/' "${MODEL2}/Emulator.ini"
    sed -i s/'^RawDevP1=.*/RawDevP1=0/'   "${MODEL2}/Emulator.ini"
    sed -i s/'^RawDevP2=.*/RawDevP2=0/'   "${MODEL2}/Emulator.ini"
fi

################################################################################

### TELA CHEIA

sed -i s/'^AutoFull=.*/AutoFull=1/' "${MODEL2}/Emulator.ini"
sed -i s/'^FullMode=.*/FullMode=4/' "${MODEL2}/Emulator.ini"

################################################################################

### HOTKEY

BOTOES="$(/opt/Wine/getHotkeyStart "${P1GUID}")"
BOTAO_HOTKEY="$(echo "${BOTOES}" | cut -d ' ' -f 1)"
BOTAO_START="$(echo "${BOTOES}"  | cut -d ' ' -f 2)"

if [ "${BOTAO_HOTKEY}" ] && [ "${BOTAO_START}" ]; then
    # Impede que o xjoykill seja encerrado enquanto o jogo está em execução.
    while : ; do
        nice -n 20 xjoykill -hotkey "${BOTAO_HOTKEY}" -start "${BOTAO_START}" -kill /usr/bin/killwine
        if ! [ "$(pidof wineserver)" ]; then
            break
        fi
        sleep 5
    done &
fi

################################################################################

### EXECUTA O JOGO

cd "${MODEL2}" || exit $?

if [ "${JOGO}" == "${JOGO%zip}zip" ] || [ "${JOGO}" == "${JOGO%ZIP}ZIP" ]; then
    JOGO="$(basename "${JOGO}" .zip )"
    JOGO="${JOGO%.ZIP}"

    if [ "${CORE}" == 'singlecore' ] || [ "${CORE}" == 'auto' ]; then
        # Executa em single core
        wine-lutris 'emulator.exe' "${JOGO}"
    elif [ "${CORE}" == 'multicore' ]; then
        # Executa em multi core
        wine-lutris 'emulator_multicpu.exe' "${JOGO}"
    fi
fi

################################################################################

### FINALIZA A EXECUÇÃO DO JOGO

# Mata o emulador de teclado ###
if [ "$(pidof -s xjoykill)" ]; then
    killall -9 xjoykill
elif [ "$(pidof -s xjoykill-mugen)" ]; then
    killall -9 xjoykill-mugen
fi

# Restaura a resolução do jogo caso tenha mudado
RES_STOP="$(batocera-resolution currentResolution)"
if [ "${RES_START}" != "${RES_STOP}" ]; then
    batocera-resolution setMode "${RES_START}"
fi

exit 0
