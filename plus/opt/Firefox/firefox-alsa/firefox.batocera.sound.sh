#!/bin/sh

##
 # firefox-batocera
 # Este script executa o navegador firefox no batocera-linux
 # Testado no batocera-linux 5.16 e 5.17 (pode funcionar em outras)
 # Funciona com PC x86_64
 #
 # Autor:  Alexandre Freire dos Santos
 # E-Mail: alexxandre.freire@gmail.com
 # Data:   16/set/2018
 # Local:  Sao Paulo, SP, Brasil
 ##

##
 # Define o local para salvar o perfil (save).
 ##
SAVE_DIR=$HOME/../saves/pc/Mozilla-Firefox

##
 # Pasta de downloads para os arquivos baixados da internet.
 ##
DOWNLOADS_DIR=$HOME/../downloads

##
 # Descobre e define o local dos arquivos do firefox.
 ##
if [ -e $(pwd)/batocera.sh ]; then
    FIREFOX_DIR=$(pwd)
elif [ -e $HOME/../roms/pc/Mozilla-Firefox.pc ]; then
    FIREFOX_DIR=$HOME/../roms/pc/Mozilla-Firefox.pc
else
    echo erro, firefox nao encontrado.
    exit
fi

##
 # Instala Bibliotecas extras.
 ##
ln -s -f $FIREFOX_DIR/extra-libs/libgtk-3.so.0          /lib64
ln -s -f $FIREFOX_DIR/extra-libs/libgdk-3.so.0          /lib64
ln -s -f $FIREFOX_DIR/extra-libs/libatspi.so.0          /lib64
ln -s -f $FIREFOX_DIR/extra-libs/libatk-bridge-2.0.so.0 /lib64
ln -s -f $FIREFOX_DIR/extra-libs/libwayland-client.so.0 /lib64
ln -s -f $FIREFOX_DIR/extra-libs/libwayland-cursor.so.0 /lib64
ln -s -f $FIREFOX_DIR/extra-libs/libwayland-egl.so.1    /lib64
ln -s -f $FIREFOX_DIR/extra-libs/libxkbcommon.so.0      /lib64

##
 # Instala o flash plugin.
 ##
mkdir -p /usr/lib/mozilla/plugins
ln -s -f $FIREFOX_DIR/flash-plugin/libflashplayer.so /usr/lib/mozilla/plugins

##
 # Instala fonts padrões do Windows no Firefox para evitar incompatibilidades de sites.
 ##
rm -r -f $FIREFOX_DIR/firefox-alsa/fonts
ln -s -f $FIREFOX_DIR/fonts-windows $FIREFOX_DIR/firefox-alsa/fonts

##
 # Cria o perfil padrao (save) e a pasta de downloads.
 ##
if ! [ -e $SAVE_DIR ]; then
    mkdir -p $SAVE_DIR
    7zr x $FIREFOX_DIR/default-profile/default-profile.7z -o$SAVE_DIR

    mkdir -p $DOWNLOADS_DIR
    ln -s -f $DOWNLOADS_DIR $SAVE_DIR/Downloads
fi

##
 # Ativa a tradução para o português do Brasil.
 ##
echo 'pref("app.update.channel", "default");'  >  $FIREFOX_DIR/firefox-alsa/defaults/pref/channel-prefs.js
echo 'pref("intl.locale.requested", "pt-BR");' >> $FIREFOX_DIR/firefox-alsa/defaults/pref/channel-prefs.js

##
 # Ativa o ponteiro do mouse.
 ##
matchbox-remote -exit
matchbox-window-manager -use_cursor yes -use_titlebar no -use_desktop_mode no -use_lowlight no &

##
 # Executa o navegador.
 # https://developer.mozilla.org/en-US/docs/Mozilla/Command_Line_Options
 ##
HOME=$SAVE_DIR exec $FIREFOX_DIR/firefox-alsa/firefox --profile $SAVE_DIR

##
 # Desativa o ponteiro do mouse
 ##
matchbox-remote -exit
matchbox-window-manager -use_cursor no -use_titlebar no -use_desktop_mode no -use_lowlight no &
