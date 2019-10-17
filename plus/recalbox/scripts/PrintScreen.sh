#!/bin/sh

FILE_NAME="print_$(date +%F_%H.%M.%S).$1"

# Limita os prints em 1 por segundo.
if [ -f "$HOME/../screenshots/$FILE_NAME" ]; then
    exit 1
fi

# Print Screen
/usr/bin/ImageMagick import -window root -display :0.0 "$HOME/../screenshots/$FILE_NAME" || exit 1

# Mensagem na Tela
echo "save to $FILE_NAME" | LC_ALL=C DISPLAY=:0.0 osd_cat -f -*-*-bold-*-*-*-32-120-*-*-*-*-*-* -cred -s 2 -d 4 -l 100 -A center -ccyan &

exit 0
