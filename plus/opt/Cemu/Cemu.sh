#!/bin/sh
##
## Batocera.PLUS
##
## Código escrito por: Sérgio de Carvalho Júnior
## Colaborador: Alexandre Freire dos Santos
## 
## Linha de comando:
## Cemu.sh [ROM] [RENDER] [SYNC] [P1GUID]
##
## ROM = Caminho do jogo até a iso ou rpx
## RENDER = vulkan, opengl ou auto
## SYNC = esync, fsync ou auto
## INTEL = use new intel graphics
##
## SITE QUE AJUDOU NA MONTAGEM DESTE SCRIPT
## https://synappsis.wordpress.com/category/qt/

################################################################################

### PARÂMETROS

JOGO="${1}"
RENDER="${2}"
SYNC="${3}"
INTEL="${4}"

################################################################################

### CAMINHOS

CEMU_DIR='/opt/Cemu'
CEMU="${HOME}/configs/cemu"
SAVE="${HOME}/../saves/wiiu"
WINE=proton-valve
WINERUN="${WINE}-64"

#echo ["$(date +%T)"] "Running: ${WINE} cemu.exe ${JOGO} ${RENDER} ${SYNC} ${P1GUID} ${INTEL}" > "${HOME}/logs/cemu_launch.log"

################################################################################

### EXPORTS

export WINEPREFIX="${SAVE}/wine"
export WINEDLLOVERRIDES='keystone.dll=n,b;cemuhook.dll=n,b'
export vblank_mode=0
export mesa_glthread=true
export __GL_THREADED_OPTIMIZATIONS=1

################################################################################

### HELP

function help()
{
    echo ' Cemu launcher for Batocera.PLUS'
    echo
    echo ' Codigo escrito por: Sergio de Carvalho Junior'
    echo ' Colaborador: Alexandre Freire dos Santos'
    echo
    echo ' Linha de comando:'
    echo ' Cemu.sh [ROM] [OTIMIZATIONS] [RENDER] [SYNC] [DXVK] [P1GUID]'
    echo
    echo ' ROM          = Caminho do jogo até a .iso ou .rpx'
    echo ' RENDER       = vulkan, opengl ou auto'
    echo ' SYNC         = esync, fsync ou auto'
    echo ' INTEL        = use new intel graphics'
    echo
}

if [ "${JOGO}" == '--help' ]; then
    help
    exit 0
fi

################################################################################

### NÃO EXECUTA O EMULADOR DUAS VEZES

if [ "$(pidof wineserver)" ]; then
    echo ' Cemu launcher ja esta sendo executado'
    exit 1
fi

################################################################################

### LAUNCHER INFO

echo ' Cemu launcher for Batocera.PLUS'
echo ' '
echo ' Codigo escrito por: Sergio de Carvalho Junior'
echo ' Colaborador: Alexandre Freire dos Santos'
echo ' '

if [ "${RENDER}" == ' ' ]; then
    echo " Ulimit ativo com limite de $(ulimit -Hn) arquivos abertos"
    echo ' Cemu sendo executado com as configurações default'
fi

################################################################################

### INSTALAÇÃO DO CEMU

if [ ! "$(ls -A "${CEMU}" 2> /dev/null)" ] || [ ! "$(ls -A "${SAVE}"  2> /dev/null)" ]; then
    # Montando o cemu em "system/configs/cemu"
    mkdir -p "$(dirname "${CEMU}/log.txt")" "${CEMU}/sharedFonts"|| exit $?
    cp -rf "${CEMU_DIR}/emulator/resources"            "${CEMU}" || exit $?
    cp -f  "${CEMU_DIR}/cemuhook/keystone.dll"         "${CEMU}" || exit $?
    cp -f  "${CEMU_DIR}/emulator/Cemu.exe"             "${CEMU}" || exit $?
    cp -f  "${CEMU_DIR}/cemuextras/cemuhook.ini"       "${CEMU}" || exit $?
    cp -f  "${CEMU_DIR}/cemuhook/cemuhook.dll"         "${CEMU}" || exit $?
    cp -f  "${CEMU_DIR}/cemuextras/keys.txt"           "${CEMU}" || exit $?
    cp -f  "${CEMU_DIR}/fakefiles/otp.bin"             "${CEMU}" || exit $?
    cp -f  "${CEMU_DIR}/fakefiles/seeprom.bin"         "${CEMU}" || exit $?
    cp -f  "${CEMU_DIR}/cemuextras/settings.xml"       "${CEMU}" || exit $?

    # Montando a pasta do usuário em "share/save/wiiu"
    mkdir -p "${SAVE}/hfiomlc01" "${WINEPREFIX}"                 || exit $?
    cp -rf "${CEMU_DIR}/cemuextras/controllerProfiles" "${SAVE}" || exit $?
    cp -rf "${CEMU_DIR}/emulator/gameProfiles"         "${SAVE}" || exit $?
    cp -rf "${CEMU_DIR}/cemuextras/graphicPacks"       "${SAVE}" || exit $?
    cp -rf "${CEMU_DIR}/fakefiles/mlc01"               "${SAVE}" || exit $?
    cp -rf "${CEMU_DIR}/emulator/shaderCache"          "${SAVE}" || exit $?

    # Criando links simbólicos para a pasta "system/configs/cemu"
    FOLDERS='controllerProfiles gameProfiles graphicPacks mlc01 shaderCache'
    for i in $FOLDERS; do
        ln -sf "${SAVE}/${i}" "${CEMU}"
    done

    # Compatibilidade com a instalação de DLC e UPDATES pela interface com cemu
    mkdir -p "{HOME}/../saves/windows/wine-profiles/users/cemu"
    ln -sf "${SAVE}/mlc01" "{HOME}/../saves/windows/wine-profiles/users/cemu"

    ln -sf "${CEMU}/log.txt" "${HOME}/logs/cemu.log"
    ln -sf '/usr/share/fonts/truetype/msttcorefonts/CafeCn.ttf'  "${CEMU}/sharedFonts"
    ln -sf '/usr/share/fonts/truetype/msttcorefonts/CafeKr.ttf'  "${CEMU}/sharedFonts"
    ln -sf '/usr/share/fonts/truetype/msttcorefonts/CafeStd.ttf' "${CEMU}/sharedFonts"
    ln -sf '/usr/share/fonts/truetype/msttcorefonts/CafeTw.ttf'  "${CEMU}/sharedFonts"
fi

################################################################################

### ATUALIZA OU CRIA O PREFIXO SE NECESSÁRIO

if [ -e "${WINEPREFIX}/.update-timestamp" ]; then # if wine version has changed
    SDIR_VERSION="$(cat -e "${WINEPREFIX}/.update-timestamp" | cut -d '^' -f 1)"
    OPT_WINE="$(stat -t "/opt/Wine/$WINE/share/wine/wine.inf" | awk '{print $12}')"
    if [ "${OPT_WINE}" != "${SDIR_VERSION}" ] && [ -e "${WINEPREFIX}" ]; then
        rm -r "${WINEPREFIX}"
    fi
fi

if [ ! "$(ls -A "${WINEPREFIX}" 2> /dev/null)" ]; then # if wineprefix if does not exist
    export INSTALL_EXTRAS=1
    mkdir -p "${WINEPREFIX}"
fi

################################################################################

### FORCE SOME SETTINGS

if [ "${JOGO}" == '' ]; then
    sed -i 's/<fullscreen>.*/<fullscreen>false<\/fullscreen>/'       "${CEMU}/settings.xml"
    sed -i 's/<check_update>.*/<check_update>true<\/check_update>/'  "${CEMU}/settings.xml"
else
    sed -i 's/<fullscreen>.*/<fullscreen>true<\/fullscreen>/'        "${CEMU}/settings.xml"
    sed -i 's/<check_update>.*/<check_update>false<\/check_update>/' "${CEMU}/settings.xml"
fi

sync

################################################################################

### LINGUAGEM

SLANG="$(batocera-settings -command load -key system.language)"
case ${SLANG} in
    fr_FR)       sed -i 's/<language>.*/<language>80<\/language>/'  "${CEMU}/settings.xml" ;;
    en_US|en_GB) sed -i 's/<language>.*/<language>57<\/language>/'  "${CEMU}/settings.xml" ;;
    de_DE)       sed -i 's/<language>.*/<language>89<\/language>/'  "${CEMU}/settings.xml" ;;
    pt_BR)       sed -i 's/<language>.*/<language>154<\/language>/' "${CEMU}/settings.xml" ;;
    es_ES)       sed -i 's/<language>.*/<language>180<\/language>/' "${CEMU}/settings.xml" ;;
    it_IT)       sed -i 's/<language>.*/<language>110<\/language>/' "${CEMU}/settings.xml" ;;
    tr_TR)       sed -i 's/<language>.*/<language>215<\/language>/' "${CEMU}/settings.xml" ;;
    zh_CN)       sed -i 's/<language>.*/<language>44<\/language>/'  "${CEMU}/settings.xml" ;;
esac

sync
 
################################################################################

### RENDER

if [ "${RENDER}" == 'vulkan' ]; then
    sed -i '/<Graphic>/!b;n;c\        <api>1</api>' "${CEMU}/settings.xml"
else
    sed -i '/<Graphic>/!b;n;c\        <api>0</api>' "${CEMU}/settings.xml"
fi

sync

################################################################################

### SYNC

case ${SYNC} in
    esync)
        export WINEESYNC=1
        ;;
    fsync)
        export WINEFSYNC=1
        ;;
    auto)
        continue
        ;;
esac

################################################################################

### CAPTURA O JOGO

# Checa se tem uma rom válida na variável JOGO
# Este também é o gatilho pra decidir se o GUI será aberto ou se o jogo será executado em linha de comando

if [ -d "${JOGO}" ]; then # Se o jogo for um diretório
    cd "${JOGO}"
    ROM_EXTENSION='.wud .wux .iso .wad .rpx .elf .WUD .WUX .ISO .WAD .RPX .ELF' 
    for i in $ROM_EXTENSION; do
        JOGO_NOME="$(find . -type f -iname *${i} -print -quit | cut -c2- )"
        if [ "$(echo "${JOGO_NOME}" | grep "${i}")" ]; then
            JOGO="$(echo "Z:${JOGO}${JOGO_NOME}" | sed -e 's#/#\\#g')"
            break
        fi
    done
elif [ -f "${JOGO}" ]; then # Se o jogo for um arquivo
    JOGO="$(echo "Z:${JOGO}" | sed -e 's#/#\\#g')"
fi

################################################################################

### CONTROLES

# Salva um perfil de controle padrão se nenhum for achado
if ! [ "$(ls -1 "${CEMU}/controllerProfiles" | grep '.txt' | tail -n 1)" ]; then
    mkdir -p "${SAVE}/controllerProfiles"
    cp -rf "${CEMU_DIR}/cemuextras/controllerProfiles/"* "${SAVE}/controllerProfiles"
    ln -sf "${SAVE}/controllerProfiles" "${CEMU}"
fi

################################################################################

### EXECUTA O JOGO OU O CONFIGURADOR

# Executa o Cemu com as configurações selecionadas
if [ "${JOGO}" == '' ]; then
    $WINERUN "${CEMU}/Cemu.exe"
elif [ "${JOGO}" != '' ] && [ "${INTEL}" == 'on' ]; then
    $WINERUN "${CEMU}/Cemu.exe" -legacy -g "${JOGO}"
else
    $WINERUN "${CEMU}/Cemu.exe" -g "${JOGO}"
fi

################################################################################

### FINALIZA A EXECUÇÃO DO JOGO

# Aguarda o Cemu encerrar a execução
while [ "$(pidof wineserver)" ]; do
    sleep 1
done

exit 0
