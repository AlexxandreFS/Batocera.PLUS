#!/bin/sh
#
# Batocera.PLUS
#
# Código escrito por: Sérgio de Carvalho Júnior
#
# COMMAND LINE
# vpinball.sh [ROM] [RESOLUTION] [P1GUID]
#
# XJOYPAD LEGEND
# Keyboard - xinput
#  Default   Default
#    1         A
#    2         B
#    3         X
#    4         Y
#    5         LB
#    6         RB
#    7         Select
#    8         Start
#    9         Guide Button
#    0         Left Analog Button
#    Q         Right Analog Button
#    W         Dpad Left
#    E         Dpad Rigt
#    R         Dpad Up
#    T         Dpad Down
#    Z         ?
#   UP         Left Analog Pad
#  DOWN        Left Analog Pad
#  LEFT        Left Analog Pad
#  RIGHT       Left Analog Pad
#
# SOURCE OF INFORMATION
# https://github.com/vpinball/vpinball
# https://github.com/vpinball/pinmame
# https://www.vpforums.org/
# https://vpuniverse.com/forums/
# https://www.vpforums.org/index.php?showtopic=43650

################################################################################

### PARÂMETROS

JOGO="${1}"
RESOLUTION="${2}"
P1GUID="${3}"
JOYPAD="${4}"
P1NAME="${5}"
LOG_GAME="${JOGO}"
WINE='wine-stable'


################################################################################

### CAMINHOS

VP_DIR='/opt/VisualPinball'
VP_SDIR="$HOME/../saves/vpinball"
VP_CDIR="$HOME/configs/vpinball"

################################################################################

### EXPORTS

export WINEPREFIX="${VP_SDIR}/wine"

################################################################################

### HELP

function help()
{
    echo
    echo ' Visual Pinball Launcher for Batocera.PLUS'
    echo
    echo ' Codigo escrito por: Sérgio de Carvalho Júnior'
    echo
    echo ' Linha de comando:'
    echo ' vpinball.sh [ROM] [RESOLUTION] [P1GUID]'
    echo
    echo ' ROM = Caminho do jogo até a .vpt ou .vpx'
    echo ' RESULUTION = auto ou algo que respeite a regra XXXXxXXXX ex: [1920x1080]'
    echo ' PIGUID = parâmetro do emulatorlauncher.sh (OPICIONAL)'
    echo
}

if [ "${1}" == '--help' ]; then
    help
    exit 0
fi

################################################################################

### NÃO EXECUTA O EMULADOR DUAS VEZES

if [ "$(pidof wineserver)" ]; then
    echo ' Visual Pinball Launcher já esta sendo executado'
    exit 1
fi

################################################################################

### LAUNCHER INFO

echo
echo ' Visual Pinball Launcher for Batocera.PLUS'
echo
echo ' Codigo escrito por: Sergio de Carvalho Junior'
echo

################################################################################

### INSTALAÇÃO DO VISUAL PINBALL

function createFolders()
{
    ### Create work dir
    mkdir -p "${VP_CDIR}"
    cp -rf "${VP_DIR}/emulator/VPinMAME" "${VP_CDIR}"
    cp -rf "${VP_DIR}/emulator/0995"     "${VP_CDIR}"
    cp -rf "${VP_DIR}/emulator/1062"     "${VP_CDIR}"
    cp -r "${VP_DIR}/emulator/run.exe"  "${VP_CDIR}"

    ### Create save dir
    mkdir -p "${VP_SDIR}/Music" \
             "${VP_SDIR}/wine" \
             "${VP_SDIR}/User"
    cp -rf "${VP_DIR}/deps/Scripts"      "${VP_SDIR}"
    cp -rf "${VP_DIR}/deps/samples"      "${VP_SDIR}"
    cp -rf "${VP_DIR}/deps/nvram"        "${VP_SDIR}"

    ### Create folders
    DIRS='artwork cfg diff hi inp memcard snap sta wave Scripts Music User'
    for i in ${DIRS}; do
        case ${i} in
            Scripts|User|Music)
                ln -sf "${VP_SDIR}/$i" "${VP_CDIR}/0995"
                ln -sf "${VP_SDIR}/$i" "${VP_CDIR}/1062" ;;
            *)
                mkdir -p "${VP_SDIR}/$i"
        esac
    done
}

function applyConfig()
{
    ### Install wine extras on wine prefix
    export INSTALL_EXTRAS=1
    export WINE_LOADINGSCREEN=0

    ### install deps for future pinball
	echo 'Install deps for future pinball...'
    batocera-load-screen -t 600 -i '/opt/VisualPinball/pinball_loading.jpg' &

    ### Apply default configs
    echo 'Apply visual pinball default configs...'
    $WINE regedit "${VP_DIR}/emulator/config.reg" 2>&1&> /dev/null
	
	### Install wsh57
    echo 'Installing MS Windows Script Host 5.7...'
    ln -sf "${VP_DIR}/deps/wsh57/"* "$WINEPREFIX/drive_c/windows/syswow64"
	DLL='dispex.dll jscript.dll scrobj.dll scrrun.dll vbscript.dll wshcon.dll wshext.dll'
    for i in $DLL; do
	    $WINE regsvr32 "$WINEPREFIX/drive_c/windows/syswow64/${i}" 2>&1&> /dev/null
		echo "${i} Successfully registered!"
	done

    ### Install oleaut32
	ln -sf "${VP_DIR}/deps/oleaut32/x32/oleaut32.dll" "$WINEPREFIX/drive_c/windows/system32" 2>&1&> /dev/null
	ln -sf "${VP_DIR}/deps/oleaut32/x64/oleaut32.dll" "$WINEPREFIX/drive_c/windows/syswow64" 2>&1&> /dev/null

    sleep 0.5

    ### Install PinMAME.dll
    echo 'Installing VPinMAME...'
    $WINE regsvr32 "${VP_CDIR}/VPinMAME/VPinMAME.dll" 2>&1&> /dev/null
    echo 'VPinMAME.dll Successfully registered!'
	
	while [ "$(pidof wineserver)" ]; do
           sleep 1
    done

    if [ "$(pidof yad)" ]; then
        killall yad
    fi

}

function choseEmu()
{
    # Open configurator in miximized window
    sed -i s'/"WindowMaximized"=.*/"WindowMaximized"=dword:00000001/' "${VP_SDIR}/wine/user.reg"

    yad --form \
    --title='VISUAL PINBALL' \
    --window-icon='/usr/share/icons/batocera/vpinball.png' \
    --text='\n  Choose a option.\n' \
    --button='VISUAL PINBALL:0' \
    --button='VISUAL PINBALX:1' \
    --fixed --center \
    --close-on-unfocus

    case ${?} in
        0) GUI="${VP_CDIR}/0995/VPinball995.exe" ;;
        1) GUI="${VP_CDIR}/1062/VPinballX.exe"   ;;
        *) exit 0
    esac
}

################################################################################

### CHECK FOLDERS

if [ -e "${VP_SDIR}/wine/.update-timestamp" ]; then # if wine version has changed
    SDIR_VERSION="$(cat -e "${VP_SDIR}/wine/.update-timestamp" | cut -d '^' -f 1)"
    OPT_WINE="$(stat -t "/opt/Wine/${WINE}/share/wine/wine.inf" | awk '{print $12}')"
    if [ "${OPT_WINE}" != "${SDIR_VERSION}" ] && [ -e "${VP_SDIR}/wine" ]; then
        rm -r "${VP_SDIR}/wine"
    fi
fi

if [ ! "$(ls -A "${VP_CDIR}" 2> /dev/null)" ] || [ ! "$(ls -A "${VP_SDIR}"  2> /dev/null)" ]; then # if is a new instalation
    createFolders
    applyConfig
elif [ ! "$(ls -A "${VP_SDIR}/wine" 2> /dev/null)" ]; then # if wineprefix if does not exist
    mkdir -p "${VP_SDIR}/wine"
    applyConfig
fi

################################################################################

### FORCE SOME SETTINGS

if [ -e "${VP_SDIR}/wine/user.reg" ]; then
    # fix Visual Pinball settings
    sed -i s'/"FullScreen"=.*/"FullScreen"=dword:00000001/'          "${VP_SDIR}/wine/user.reg"
    
    # PinMAME fix settings
    sed -i s'/"cabinet_mode"=.*/"cabinet_mode"=dword:00000001/'      "${VP_SDIR}/wine/user.reg"
    sed -i s'/"showpindmd"=.*/"showpindmd"=dword:00000000/'          "${VP_SDIR}/wine/user.reg"
    sed -i s'/"showwindmd"=.*/"showwindmd"=dword:00000001'           "${VP_SDIR}/wine/user.reg"
    sed -i s'/"skip_disclaimer"=.*/"skip_disclaimer"=dword:00000000' "${VP_SDIR}/wine/user.reg"
    sed -i s'/"skip_gameinfo"=.*/"skip_gameinfo"=dword:00000000'     "${VP_SDIR}/wine/user.reg"
    sed -i s'/"dmd_doublesize"=.*/"dmd_doublesize"=dword:00000001'   "${VP_SDIR}/wine/user.reg"
fi

################################################################################
    
### RESOLUTION

RES_START="$(batocera-resolution currentMode)"

if [ "${RESOLUTION}" == 'auto' ] || [ "${RESOLUTION}" == '' ]; then
    XRES="$(echo "${RES_START}" | cut -d 'x' -f 1)"
    YRES="$(echo "${RES_START}" | cut -d 'x' -f 2)"
else
    batocera-resolution setMode "${RESOLUTION}"
    XRES="$(echo "${RESOLUTION}" | cut -d 'x' -f 1)"
    YRES="$(echo "${RESOLUTION}" | cut -d 'x' -f 2)"
fi

XRES="$( printf "%x\n" "${XRES}")"
YRES="$( printf "%x\n" "${YRES}")"
sed -i s'/"Width"=.*/"Width"=dword:00000'"${XRES}"'/'   "${VP_SDIR}/wine/user.reg"
sed -i s'/"Height"=.*/"Height"=dword:00000'"${YRES}"'/' "${VP_SDIR}/wine/user.reg"

################################################################################

### ROM/EMULATOR DETECTION

if [ "${JOGO}" != '' ]; then
    ROM_EXTENSION='.vpt .VPT .vpx .VPX'
    for i in ${ROM_EXTENSION}; do
        if [ "$(echo "${JOGO}" | grep "${i}")" ]; then
            JOGO="$(echo "Z:${JOGO}" | sed -e 's#/#\\#g')"
            case $i in
                .vpt|.VPT) EMU_EXE="${VP_CDIR}/0995/VPinball995.exe"
                           EMU_PID='VPinball995.exe';;
                .vpx|.VPX) EMU_EXE="${VP_CDIR}/1062/VPinballX.exe"
                           EMU_PID='VPinballX.exe';;
            esac
            break        
        fi
    done
else
    EMU_EXE='gui'
fi

################################################################################

### HOTKEY

if [ "${P1GUID}" != '' ]; then
    BOTOES="$(/opt/Wine/getHotkeyStart "${P1GUID}")"
    BOTAO_HOTKEY="$(echo "${BOTOES}" | cut -d ' ' -f 1)"
    BOTAO_START="$(echo "${BOTOES}"  | cut -d ' ' -f 2)"

    if [ "${BOTAO_HOTKEY}" ] && [ "${BOTAO_START}" ]; then
        # persistent mode for hotkey detection
        while : ; do
            nice -n 20 xjoykill -hotkey "${BOTAO_HOTKEY}" -start "${BOTAO_START}" -kill /opt/VisualPinball/killvpinball
            if [ ! "$(pidof "${EMU_PID}")" ]; then
                break
            fi
            sleep 5
        done &
    fi
fi

################################################################################

### PAD TO KEYBOARD

if [ "${JOYPAD}" ]; then
    if [ "${JOYPAD}" != 'off' ]; then
        # Visual Pinball keyboard fix settings ( if user change this setting )
        sed -i s'/"PlungerKey"=.*/"PlungerKey"=dword:0000001c/'   "${VP_SDIR}/wine/user.reg" 2>&1&> /dev/null
        sed -i s'/"RFlipKey"=.*/"RFlipKey"=dword:00000036/'       "${VP_SDIR}/wine/user.reg" 2>&1&> /dev/null
        sed -i s'/"LFlipKey"=.*/"LFlipKey"=dword:0000002a/'       "${VP_SDIR}/wine/user.reg" 2>&1&> /dev/null
        sed -i s'/"RTiltKey"=.*/"RTiltKey"=dword:00000035/'       "${VP_SDIR}/wine/user.reg" 2>&1&> /dev/null
        sed -i s'/"LTiltKey"=.*/"LTiltKey"=dword:0000002c/'       "${VP_SDIR}/wine/user.reg" 2>&1&> /dev/null
        sed -i s'/"MechTilt"=.*/"MechTilt"=dword:00000014/'       "${VP_SDIR}/wine/user.reg" 2>&1&> /dev/null
	    sed -i s'/"UDAxis"=.*/"UDAxis"=dword:00000000/'           "${VP_SDIR}/wine/user.reg" 2>&1&> /dev/null
        sed -i s'/"UDAxisFlip"=.*/"UDAxisFlip"=dword:00000000/'   "${VP_SDIR}/wine/user.reg" 2>&1&> /dev/null
        sed -i s'/"PlungerAxis"=.*/"PlungerAxis"=dword:00000006/' "${VP_SDIR}/wine/user.reg" 2>&1&> /dev/null
        sed -i s'/"PlungerKey"=.*/"PlungerKey"=dword:0000001c/'   "${VP_SDIR}/wine/user.reg" 2>&1&> /dev/null
        sed -i s'/"LRAxis"=.*/"LRAxis"=dword:00000000/'           "${VP_SDIR}/wine/user.reg" 2>&1&> /dev/null
        sed -i s'/"LRAxisFlip"=.*/"LRAxisFlip"=dword:00000000/'   "${VP_SDIR}/wine/user.reg" 2>&1&> /dev/null

        # Auto detect pluged controller
	    if [ "$(echo "${P1NAME}" | grep 'PS3' )" ] || [ "$(echo "${P1NAME}" | grep 'PLAYSTATION' )" ]; then
            KEY_PAD='-device /dev/input/js0 -up 42 -down 42 -left 42 -right 42 -buttons 36 42 42 42 50 62 42 42 14 10 42 42 42 52 97 28 65'
        elif [ "$(echo "${P1NAME}" | grep 'Xbox' )" ] || [ "$(echo "${P1NAME}" | grep 'X-Box' )" ]; then
            KEY_PAD='-device /dev/input/js0 -up 42 -down 42 -left 42 -right 42 -buttons 36 42 42 42 50 62 14 10 42 42 42 52 97 28 65 42 00'
	    else
	        KEY_PAD='-device /dev/input/js0 -up 52 -down 65 -left 97 -right 28 -buttons 42 42 36 42 50 62 42 42 14 10 42 42 42 52 65 97 28'
	    fi

        # Persistent mode gamepad detection
        if [ -e '/dev/input/js0' ]; then
            while :; do
                nice -n -15 xjoypad ${KEY_PAD}
                if [ ! "$(pidof "${EMU_PID}")" ]; then
                    break
                fi
                sleep 5
            done &
        fi
	fi
fi

################################################################################

### LOGS

echo "received: /opt/VirtualPinball/vpinball.sh ${LOG_GAME} ${RESOLUTION} ${RATIO} ${P1GUID} ${CTRL_TYPE}" > "${HOME}/logs/vpinball.log"
if [ "${EMU_EXE}" == 'gui' ]; then
    echo "running: /opt/VirtualPinball/vpinball.sh ${EMU_EXE}" >> "${HOME}/logs/vpinball.log"
else
    echo "running: ${EMU_EXE} -minimized -exit -play ${JOGO}" >> "${HOME}/logs/vpinball.log"
fi

################################################################################

### RUN

export VIRTUAL_DESKTOP=1
case ${EMU_EXE} in
    "${VP_CDIR}/1062/VPinballX.exe")    
                        $WINE "${VP_CDIR}/run.exe" \
		                "${EMU_EXE}" "${JOGO}" ;;         # run visual pinball X
    "${VP_CDIR}/0995/VPinball995.exe")
                        $WINE "${VP_CDIR}/run.exe" \
                        "${EMU_EXE}" "${JOGO}" ;;         # run visual pinball 9
    gui)
                        choseEmu                          # opens selection menu
                        $WINE "${GUI}" ;;                 # execute selected
    *)                  exit 0
esac

################################################################################

### END OF EMULATOR EXECUTION

# Wait the emulator to finish execution
while [ "$(pidof wineserver)" ]; do
    sleep 1
done

# Kill keyboard emulator
if [ "$(pidof -s xjoypad)" ]; then
    killall -9 xjoypad
fi

exit 0
