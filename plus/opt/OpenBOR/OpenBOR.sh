#!/bin/sh

################################################################################

### OpenBOR - Batocera.PLUS
### Autor:  Alexandre Freire dos Santos
### E-Mail: alexxandre.freire@gmail.com

################################################################################

### Local dos arquivos usados pelo OpenBOR.

OPENBOR_DIR='/opt/OpenBOR'
TMP_DIR="/tmp/OpenBOR"

ROM_DIR="$HOME/../roms/openbor"
SAVE_DIR="$HOME/../saves/openbor"
SCREENSHOT_DIR="$HOME/../screenshots"
LOG_DIR="$HOME/logs"

CORE="$1"
ROM="$2"

################################################################################

### Define o core padrão.

if [ "$CORE" == auto ]; then
    CORE='OpenBOR_v6330'
fi

################################################################################

### Cria as pastas usadas pelo OpenBOR

if [ -e "$TMP_DIR" ]; then
    rm -r "$TMP_DIR"
else
    mkdir -p "$TMP_DIR"
fi

mkdir -p "$ROM_DIR" \
         "$SAVE_DIR" \
         "$SCREENSHOT_DIR" \
         "$LOG_DIR" \
         "$TMP_DIR/Paks"

ln -s "$ROM" "$TMP_DIR/Paks"
ln -s "$SAVE_DIR" "$TMP_DIR/Saves"
ln -s "$HOME/../screenshots" "$TMP_DIR/ScreenShots"
ln -s "$LOG_DIR" "$TMP_DIR/Logs"

################################################################################

### Cria um save padrão com a configuração de tela cheia
### ativada e outros filtros de imagem.

if ! [ -f "$SAVE_DIR/$CORE_default.cfg" ]; then
    cp "$OPENBOR_DIR/lib/${CORE}_default.cfg" "$SAVE_DIR"
fi
ln -sf "$SAVE_DIR/${CORE}_default.cfg" "$SAVE_DIR/default.cfg"

ROM_NAME="$(basename "${ROM}" .pak)"
ROM_NAME="${ROM_NAME%.PAK}"

if ! [ -f "$SAVE_DIR/${ROM_NAME} (${CORE}).cfg" ]; then
    cp -f "${SAVE_DIR}/${CORE}_default.cfg" "${SAVE_DIR}/${ROM_NAME} (${CORE}).cfg"
fi

ln -sf "${SAVE_DIR}/${ROM_NAME} (${CORE}).cfg" "${SAVE_DIR}/${ROM_NAME}.cfg"

################################################################################

### Bibliotecas extras.

export LD_LIBRARY_PATH="$OPENBOR_DIR/lib:$LD_LIBRARY_PATH"
export DISPLAY=:0.0

################################################################################

### Executa o OpenBOR.
cd "$TMP_DIR"

sleep 0.3

"$OPENBOR_DIR/$CORE"

################################################################################

### Remove arquivos temporários.

rm -r "$TMP_DIR"
rm    "${SAVE_DIR}/default.cfg"
rm    "${SAVE_DIR}/${ROM_NAME}.cfg"

exit 0
