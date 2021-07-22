#!/bin/sh
###
### MOZILLA FIREFOX
### Batocera.PLUS
### alexxandre.freire@gmail.com
###

##
 # Define o local para salvar o perfil (save).
 ##
SAVE_DIR="$HOME/../saves/internet/firefox"

##
 # Pasta de downloads para os arquivos baixados da internet.
 ##
DOWNLOADS_DIR="$HOME/../downloads"

##
 # Diretório de roms (links)
 ##
ROM_DIR="$HOME/../roms/internet"

##
 # Local dos arquivos que fazem o firefox ser executado no Batocera.PLUS.
 ##
APP_DIR='/opt/Firefox'

##
 # Define o tipo de conteúdo que será executado pelo navegador.
 # Ex. flash, internet
 ##
SYSTEM="$1"

##
 # Nome e local do conteúdo a ser executado pelo navegador.
 ##
ROM="$2"

##
 # Local dos arquivos do firefox, ideal para usar o navegar em outros idiomas
 # e para atualizar o navegador.
 ##
if [ -f "$ROM_DIR/firefox.linux64/firefox" ]; then
    FIREFOX_DIR="$ROM_DIR/firefox.linux64"
else
    FIREFOX_DIR="$APP_DIR/firefox-esr"
fi

##
 # Ativa o ponteiro do mouse.
 ##
mouse-pointer on

################################################################################

##
 # Bibliotecas extras.
 ##
#ln -s -f $APP_DIR/extra-libs/libgtk-3-original.so.0    $APP_DIR/extra-libs/libgtk-3.so.0
ln -s -f $APP_DIR/extra-libs/libgtk-3-alternative.so.0 $APP_DIR/extra-libs/libgtk-3.so.0

export LD_LIBRARY_PATH="${APP_DIR}/extra-libs:${APP_DIR}/apulse:${LD_LIBRARY_PATH}"
export XDG_DATA_DIRS="/usr/share:$APP_DIR/extra-libs"


################################################################################

##
 # Cria o perfil padrao (save) e a pasta de downloads.
 ##
if ! [ -e $SAVE_DIR ]; then
    mkdir -p $SAVE_DIR
    7zr x $APP_DIR/default-profile/default-profile.7z -o$SAVE_DIR

    mkdir -p $DOWNLOADS_DIR
    ln -s -f $DOWNLOADS_DIR $SAVE_DIR/Downloads
fi

################################################################################

##
 # Resolve o problema com o som.
 # Usa a mesma saída de som padrão do Batocera no Firefox.
 ##
if [ -e $HOME/asound.state ]; then
    if ! [ -e $SAVE_DIR/asound.state ]; then
        ln -s $HOME/asound.state $SAVE_DIR
    fi
elif [ -e $SAVE_DIR/asound.state ]; then
    rm $SAVE_DIR/asound.state
fi

if [ -e $HOME/.asoundrc ]; then
    if ! [ -e $SAVE_DIR/.asoundrc ]; then
        ln -s $HOME/.asoundrc $SAVE_DIR
    fi
elif [ -e $SAVE_DIR/.asoundrc ]; then
    rm $SAVE_DIR/.asoundrc
fi

################################################################################

##
 #  Executa o navegador normalmente.
 #  Quando não é passado nenhum parâmetro.
 ##
if ! [ -f "$ROM" ]; then
    HOME="$SAVE_DIR" "$FIREFOX_DIR/firefox" --profile "$SAVE_DIR"
    exit 0
fi
if [ "$SYSTEM" == 'internet' ]; then
    if ! [ "$(head -n 1 "$ROM")" ]; then
        HOME="$SAVE_DIR" "$FIREFOX_DIR/firefox" --profile "$SAVE_DIR"
        exit 0
    fi
fi

################################################################################

##
 # Configura o navegador para abrir com todas orelhas fechadas.
 ##
### Faz backup do arquivo de configuração do navegaor antes de fazer alterações.
cp "$SAVE_DIR/sessionstore.jsonlz4" "$SAVE_DIR/sessionstore.jsonlz4.original"
### Fecha todas orelhas.
sed -i s/'^user_pref("browser.startup.page", .*/user_pref("browser.startup.page", 1);/' "$SAVE_DIR/user.js"

################################################################################

##
 # Abre o navegador na página escolhida.
 ##
if [ "$SYSTEM" == 'internet' ]; then
    ### Abre o navegador com todas as orelhas fechadas
    HOME="$SAVE_DIR" "$FIREFOX_DIR/firefox" --profile "$SAVE_DIR" "$(head -n 1 "$ROM")"
fi

################################################################################

##
 # Executa o navegador com o conteúdo em flash.
 ##
if [ "$SYSTEM" == 'flash' ]; then
    ### Abre o navegador com o conteúdo em flash.
    HOME="$SAVE_DIR" "$FIREFOX_DIR/firefox" --profile "$SAVE_DIR" "$ROM"
fi

################################################################################

##
 # Restaura as configurações do navegador.
 ##
mv  -f "$SAVE_DIR/sessionstore.jsonlz4.original" "$SAVE_DIR/sessionstore.jsonlz4"
sed -i s/'^user_pref("browser.startup.page", .*/user_pref("browser.startup.page", 3);/' "$SAVE_DIR/user.js"

exit 0
