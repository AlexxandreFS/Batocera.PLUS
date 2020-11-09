#!/bin/sh
##
## Batocera.PLUS
##

################################################################################

### PARÂMETROS

JOGO="${1}"
OTIMIZATIONS="${2}" 
RENDER="${3}"
ESYNC="${4}"
DXVK="${5}"
SHOWFPS="${6}"

################################################################################

### CAMINHOS

CEMU_DIR='/opt/Cemu'
CEMU="$HOME/configs/cemu"
SAVE="$HOME/../saves/wiiu"

################################################################################

### NÃO EXECUTA O EMULADOR DUAS VEZES

# Executa o Cemu/Wine se não estiver sendo executado
if [ "$(pidof wineserver)" ]; then
    exit 1
fi

################################################################################

### INSTALAÇÃO DO CEMU

# Instalação do Cemu
if [ ! "$(ls -A "${CEMU}" 2> /dev/null)" ] || [ ! "$(ls -A "${SAVE}"  2> /dev/null)" ]; then
    # Montando o cemu em "system/configs/cemu"
    mkdir -p "$(dirname "${CEMU}/log.txt")"                     || exit $?
    ln -s  "${CEMU}/log.txt" "${HOME}/logs/cemu.log"
    cp -f  "${CEMU_DIR}/emulator/resources"            "${CEMU}" || exit $?
    cp -f  "${CEMU_DIR}/cemuextras/sharedFonts"        "${CEMU}" || exit $?
    cp -f  "${CEMU_DIR}/cemuhook/keystone.dll"         "${CEMU}" || exit $?
    cp -f  "${CEMU_DIR}/emulator/Cemu.exe"             "${CEMU}" || exit $?
    cp -f  "${CEMU_DIR}/cemuextras/cemuhook.ini"       "${CEMU}" || exit $?
    cp -f  "${CEMU_DIR}/cemuhook/dbghelp.dll"          "${CEMU}" || exit $?
    cp -f  "${CEMU_DIR}/cemuextras/keys.txt"           "${CEMU}" || exit $?
    cp -f  "${CEMU_DIR}/fakefiles/otp.bin"             "${CEMU}" || exit $?
    cp -f  "${CEMU_DIR}/fakefiles/seeprom.bin"         "${CEMU}" || exit $?
    cp -f  "${CEMU_DIR}/cemuextras/settings.xml"       "${CEMU}" || exit $?

    # Montando o cemu em "share/save/wiiu"
    mkdir -p "${SAVE}/hfiomlc01"                                 || exit $?
    cp -rf "${CEMU_DIR}/cemuextras/controllerProfiles" "${SAVE}" || exit $?
    cp -rf "${CEMU_DIR}/emulator/gameProfiles"         "${SAVE}" || exit $?
    cp -rf "${CEMU_DIR}/emulator/graphicPacks"         "${SAVE}" || exit $?
    cp -rf "${CEMU_DIR}/cemuhook/graphicPacks"         "${SAVE}" || exit $?
    cp -rf "${CEMU_DIR}/cemuextras/graphicPacks"       "${SAVE}" || exit $?
    cp -rf "${CEMU_DIR}/fakefiles/mlc01"               "${SAVE}" || exit $?
    cp -rf "${CEMU_DIR}/emulator/shaderCache"          "${SAVE}" || exit $?

    # Criando links simbólicos para a pasta "system/configs/cemu"
    ln -sf "${SAVE}/"* "${CEMU}"
fi

################################################################################

### SANITY CHECK

# Checa se a interface foi executada de forma correta na última vez
# Esse site salvou minha vida https://dwaves.de/tools/escape/
if [ "$(grep '<check_update>true<\/check_update>' "${CEMU}/settings.xml" )" ]; then
    sed -i 's/<check_update>true<\/check_update>/<check_update>false<\/check_update>/' "${CEMU}/settings.xml"
fi

################################################################################

### LINGUAGEM

SLANG="$(batocera-settings -command load -key system.language)"
case ${SLANG} in
    fr_FR)             sed -i 's/<language>.*/<language>79<\/language>/'  "${CEMU}/settings.xml" ;;
    en_US|en_GB|eu_ES) sed -i 's/<language>.*/<language>57<\/language>/'  "${CEMU}/settings.xml" ;;
    de_DE)             sed -i 's/<language>.*/<language>88<\/language>/'  "${CEMU}/settings.xml" ;;
    pt_BR)             sed -i 's/<language>.*/<language>153<\/language>/' "${CEMU}/settings.xml" ;;
    es_ES)             sed -i 's/<language>.*/<language>179<\/language>/' "${CEMU}/settings.xml" ;;
    it_IT)             sed -i 's/<language>.*/<language>109<\/language>/' "${CEMU}/settings.xml" ;;
    tr_TR)             sed -i 's/<language>.*/<language>214<\/language>/' "${CEMU}/settings.xml" ;;
    zh_CN)             sed -i 's/<language>.*/<language>44<\/language>/'  "${CEMU}/settings.xml" ;;
 esac
 
 ################################################################################
 
### OTIMIZAÇÕES

if [ "${OTIMIZATIONS}" == 'nvidia' ] ; then
    export __GL_THREADED_OPTIMIZATIONS=1
    export vblank_mode=0
elif [ "${OTIMIZATIONS}" == 'amd' ] ; then
    export R600_DEBUG=nohyperz
    export mesa_glthread=true
    export vblank_mode=0
elif [ "${OTIMIZATIONS}" == 'intel' ] ; then
    export MESA_GL_VERSION_OVERRIDE=4.5COMPAT
    export vblank_mode=0
fi

################################################################################

### RENDER

if [ "${RENDER}" == 'auto' ] || [ "${RENDER}" == 'opengl' ]; then
    sed -i '/<Graphic>/!b;n;c\        <api>0</api>' "${CEMU}/settings.xml"
else
    sed -i '/<Graphic>/!b;n;c\        <api>1</api>' "${CEMU}/settings.xml"
fi

################################################################################

### ESYNC
if [ "${ESYNC}" == 'on' ] || [ "${ESYNC}" == 'off' ]; then
    export WINEESYNC=1
fi

################################################################################

### FSYNC (Futura implementação)

#if [ "${FSYNC}" == 'on' ]; then
#    export WINEFSYNC=1
#fi

################################################################################

### DXVK

# Se não ativar o DXVK as informações de VRAM utilizada não aparecem quando SHOW FPS está ativado (será resolvido de outra forma no futuro)
if [ "${DXVK}" == 'on' ] || [ "${DXVK}" == 'auto' ] || [ "${SHOWFPS}" != 'auto' ]; then
    export DXVK=1
fi

################################################################################

### SHOWFPS

if [ "${SHOWFPS}" != 'auto' ]; then
    case $SHOWFPS in
        topleft)      sed -i '/<Overlay>/!b;n;c\            <Position>1</Position>' "${CEMU}/settings.xml" ;;
        topcenter)    sed -i '/<Overlay>/!b;n;c\            <Position>2</Position>' "${CEMU}/settings.xml" ;;
        topright)     sed -i '/<Overlay>/!b;n;c\            <Position>3</Position>' "${CEMU}/settings.xml" ;;
        bottonleft)   sed -i '/<Overlay>/!b;n;c\            <Position>4</Position>' "${CEMU}/settings.xml" ;;
        bottoncenter) sed -i '/<Overlay>/!b;n;c\            <Position>5</Position>' "${CEMU}/settings.xml" ;;
        bottonright)  sed -i '/<Overlay>/!b;n;c\            <Position>6</Position>' "${CEMU}/settings.xml" ;;
    esac
else
    sed -i '/<Overlay>/!b;n;c\            <Position>0</Position>'                   "${CEMU}/settings.xml"
fi

################################################################################

### CAPTURA O JOGO

# Checa se tem uma rom válida na variável JOGO
# Este também é o gatilho pra decidir se o GUI será aberto ou se o jogo será executado em linha de comando

EXT='.wud .wux .iso .wad .rpx .elf .WUD .WUX .ISO .WAD .RPX .ELF'

for i in ${EXT}; do
    if [ "$(echo "${JOGO}" | grep "${i}")" ]; then
        JOGO="$(echo "Z:${JOGO}" | sed -e 's#/#\\#g')"
        break
    fi
done

################################################################################

### UPDATE

# Ativa autoupdate do Cemu se ele for executado pelo menu F1
if [ "$(grep '<check_update>false<\/check_update>' "${CEMU}/settings.xml" )" ] && [ "${JOGO}" == '' ]; then
    sed -i 's/<check_update>false<\/check_update>/<check_update>true<\/check_update>/' "${CEMU}/settings.xml"
fi

################################################################################

### AVISO DOS CONTROLES

# É sempre bom avisar ao usuário porque o controle dele não funciona.
if ! [ "$(ls -1 "${CEMU}/controllerProfiles" | grep '.txt' | tail -n 1)" ] && [ "${JOGO}" == '' ]; then
      /bin/echo -e "\nAVISO\nConfigure um controle\npara o Cemu no menu F1" | LC_ALL=C HOME=/userdata/system DISPLAY=:0.0 osd_cat -f -*-*-bold-*-*-*-32-120-*-*-*-*-*-* -cred -s 2 -d 4 -l 100 -cgreen -o 480 -A center
fi

################################################################################

### EXECUTA O JOGO OU O CONFIGURADOR

# Habilita as dependências necessárias para o cemuhook
export WINEDLLOVERRIDES='keystone.dll=n,b;dbghelp.dll=n,b'

# Captura a resolução da tela antes de iniciar o jogo
RES_START="$(batocera-resolution currentMode)"

# Executa o Cemu com as configurações selecionadas
if [ "${JOGO}" == '' ]; then
    wine-lutris "${CEMU}/Cemu.exe"
    sed -i 's/<check_update>true<\/check_update>/<check_update>false<\/check_update>/' "${CEMU}/settings.xml"
else
    wine-lutris "${CEMU}/Cemu.exe" -f -g "${JOGO}"
fi

################################################################################

### FINALIZA A EXECUÇÃO DO JOGO

# Aguarda o Cemu encerrar a execução
while [ "$(pidof wineserver)" ]; do
    sleep 1
done

# Restaura a resolução do jogo caso tenha mudado
RES_STOP="$(batocera-resolution currentResolution)"
if [ "${RES_START}" != "${RES_STOP}" ]; then
    batocera-resolution setMode "${RES_START}"
fi

exit 0