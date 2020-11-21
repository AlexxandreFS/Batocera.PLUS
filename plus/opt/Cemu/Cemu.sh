#!/bin/sh
##
## Batocera.PLUS
##
## Código escrito por: Sérgio de Carvalho Júnior
## Colaborador: Alexandre Freire dos Santos
## 
## Linha de comando:
## Cemu.sh [ROM] [OTIMIZATIONS] [RENDER] [SYNC] [DXVK] [SHOWFPS] [MOUSE] [P1GUID]
##
## ROM = Caminho do jogo até a iso ou rpx
## OTIMIZATIONS = nvidia, amd, intel ou auto
## RENDER = vulkan, opengl ou auto
## SYNC = esync, fsync ou auto
## DXVK = on, off ou auto
## SHOWFPS = on, off ou auto
## MOUSE = on, off ou auto
## PIGUID = parâmetro do emulatorlauncher.sh

################################################################################

### PARÂMETROS

JOGO="${1}"
OTIMIZATIONS="${2}" 
RENDER="${3}"
SYNC="${4}"
DXVK="${5}"
SHOWFPS="${6}"
MOUSE="${7}"
P1GUID="${8}"

################################################################################

### CAMINHOS

CEMU_DIR='/opt/Cemu'
CEMU="$HOME/configs/cemu"
SAVE="$HOME/../saves/wiiu"

################################################################################


### HELP

function help()
{
    echo " Cemu launcher for Batocera.PLUS"
    echo " "
    echo " Codigo escrito por: Sergio de Carvalho Junior"
    echo " Colaborador: Alexandre Freire dos Santos"
    echo " "
    echo " Linha de comando:"
    echo " Cemu.sh [ROM] [OTIMIZATIONS] [RENDER] [SYNC] [DXVK] [SHOWFPS] [MOUSE] [P1GUID]"
    echo " "
    echo " ROM = Caminho do jogo até a .iso ou .rpx"
    echo " OTIMIZATIONS = nvidia, amd, intel ou auto"
    echo " RENDER = vulkan, opengl ou auto"
    echo " SYNC = esync, fsync ou auto"
    echo " DXVK = on, off ou auto"
    echo " SHOWFPS = on, off ou auto"
    echo " MOUSE = on, off ou auto"
    echo " PIGUID = parâmetro do emulatorlauncher.sh (OPICIONAL)"
    echo " "
}

if [ "${1}" == '--help' ]; then
    help
    exit 0
fi

################################################################################

### NÃO EXECUTA O EMULADOR DUAS VEZES

if [ "$(pidof wineserver)" ]; then
    echo " Cemu launcher ja esta sendo executado"
    exit 1
fi

################################################################################

### LAUNCHER INFO

echo " Cemu launcher for Batocera.PLUS"
echo " "
echo " Codigo escrito por: Sergio de Carvalho Junior"
echo " Colaborador: Alexandre Freire dos Santos"
echo " "


################################################################################

### INSTALAÇÃO DO CEMU

if [ ! "$(ls -A "${CEMU}" 2> /dev/null)" ] || [ ! "$(ls -A "${SAVE}"  2> /dev/null)" ]; then
    # Montando o cemu em "system/configs/cemu"
    mkdir -p "$(dirname "${CEMU}/log.txt")"                      || exit $?
    ln -sf "${CEMU}/log.txt" "${HOME}/logs/cemu.log"
    cp -rf "${CEMU_DIR}/emulator/resources"            "${CEMU}" || exit $?
    cp -rf "${CEMU_DIR}/cemuextras/sharedFonts"        "${CEMU}" || exit $?
    cp -f  "${CEMU_DIR}/cemuhook/keystone.dll"         "${CEMU}" || exit $?
    cp -f  "${CEMU_DIR}/emulator/Cemu.exe"             "${CEMU}" || exit $?
    cp -f  "${CEMU_DIR}/cemuextras/cemuhook.ini"       "${CEMU}" || exit $?
    cp -f  "${CEMU_DIR}/cemuhook/dbghelp.dll"          "${CEMU}" || exit $?
    cp -f  "${CEMU_DIR}/cemuextras/keys.txt"           "${CEMU}" || exit $?
    cp -f  "${CEMU_DIR}/fakefiles/otp.bin"             "${CEMU}" || exit $?
    cp -f  "${CEMU_DIR}/fakefiles/seeprom.bin"         "${CEMU}" || exit $?
    cp -f  "${CEMU_DIR}/cemuextras/settings.xml"       "${CEMU}" || exit $?

    # Montando a pasta do usuário em "share/save/wiiu"
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

### SYNC
if [ "${SYNC}" == 'esync' ]; then
    export WINEESYNC=1
elif [ "${SYNC}" == 'fsync' ]; then
    export WINEFSYNC=1
else
    export WINEESYNC=0
    export WINEFSYNC=0
fi

################################################################################

### DXVK

# Se não ativar o DXVK as informações de VRAM utilizada não aparecem quando SHOW FPS está ativado (será resolvido de outra forma no futuro)
if [ "${DXVK}" == 'on' ] ; then
    export DXVK=1
    export PBA_ENABLE=0
elif [ "${DXVK}" == 'pba' ]; then
    export DXVK=0
    export PBA_ENABLE=1
elif [ "${DXVK}" == 'off' ] || [ "${DXVK}" == 'auto' ]; then
    export DXVK=0
	export PBA_ENABLE=0
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
    export DXVK=1
else
    sed -i '/<Overlay>/!b;n;c\            <Position>0</Position>'                   "${CEMU}/settings.xml"
    if [ "${DXVK}" == 'off' ] || [ "${DXVK}" == 'auto' ]; then
        export DXVK=0
    fi
fi

################################################################################

### MOUSE POINTER

if [ "${MOUSE}" == 'on' ] || [ "${JOGO}" == '' ]; then
    mouse-pointer on
elif [ "${MOUSE}" == 'auto' ] || [ "${MOUSE}" == 'off' ]; then
    mouse-pointer off
fi

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

### CAPTURA O JOGO

# Checa se tem uma rom válida na variável JOGO
# Este também é o gatilho pra decidir se o GUI será aberto ou se o jogo será executado em linha de comando

EXT='.wud .wux .iso .wad .rpx .elf .wiiu .WUD .WUX .ISO .WAD .RPX .ELF .WIIU'

for i in ${EXT}; do
    if [ "$(echo "${JOGO}" | grep "${i}")" ]; then
        # Se o jogo estiver dentro de uma pasta
        if [ "$(echo "${JOGO}" | grep ".wiiu")" ] || [ "$(echo "${JOGO}" | grep ".WIIU")" ]; then
            cd "${JOGO}"
            JOGO_NOME="$(find . -type f -iname *.rpx -print -quit | cut -c2- )"
            JOGO="$(echo "Z:${JOGO}${JOGO_NOME}" | sed -e 's#/#\\#g')"
            break
        fi
        # Se o jogo estiver fora de uma pasta
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

### CONTROLES

# Salva um perfil de controle padrão se nenhum for achado
if ! [ "$(ls -1 "${CEMU}/controllerProfiles" | grep '.txt' | tail -n 1)" ]; then
      mkdir -p "${SAVE}/controllerProfiles"
      cp -rf "${CEMU_DIR}/cemuextras/controllerProfiles/"* "${SAVE}/controllerProfiles"
      ln -sf "${SAVE}/controllerProfiles" "${CEMU}"
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

# Desativa variaveis exportadas
export DXVK=0
export PBA_ENABLE=0

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
