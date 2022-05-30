#!/bin/bash
###
### Batocera.PLUS
### Alexandre Freire dos Santos
### alexxandre.freire@gmail.com
###
### Mozilla Firefox

### Define o local para salvar o perfil (save).
SAVE_DIR=/userdata/saves/internet/firefox

### Pasta de downloads para os arquivos baixados da internet.
DOWNLOADS_DIR=/userdata/downloads

### Diretório de roms (links)
ROM_DIR=/userdata/roms/internet

### Local dos arquivos que fazem o firefox ser executado no Batocera.PLUS.
APP_DIR=/opt/Firefox

### Define o tipo de conteúdo que será executado pelo navegador.
SYSTEM="${1}"

### Nome e local do conteúdo a ser executado pelo navegador.
ROM="${2}"

### Local dos arquivos do firefox, pode ser usado para atualizar o navegador.
if [ -f "${ROM_DIR}/firefox.linux64/firefox" ]; then
    FIREFOX_DIR="${ROM_DIR}/firefox.linux64"
else
    FIREFOX_DIR="${APP_DIR}/firefox-esr"
fi

### Ativa o ponteiro do mouse.
mouse-pointer on

################################################################################

### Bibliotecas extras.
export LD_LIBRARY_PATH="${APP_DIR}/extra-libs:${APP_DIR}/apulse:${LD_LIBRARY_PATH}"

################################################################################

### DEFAULT PROFILE
### Cria o perfil padrao (save) e a pasta de downloads.

if ! [ -e "${SAVE_DIR}" ]
then
    mkdir -p "${SAVE_DIR}"
    cp -r "${APP_DIR}/default-profile-esr/"* "${SAVE_DIR}"

    mkdir -p "${DOWNLOADS_DIR}"
    ln -sf "${DOWNLOADS_DIR}" "${SAVE_DIR}/Downloads"
fi

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

###  Executa o navegador normalmente.
###  Quando não é passado nenhum parâmetro.

if ! [ -f "${ROM}" ]
then
    HOME="${SAVE_DIR}" "${FIREFOX_DIR}/firefox" --profile "${SAVE_DIR}"
    exit 0
fi

if [ "${SYSTEM}" == 'internet' ]
then
    if ! [ "$(head -n 1 "$ROM")" ]; then
        HOME="${SAVE_DIR}" "${FIREFOX_DIR}/firefox" --profile "${SAVE_DIR}"
        exit 0
    fi
fi

################################################################################

### Configura o navegador para abrir com todas orelhas fechadas.
### Faz backup do arquivo de configuração do navegaor antes de fazer alterações.
cp "${SAVE_DIR}/sessionstore.jsonlz4" "${SAVE_DIR}/sessionstore.jsonlz4.original"

### Fecha todas orelhas.
sed -i s/'^user_pref("browser.startup.page", .*/user_pref("browser.startup.page", 1);/' "${SAVE_DIR}/user.js"

################################################################################

### Abre o navegador na página escolhida.

if [ "${SYSTEM}" == 'internet' ]
then
    ### Abre o navegador com todas as orelhas fechadas
    HOME="${SAVE_DIR}" "${FIREFOX_DIR}/firefox" --profile "${SAVE_DIR}" "$(head -n 1 "${ROM}")"
fi

################################################################################

### Restaura as configurações do navegador.

mv  -f "${SAVE_DIR}/sessionstore.jsonlz4.original" "${SAVE_DIR}/sessionstore.jsonlz4"
sed -i s/'^user_pref("browser.startup.page", .*/user_pref("browser.startup.page", 3);/' "${SAVE_DIR}/user.js"

exit 0
