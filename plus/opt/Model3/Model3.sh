#!/bin/sh

# Parametros externos
JOGO="${1}"
CORE="${2}"
RESOLUTION="${3}"
WIDESCREEN="${4}"
MULTITEXTURE="${5}"
MULTITHREAD="${6}"
QUADRENDERING="${7}"
VSYNC="${8}"
NEW3DENGINE="${9}"
THROTTLE="${10}"
STRETCH="${11}"
INTEGERSCALE="${12}"
POWERPCFREQUENCY="${13}"
RUMBLE="${14}"
EMULATENET="${15}"

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
    cp -r "${MODEL3_DIR}/emulator/Supermodel.exe"      "${MODEL3}" || exit $?
    cp -r "${MODEL3_DIR}/emulator/Shaders"             "${MODEL3}" || exit $?
    
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
case "${WIDESCREEN}" in
    4/3|1/1|16/15|3/2|3/4|4/4|5/4|6/5|7/9|8/7|auto|custom|squarepixel)
        sed -i s/'^WideScreen=.*/WideScreen=0/' "${MODEL3}/Config/Supermodel.ini"
        ;;
    16/9|19/12|19/14|2/1|21/9|30/17|32/9|4/1|8/3)
        sed -i s/'^WideScreen=.*/WideScreen=1/' "${MODEL3}/Config/Supermodel.ini"
        ;;
esac

# Carrega a resolução do sistema configurado pelo emulationstation
if [ "${RESOLUTION}" == 'auto' ]; then
    XRES="$(echo "${RES_START}" | cut -d 'x' -f 1)"
 sed -i s/'^XResolution=.*/XResolution='"${XRES}"'/' "${MODEL3}/Config/Supermodel.ini"
    YRES="$(echo "${RES_START}" | cut -d 'x' -f 2)"
 sed -i s/'^YResolution=.*/YResolution='"${YRES}"'/' "${MODEL3}/Config/Supermodel.ini"
else
    XRES="$(echo "${RESOLUTION}" | cut -d 'x' -f 1)"
 sed -i s/'^XResolution=.*/XResolution='"${XRES}"'/' "${MODEL3}/Config/Supermodel.ini"
    YRES="$(echo "${RESOLUTION}" | cut -d 'x' -f 2)"
 sed -i s/'^YResolution=.*/YResolution='"${YRES}"'/' "${MODEL3}/Config/Supermodel.ini"
fi

# MultiThread
if [ "${MULTITHREAD}" == 'auto' ] || [ "${MULTITHREAD}" == 'off' ]; then
    sed -i s/'^MultiThreaded=.*/MultiThreaded=0/' "${MODEL3}/Config/Supermodel.ini"
 sed -i s/'^GPUMultiThreaded=.*/GPUMultiThreaded=0/' "${MODEL3}/Config/Supermodel.ini"
else
    sed -i s/'^MultiThreaded=.*/MultiThreaded=1/' "${MODEL3}/Config/Supermodel.ini"
 sed -i s/'^GPUMultiThreaded=.*/GPUMultiThreaded=1/' "${MODEL3}/Config/Supermodel.ini"
fi

# MultiTexture
if [ "${MULTITEXTURE}" == 'auto' ] || [ "${MULTITEXTURE}" == 'on' ]; then
    sed -i s/'^MultiTexture=.*/MultiTexture=1/' "${MODEL3}/Config/Supermodel.ini"
else
    sed -i s/'^MultiTexture=.*/MultiTexture=0/' "${MODEL3}/Config/Supermodel.ini"    
fi

# Quad Rendering
if [ "${QUADRENDERING}" == 'auto' ] || [ "${QUADRENDERING}" == 'on' ]; then
    sed -i s/'^QuadRendering=.*/QuadRendering=1/' "${MODEL3}/Config/Supermodel.ini"
else
    sed -i s/'^QuadRendering=.*/QuadRendering=0/' "${MODEL3}/Config/Supermodel.ini"    
fi

# Vsync
if [ "${VSYNC}" == 'auto' ] || [ "${VSYNC}" == 'on' ]; then
    sed -i s/'^VSync=.*/VSync=1/' "${MODEL3}/Config/Supermodel.ini"
else
    sed -i s/'^VSync=.*/VSync=0/' "${MODEL3}/Config/Supermodel.ini"    
fi

# New 3D Engine
if [ "${NEW3DENGINE}" == 'auto' ] || [ "${NEW3DENGINE}" == 'on' ]; then
    sed -i s/'^New3DEngine=.*/New3DEngine=1/' "${MODEL3}/Config/Supermodel.ini"
else
    sed -i s/'^New3DEngine=.*/New3DEngine=0/' "${MODEL3}/Config/Supermodel.ini"    
fi

# Throttle
if [ "${THROTTLE}" == 'auto' ] || [ "${THROTTLE}" == 'on' ]; then
    sed -i s/'^Throttle=.*/Throttle=1/' "${MODEL3}/Config/Supermodel.ini"
else
    sed -i s/'^Throttle=.*/Throttle=0/' "${MODEL3}/Config/Supermodel.ini"    
fi

# Stretch
if [ "${STRETCH}" == 'auto' ] || [ "${STRETCH}" == '0' ]; then
    sed -i s/'^Stretch=.*/Stretch=0/' "${MODEL3}/Config/Supermodel.ini"
else
    sed -i s/'^Stretch=.*/Stretch=1/' "${MODEL3}/Config/Supermodel.ini"    
fi

# Power PC Frequency
if [ "${POWERPCFREQUENCY}" == 'auto' ]; then
    sed -i s/'^PowerPCFrequency=.*/PowerPCFrequency=100/' "${MODEL3}/Config/Supermodel.ini"
else
    sed -i s/'^PowerPCFrequency=.*/PowerPCFrequency='"${POWERPCFREQUENCY}"'/' "${MODEL3}/Config/Supermodel.ini"    
fi

# ForceFeedback
if [ "${RUMBLE}" == 'auto' ] || [ "${RUMBLE}" == 'on' ]; then
 sed -i s/'^ForceFeedback=.*/ForceFeedback=1/' "${MODEL3}/Config/Supermodel.ini" 
else
    sed -i s/'^ForceFeedback=.*/ForceFeedback=0/' "${MODEL3}/Config/Supermodel.ini" 
fi

# EmulateNet
if [ "${EMULATENET}" == 'auto' ] || [ "${EMULATENET}" == 'off' ]; then
 sed -i s/'^EmulateNet=.*/EmulateNet=0/' "${MODEL3}/Config/Supermodel.ini" 
else
    sed -i s/'^EmulateNet=.*/EmulateNet=1/' "${MODEL3}/Config/Supermodel.ini" 
fi

#Sempre executa em tela cheia
sed -i s/'^FullScreen=.*/FullScreen=1/' "${MODEL3}/Config/Supermodel.ini"

cd "$MODEL3"
# Executa o jogo ou o configurador
if [ "${JOGO}" == "${JOGO%zip}zip" ] || [ "${JOGO}" == "${JOGO%ZIP}ZIP" ]; then
 export WINEDLLOVERRIDES="SDL.dll=n,b"
 wine "supermodel.exe" "$JOGO" -flip-stereo -sound-volume=50 -music-volume=200
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