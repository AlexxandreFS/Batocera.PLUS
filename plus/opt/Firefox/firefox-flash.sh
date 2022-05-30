#!/bin/bash
###
### Batocera.PLUS
### Alexandre Freire dos Santos
### alexxandre.freire@gmail.com
###
### Mozilla Firefox, old version with flash support.
###

################################################################################

### PATH

FIREFOX_DIR=/opt/Firefox
SAVE_DIR=/userdata/saves/flash/firefox

DOWNLOADS_DIR=/userdata/downloads
ROM="${1}"

export LD_LIBRARY_PATH="${FIREFOX_DIR}/extra-libs:${FIREFOX_DIR}/apulse:${LD_LIBRARY_PATH}"

################################################################################

### DEFAULT PROFILE
### Cria o perfil padrao (save) e a pasta de downloads.

if ! [ -e "${SAVE_DIR}" ]; then
    mkdir -p "${SAVE_DIR}"
    cp -r "${FIREFOX_DIR}/default-profile-legacy/"* "${SAVE_DIR}"

    mkdir -p "${DOWNLOADS_DIR}"
    ln -sf   "${DOWNLOADS_DIR}" "${SAVE_DIR}/Downloads"
fi

################################################################################

### Configura o navegador para abrir com todas as orelhas fechadas.
sed -i s/'^user_pref("browser.startup.page", .*/user_pref("browser.startup.page", 1);/' "${SAVE_DIR}/user.js"

################################################################################

### SOUND FIX
### Resolve problemas com audio.

for FILE in asound.state .asoundrc
do
    if [ ! -e "${SAVE_DIR}/${FILE}" ]
    then
        if [ -e "${HOME}/${FILE}" ]
        then
            ln -s "${HOME}/${FILE}" "${SAVE_DIR}"
        elif [ -e "${SAVE_DIR}/${FILE}" ]
        then
            rm "${SAVE_DIR}/${FILE}"
        fi
    fi
done

################################################################################

### Executa o navegador com o conteúdo em flash.

export HOME="${SAVE_DIR}"

exec "${FIREFOX_DIR}/firefox-legacy/firefox" -no-remote --profile "${SAVE_DIR}" "${ROM}"
