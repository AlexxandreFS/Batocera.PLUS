#!/bin/bash
##
## Batocera.PLUS
##
## Código escrito por: Sérgio de Carvalho Júnior
## Supervisão: Alexandre Freire dos Santos
##
## https://forums.pcsx2.net/Thread-PCSX2-Widescreen-Game-Patches?pid=271674#pid271674
## https://www.mediafire.com/file/j48lgoeeli5evve/PCSX_Cheats_Pack_v1.1_-_Mateus_Auri.rar/file
##
################################################################################

ROMS_FOLDER=/userdata/roms/ps2
PCSX2_SAVE_DIR="/userdata/saves/ps2"
PCSX2_DIR="$(dirname ${0})"

################################################################################

### CRIA LISTA TEMPORARIA

LISTA="$( ls -al "${ROMS_FOLDER}" | grep -Ev '\.(txt|xml|mds)$' | egrep -v ^d | cut -b 58- | sed 's/^ *//' | sed '/^$/d' )"
echo "${LISTA}" > /tmp/LISTA.txt

################################################################################

### POPULATE ALL PCSX2 STANDALONE

mkdir -p "${PCSX2_SAVE_DIR}/pcsx2/Slot 1" \
         "${PCSX2_SAVE_DIR}/pcsx2/Slot 2" \
         "${PCSX2_SAVE_DIR}/sstates" \
         "${PCSX2_SAVE_DIR}/cheats" \
         "${PCSX2_SAVE_DIR}/cheats_ws" \
         "${PCSX2_SAVE_DIR}/memcards" \
         "${PCSX2_SAVE_DIR}/textures" \
         "${HOME}/configs/${CORE}" \
         "${HOME}/.cache/pcsx2_cache"

"${PCSX2_DIR}/pcsx2-mainline/pcsx2-mainline.sh" 'populate'
"${PCSX2_DIR}/pcsx2-legacy/pcsx2-legacy.sh"     'populate'
"${PCSX2_DIR}/pcsx2/pcsx2-pcsx2.sh"             'populate'


for INDEX in {1..2}
do
    touch "${PCSX2_SAVE_DIR}/pcsx2/Slot ${INDEX}/Shared Memory Card (8 MB).ps2"

    if ! [ -e "${PCSX2_SAVE_DIR}/memcards/Mcd00${INDEX}.ps2" ]
    then
        ln -s "${PCSX2_SAVE_DIR}/pcsx2/Slot ${INDEX}/Shared Memory Card (8 MB).ps2" \
              "${PCSX2_SAVE_DIR}/memcards/Mcd00${INDEX}.ps2"
    fi
done

################################################################################

### FUNÇÕES

function mainList()
{

    local RESOLUTION=$(batocera-resolution currentResolution)
    local RESOLUTION_X=$(echo ${RESOLUTION} | cut -d x -f 1)
    local RESOLUTION_Y=$(echo ${RESOLUTION} | cut -d x -f 1)
    local MAX_SIZE_X
    local MAX_SIZE_Y
    local RESP

    MAX_SIZE_X=800
    MAX_SIZE_Y=600

    if [ "${RESOLUTION_X}" -ge '1024' ]
    then
        RESOLUTION_X=${MAX_SIZE_X}
    else
        RESOLUTION_X=$(( ${RESOLUTION_X} - 20 ))
    fi

    if [ "${RESOLUTION_Y}" -ge '768' ]
    then
        RESOLUTION_Y=${MAX_SIZE_Y}
    else
        RESOLUTION_Y=$(( ${RESOLUTION_Y} - 20 ))
    fi

    X="${RESOLUTION_X}"
	Y="${RESOLUTION_Y}"

    RESP=$( yad \
        --title='PCSX2 MANUAL CONFIGURATOR' \
	    --window-icon=/usr/share/icons/batocera/pcsx2.png \
        --fixed \
        --center \
        --no-headers \
	    --list \
        --column='' < /tmp/LISTA.txt \
        --width=${X} \
        --height=${Y}
	)

    ROM="$( echo "${RESP}" | cut -d '|' -f 1 )"
	
}

function mainSelector()
{
    case ${LANG%.*} in
        pt_BR) MSG='ESCOLHA UMA OPÇÃO' ;;
        es_ES) MSG='ESCOGE UNA OPCIÓN' ;;
            *) MSG='CHOOSE A OPTION'
    esac

    yad --form \
        --title='PCSX2 MANUAL' \
        --window-icon='/usr/share/icons/batocera/pcsx2.png' \
        --text=''"\n${MSG}\n"'' \
        --text-align=center \
        --button='PCSX2-LEGACY:0' \
        --button='PCSX2-MAINLINE:1' \
        --fixed \
        --center

    case ${?} in
        0) PCSX2='/opt/Pcsx2/pcsx2-legacy/pcsx2-legacy.sh' ;;
        1) PCSX2='/opt/Pcsx2/pcsx2-mainline/pcsx2-mainline.sh' ;;
        *) exit 0
    esac
	
}

################################################################################

ROM=''

while [ "${ROM}" == '' ]
do
    mainSelector
	mainList
done

$PCSX2 "${ROMS_FOLDER}/${ROM}" " " "2"
