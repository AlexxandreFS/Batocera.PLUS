#!/bin/sh

################################################################################

### BATOCERA.PLUS

################################################################################

### CAPTURA E SEPARAÇÃO DE PARAMETROS.

RETROARCH='/usr/bin/retroarch.sh'

CORE="$(echo "$@" | cut -d ' ' -f 2)"         || exec $RETROARCH "$@"
CORE_DIR="$(dirname "$CORE")"                 || exec $RETROARCH "$@"
CORE_NAME="$(basename "$CORE")"               || exec $RETROARCH "$@"
CORE_PARAM="$(echo "$@" | cut -d ' ' -f 1)"   || exec $RETROARCH "$@"

CONFIG="$(echo "$@" | cut -d' ' -f 4)"        || exec $RETROARCH "$@"
CONFIG_DIR="$(dirname "$CONFIG")"             || exec $RETROARCH "$@"
CONFIG_NAME="$(basename "$CONFIG")"           || exec $RETROARCH "$@"
CONFIG_PARAM="$(echo "$@" | cut -d ' ' -f 3)" || exec $RETROARCH "$@"

ROM="$(echo "$@" | cut -d ' ' -f 5-)"         || exec $RETROARCH "$@"
ROM_DIR="$(dirname "$ROM")"                   || exec $RETROARCH "$@"
ROM_NAME="$(basename "$ROM")"                 || exec $RETROARCH "$@"
ROM_NEW=''

################################################################################

### TESTE DE SANIDADE.

if ! [ "$CORE" ]; then
    exec $RETROARCH "$@"
elif ! [ "$CORE_DIR" ]; then
    exec $RETROARCH "$@"
elif ! [ "$CORE_NAME" ]; then
    exec $RETROARCH "$@"
elif ! [ "$CORE_PARAM" ]; then
    exec $RETROARCH "$@"
fi

if ! [ "$CONFIG" ]; then
    exec $RETROARCH "$@"
elif ! [ "$CONFIG_DIR" ]; then
    exec $RETROARCH "$@"
elif ! [ "$CONFIG_NAME" ]; then
    exec $RETROARCH "$@"
elif ! [ "$CONFIG_PARAM" ]; then
    exec $RETROARCH "$@"
fi

if ! [ "$ROM" ]; then
    exec $RETROARCH "$@"
elif ! [ "$ROM_DIR" ]; then
    exec $RETROARCH "$@"
elif ! [ "$ROM_NAME" ]; then
    exec $RETROARCH "$@"
fi

if [ "$CORE_DIR" != '/usr/lib/libretro' ]; then
    exec $RETROARCH "$@"
elif [ "$CORE_PARAM" !=  '-L' ]; then
    exec $RETROARCH "$@"
elif [ "$CONFIG" !=  '/recalbox/share/system/configs/retroarch/retroarchcustom.cfg' ]; then
    exec $RETROARCH "$@"
elif [ "$CONFIG_DIR" !=  '/recalbox/share/system/configs/retroarch' ]; then
    exec $RETROARCH "$@"
elif [ "$CONFIG_NAME" !=  'retroarchcustom.cfg' ]; then
    exec $RETROARCH "$@"
elif [ "$CONFIG_PARAM" !=  '--config' ]; then
    exec $RETROARCH "$@"
fi

################################################################################

### CONFIGURA O CORE FBA PARA EXECUTAR NEOGEO CD

if [ $CORE_NAME == 'fba_libretro.so' ]; then
    if [ "$(echo "$@" | grep -i '.cue$')" ]; then
        exec /usr/bin/retroarch.sh "$@" --subsystem neocd
    fi
fi

################################################################################

if [ "$ROM_NEW" ]; then
    exec "$RETROARCH" "$CORE_PARAM" "$CORE" "$CONFIG_PARAM" "$CONFIG" "$ROM_NEW"
else
    exec $RETROARCH "$@"
fi
