#!/bin/bash
##
 # Batocera.PLUS - Raine Emulator
 # Autor:  Alexandre Freire dos Santos
 # E-Mail: alexxandre.freire@gmail.com
 # Local:  São Paulo, SP, Brasil
 ##

################################################################################

### DEFINIÇÕES GERAIS

SHARE='/userdata'
RAINE_DIR='/opt/Raine'
if [ -f "$HOME/configs/emulationstation/es_input.cfg" ]; then
    ES_INPUT="$HOME/configs/emulationstation/es_input.cfg"
else
    ES_INPUT="/usr/share/batocera/datainit/system/configs/emulationstation/es_input.cfg"
fi
ROM="$1"
CORE="$2"
CONTROLE_NUM1="$3"
CONTROLE_ID1="$4"
CONTROLE_NUM2="$5"
CONTROLE_ID2="$6"

################################################################################

### CRIA DIRETÓRIOS USADOS PELO RAINE.

mkdir -p "$SHARE/roms/neogeocd"        \
         "$SHARE/saves/neogeocd"       \
         "$SHARE/screenshots"          \
         "$SHARE/system/configs/raine" \
         "$SHARE/bios/raine/artwork"   \
         "$SHARE/bios/raine/debug"     \
         "$SHARE/bios/raine/demos"     \
         "$SHARE/bios/raine/emudx"     \
         "$SHARE/bios/raine/artwork"

# O raine roda dentro de um diretório temprário.
# Os diretórios usados por ele são links simbólicos.
if [ -e '/tmp/raine' ]; then
    rm -r '/tmp/raine'
fi

mkdir -p '/tmp/raine/.raine'
ln -s -f "$SHARE/saves/neogeocd"       '/tmp/raine/.raine/savedata'
ln -s -f "$SHARE/saves/neogeocd"       '/tmp/raine/.raine/savegame'
ln -s -f "$SHARE/system/configs/raine" '/tmp/raine/.raine/config'
ln -s -f "$SHARE/bios/raine/"*         '/tmp/raine/.raine'
ln -s -f "$SHARE/roms/neogeocd"        '/tmp/raine/.raine'

if ! [ -f "$HOME/batocera.conf" ]; then
    exit 1
fi

################################################################################

### APLICA A CONFIGURAÇÃO DE BOTÕES DO EMULATIONSTATION NO RAINE.

function salvarControle() {
    JOY_NUM="$(($1 + 1))"
    JOY_ID="$2"

    # Cria e inicializa as matrizes.
    BOTOES='a b x y start select pageup pagedown l2 r2 l3 r3 hotkey'
    declare -A CONTROLE
    for BOTAO in $BOTOES; do
        CONTROLE[$BOTAO]=''
    done

    # Faz a leitura do arquivo de configuracao do controle e
    # captura a sequencia de botoes definida pelo usuario.
    ES_INPUTS=`xml sel -T -t -m "/inputList/inputConfig[@deviceGUID='$JOY_ID']/*" -v "concat(@name,'|', @id)" -n "$ES_INPUT"`

    # Atribui os valores do arquivo de configuração as variáveis.
    for ES_INPUT in $ES_INPUTS; do
        ES_NAME="$(echo $ES_INPUT | cut -d '|' -f 1)"
        ES_ID="$(echo $ES_INPUT | cut -d '|' -f 2)"
        CONTROLE[$ES_NAME]=$ES_ID
    done

    # Converte os códigos de botões do emulationstation para os códigos
    # de botões usados no arquivo de configuração do Raine.
    for BOTAO in $BOTOES; do
        if [ -z "${CONTROLE[$BOTAO]}" ]; then
            continue
        fi
        CONTROLE[$BOTAO]=$((${CONTROLE[$BOTAO]} + 1))
        CONTROLE[$BOTAO]=$(printf "%x" ${CONTROLE[$BOTAO]})
        CONTROLE[$BOTAO]=${CONTROLE[$BOTAO]}000${JOY_NUM}
        CONTROLE[$BOTAO]=$(echo $((0x${CONTROLE[$BOTAO]})))
    done

    # Evita que o cabeçalho seja gravado duas vezes.
    # Evita que a tecla hotkey seja atribuída duas vezes.
    if [ "$JOY_NUM" == '1' ]; then
        echo '[emulator_joy_config]'                                   >> "$HOME/configs/raine/rainex_sdl.cfg"
        echo "Return_to_gui = ${CONTROLE['hotkey']}"                   >> "$HOME/configs/raine/rainex_sdl.cfg"
        echo ''                                                        >> "$HOME/configs/raine/rainex_sdl.cfg"
        echo '[default_game_key_config]'                               >> "$HOME/configs/raine/rainex_sdl.cfg"
    fi

    case "$JOY_NUM" in
        1) echo "Def_Coin_A_joystick = ${CONTROLE['select']}"          >> "$HOME/configs/raine/rainex_sdl.cfg" ;;
        2) echo "Def_Coin_B_joystick = ${CONTROLE['select']}"          >> "$HOME/configs/raine/rainex_sdl.cfg" ;;
        3) echo "Def_Coin_C_joystick = ${CONTROLE['select']}"          >> "$HOME/configs/raine/rainex_sdl.cfg" ;;
        4) echo "Def_Coin_D_joystick = ${CONTROLE['select']}"          >> "$HOME/configs/raine/rainex_sdl.cfg" ;;
        *) exit 1 ;;
    esac

    echo "Def_P${JOY_NUM}_Start_joystick = ${CONTROLE['start']}"       >> "$HOME/configs/raine/rainex_sdl.cfg"
    echo "Def_P${JOY_NUM}_Up_joystick = $((3584 + $JOY_NUM))"          >> "$HOME/configs/raine/rainex_sdl.cfg"
    echo "Def_P${JOY_NUM}_Down_joystick = $((3840 + $JOY_NUM))"        >> "$HOME/configs/raine/rainex_sdl.cfg"
    echo "Def_P${JOY_NUM}_Left_joystick = $((3072 + $JOY_NUM))"        >> "$HOME/configs/raine/rainex_sdl.cfg"
    echo "Def_P${JOY_NUM}_Right_joystick = $((3328 + $JOY_NUM))"       >> "$HOME/configs/raine/rainex_sdl.cfg"
    echo "Def_P${JOY_NUM}_Button_1_joystick = ${CONTROLE['y']}"        >> "$HOME/configs/raine/rainex_sdl.cfg"
    echo "Def_P${JOY_NUM}_Button_2_joystick = ${CONTROLE['b']}"        >> "$HOME/configs/raine/rainex_sdl.cfg"
    echo "Def_P${JOY_NUM}_Button_3_joystick = ${CONTROLE['x']}"        >> "$HOME/configs/raine/rainex_sdl.cfg"
    echo "Def_P${JOY_NUM}_Button_4_joystick = ${CONTROLE['a']}"        >> "$HOME/configs/raine/rainex_sdl.cfg"
    echo "Def_P${JOY_NUM}_Button_5_joystick = ${CONTROLE['pageup']}"   >> "$HOME/configs/raine/rainex_sdl.cfg"
    echo "Def_P${JOY_NUM}_Button_6_joystick = ${CONTROLE['pagedown']}" >> "$HOME/configs/raine/rainex_sdl.cfg"
    echo "Def_P${JOY_NUM}_Button_7_joystick = ${CONTROLE['l2']}"       >> "$HOME/configs/raine/rainex_sdl.cfg"
    echo "Def_P${JOY_NUM}_Button_8_joystick = ${CONTROLE['r2']}"       >> "$HOME/configs/raine/rainex_sdl.cfg"

    echo "Player${JOY_NUM}_B2_B3_joystick = ${CONTROLE['pagedown']}"   >> "$HOME/configs/raine/rainex_sdl.cfg"
    echo "Player${JOY_NUM}_B1_B2_B3_joystick = ${CONTROLE['pageup']}"  >> "$HOME/configs/raine/rainex_sdl.cfg"
}

################################################################################

### CRIA A CONFIGURAÇÃO PADRÃO PARA A PRIMEIRA EXECUÇÃO DO RAINE.

if ! [ -f "$HOME/configs/raine/rainex_sdl.cfg" ]; then

    ### DIRETORIOS
    echo '[Directories]'                          >> "$HOME/configs/raine/rainex_sdl.cfg"
    echo "ScreenShots = $SHARE/screenshots/"      >> "$HOME/configs/raine/rainex_sdl.cfg"
    echo "emudx = $SHARE/bios/raine/emudx/"       >> "$HOME/configs/raine/rainex_sdl.cfg"
    echo "artwork = $SHARE/bios/raine/artwork/"   >> "$HOME/configs/raine/rainex_sdl.cfg"
    echo "rom_dir_0 = $SHARE/roms/neogeocd/"      >> "$HOME/configs/raine/rainex_sdl.cfg"
    echo "rom_dir_1 = $SHARE/roms/mame/"          >> "$HOME/configs/raine/rainex_sdl.cfg"
    echo ''                                       >> "$HOME/configs/raine/rainex_sdl.cfg"

    ### FILTROS
    echo '[Display]'                              >> "$HOME/configs/raine/rainex_sdl.cfg"
    echo 'ogl_filter = 9729'                      >> "$HOME/configs/raine/rainex_sdl.cfg"
    echo 'ogl_shader = None'                      >> "$HOME/configs/raine/rainex_sdl.cfg"
    echo ''                                       >> "$HOME/configs/raine/rainex_sdl.cfg"

    ### NEOGEO CD
    echo '[neocd]'                                >> "$HOME/configs/raine/rainex_sdl.cfg"
    echo 'music_volume = 100'                     >> "$HOME/configs/raine/rainex_sdl.cfg"
    echo 'sfx_volume = 100'                       >> "$HOME/configs/raine/rainex_sdl.cfg"
    echo 'allowed_speed_hacks = 0'                >> "$HOME/configs/raine/rainex_sdl.cfg"
    echo 'cdrom_speed = 16'                       >> "$HOME/configs/raine/rainex_sdl.cfg"
    echo "neocd_dir = $SHARE/roms/neogeocd/"      >> "$HOME/configs/raine/rainex_sdl.cfg"
    echo "neocd_bios = $SHARE/bios/neocd-cdz.bin" >> "$HOME/configs/raine/rainex_sdl.cfg"
    echo ''                                       >> "$HOME/configs/raine/rainex_sdl.cfg"

    ### IDIOMA
    echo '[General]'                              >> "$HOME/configs/raine/rainex_sdl.cfg"


    XLANG="$(grep '^system.language=' "$HOME/batocera.conf" | cut -d '=' -f 2)"
    case $XLANG in
        pt_BR|pt_PT) echo 'language = pt'     >> "$HOME/configs/raine/rainex_sdl.cfg" ;;
        es_ES)       echo 'language = es'     >> "$HOME/configs/raine/rainex_sdl.cfg" ;;
        fr_FR)       echo 'language = fr'     >> "$HOME/configs/raine/rainex_sdl.cfg" ;;
        it_IT)       echo 'language = it'     >> "$HOME/configs/raine/rainex_sdl.cfg" ;;
        *)           echo 'language = C'      >> "$HOME/configs/raine/rainex_sdl.cfg" ;;
    esac

    echo ''                                   >> "$HOME/configs/raine/rainex_sdl.cfg"

    ### CONTROLES
    if [ "$CONTROLE_ID1" ]; then
        salvarControle $CONTROLE_NUM1 $CONTROLE_ID1
    fi

    # A configuração automática de controles funciona apenas para 1 controle.
    # Precisa verificar no raine como inverter a ordem dos controles
    # quem sabe com o parametro  -j /dev/input/js1 quando a paciência voltar vejo isso.
    # CONTINUA....
fi

################################################################################

### MANTÉM CONFIGURAÇÕES ESSENCIAIS DO RAINE.

#[Directories]
sed -i "s#^ScreenShots = .*#ScreenShots = $SHARE/screenshots/#" "$HOME/configs/raine/rainex_sdl.cfg"
sed -i "s#^emudx = .*#emudx = $SHARE/bios/emudx/#"              "$HOME/configs/raine/rainex_sdl.cfg"
sed -i "s#^artwork = .*#artwork = $SHARE/bios/artwork/#"        "$HOME/configs/raine/rainex_sdl.cfg"
sed -i "s#^rom_dir_0 = .*#rom_dir_0 = $SHARE/roms/neogeocd/#"   "$HOME/configs/raine/rainex_sdl.cfg"
sed -i "s#^rom_dir_1 = .*#rom_dir_1 = $SHARE/roms/mame/#"       "$HOME/configs/raine/rainex_sdl.cfg"
sed -i "s#^neocd_dir = .*#neocd_dir = $SHARE/roms/neogeocd/#"   "$HOME/configs/raine/rainex_sdl.cfg"

################################################################################

### CORE (BIOS).

BIOS_GAME="$(grep -F "neogeocd[\"$(basename "${ROM}")\"].bios=" "${HOME}/batocera.conf" | cut -d '=' -f 2)"
BIOS_NEOCD="$(grep '^neogeocd.bios='                            "${HOME}/batocera.conf" | cut -d '=' -f 2)"

if [ "${BIOS_GAME}" ] && [ ! "${BIOS_GAME}" == 'auto' ]; then
    BIOS="${BIOS_GAME}"
elif [ "${BIOS_NEOCD}" ] && [ ! "${BIOS_NEOCD}" == 'auto' ]; then
    BIOS="${BIOS_NEOCD}"
else
    BIOS='auto'
fi

case ${BIOS} in
    cdz|auto)   NEOCD_BIOS='neocd-cdz.bin'        ;;
    front-load) NEOCD_BIOS='neocd-front-load.bin' ;;
    top-load)   NEOCD_BIOS='neocd-top-load.bin'   ;;
    unibios)    NEOCD_BIOS='neocd-unibios.bin'    ;;
    *)          exit 1                            ;;
esac

# Verifica se a bios existe na pasta de bios, o raine não funciona sem bios.
if ! [ -f "${SHARE}/bios/${NEOCD_BIOS}" ]; then
    exit 1
fi

sed -i "s#^neocd_bios = .*#neocd_bios = ${SHARE}/bios/${NEOCD_BIOS}#" "${HOME}/configs/raine/rainex_sdl.cfg"

################################################################################

### SUAVISAR IMAGEM (SE DEFINIDO NAS OPÇÕES DO EMULATIONSTATION)

SUAVIZACAO_GAME="$(grep -F "neogeocd[\"$(basename "${ROM}")\"].smooth=" "$HOME/batocera.conf" | cut -d '=' -f 2)"
SUAVIZACAO_NEOCD="$(grep '^neogeocd.smooth=' "$HOME/batocera.conf" | cut -d '=' -f 2)"
SUAVIZACAO_GLOBAL="$(grep '^global.smooth=' "$HOME/batocera.conf" | cut -d '=' -f 2)"

if [ "$SUAVIZACAO_GAME" ] && [ ! "$SUAVIZACAO_GAME" == 'auto' ]; then
    SUAVIZACAO="$SUAVIZACAO_GAME"
elif [ "$SUAVIZACAO_NEOCD" ] && [ ! "$SUAVIZACAO_NEOCD" == 'auto' ]; then
    SUAVIZACAO="$SUAVIZACAO_NEOCD"
elif [ "$SUAVIZACAO_GLOBAL" ] && [ ! "$SUAVIZACAO_GLOBAL" == 'auto' ]; then
    SUAVIZACAO="$SUAVIZACAO_GLOBAL"
else
    SUAVIZACAO='auto'
fi

if [ "$SUAVIZACAO" == '0' ]; then
    sed -i s/'^ogl_filter = .*/ogl_filter = 9728/' "$HOME/configs/raine/rainex_sdl.cfg"
else
    sed -i s/'^ogl_filter = .*/ogl_filter = 9729/' "$HOME/configs/raine/rainex_sdl.cfg"
fi

################################################################################

### SHADERS (SE DEFINIDO NAS OPÇÕES DO EMULATIONSTATION)

FILTRO_GAME="$(grep -F "neogeocd[\"$(basename "${ROM}")\"].shaderset=" "$HOME/batocera.conf" | cut -d '=' -f 2)"
FILTRO_NEOCD="$(grep '^neogeocd.shaderset=' "$HOME/batocera.conf" | cut -d '=' -f 2)"
FILTRO_GLOBAL="$(grep '^global.shaderset=' "$HOME/batocera.conf" | cut -d '=' -f 2)"

if [ "$FILTRO_GAME" ] && [ ! "$FILTRO_GAME" == 'auto' ]; then
    FILTRO="$FILTRO_GAME"
elif [ "$FILTRO_NEOCD" ] && [ ! "$FILTRO_NEOCD" == 'auto' ]; then
    FILTRO="$FILTRO_NEOCD"
elif [ "$FILTRO_GLOBAL" ] && [ ! "$FILTRO_GLOBAL" == 'auto' ]; then
    FILTRO="$FILTRO_GLOBAL"
else
    FILTRO='auto'
fi

case "$FILTRO" in
    scanlines) sed -i "s#^ogl_shader = .*#ogl_shader = $RAINE_DIR/RaineEmu/shaders/scanline-3x.shader#" \
               "$HOME/configs/raine/rainex_sdl.cfg"
               ;;
    retro)     sed -i "s#^ogl_shader = .*#ogl_shader = $RAINE_DIR/RaineEmu/shaders/Themaister-scanlines.shader#" \
               "$HOME/configs/raine/rainex_sdl.cfg"
               ;;
    enhanced)  sed -i "s#^ogl_shader = .*#ogl_shader = $RAINE_DIR/RaineEmu/shaders/5xBR-v3.7c+CRT.OpenGL(hunterk).shader#" \
               "$HOME/configs/raine/rainex_sdl.cfg"
               ;;
    curvature) sed -i "s#^ogl_shader = .*#ogl_shader = $RAINE_DIR/RaineEmu/shaders/CRT-simple.shader#" \
               "$HOME/configs/raine/rainex_sdl.cfg"
               ;;
    auto)      sed -i "s#^ogl_shader = .*#ogl_shader = $RAINE_DIR/RaineEmu/shaders/None.shader#" \
               "$HOME/configs/raine/rainex_sdl.cfg"
esac

################################################################################

### ESTICAR IMAGEM (TELA CHEIA)

RES_GAME="$(grep -F "neogeocd[\"$(basename "${ROM}")\"].ratio=" "$HOME/batocera.conf" | cut -d '=' -f 2)"
RES_NEOCD="$(grep '^neogeocd.ratio=' "$HOME/batocera.conf" | cut -d '=' -f 2)"
RES_GLOBAL="$(grep '^global.ratio=' "$HOME/batocera.conf" | cut -d '=' -f 2)"

if [ "$RES_GAME" ] && [ ! "$RES_GAME" == 'auto' ]; then
    RESOLUTION="$RES_GAME"
elif [ "$RES_NEOCD" ] && [ ! "$RES_NEOCD" == 'auto' ]; then
    RESOLUTION="$RES_NEOCD"
elif [ "$RES_GLOBAL" ] && [ ! "$RES_GLOBAL" == 'auto' ]; then
    RESOLUTION="$RES_GLOBAL"
else
    RESOLUTION='auto'
fi

case "$RESOLUTION" in
    4/3|1/1|16/15|3/2|3/4|4/4|5/4|6/5|7/9|8/7|auto|custom|squarepixel)
        sed -i s/'^keep_ratio = .*/keep_ratio = 1/' "$HOME/configs/raine/rainex_sdl.cfg"
        ;;
    16/9|19/12|19/14|2/1|21/9|30/17|32/9|4/1|8/3)
        sed -i s/'^keep_ratio = .*/keep_ratio = 0/' "$HOME/configs/raine/rainex_sdl.cfg"
        ;;
esac

################################################################################

### USA A SAÍDA DE SOM PADRÃO DO BATOCERA NO RAINE.

if [ -e "$HOME/asound.state" ]; then
    if ! [ -e '/tmp/raine/asound.state' ]; then
        ln -s "$HOME/asound.state" '/tmp/raine'
    fi
elif [ -e '/tmp/raine/asound.state' ]; then
    rm '/tmp/raine/asound.state'
fi

if [ -e "$HOME/.asoundrc" ]; then
    if ! [ -e '/tmp/raine/.asoundrc' ]; then
        ln -s "$HOME/.asoundrc" '/tmp/raine'
    fi
elif [ -e '/tmp/raine/.asoundrc' ]; then
    rm '/tmp/raine/.asoundrc'
fi

################################################################################

### BIBLIOTECAS EXTRAS E OUTRAS CONFIGURAÇÕES

export LD_LIBRARY_PATH="$RAINE_DIR/libs:/lib32"
export LIBGL_DRIVERS_PATH='/lib32/dri'

export DISPLAY=:0.0
export HOME='/tmp/raine'

################################################################################

#### EXECUTA O RAINE (FINALMENTE)

cd "${RAINE_DIR}/RaineEmu"

case ${CORE} in
    raine2020|auto)
        ${MANGOHUD_CMD} ./raine2020 -video 0 -dbuf 1 -fullscreen 1 -nogui "${ROM}"
        ;;
    raine2015)
        ${MANGOHUD_CMD} ./raine2015 -video 0 -dbuf 1 -fullscreen 1 -nogui "${ROM}"
        ;;
    *)
        exit 1
esac

rm -r '/tmp/raine'

exit 0
