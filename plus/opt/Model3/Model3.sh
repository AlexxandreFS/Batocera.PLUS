#!/bin/sh
##
## Batocera.PLUS
##

################################################################################

### PARÂMETROS

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

################################################################################

### CAMINHOS

# Variáveis da instalação do Model 3
MODEL3_DIR='/opt/Model3'

# Variáveis para configuração do Model 3
MODEL3="${HOME}/configs/model3"
SAVE="${HOME}/../saves/model3"

################################################################################

### NÃO EXECUTA O EMULADOR DUAS VEZES

# Executa o Model2/Wine se não estiver sendo executado
if [ "$(pidof supermodel.exe)" ]; then
    exit 1
fi

################################################################################

### INSTALAÇÃO DO MODEL 3

if [ ! "$(ls -A "${MODEL3}" 2> /dev/null)" ] || [ ! "$(ls -A "${SAVE}"  2> /dev/null)" ]; then
    # Montando o model2 em "system/configs/model2"
    mkdir -p "${SAVE}"                              "${MODEL3}" || exit $?

    cp -rf  "${MODEL3_DIR}/emulator/SDL.dll"         "${MODEL3}" || exit $?
    cp -rf  "${MODEL3_DIR}/emulator/Supermodel.exe"  "${MODEL3}" || exit $?
    cp -rf "${MODEL3_DIR}/emulator/Shaders"         "${MODEL3}" || exit $?
    
    # Montando o model2 em "share/save/model2"
    cp -rf "${MODEL3_DIR}/emulator/Config"          "${SAVE}"   || exit $?
    cp -rf "${MODEL3_DIR}/emulator/NVRAM"           "${SAVE}"   || exit $?
    cp -rf "${MODEL3_DIR}/emulator/Saves"           "${SAVE}"   || exit $?

    # Criando links simbólicos para "system/configs/model2"
    ln -sf "${SAVE}/"*                              "${MODEL3}"
fi

################################################################################

### WIDESCREEN

# Ativa WideScreen per-game ou global
case "${WIDESCREEN}" in
    4/3|1/1|16/15|3/2|3/4|4/4|5/4|6/5|7/9|8/7|auto|custom|squarepixel)
        sed -i s/'^WideScreen=.*/WideScreen=0/' "${MODEL3}/Config/Supermodel.ini"
        ;;
    16/9|19/12|19/14|2/1|21/9|30/17|32/9|4/1|8/3)
        sed -i s/'^WideScreen=.*/WideScreen=1/' "${MODEL3}/Config/Supermodel.ini"
        ;;
esac

################################################################################

### RESOLUTION

RES_START="$(batocera-resolution currentMode)"

# Carrega a resolução do sistema configurado pelo emulationstation
if [ "${RESOLUTION}" == 'auto' ]; then
    XRES="$(echo "${RES_START}" | cut -d 'x' -f 1)"
    YRES="$(echo "${RES_START}" | cut -d 'x' -f 2)"

    sed -i s/'^XResolution=.*/XResolution='"${XRES}"'/' "${MODEL3}/Config/Supermodel.ini"
    sed -i s/'^YResolution=.*/YResolution='"${YRES}"'/' "${MODEL3}/Config/Supermodel.ini"
else
    XRES="$(echo "${RESOLUTION}" | cut -d 'x' -f 1)"
    YRES="$(echo "${RESOLUTION}" | cut -d 'x' -f 2)"

    sed -i s/'^XResolution=.*/XResolution='"${XRES}"'/' "${MODEL3}/Config/Supermodel.ini"
    sed -i s/'^YResolution=.*/YResolution='"${YRES}"'/' "${MODEL3}/Config/Supermodel.ini"
fi

################################################################################

### MULTITHREAD

if [ "${MULTITHREAD}" == 'auto' ] || [ "${MULTITHREAD}" == 'off' ]; then
    sed -i s/'^MultiThreaded=.*/MultiThreaded=0/'       "${MODEL3}/Config/Supermodel.ini"
    sed -i s/'^GPUMultiThreaded=.*/GPUMultiThreaded=0/' "${MODEL3}/Config/Supermodel.ini"
else
    sed -i s/'^MultiThreaded=.*/MultiThreaded=1/'       "${MODEL3}/Config/Supermodel.ini"
    sed -i s/'^GPUMultiThreaded=.*/GPUMultiThreaded=1/' "${MODEL3}/Config/Supermodel.ini"
fi

################################################################################

### MULTI TEXTURE

if [ "${MULTITEXTURE}" == 'auto' ] || [ "${MULTITEXTURE}" == 'on' ]; then
    sed -i s/'^MultiTexture=.*/MultiTexture=1/' "${MODEL3}/Config/Supermodel.ini"
else
    sed -i s/'^MultiTexture=.*/MultiTexture=0/' "${MODEL3}/Config/Supermodel.ini"    
fi

################################################################################

### QUADRENDERING

if [ "${QUADRENDERING}" == 'auto' ] || [ "${QUADRENDERING}" == 'on' ]; then
    sed -i s/'^QuadRendering=.*/QuadRendering=1/' "${MODEL3}/Config/Supermodel.ini"
else
    sed -i s/'^QuadRendering=.*/QuadRendering=0/' "${MODEL3}/Config/Supermodel.ini"    
fi

################################################################################

### VSYNC

if [ "${VSYNC}" == 'auto' ] || [ "${VSYNC}" == 'on' ]; then
    sed -i s/'^VSync=.*/VSync=1/' "${MODEL3}/Config/Supermodel.ini"
else
    sed -i s/'^VSync=.*/VSync=0/' "${MODEL3}/Config/Supermodel.ini"    
fi

################################################################################

### NEW 3D ENGINE

if [ "${NEW3DENGINE}" == 'auto' ] || [ "${NEW3DENGINE}" == 'on' ]; then
    sed -i s/'^New3DEngine=.*/New3DEngine=1/' "${MODEL3}/Config/Supermodel.ini"
else
    sed -i s/'^New3DEngine=.*/New3DEngine=0/' "${MODEL3}/Config/Supermodel.ini"    
fi

################################################################################

### THROTTLE

if [ "${THROTTLE}" == 'auto' ] || [ "${THROTTLE}" == 'on' ]; then
    sed -i s/'^Throttle=.*/Throttle=1/' "${MODEL3}/Config/Supermodel.ini"
else
    sed -i s/'^Throttle=.*/Throttle=0/' "${MODEL3}/Config/Supermodel.ini"    
fi

################################################################################

### STRETCH

if [ "${STRETCH}" == 'auto' ] || [ "${STRETCH}" == '0' ]; then
    sed -i s/'^Stretch=.*/Stretch=0/' "${MODEL3}/Config/Supermodel.ini"
else
    sed -i s/'^Stretch=.*/Stretch=1/' "${MODEL3}/Config/Supermodel.ini"    
fi

################################################################################

### POWER PC FREQUENCY

if [ "${POWERPCFREQUENCY}" == 'auto' ]; then
    sed -i s/'^PowerPCFrequency=.*/PowerPCFrequency=100/'                     "${MODEL3}/Config/Supermodel.ini"
else
    sed -i s/'^PowerPCFrequency=.*/PowerPCFrequency='"${POWERPCFREQUENCY}"'/' "${MODEL3}/Config/Supermodel.ini"    
fi

################################################################################

### RUMBLE

if [ "${RUMBLE}" == 'auto' ] || [ "${RUMBLE}" == 'on' ]; then
    sed -i s/'^ForceFeedback=.*/ForceFeedback=1/' "${MODEL3}/Config/Supermodel.ini" 
else
    sed -i s/'^ForceFeedback=.*/ForceFeedback=0/' "${MODEL3}/Config/Supermodel.ini" 
fi

################################################################################

### EMULATENET

if [ "${EMULATENET}" == 'auto' ] || [ "${EMULATENET}" == 'off' ]; then
    sed -i s/'^EmulateNet=.*/EmulateNet=0/' "${MODEL3}/Config/Supermodel.ini" 
else
    sed -i s/'^EmulateNet=.*/EmulateNet=1/' "${MODEL3}/Config/Supermodel.ini" 
fi

# Sempre executa em tela cheia
sed -i s/'^FullScreen=.*/FullScreen=1/'     "${MODEL3}/Config/Supermodel.ini"

################################################################################

### EXECUTA O JOGO

cd "${MODEL3}"

# Executa o jogo ou o configurador
if [ "${JOGO}" == "${JOGO%zip}zip" ] || [ "${JOGO}" == "${JOGO%ZIP}ZIP" ]; then
    export WINEDLLOVERRIDES='SDL.dll=n,b'
    wine-lutris 'supermodel.exe' "${JOGO}" -flip-stereo -sound-volume=50 -music-volume=200
fi

################################################################################

### FINALIZA A EXECUÇÃO DO JOGO

for i in {1..30}; do
    if [ "$(pidof wineserver)" ]; then
        # Aguarda encerrar a execução do jogo
        sleep 1
    fi

    if [ "${i}" == '30' ]; then
        killwine
    fi
done

# Restaura a resolução, caso o jogo tenha mudado ### 
RES_STOP="$(batocera-resolution currentResolution)"
if [ "${RES_START}" != "${RES_STOP}" ]; then
    batocera-resolution setMode "${RES_START}"
fi

exit 0
