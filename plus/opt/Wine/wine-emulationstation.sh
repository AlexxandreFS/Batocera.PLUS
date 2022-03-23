#!/bin/bash
###
### Batocera.PLUS
### Alexandre Freire dos Santos
###
### Este script é usado para processar as opções configuradas pelo usuário no
### emulationstation para o wine.
###
################################################################################

SYSTEM="${1}"
EMULATOR="${2}"
CORE="${3}"
ROM="${4}"
P1GUID="${5}"

readonly SHARE="${6}"
readonly SAVES_DIR="${7}"
readonly EXTRACTIONS_DIR="${8}"
readonly LOG_DIR="${9}"

readonly SCRIPT="${10}"
readonly SYNC="${11}"
readonly DIRECTX="${12}"
readonly MANGOHUD="${13}"
readonly VKBASALT="${14}"
readonly OPTIMIZATIONS="${15}"
readonly INGAME_VIDEOS="${16}"
readonly JOYPAD="${17}"
readonly VIDEOMODE="${18}"

################################################################################

### Captura o nome da rom sem extenção.

ROM_NAME="$(basename "${ROM}")"

if [ "${ROM_NAME}" == "${ROM_NAME%plus}plus" ]; then
    ROM_NAME="${ROM_NAME%.plus}"
elif [ "${ROM_NAME}" == "${ROM_NAME%PLUS}PLUS" ]; then
    ROM_NAME="${ROM_NAME%.PLUS}"
else
    exit 1
fi

################################################################################

### Monta e acessa o diretório do jogo.

if [ -d "${ROM}" ]; then
    cd "${ROM}"
elif [ -f "${ROM}" ]; then
    # Somente para roms compatactadas no formato squashfs

    MOUNT_DIR="${EXTRACTIONS_DIR}/$(basename "${ROM}")"

    OVERLAY_DIR='/tmp/wine_overlay'
    LOWER_DIR="${OVERLAY_DIR}/lowerdir"
    UPPER_DIR="${OVERLAY_DIR}/upperdir"
    WORK_DIR="${OVERLAY_DIR}/workdir"

    GAME_SAVE_DIR="${SAVES_DIR}/${SYSTEM}/$(basename "${ROM}" .plus)"
    GAME_SAVE_DIR="${GAME_SAVE_DIR%.PLUS}"

    mkdir -p "${MOUNT_DIR}" \
             "${LOWER_DIR}" \
             "${UPPER_DIR}" \
             "${WORK_DIR}"

    if mount -o ro "${ROM}" "${LOWER_DIR}"; then
        # Restaura as modificações feitas na pasta do próprio jogo durante o gameplay
        if [ -d "${GAME_SAVE_DIR}" ]; then
            rsync -a --delete "${GAME_SAVE_DIR}/" "${UPPER_DIR}"
        fi

        if mount -t overlay -o rw,lowerdir="${LOWER_DIR}",upperdir="${UPPER_DIR}",workdir="${WORK_DIR}" overlay "${MOUNT_DIR}"; then
            ROM="${MOUNT_DIR}"
            cd "${MOUNT_DIR}"
        else
            exit $?
        fi
    else
        exit $?
    fi
else
    exit 1
fi

################################################################################

### Procura pelo executável do jogo.
### Formatos aceitos: batocera.plus, batocera.plus.exe, .plus.exe, .PLUS.EXE, .exe, .EXE

GAME_EXE=''

if [ -f 'batocera.plus' ]; then
    # Ignora script batocera.plus se ativado na interface do ES.

    if [ "${SCRIPT}" == 'auto' ] || [ "${SCRIPT}" == 'on' ]; then
        # Converte quebra de linhas para o padrão unix.
        if [ "$(dos2unix --info=c "${GAME_EXE}")" ]; then
            dos2unix "${GAME_EXE}"
        fi

        # Ativa a permisão de executável no script.
        if ! [ -x "${GAME_EXE}" ]; then
            chmod +x "${GAME_EXE}"
        fi

        GAME_EXE='batocera.plus'
    fi
fi

if [ -f 'batocera.plus' ] && [ -z "${GAME_EXE}" ]; then
    if [ -f 'batocera.plus.exe' ]; then
        GAME_EXE='batocera.plus.exe'
    fi
fi

if [ -z "${GAME_EXE}" ]; then
    GAME_EXE="$(ls -1 | grep -i '.plus.exe$' | head -n 1)"
fi

if [ -z "${GAME_EXE}" ]; then
    GAME_EXE="$(ls -1 | grep -i '.exe$' | head -n 1)"
fi

if [ -z "${GAME_EXE}" ]; then
    GAME_EXE="$(find . -type f -iname batocera.plus.exe -print -quit)"
fi

if [ -z "${GAME_EXE}" ]; then
    GAME_EXE="$(find . -type f -iname *.plus.exe -print -quit)"
fi

if [ -z "${GAME_EXE}" ]; then
    GAME_EXE="$(find . -type f -iname *.exe -print -quit)"
fi

if [ -z "${GAME_EXE}" ]; then
    GAME_EXE='explorer'
fi

cd "$(dirname "${GAME_EXE}")"
GAME_EXE="$(basename "${GAME_EXE}")"

################################################################################

### Configura o save.

if [ "${GAME_EXE}" == 'batocera.plus' ]; then
    WIN_SAVE_DIR="$(grep '^WIN_SAVE_DIR=' batocera.plus | cut -d "'" -f 2)"

    if [ "${WIN_SAVE_DIR}" ]; then
        BATOCERA_SAVE="${SAVES_DIR}/windows/${ROM_NAME}"

        mkdir -p "${BATOCERA_SAVE}"

        WIN_SAVE_DIR="${SHARE}/system/configs/wine/${CORE}/drive_c/${WIN_SAVE_DIR:3}"

        if ! [ -d "${WIN_SAVE_DIR}" ]; then
            mkdir -p "${WIN_SAVE_DIR}/.."
            rm -r  "${WIN_SAVE_DIR}"
            ln -sf "${BATOCERA_SAVE}" "${WIN_SAVE_DIR}"
        fi
    fi
fi

################################################################################

### Fecha o jogo pelo controle (hotkey + start)

if [ "${SYSTEM}" == 'windows' ]; then
    BOTOES="$(/opt/Wine/getHotkeyStart "${P1GUID}")"
    BOTAO_HOTKEY="$(echo "${BOTOES}" | cut -d ' ' -f 1)"
    BOTAO_START="$(echo  "${BOTOES}" | cut -d ' ' -f 2)"

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
elif [ "${SYSTEM}" == 'mugen' ]; then
    BOTOES="$(/opt/Mugen/getHotkeys "${P1GUID}")"
    BOTAO_HOTKEY="$(echo "${BOTOES}" | cut -d ' ' -f 1)"
    BOTAO_START="$(echo  "${BOTOES}" | cut -d ' ' -f 2)"
    BOTAO_SELECT="$(echo "${BOTOES}" | cut -d ' ' -f 3)"

    if [ "${BOTAO_HOTKEY}" ] && [ "${BOTAO_START}" ] && [ "${BOTAO_SELECT}" ]; then
        # Impede que o xjoykill-mugen seja encerrado enquanto o jogo está em execução.
        while : ; do
            nice -n 20 /opt/Mugen/xjoykill-mugen -hotkey "${BOTAO_HOTKEY}" -start "${BOTAO_START}" -select "${BOTAO_SELECT}" -kill /usr/bin/killwine -esc '/usr/bin/xSendKey esc'
            if ! [ "$(pidof wineserver)" ]; then
                break
            fi
            sleep 5
        done &
    fi
fi

################################################################################

### Ativa o FSYNC e ESYNC.

case ${SYNC} in
    fsync)
        export WINEFSYNC=1
        export WINEESYNC=1
        ;;
    esync)
        export WINEESYNC=1
        ;;
    default|auto)
        ;;
esac

################################################################################

### DirectX Engine.

case ${DIRECTX} in
    dxvk)
        export DXVK=1
        ;;
    dxvk_legacy)
        export DXVK=3
        ;;
    dxvk_proton_ge_custom)
        export DXVK=5
        ;;
    pba)
        export PBA_ENABLE=1
        ;;
    default|auto)
        ;;
esac

# DXVK Show FPS
if [ "${DXVK}" ] && [ "${MANGOHUD}" == '2' ]; then
    let DXVK=${DXVK}+1
    export DXVK
fi

################################################################################

### Otimizações.

case ${OPTIMIZATIONS} in
    nvidia|nvidia_generic)
        export __GL_THREADED_OPTIMIZATIONS=1
            ;;
        amd|amd_generic)
            export R600_DEBUG=nohyperz
            export mesa_glthread=true
            ;;
        intel|intel_generic)
            export MESA_GL_VERSION_OVERRIDE=4.5COMPAT
            ;;
        none|auto)
            ;;
    esac

    case ${OPTIMIZATIONS} in
        generic|nvidia_generic|amd_generic|intel_generic)
            export WINEDEBUG=-all
            export STAGING_WRITECOPY=1
            export STAGING_SHARED_MEMORY=1
            export STAGING_RT_PRIORITY_BASE=90
            export STAGING_RT_PRIORITY_SERVER=90
            if [ "${DXVK}" ]; then
                export DXVK_ASYNC=1
            fi
            if [ "${CORE}" == 'auto' ]; then
                for i in /opt/Wine/wine-*/bin/wineserver /opt/Wine/proton-*/bin/wineserver; do
                    setcap cap_sys_nice+ep ${i}
                done
            else
                setcap cap_sys_nice+ep "/opt/Wine/${CORE}/bin/wineserver"
            fi
            ;;
        none|auto)
            ;;
    esac

################################################################################

### Melhoramento de imagem.

if [ "${VKBASALT}" != 'auto' ]; then
    export ENABLE_VKBASALT=1
    export VKBASALT_LOG_LEVEL=info
    export VKBASALT_LOG_FILE="${LOG_DIR}/vkBasalt.log"

    case ${VKBASALT} in
        clarity)                
            export VKBASALT_CONFIG_FILE=/opt/vkBasalt/profiles/vkBasalt.conf.clarity
            ;;
        fakehdr)
            export VKBASALT_CONFIG_FILE=/opt/vkBasalt/profiles/vkBasalt.conf.fakehdr
            ;;
        gaussian)
            export VKBASALT_CONFIG_FILE=/opt/vkBasalt/profiles/vkBasalt.conf.gaussian
            ;;
        reshade)
            export VKBASALT_CONFIG_FILE=/opt/vkBasalt/profiles/vkBasalt.conf.reshade
            ;;
        user)
            # Carrega uma config "vkBasalt.conf" na pasta do jogo
            # caso não seja encontrado é carregado uma config em "${HOME}/.config/vkBasalt/vkBasalt.conf"
            # previamente criada no goverlay
            ;;
    esac
fi

################################################################################

### Pula os vídeos.

case "${INGAME_VIDEOS}" in 
    auto)
        if [ "${CORE}" == 'wine-old-stable' ]; then
            # Desativa os vídeos por padrão somente no wine-old-stable
            export WINEDLLOVERRIDES='winegstreamer=d'
        else
            export WINEDLLOVERRIDES='winegstreamer=b'
        fi
        ;;
    skip)
        export WINEDLLOVERRIDES='winegstreamer=d'
        ;;
    enable)
        export WINEDLLOVERRIDES='winegstreamer=b'
        ;;
    mf)
        export WINE_MF=1
        ;;
    *)
        echo "error, option ${OPTION} not supported to skip videos."
        exit 1
esac

################################################################################

### Exibe o ponteiro do mouse no gerenciador de arquivos.

if [ "${GAME_EXE}" == 'explorer' ]; then
    mouse-pointer on
fi

################################################################################

### Define a versão padrão do wine (auto)

if [ "${CORE}" == 'auto' ]; then
    CORE='wine'
fi

################################################################################

### Virtual Desktop (Video Mode)

if [ "${VIDEOMODE}" != 'auto' ]; then
    export VIRTUAL_DESKTOP=${VIDEOMODE}
fi

################################################################################

### Emulate Joypad (xjoypad)

case ${JOYPAD} in
    emulate)
        # Ativa a emulação do controle pelo teclado.
        # Não executa o xjoypad se não for encontrado nenhum controle conectado.
        if [ -e '/dev/input/js0' ]; then
            # Impede que o xjoypad seja encerrado enquanto o jogo está em execução.
            while :; do
                nice -n -15 xjoypad -device /dev/input/js0 \
                                    -up 111 -down 116 -left 113 -right 114 \
                                    -buttons 25 27 28 29 30 31 32 42 44 45 46 55 56 57 58

                if ! [ "$(pidof wineserver)" ]; then
                    break
                fi

                sleep 5
            done &
        fi
        ;;
    hidraw)
        # Joystick Alternative Driver
        # https://wiki.winehq.org/Useful_Registry_Keys

        ${CORE} reg add "HKEY_LOCAL_MACHINE\System\CurrentControlSet\Services\WineBus"     /f /v "DisableHidraw" /t REG_DWORD /d "0"

        if [ "${CORE}" == 'proton-valve' ]; then
            ${CORE} reg add "HKEY_LOCAL_MACHINE\System\CurrentControlSet\Services\WineBus" /f /v "Enable SDL"    /t REG_DWORD /d "1"
        else
            ${CORE} reg add "HKEY_LOCAL_MACHINE\System\CurrentControlSet\Services\WineBus" /f /v "Enable SDL"    /t REG_DWORD /d "0"
        fi
        ;;
    *)
        ${CORE} reg add "HKEY_LOCAL_MACHINE\System\CurrentControlSet\Services\WineBus"     /f /v "Enable SDL"    /t REG_DWORD /d "1"

        if [ "${CORE}" == 'proton-valve' ]; then
            ${CORE} reg add "HKEY_LOCAL_MACHINE\System\CurrentControlSet\Services\WineBus" /f /v "DisableHidraw" /t REG_DWORD /d "1"
        else
            ${CORE} reg add "HKEY_LOCAL_MACHINE\System\CurrentControlSet\Services\WineBus" /f /v "DisableHidraw" /t REG_DWORD /d "0"
        fi
esac

################################################################################

### Executa o jogo.

# O ES não cria um stdout e stderror para o script (bug ???)
# Se não redirecionar a saída para um arquivo de log ou para /dev/null alguns jogos não funcionam pelo ES.

case "${GAME_EXE}" in
    batocera.plus)
        # A variável core será usada pelo script principal do wine para forçar
        # a utilização de um determinado core quando escolhido na interface do ES.
        export CORE
        ./batocera.plus "${@}"                                   > "${LOG_DIR}/wine.log" 2>&1
        ;;
    explorer)
        ${CORE} "${GAME_EXE}" "z:/userdata/roms/windows/${ROM}"  > "${LOG_DIR}/wine.log" 2>&1
        ;;
    *)
        ${CORE} "${GAME_EXE}"                                    > "${LOG_DIR}/wine.log" 2>&1
        ;;
esac

################################################################################

### Aguarda o jogo encerrar a execução.

while [ "$(pidof wineserver)" ]; do
    sleep 1
done

################################################################################

### Mata o emulador de teclado.

if [ "$(pidof -s xjoykill)" ]; then
    killall -9 xjoykill
elif [ "$(pidof -s xjoykill-mugen)" ]; then
    killall -9 xjoykill-mugen
fi

if [ "$(pidof -s xjoypad)" ]; then
    killall -9 xjoypad
fi

################################################################################

### Desmonta imagem squashfs.
### Salva as modificações feitas na pasta do jogo durante o gameplay.

wait

if [ "${ROM}" == "${MOUNT_DIR}" ]; then
    cd "${MOUNT_DIR}/.."

    # Desmonta a união de diretórios.
    for i in {1..5}; do
        if umount -f "${MOUNT_DIR}"; then
            break
        fi

        if [ "${i}" == '4' ]; then
            /usr/bin/killwine
        fi

        sleep 1
    done

    # Desmonta o jogo compactado no formato squashfs.
    for i in {1..5}; do
        if umount -f "${LOWER_DIR}"; then
            break
        fi

        if [ "${i}" == '4' ]; then
            /usr/bin/killwine
        fi

        sleep 1
    done

    # Salva as modificações na pasta do próprio jogo durante o gameplay
    # somente em jogos compactados no formato squashfs (.plus)
    if [ "$(ls -1A "${UPPER_DIR}" | head -n 1)" ]; then
        mkdir -p "${GAME_SAVE_DIR}"
        rsync -a --delete  "${UPPER_DIR}/" "${GAME_SAVE_DIR}"
    fi

    rmdir "${MOUNT_DIR}"
    rm -r "${OVERLAY_DIR}"
fi

################################################################################

exit 0
