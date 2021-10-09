#!/bin/bash
### Batocera.PLUS
### Alexandre Freire dos Santos
### Cria a configuração inicial de controles para o Yuzu.

################################################################################

PLAYER=${1}
GUID=${2}

################################################################################

### ESTE MODELO FOI COPIADO DO ARQUIVO DE CONFIGIRAÇÃO DO YUZU

TEMPLATE=(
    # Direções
    'player_%PLAYER%_button_dup="hat:0,direction:up,guid:%GUID%,port:0,engine:sdl"'
    'player_%PLAYER%_button_dup\default=false'
    'player_%PLAYER%_button_ddown="hat:0,direction:down,guid:%GUID%,port:0,engine:sdl"'
    'player_%PLAYER%_button_ddown\default=false'
    'player_%PLAYER%_button_dleft="hat:0,direction:left,guid:%GUID%,port:0,engine:sdl"'
    'player_%PLAYER%_button_dleft\default=false'
    'player_%PLAYER%_button_dright="hat:0,direction:right,guid:%GUID%,port:0,engine:sdl"'
    'player_%PLAYER%_button_dright\default=false'

    # Principais botões
    'player_%PLAYER%_button_a="toggle:0,button:%a%,guid:%GUID%,port:0,engine:sdl"'
    'player_%PLAYER%_button_a\default=false'
    'player_%PLAYER%_button_b="toggle:0,button:%b%,guid:%GUID%,port:0,engine:sdl"'
    'player_%PLAYER%_button_b\default=false'
    'player_%PLAYER%_button_x="toggle:0,button:%x%,guid:%GUID%,port:0,engine:sdl"'
    'player_%PLAYER%_button_x\default=false'
    'player_%PLAYER%_button_y="toggle:0,button:%y%,guid:%GUID%,port:0,engine:sdl"'
    'player_%PLAYER%_button_y\default=false'

    # Botões de ombro da esquerda
    'player_%PLAYER%_button_l="toggle:0,button:%pagedown%,guid:%GUID%,port:0,engine:sdl"'
    'player_%PLAYER%_button_l\default=false'
    'player_%PLAYER%_button_sl="toggle:0,button:%l2%,guid:%GUID%,port:0,engine:sdl"'
    'player_%PLAYER%_button_sl\default=false'
    'player_%PLAYER%_button_lstick="toggle:0,button:%l3%,guid:%GUID%,port:0,engine:sdl"'
    'player_%PLAYER%_button_lstick\default=false'

    # Botões de ombro da direita
    'player_%PLAYER%_button_r="toggle:0,button:%pageup%,guid:%GUID%,port:0,engine:sdl"'
    'player_%PLAYER%_button_r\default=false'
    'player_%PLAYER%_button_sr="toggle:0,button:%r2%,guid:%GUID%,port:0,engine:sdl"'
    'player_%PLAYER%_button_sr\default=false'
    'player_%PLAYER%_button_rstick="toggle:0,button:%r3%,guid:%GUID%,port:0,engine:sdl"'
    'player_%PLAYER%_button_rstick\default=false'

    # Botões auxiliares
    'player_%PLAYER%_button_minus="toggle:0,button:%select%,guid:%GUID%,port:0,engine:sdl"'
    'player_%PLAYER%_button_minus\default=false'
    'player_%PLAYER%_button_plus="toggle:0,button:%start%,guid:%GUID%,port:0,engine:sdl"'
    'player_%PLAYER%_button_plus\default=false'
    'player_%PLAYER%_button_home="toggle:0,button:%hotkey%,guid:%GUID%,port:0,engine:sdl"'
    'player_%PLAYER%_button_home\default=false'

    # Gatilhos
    'player_%PLAYER%_button_zl="threshold:0.5,axis:2,direction:+,guid:%GUID%,port:0,engine:sdl"'
    'player_%PLAYER%_button_zl\default=false'
    'player_%PLAYER%_button_zr="threshold:0.5,axis:5,direction:+,guid:%GUID%,port:0,engine:sdl"'
    'player_%PLAYER%_button_zr\default=false'

    # Analógicos
    'player_%PLAYER%_lstick="range:1.000000,deadzone:0.100000,invert_y:+,invert_x:+,offset_y:-0.000000,axis_y:%joystick1up%,offset_x:-0.000000,axis_x:%joystick1left%,guid:%GUID%,port:0,engine:sdl"'
    'player_%PLAYER%_lstick\default=false'
    'player_%PLAYER%_rstick="range:1.000000,deadzone:0.100000,invert_y:+,invert_x:+,offset_y:-0.000000,axis_y:%joystick2up%,offset_x:-0.000000,axis_x:%joystick2left%,guid:%GUID%,port:0,engine:sdl"'
    'player_%PLAYER%_rstick\default=false'

    'player_%PLAYER%_button_screenshot=[empty]'
)

################################################################################

### PROCURA PELO ARQUIVO DE CONFIGURAÇÃO DE CONTROLES DO ES.

ES_INPUT_FILES=(
    "$HOME/configs/emulationstation/es_last_input.cfg"
    "$HOME/configs/emulationstation/es_input.cfg"
    '/usr/share/batocera/datainit/system/configs/emulationstation/es_input.cfg'
)

for FILE in ${ES_INPUT_FILES[*]}
do
    if [ -f "${FILE}" ]
    then
        if grep -q "deviceGUID=\"${GUID}\">" "${FILE}"
        then
            ES_INPUT_FILE="${FILE}"
            break
        fi
    fi
done

if ! [ -f "${ES_INPUT_FILE}" ]
then
    exit 1
fi

unset FILE ES_INPUT_FILES

################################################################################

### FAZ A LEITURA DO ARQUIVO DE CONFIGURAÇÃO DE CONTROLES DO ES.

BUTTONS="$(xml sel -T -t -m "/inputList/inputConfig[@deviceGUID='${GUID}']/*" -v "concat(@name,':', @id)" -n "${ES_INPUT_FILE}")"

if [ -z "${BUTTONS}" ]
then
    exit 2
fi

for BUTTON in a b x y pagedown l2 l3 pageup r2 r3 select start hotkey joystick1up joystick1left joystick2up joystick2left
do
    KEY=$(echo "${BUTTONS}" | grep -E "^${BUTTON}:" | cut -d ':' -f 2)

    case ${BUTTON} in
        a)             A=${KEY}             ;;
        b)             B=${KEY}             ;;
        x)             X=${KEY}             ;;
        y)             Y=${KEY}             ;;
        pagedown)      PAGEDOWN=${KEY}      ;;
        l2)            L2=${KEY}            ;;
        l3)            L3=${KEY}            ;;
        pageup)        PAGEUP=${KEY}        ;;
        r2)            R2=${KEY}            ;;
        r3)            R3=${KEY}            ;;
        select)        SELECT=${KEY}        ;;
        start)         START=${KEY}         ;;
        hotkey)        HOTKEY=${KEY}        ;;
        joystick1up)   JOYSTICK1UP=${KEY}   ;;
        joystick1left) JOYSTICK1LEFT=${KEY} ;;
        joystick2up)   JOYSTICK2UP=${KEY}   ;;
        joystick2left) JOYSTICK2LEFT=${KEY} ;;
    esac
done

unset BUTTONS BUTTON KEY

################################################################################

### CRIA A CONFIGURAÇÃO DE CONTROLES ALTERANDO O TEMPLATE

JOYPAD_CONF=$(
    printf "%s\n" "${TEMPLATE[@]}" |
        sed "s/%PLAYER%/${PLAYER}/g" |
        sed "s/%GUID%/${GUID}/g" |
        sed "s/%a%/${A}/" |
        sed "s/%b%/${B}/" |
        sed "s/%x%/${X}/" |
        sed "s/%y%/${Y}/" |
        sed "s/%pagedown%/${PAGEDOWN}/" |
        sed "s/%l2%/${L2}/" |
        sed "s/%l3%/${L3}/" |
        sed "s/%pageup%/${PAGEUP}/" |
        sed "s/%r2%/${R2}/" |
        sed "s/%r3%/${R3}/" |
        sed "s/%select%/${SELECT}/" |
        sed "s/%start%/${START}/" |
        sed "s/%hotkey%/${HOTKEY}/" |
        sed "s/%joystick1up%/${JOYSTICK1UP}/" |
        sed "s/%joystick1left%/${JOYSTICK1LEFT}/" |
        sed "s/%joystick2up%/${JOYSTICK2UP}/" |
        sed "s/%joystick2left%/${JOYSTICK2LEFT}/"
)

################################################################################

printf "%s\n" "${JOYPAD_CONF[@]}"

exit 0
