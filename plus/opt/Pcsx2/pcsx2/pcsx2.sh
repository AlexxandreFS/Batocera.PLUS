#!/bin/bash
###
### Batocera.PLUS
### Alexandre Freire dos Santos
###
################################################################################

PCSX2_SAVE_DIR="/userdata/saves/ps2"
PCSX2_CONFIG_DIR="${HOME}/../system/configs/PCSX2"


################################################################################

## DEFAULT CONFIG

function populate()
{
    if [ ! "$(ls -A "${PCSX2_CONFIG_DIR}/inis" 2> /dev/null)" ]
    then
        mkdir -p "${PCSX2_CONFIG_DIR}/inis"
    fi

    if ! [ -e "${PCSX2_CONFIG_DIR}/inis/PCSX2_vm.ini" ]
    then
        (echo '[EmuCore]'
         echo 'EnableWideScreenPatches=disabled'
         echo '[EmuCore/Speedhacks]'
         echo 'EECycleRate=0'
         echo 'EECycleSkip=0'
         echo 'fastCDVD=disabled'
         echo 'IntcStat=enabled'
         echo 'WaitLoop=enabled'
         echo 'vuFlagHack=enabled'
         echo 'vuThread=disabled'
         echo 'vu1Instant=enabled') > "${PCSX2_CONFIG_DIR}/inis/PCSX2_vm.ini"
    fi

    if ! [ -e "${PCSX2_CONFIG_DIR}/inis/PCSX2_ui.ini" ]
    then
        (echo 'PresetIndex=1'
         echo '[Filenames]'
         echo 'BIOS=scph39001.bin'
         echo '[ProgramLog]'
         echo 'Visible=disabled'
         echo '[GSWindow]'
         echo 'AspectRatio=4:3') > "${PCSX2_CONFIG_DIR}/inis/PCSX2_ui.ini"
    fi

    if ! [ -e "${PCSX2_CONFIG_DIR}/inis/GSdx.ini" ]
    then
        (echo 'vsync = 0'
         echo 'upscale_multiplier = 1'
         echo 'MaxAnisotropy = 0'
         echo 'UserHacks = 0') > "${PCSX2_CONFIG_DIR}/inis/GSdx.ini"
    fi

    if ! [ -e "${PCSX2_CONFIG_DIR}/PCSX2/PCSX2-reg.ini" ]
    then
        (echo 'DocumentsFolderMode=User'
         echo 'CustomDocumentsFolder=/usr/PCSX/bin'
         echo 'UseDefaultSettingsFolder=enabled'
         echo 'SettingsFolder=/userdata/system/configs/PCSX2/inis'
         echo 'Install_Dir=/usr/PCSX/bin'
         echo 'RunWizard=0') > "${PCSX2_CONFIG_DIR}/PCSX2-reg.ini"
    fi

    DIRS='sstates cheats cheats_ws memcards'

    for i in ${DIRS}; do
        if ! [ -e "${PCSX2_CONFIG_DIR}/$i" ]
        then
            ln -s "${PCSX2_SAVE_DIR}/$i" "${PCSX2_CONFIG_DIR}/$i"
        fi
    done
}

populate

exit 0
