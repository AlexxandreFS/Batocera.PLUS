#!/bin/sh
# BATOCERA.PLUS
# Este script aplica o patch do wine staging.
# Copie este script para a pasta do Wine Staging e execute.

WINE_DIR='../wine-6.6'

./patches/patchinstall.sh DESTDIR="$WINE_DIR" --all \
    -W winex11-_NET_ACTIVE_WINDOW \
    -W winex11-WM_WINDOWPOSCHANGING \
    -W imm32-com-initialization \
    -W bcrypt-ECDHSecretAgreement

exit 0

