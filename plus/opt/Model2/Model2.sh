#!/bin/sh

# Parametros externos
JOGO="$1"
CORE="$2"

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

    cp -r "${MODEL2_DIR}/emulator/d3d9.dll"              "${MODEL2}" || exit $?
    cp -r "${MODEL2_DIR}/emulator/emulator.exe"          "${MODEL2}" || exit $?
    cp -r "${MODEL2_DIR}/emulator/emulator_multicpu.exe" "${MODEL2}" || exit $?
    cp -r "${MODEL2_DIR}/emulator/Encdr.dll"             "${MODEL2}" || exit $?
    cp -r "${MODEL2_DIR}/emulator/Encof.dll"             "${MODEL2}" || exit $?
    cp -r "${MODEL2_DIR}/emulator/Sega Model 2 UI.exe"   "${MODEL2}" || exit $?
    cp -r "${MODEL2_DIR}/emulator/Source"                "${MODEL2}" || exit $?
    cp -r "${MODEL2_DIR}/emulator/snaps"                 "${MODEL2}" || exit $?
    cp -r "${MODEL2_DIR}/emulator/Emulator.ini"          "${MODEL2}" || exit $?

    # Montando o model2 em "share/save/model2"
    cp -r "$MODEL2_DIR/emulator/CFG"                     "${SAVE}"   || exit $?
    cp -r "$MODEL2_DIR/emulator/NVDATA"                  "${SAVE}"   || exit $?
    cp -r "$MODEL2_DIR/emulator/scripts"                 "${SAVE}"   || exit $?

    # Criando links simbólicos para "system/configs/model2"
    ln -s "$SAVE/"* "$MODEL2"
fi

# Capta a resolução inicial da tela antes inicar o jogo
RES_START="$(batocera-resolution currentMode)"

# Ativa WideScreen per-game ou global
WIDE_GAME="$(grep -F "model2[\"$(basename "${JOGO}")\"].ratio=" "${HOME}/batocera.conf" | cut -d '=' -f 2)"
WIDE_MODEL2="$(grep '^model2.ratio=' "${HOME}/batocera.conf" | cut -d '=' -f 2)"
WIDE_GLOBAL="$(grep '^model2.ratio=' "${HOME}/batocera.conf" | cut -d '=' -f 2)"

if [ "${WIDE_GAME}" ] && [ ! "${WIDE_GAME}" == 'auto' ]; then
    WIDESCREEN="${WIDE_GAME}"
elif [ "${WIDE_MODEL2}" ] && [ ! "${WIDE_MODEL2}" == 'auto' ]; then
    WIDESCREEN="${WIDE_MODEL2}"
elif [ "${WIDE_GLOBAL}" ] && [ ! "${WIDE_GLOBAL}" == 'auto' ]; then
    WIDESCREEN="${WIDE_GLOBAL}"
else
    WIDESCREEN='auto'
fi

case "${WIDESCREEN}" in
    4/3|1/1|16/15|3/2|3/4|4/4|5/4|6/5|7/9|8/7|auto|custom|squarepixel)
        sed -i s/'^WideScreenWindow=.*/WideScreenWindow=0/' "${MODEL2}/Emulator.ini"
        ;;
    16/9|19/12|19/14|2/1|21/9|30/17|32/9|4/1|8/3)
        sed -i s/'^WideScreenWindow=.*/WideScreenWindow=1/' "${MODEL2}/Emulator.ini"
        ;;
esac

# Carrega a resolução do sistema configurado pelo emulationstation
GAME_RES="$(grep -F "model2[\"$(basename "${JOGO}")\"].videomode=" "${HOME}/batocera.conf" | cut -d '=' -f 2)"
MODEL2_RES="$(grep '^model2.videomode=' "${HOME}/batocera.conf" | cut -d '=' -f 2)"
GLOBAL_RES="$(grep '^model2.videomode=' "${HOME}/batocera.conf" | cut -d '=' -f 2)"

if [ "${GAME_RES}" ] && [ ! "${GAME_RES}" == 'auto' ]; then
    RESOLUTION="${GAME_RES}"
elif [ "${MODEL2_RES}" ] && [ ! "${MODEL2_RES}" == 'auto' ]; then
    RESOLUTION="${MODEL2_RES}"
elif [ "${GLOBAL_RES}" ] && [ ! "${GLOBAL_RES}" == 'auto' ]; then
    RESOLUTION="${GLOBAL_RES}"
else
    RESOLUTION='auto'
fi

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

# Sempre em tela cheia
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
else
    # Executa interface gráfica do Model2 quando aberto pelo menu F1
    export WINEDLLOVERRIDES='d3dx9.dll=n,b'
    wine 'Sega Model 2 UI.exe'
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
