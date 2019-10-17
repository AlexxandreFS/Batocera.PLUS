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
EMULADOR="$3"
CONTROLE_NUM1="$4"
CONTROLE_ID1="$5"
CONTROLE_NUM2="$6"
CONTROLE_ID2="$7"

################################################################################

### CRIA DIRETÓRIOS USADOS PELO RAINE.

mkdir -p "$SHARE/roms/neogeocd"
mkdir -p "$SHARE/saves/neogeocd"
mkdir -p "$SHARE/screenshots"
mkdir -p "$SHARE/system/configs/raine"

mkdir -p "$SHARE/bios/raine/artwork"
mkdir -p "$SHARE/bios/raine/debug"
mkdir -p "$SHARE/bios/raine/demos"
mkdir -p "$SHARE/bios/raine/emudx"
mkdir -p "$SHARE/bios/raine/artwork"

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

    if [ -f "$HOME/batocera.conf" ]; then
        XLANG="$(cat "$HOME/batocera.conf" | grep ^system.language= | cut -d '=' -f 2)"
        case $XLANG in
            pt_BR|pt_PT) echo 'language = pt'     >> "$HOME/configs/raine/rainex_sdl.cfg" ;;
            es_ES)       echo 'language = es'     >> "$HOME/configs/raine/rainex_sdl.cfg" ;;
            fr_FR)       echo 'language = fr'     >> "$HOME/configs/raine/rainex_sdl.cfg" ;;
            *)           echo 'language = C'      >> "$HOME/configs/raine/rainex_sdl.cfg" ;;
        esac
    else
        echo 'language = C'                       >> "$HOME/configs/raine/rainex_sdl.cfg"
    fi
    echo ''                                       >> "$HOME/configs/raine/rainex_sdl.cfg"

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

### CONFIGURA O RAINE PARA USAR A BIOS ESCOLHIDA PELO USUÁRIO.

# Quando um core é escolhido para ser usado em todos jogos o emulationstation
# salva esta informação no arquivo $HOME/batocera.conf então este trexo do codigo
# verifica este arquivo para saber se foi definido algum core padrão para ser usado
# em todos os jogo e caso encontre ele define este core como o core a ser usado no
# jogo que será executado.

if [ "$EMULADOR" == 'auto' ]; then
    if [ -f "$HOME/batocera.conf" ] && \
       [ "$(cat $HOME/batocera.conf | grep neogeocd.emulator=)" ] && \
       [ "$(cat $HOME/batocera.conf | grep neogeocd.emulator= | cut -d'=' -f 2)" != 'auto' ]; then
        EMULADOR="$(cat $HOME/batocera.conf | grep neogeocd.emulator= | cut -d'=' -f 2)"
        if [ "$(cat $HOME/batocera.conf | grep neogeocd.core=)" ] && \
           [ "$(cat $HOME/batocera.conf | grep neogeocd.core= | cut -d'=' -f 2)" != 'auto' ]; then
            CORE="$(cat $HOME/batocera.conf | grep neogeocd.core= | cut -d'=' -f 2)"
        fi
    fi
fi

case "$EMULADOR" in
    raine-cdz|auto)   NEOCD_BIOS='neocd-cdz.bin'        ;;
    raine-front-load) NEOCD_BIOS='neocd-front-load.bin' ;;
    raine-top-load)   NEOCD_BIOS='neocd-top-load.bin'   ;;
    raine-unibios)    NEOCD_BIOS='neocd-unibios.bin'    ;;
    *)                exit 1                            ;;
esac

if [ -f "$SHARE/bios/$NEOCD_BIOS" ]; then
    sed -i "s#^neocd_bios = .*#neocd_bios = $SHARE/bios/$NEOCD_BIOS#" "$HOME/configs/raine/rainex_sdl.cfg"
else
    exit 1
fi

################################################################################

### SUAVISAR IMAGEM (SE DEFINIDO NAS OPÇÕES DO EMULATIONSTATION)

if [ -f "$HOME/batocera.conf" ]; then
    if [ "$(cat $HOME/batocera.conf | grep neogeocd.smooth= | cut -d'=' -f 2)" == '0' ]; then
        sed -i s/'^ogl_filter = .*/ogl_filter = 9728/' "$HOME/configs/raine/rainex_sdl.cfg"
    elif [ "$(cat $HOME/batocera.conf | grep neogeocd.smooth= | cut -d'=' -f 2)" == '1' ]; then
        sed -i s/'^ogl_filter = .*/ogl_filter = 9729/' "$HOME/configs/raine/rainex_sdl.cfg"
    elif [ "$(cat $HOME/batocera.conf | grep global.smooth= | cut -d'=' -f 2)" == '0' ]; then
        sed -i s/'^ogl_filter = .*/ogl_filter = 9728/' "$HOME/configs/raine/rainex_sdl.cfg"
    elif [ "$(cat $HOME/batocera.conf | grep global.smooth= | cut -d'=' -f 2)" == '1' ]; then
        sed -i s/'^ogl_filter = .*/ogl_filter = 9729/' "$HOME/configs/raine/rainex_sdl.cfg"
    fi
fi

################################################################################

### SCANLINES

if [ -f "$HOME/batocera.conf" ]; then
    FILTRO_GLOBAL="$(cat $HOME/batocera.conf | grep ^global.shaderset= | cut -d'=' -f 2)"
    FILTRO_NEOCD="$(cat $HOME/batocera.conf | grep ^neogeocd.shaderset= | cut -d'=' -f 2)"
fi

if [ "$FILTRO_NEOCD" == 'scanlines' ]; then
    sed -i "s#^ogl_shader = .*#ogl_shader = $RAINE_DIR/RaineEmu/shaders/scanline-3x.shader#"           "$HOME/configs/raine/rainex_sdl.cfg"
elif [ "$FILTRO_NEOCD" == 'retro' ]; then
    sed -i "s#^ogl_shader = .*#ogl_shader = $RAINE_DIR/RaineEmu/shaders/Themaister-scanlines.shader#"  "$HOME/configs/raine/rainex_sdl.cfg"
elif [ "$FILTRO_GLOBAL" == 'scanlines' ]; then
    sed -i "s#^ogl_shader = .*#ogl_shader = $RAINE_DIR/RaineEmu/shaders/scanline-3x.shader#"           "$HOME/configs/raine/rainex_sdl.cfg"
elif [ "$FILTRO_GLOBAL" == 'retro' ]; then
    sed -i "s#^ogl_shader = .*#ogl_shader = $RAINE_DIR/RaineEmu/shaders/Themaister-scanlines.shader#"  "$HOME/configs/raine/rainex_sdl.cfg"
fi

################################################################################

### ESTICAR IMAGEM (TELA CHEIA)

if [ -f "$HOME/batocera.conf" ]; then
    RES_NEOCD="$(cat $HOME/batocera.conf | grep neogeocd.ratio= | cut -d'=' -f 2)"
    RES_GLOBAL="$(cat $HOME/batocera.conf | grep global.ratio=   | cut -d'=' -f 2)"

    if [ "$RES_NEOCD" ]; then
        RESOLUTION="$RES_NEOCD"
    elif [ "$RES_GLOBAL" ]; then
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
fi

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

cd "$RAINE_DIR/RaineEmu"

if [ "$CORE" == 'raine2018' ] || [ "$CORE" == 'auto' ]; then
    ./raine2018 -video 0 -dbuf 1 -fullscreen 1 -nogui "$ROM"
elif [ "$CORE" == 'raine2015' ]; then
    ./raine2015 -video 0 -dbuf 1 -fullscreen 1 -nogui "$ROM"
else
    exit 1
fi

rm -r '/tmp/raine'

exit 0

################################################################################

### REFULGO

#finalburn-teste.
#bios in rom folder[neocdz.zip, neogeo.zip]
#retroarch -v -L /usr/lib/libretro/fba_libretro.so --subsystem neocd /recalbox/share/roms/neogeo/King\ of\ Fighters\ \'96\,\ The\ \(1996\)\(SNK\)\(Jp-US\)\[\!\]\[NGCD-214\ MT\ A01\,\ NGCD-214E\].cue

#cat > /etc/profile << "EOF"
# trololo
#EOF

################################################################################