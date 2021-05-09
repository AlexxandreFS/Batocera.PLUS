#!/bin/sh
##
## Batocera.PLUS
##
## Código escrito por: Sérgio de Carvalho Júnior
## Colaborador: Alexandre Freire dos Santos
## 
## Linha de comando:
## Cemu.sh [ROM] [RENDER] [SYNC] [SHOWFPS] [MOUSE] [P1GUID]
##
## ROM = Caminho do jogo até a iso ou rpx
## RENDER = vulkan, opengl ou auto
## SYNC = esync, fsync ou auto
## SHOWFPS = on, off ou auto
## MOUSE = on, off ou auto
## PIGUID = parâmetro do emulatorlauncher.sh
## INTEL = use new intel graphics
##
## SITE QUE AJUDOU NA MONTAGEM DESTE SCRIPT
## https://synappsis.wordpress.com/category/qt/

################################################################################

### PARÂMETROS

JOGO="${1}"
RENDER="${2}"
SYNC="${3}"
SHOWFPS="${4}"
MOUSE="${5}"
P1GUID="${6}"
INTEL="${7}"

#echo "${JOGO}" "${RENDER}" "${SYNC}" "${SHOWFPS}" "${MOUSE}" "${P1GUID}" "${INTEL}" > "${HOME}/../COMANDO.txt"

################################################################################

### CAMINHOS

CEMU_DIR='/opt/Cemu'
CEMU="$HOME/configs/cemu"
SAVE="$HOME/../saves/wiiu"
WINE="$HOME/../saves/wiiu/wine"

################################################################################

### EXPORTS

export WINEDLLOVERRIDES='keystone.dll=n,b;dbghelp.dll=n,b'
export WINEPREFIX="${SAVE}/wine"
export vblank_mode=0
export mesa_glthread=true
export __GL_THREADED_OPTIMIZATIONS=1

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
    echo " INTEL = use new intel graphics"
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

if [ "${2}" == ' ' ]; then
    echo " Ulimit ativo com limite de $(ulimit -Hn) arquivos abertos"
    echo " Cemu sendo executado com as configurações default"
fi

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

### FORCE SOME SETTINGS

if [ "${JOGO}" == '' ]; then
    sed -i 's/<fullscreen>.*/<fullscreen>false<\/fullscreen>/'       "${CEMU}/settings.xml"
	sed -i 's/<check_update>.*/<check_update>true<\/check_update>/'  "${CEMU}/settings.xml"
else
    sed -i 's/<fullscreen>.*/<fullscreen>true<\/fullscreen>/'        "${CEMU}/settings.xml"
	sed -i 's/<check_update>.*/<check_update>false<\/check_update>/' "${CEMU}/settings.xml"
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

### RENDER

if [ "${RENDER}" == 'auto' ] || [ "${RENDER}" == 'opengl' ] || [ "${RENDER}" == '' ]; then
    sed -i '/<Graphic>/!b;n;c\        <api>0</api>' "${CEMU}/settings.xml"
else
    sed -i '/<Graphic>/!b;n;c\        <api>1</api>' "${CEMU}/settings.xml"
fi

################################################################################

### ATUALIZA OU CRIA O PREFIXO SE NECESSÁRIO

WINE_VERSION="$(stat -t '/opt/Wine/wine-lutris/share/wine/wine.inf' | awk '{print $12}')"
WINE_VERSION_NEW="$(cat -e "${WINE}/.update-timestamp" | cut -d '^' -f 1)"
	
if [ "${WINE_VERSION}" != "${WINE_VERSION_NEW}" ]; then
    rm -rf "${WINE}"
	mkdir -p "${WINE}/drive_c/windows/mono"
	ln -s "/opt/Wine/apps/mono" "${WINE}/drive_c/windows/mono/mono-2.0"
	wine-lutris /opt/Wine/apps/directx_Jun2010_redist/DXSETUP.exe /silent

	while [ "$(pidof wineserver)" ]; do
        sleep 1
    done
fi

################################################################################

### SYNC

case ${SYNC} in
    esync)
     export WINEESYNC=1
     export WINEFSYNC=0
     ;;
    fsync)
     export WINEFSYNC=1
     export WINEESYNC=0
     ;;
    auto)
     export WINEESYNC=0
     export WINEFSYNC=0
     ;;
esac

################################################################################

### SHOWFPS

if [ "${SHOWFPS}" != 'auto' ]; then
    case ${SHOWFPS} in
        mangohud_default)
            export MANGOHUD=1
            export MANGOHUD_CONFIGFILE=/opt/MangoHud/profiles/default.conf
            ;;
        mangohud_more_info)
            export MANGOHUD=1
            export MANGOHUD_CONFIGFILE=/opt/MangoHud/profiles/more_info.conf
            ;;
        mangohud_smarty)
            export MANGOHUD=1
            export MANGOHUD_CONFIGFILE=/opt/MangoHud/profiles/smarty.conf
            ;;
        goverlay) #user-config
            export MANGOHUD=1
            if [ -f "${HOME}/.config/goverlay/MangoHud.conf" ]; then
                export MANGOHUD_CONFIGFILE="${HOME}/.config/goverlay/MangoHud.conf"
            else
                export MANGOHUD_CONFIGFILE=/opt/MangoHud/profiles/default.conf
            fi
            ;;
        dxvk_hud)
            # Execute este código deve ser executado sempre depois do bloco do DirectX Engine.
            if [ "${DXVK}" == '1' ]; then
                export DXVK=2
            else
                export MANGOHUD=1
                export MANGOHUD_CONFIGFILE=/opt/MangoHud/profiles/default.conf
            fi
            ;;
    esac
 fi
################################################################################

### MOUSE POINTER

if [ "${MOUSE}" == 'on' ] || [ "${JOGO}" == '' ]; then
    mouse-pointer on
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

# Captura a resolução da tela antes de iniciar o jogo
RES_START="$(batocera-resolution currentMode)"

# Executa o Cemu com as configurações selecionadas
if [ "${JOGO}" == '' ]; then
    wine-lutris "${CEMU}/Cemu.exe"
elif [ "${JOGO}" != '' ] && [ "${INTEL}" == 'on' ]; then
    wine-lutris "${CEMU}/Cemu.exe" -legacy -g "${JOGO}"
else
    wine-lutris "${CEMU}/Cemu.exe" -g "${JOGO}"
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
