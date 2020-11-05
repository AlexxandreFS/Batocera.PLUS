#!/bin/sh

# Parametros externos
JOGO="${1}"
CORE="${2}"
RESOLUTION="${3}"
WIDESCREEN="${4}"
ANTIALIASING="${5}"
VSYNC="${6}"
ANISOTROPICFILTER="${7}"
DRAWCROSS="${8}"
RUMBLE="${9}"

# Variáveis da instalação do Model 2
MODEL2_DIR='/opt/Model2'

# Variáveis pra configuração do Model 2
MODEL2="$HOME/configs/model2"
SAVE="$HOME/../saves/model2"

# Executa o Model2/Wine se não estiver sendo executado
if [ "$(pidof wineserver)" ]; then
    exit 1
fi

# Instalação do Model2
if [ ! "$(ls -A "${MODEL2}" 2> /dev/null)" ] || [ ! "$(ls -A "${SAVE}"  2> /dev/null)" ]; then
    # Montando o model2 em "system/configs/model2"
    mkdir -p "${SAVE}"                                   "${MODEL2}" || exit $?
    cp -r "${MODEL2_DIR}/emulator/emulator.exe"          "${MODEL2}" || exit $?
    cp -r "${MODEL2_DIR}/emulator/emulator_multicpu.exe" "${MODEL2}" || exit $?
    cp -r "${MODEL2_DIR}/emulator/Emulator.ini"          "${MODEL2}" || exit $?

    # Montando o model2 em "share/save/model2"
    cp -r "$MODEL2_DIR/emulator/CFG"                     "${SAVE}"   || exit $?
    cp -r "$MODEL2_DIR/emulator/NVDATA"                  "${SAVE}"   || exit $?
    cp -r "$MODEL2_DIR/emulator/scripts"                 "${SAVE}"   || exit $?

    # Criando links simbólicos para "system/configs/model2"
    ln -s "$SAVE/"* "$MODEL2"
fi

# Captura a resolução inicial da tela antes inicar o jogo
RES_START="$(batocera-resolution currentMode)"

# WIDESCREEN
case "${WIDESCREEN}" in
    4/3|1/1|16/15|3/2|3/4|4/4|5/4|6/5|7/9|8/7|auto|custom|squarepixel)
        sed -i s/'^WideScreenWindow=.*/WideScreenWindow=0/' "${MODEL2}/Emulator.ini"
        ;;
    16/9|19/12|19/14|2/1|21/9|30/17|32/9|4/1|8/3)
        sed -i s/'^WideScreenWindow=.*/WideScreenWindow=1/' "${MODEL2}/Emulator.ini"
        ;;
esac

# RESOLUÇÃO
if [ "${RESOLUTION}" == 'auto' ]; then
    XRES="$(echo "${RES_START}" | cut -d 'x' -f 1)"
    YRES="$(echo "${RES_START}" | cut -d 'x' -f 2)"
	sed -i 's/^FullScreenWidth=.*/FullScreenWidth='"${XRES}"'/' "${MODEL2}/Emulator.ini"
	sed -i 's/^FullScreenHeight=.*/FullScreenHeight='"${YRES}"'/' "${MODEL2}/Emulator.ini"
else
    XRES="$(echo "${RESOLUTION}" | cut -d 'x' -f 1)"
    YRES="$(echo "${RESOLUTION}" | cut -d 'x' -f 2)"
	sed -i 's/^FullScreenWidth=.*/FullScreenWidth='"${XRES}"'/' "${MODEL2}/Emulator.ini"
	sed -i 's/^FullScreenHeight=.*/FullScreenHeight='"${YRES}"'/' "${MODEL2}/Emulator.ini"
fi

# ANTIALIASING
if [ "${ANTIALIASING}" == 'auto' ] || [ "${ANTIALIASING}" == 'on' ]; then
    sed -i s/'^FSAA=.*/FSAA=1/' "${MODEL2}/Emulator.ini"
else
    sed -i s/'^FSAA=.*/FSAA=0/' "${MODEL2}/Emulator.ini"
fi

# ANISOTROPICFILTER
if [ "${ANISOTROPICFILTER}" == 'bilinear' ]; then
    sed -i s/'^Bilinear=.*/Bilinear=1/' "${MODEL2}/Emulator.ini"
	sed -i s/'^Trilinear=.*/Trilinear=0/' "${MODEL2}/Emulator.ini"
elif [ "${ANISOTROPICFILTER}" == 'trilinear' ]; then
    sed -i s/'^Bilinear=.*/Bilinear=0/' "${MODEL2}/Emulator.ini"
	sed -i s/'^Trilinear=.*/Trilinear=1/' "${MODEL2}/Emulator.ini"
else
    sed -i s/'^Bilinear=.*/Bilinear=0/' "${MODEL2}/Emulator.ini"
	sed -i s/'^Trilinear=.*/Trilinear=0/' "${MODEL2}/Emulator.ini"
fi

# VSYNC
if [ "${VSYNC}" == 'off' ] || [ "${VSYNC}" == 'on' ]; then
    sed -i s/'^ForceSync=.*/ForceSync=1/' "${MODEL2}/Emulator.ini"
else
    sed -i s/'^ForceSync=.*/ForceSync=0/' "${MODEL2}/Emulator.ini"
fi

# DRAWCROSS
# Para jogos de tiro, seria interessante portar o demulshooter
if [ "${DRAWCROSS}" == 'auto' ] || [ "${DRAWCROSS}" == 'off' ]; then
    mouse-pointer off
	sed -i s/'^DrawCross=.*/DrawCross=0/' "${MODEL2}/Emulator.ini"
	sed -i s/'^RawDevP1=.*/RawDevP1=0/' "${MODEL2}/Emulator.ini"
	sed -i s/'^RawDevP2=.*/RawDevP1=0/' "${MODEL2}/Emulator.ini"
else
    mouse-pointer on
	sed -i s/'^DrawCross=.*/DrawCross=1/' "${MODEL2}/Emulator.ini"
	sed -i s/'^RawDevP1=.*/RawDevP1=0/' "${MODEL2}/Emulator.ini"
	sed -i s/'^RawDevP2=.*/RawDevP1=1/' "${MODEL2}/Emulator.ini"
fi

# FORCE FEEDBACK
if [ "${RUMBLE}" == 'auto' ] || [ "${RUMBLE}" == 'on' ]; then
	sed -i s/'^EnableFF=.*/EnableFF=1/' "${MODEL2}/Emulator.ini"
	sed -i s/'^Force Feedback=.*/Force Feedback=1/' "${MODEL2}/Emulator.ini"
else
    sed -i s/'^EnableFF=.*/EnableFF=0/' "${MODEL2}/Emulator.ini"
    sed -i s/'^Force Feedback=.*/Force Feedback=0/' "${MODEL2}/Emulator.ini"
fi

# TELA CHEIA
sed -i s/'^AutoFull=.*/AutoFull=1/' "${MODEL2}/Emulator.ini"
sed -i s/'^FullMode=.*/FullMode=4/' "${MODEL2}/Emulator.ini"

# Executa o emulador por linha de comando ou abre o configurador
cd "${MODEL2}" || exit $?

if [ "${JOGO}" == "${JOGO%zip}zip" ] || [ "${JOGO}" == "${JOGO%ZIP}ZIP" ]; then
    JOGO="$(basename "${JOGO}" .zip )"
    JOGO="${JOGO%.ZIP}"

    if [ "${CORE}" == 'singlecore' ] || [ "${CORE}" == 'auto' ]; then
        # Executa o Model2 por linha de comando (single core)
        wine 'emulator.exe' "${JOGO}"
    elif [ "${CORE}" == 'multicore' ]; then
        # Executa o Model2 por linha de comando (multi core)
        wine 'emulator_multicpu.exe' "${JOGO}"
    fi
fi

# Aguarda encerrar a execução do jogo
while [ "$(pidof wineserver)" ]; do
    sleep 1
done

# Restaura a resolução, caso o jogo tenha mudado ###	
RES_STOP="$(batocera-resolution currentResolution)"
if [ "${RES_START}" != "${RES_STOP}" ]; then
    batocera-resolution setMode "${RES_START}"
fi

exit 0
