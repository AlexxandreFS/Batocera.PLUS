#!/bin/sh

# Parametros externos
JOGO="$1"

# Variáveis da instalação do Model 3
MODEL3_DIR='/opt/Model3'

# Variáveis pra configuração do Model 3
MODEL3="$HOME/configs/model3"
SAVE="$HOME/../saves/model3"

# Executa o Model2/Wine se não estiver sendo executado
if [ "$(pidof wineserver)" ]; then
    exit 1
fi

# Instalação do Model3
if [ ! "$(ls -A "${MODEL3}" 2> /dev/null)" ] || [ ! "$(ls -A "${SAVE}"  2> /dev/null)" ]; then
    # Montando o model2 em "system/configs/model2"
    mkdir -p "${SAVE}"                                 "${MODEL3}" || exit $?

    cp -r "${MODEL3_DIR}/emulator/SDL.dll"             "${MODEL3}" || exit $?
    cp -r "${MODEL3_DIR}/emulator/Sega Model 3 UI.exe" "${MODEL3}" || exit $?
    cp -r "${MODEL3_DIR}/emulator/Supermodel.exe"      "${MODEL3}" || exit $?
    cp -r "${MODEL3_DIR}/emulator/Shaders"             "${MODEL3}" || exit $?
    cp -r "${MODEL3_DIR}/emulator/Snaps"               "${MODEL3}" || exit $?
    
    # Montando o model2 em "share/save/model2"
    cp -r "$MODEL3_DIR/emulator/Config"                "${SAVE}"   || exit $?
    cp -r "$MODEL3_DIR/emulator/NVRAM"                 "${SAVE}"   || exit $?
    cp -r "$MODEL3_DIR/emulator/Saves"                 "${SAVE}"   || exit $?

    # Criando links simbólicos para "system/configs/model2"
    ln -s "$SAVE/"* "$MODEL3"
fi

# Capta a resolução inicial da tela antes inicar o jogo
RES_START="$(batocera-resolution currentMode)"

# Ativa WideScreen per-game ou global
WIDE_GAME="$(grep -F "model3[\"$(basename "${JOGO}")\"].ratio=" "${HOME}/batocera.conf" | cut -d '=' -f 2)"
WIDE_MODEL3="$(grep '^model3.ratio=' "${HOME}/batocera.conf" | cut -d '=' -f 2)"
WIDE_GLOBAL="$(grep '^model3.ratio=' "${HOME}/batocera.conf" | cut -d '=' -f 2)"

if [ "${WIDE_GAME}" ] && [ ! "${WIDE_GAME}" == 'auto' ]; then
    WIDESCREEN="${WIDE_GAME}"
elif [ "${WIDE_MODEL3}" ] && [ ! "${WIDE_MODEL3}" == 'auto' ]; then
    WIDESCREEN="${WIDE_MODEL3}"
elif [ "${WIDE_GLOBAL}" ] && [ ! "${WIDE_GLOBAL}" == 'auto' ]; then
    WIDESCREEN="${WIDE_GLOBAL}"
else
    WIDESCREEN='auto'
fi

case "${WIDESCREEN}" in
    4/3|1/1|16/15|3/2|3/4|4/4|5/4|6/5|7/9|8/7|auto|custom|squarepixel)
        sed -i s/'^WideScreen=.*/WideScreen=0/' "${MODEL3}/Config/Supermodel.ini"
        ;;
    16/9|19/12|19/14|2/1|21/9|30/17|32/9|4/1|8/3)
        sed -i s/'^WideScreen=.*/WideScreen=1/' "${MODEL3}/Config/Supermodel.ini"
        ;;
esac

# Carrega a resolução do sistema configurado pelo emulationstation
GAME_RES="$(grep -F "model3[\"$(basename "${JOGO}")\"].videomode=" "${HOME}/batocera.conf" | cut -d '=' -f 2)"
MODEL3_RES="$(grep '^model3.videomode=' "${HOME}/batocera.conf" | cut -d '=' -f 2)"
GLOBAL_RES="$(grep '^model3.videomode=' "${HOME}/batocera.conf" | cut -d '=' -f 2)"

if [ "${GAME_RES}" ] && [ ! "${GAME_RES}" == 'auto' ]; then
    RESOLUTION="${GAME_RES}"
elif [ "${MODEL3_RES}" ] && [ ! "${MODEL3_RES}" == 'auto' ]; then
    RESOLUTION="${MODEL3_RES}"
elif [ "${GLOBAL_RES}" ] && [ ! "${GLOBAL_RES}" == 'auto' ]; then
    RESOLUTION="${GLOBAL_RES}"
else
    RESOLUTION='auto'
fi

if [ "${RESOLUTION}" == 'auto' ]; then
    XRES="$(echo "${RES_START}" | cut -d 'x' -f 1)"
    YRES="$(echo "${RES_START}" | cut -d 'x' -f 2)"
else
    XRES="$(echo "${RESOLUTION}" | cut -d 'x' -f 1)"
    YRES="$(echo "${RESOLUTION}" | cut -d 'x' -f 2)"
fi

cd "$MODEL3"
# Executa o jogo ou o configurador
if [ "${JOGO}" == "${JOGO%zip}zip" ] || [ "${JOGO}" == "${JOGO%ZIP}ZIP" ]; then
	export WINEDLLOVERRIDES="SDL.dll=n,b"
	wine "supermodel.exe" "$JOGO" -res="$XRES","$YRES" -fullscreen -new3d -quad-rendering -flip-stereo -sound-volume=50 -music-volume=200 -no-throttle -ppc-frequency=57
else
	wine "Sega Model 3 UI.exe"
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