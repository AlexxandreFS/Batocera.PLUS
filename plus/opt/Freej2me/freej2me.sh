#!/bin/bash
###
### Batocera.PLUS
### Alexandre Freire dos Santos
###

### Caminhos

ROM="file://${1}"
SAVE_DIR='/userdata/saves/j2me'
FREJ2ME_DIR="$(dirname ${0})"

mkdir -p "${SAVE_DIR}"

### Emulador de teclado ###

if [ -e '/dev/input/js0' ]
then
    while :
    do
        nice -n -15 xjoypad \
            -device /dev/input/js0 \
            -up 111 -down 116 -left 113 -right 114 \
            -buttons 36  85 81 83 24 25 26 27 87 89 9   90 56 57 58
                   # ent 6  9  4  q  w  e  r  1  3  esc 0  84

        if ! [ "$(pidof java)" ]
        then
            break
        fi

        sleep 5
    done &
fi

### Executa o jogo

java -Dsun.java2d.opengl=True -jar "${FREJ2ME_DIR}/freej2me.jar" "${ROM}"

### Mata o emulador de teclado ###

if [ "$(pidof -s xjoypad)" ]
then
    killall -9 xjoypad
fi

exit 0
