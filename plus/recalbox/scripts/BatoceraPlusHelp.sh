#!/bin/sh
clear
cat << EOF

    JOYSTICK BASIC KEY
    ============================================================================

    B      = CONFIRM
    A      = RETURN
    Y      = ADD GAME TO FAVORITES
    X      = RUN KODI
    L1     = PREVIOUS PAGE (if activated in options)
    R1     = NEXT PAGE (if activated in options)
    START  = MENU
    SELECT = OPTIONS

    Batocera.PLUS [Press any key to continue...]
EOF

read -n 1 -s x
clear
cat << EOF

    JOYSTICK SHORTCURTS
    ============================================================================

    HOTKEY + B     = RETROARCH MENU                                
    HOTKEY + A     = RESET GAME
    HOTKEY + Y     = SAVE STATE 
    HOTKEY + X     = LOAD STATE

    HOTKEY + L1    = SAVE SCREENSHOT
    HOTKEY + R1    = NO USE
    HOTKEY + L2    = PREVIOUS SHADER PRESET
    HOTKEY + R2    = NEXT SHADER PRESET

    HOTKEY + UP    = SELECT SAVE SLOT -1
    HOTKEY + DOWN  = SELECT SAVE SLOT +1
    HOTKEY + RIGHT = SPEEDUP GAME
    HOTKEY + Left  = REWIND (if activated in options)

    HOTKEY + START = END GAME AND QUIT TO MAIN MENU

    Batocera.PLUS [Press any key to continue...]
EOF
read -n 1 -s x
clear

cat << EOF

    KEYBOARD SHORTCURTS
    ============================================================================

    F5              = BASIC INFO
    WIN + F5        = THIS HELP

    F1              = FILE EXPLORER
    WIN  + F4       = OPEN A TERMINAL
    WIN  + F10      = OPEN THE MOZILLA FIREFOX BROWSER
    CTRL + ALT + F3 = OPEN COMMAND LINE LINUX (user: root | password: linux)

    PRINT           = SAVE SCREENSHOT IN PNG FORMAT
    WIN  + P        = SAVE SCREENSHOT IN PNG FORMAT    
    WIN  + PRINT    = SAVE SCREENSHOT IN JPG FORMAT
    WIN  + J        = SAVE SCREENSHOT IN JPG FORMAT

    WIN  + LEFT     = VOLUME -
    WIN  + RIGHT    = VOLUME +
    WIN  + DOWN     = MUTE
    WIN  + UP       = VOLUME 50%
    WIN  + UP       = VOLUME 100% (if hold)
    CTRL + ALT + F4 = OPEN VOLUME MIXER

    WIN  + F3       = MOUSE POINTER ON / OFF

    ALT  + TAB      = TOGGLES BETWEEN WINDOWS
    ALT  + F4       = CLOSE WINDOWN
    ALT  + Q        = CLOSE SOME WINDOWS (pcmanfm, leafpad, firefox, etc...)
    ALT  + W        = CLOSE POP-UP WINDOW (FireFox)

    Batocera.PLUS [Press any key to exit...]
EOF
read -n 1 -s x

exit 0
