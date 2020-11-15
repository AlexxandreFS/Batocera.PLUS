#!/bin/sh
###
### Batocera.PLUS
###

################################################################################

# EXPORTADOS PELO SCRIPT /usr/lib/python2.7/site-packages/configgen/emulatorlauncher.sh
# SYSTEM
# ROM
# BATOCERA_CONF
# DOLPHIN_CFG
# DOLPHIN_CFG_DIR

################################################################################

### GAMECUBE - FULLBOOT E FASTBOOT

if [ "${SYSTEM}" == 'gamecube' ]; then
    if grep -q 'SkipIPL' "${DOLPHIN_CFG}"; then
        if [ "$(grep '^gamecube.fullboot=0' "${BATOCERA_CONF}")" ]; then
            sed -i 's/^SkipIPL.*/SkipIPL = True/'  "${DOLPHIN_CFG}"
        else
            sed -i 's/^SkipIPL.*/SkipIPL = False/' "${DOLPHIN_CFG}"
        fi
    else
        sed -i 's#^\[Core\]#[Core]\nSkipIPL = False#' "${DOLPHIN_CFG}"
    fi
else
    # WII - FIX ASSINATURA DIGITAL (Sempre desativado)
    if grep -q 'EnableSignatureChecks' "${DOLPHIN_CFG}"; then
        sed -i 's/^EnableSignatureChecks.*/EnableSignatureChecks = False/' "${DOLPHIN_CFG}"
    else
        sed -i 's#^\[Core\]#[Core]\nEnableSignatureChecks = False#' "${DOLPHIN_CFG}"
    fi
fi

################################################################################

### CRIA UMA CONFIGURAÇÃO INICIAL PARA O DOLPHIN-USER-CONFIG

if ! [ -f "${DOLPHIN_CFG_DIR}/batocera.plus" ]; then
    mkdir -p "${DOLPHIN_CFG_DIR}/dolphin-emu"

    cp -f  "${DOLPHIN_CFG_DIR}/"*.ini "${DOLPHIN_CFG_DIR}/dolphin-emu"
    ln -sf "${DOLPHIN_CFG_DIR}/Hotkeys.ini" "${DOLPHIN_CFG_DIR}/dolphin-emu/Hotkeys.ini"
    sed -i 's#^\[Interface\]#\[Interface\]\nThemeName = Clean Emerald#' "${DOLPHIN_CFG_DIR}/dolphin-emu/Dolphin.ini"
    
    echo 'NOT ERASE' > "${DOLPHIN_CFG_DIR}/batocera.plus"

    rm -r "${DOLPHIN_CFG_DIR}/retroarch" 2> /dev/null
fi

################################################################################

### NÃO EXECUTA O DOLPHIN SE FOR EXECUTADO PELO GERENCIADOR DE ARQUIVOS (F1)

if [ "${ROM}" == '/userdata/roms/gamecube/batocera.plus' ]; then
    exit 0
else
    unset BATOCERA_CONF
    unset DOLPHIN_CFG
    unset DOLPHIN_CFG_DIR

    unset SYSTEM
    unset ROM

    exec /usr/bin/dolphin-emu "$@"   
fi
