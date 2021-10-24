#!/bin/sh

##
## Batocera.PLUS
##
## Cria a esturura de pastas padrão para todas as versões do wine.
## Esta estrutura é necessária para savar o jogo.
## Este script é parte integrante do script de execução do wine.
##

FOLDERS=(
    'ProgramData/Microsoft/Windows/Templates'
    'ProgramData/Microsoft/Windows/Start Menu/Programs/Administrative Tools'
    'ProgramData/Microsoft/Windows/Start Menu/Programs/StartUp'
    'users/wine/Templates'
    'users/wine/Music'
    'users/wine/Application Data/Microsoft/Windows'
    'users/wine/Application Data/Microsoft/Windows/Themes'
    'users/wine/Favorites'
    'users/wine/Pictures'
    'users/wine/My Music'
    'users/wine/Downloads'
    'users/wine/Links'
    'users/wine/Searches'
    'users/wine/My Documents'
    'users/wine/AppData/LocalLow'
    'users/wine/AppData/Local/Microsoft/Windows/History'
    'users/wine/AppData/Local/Microsoft/Windows/INetCookies'
    'users/wine/AppData/Local/Microsoft/Windows/INetCache'
    'users/wine/AppData/Roaming/Microsoft/Windows/Templates'
    'users/wine/AppData/Roaming/Microsoft/Windows/Themes'
    'users/wine/AppData/Roaming/Microsoft/Windows/Printer Shortcuts'
    'users/wine/AppData/Roaming/Microsoft/Windows/Start Menu/Programs/Administrative Tools'
    'users/wine/AppData/Roaming/Microsoft/Windows/Start Menu/Programs/StartUp'
    'users/wine/AppData/Roaming/Microsoft/Windows/Recent'
    'users/wine/AppData/Roaming/Microsoft/Windows/SendTo'
    'users/wine/AppData/Roaming/Microsoft/Windows/Network Shortcuts'
    'users/wine/Contacts'
    'users/wine/Temp'
    'users/wine/Saved Games'
    'users/wine/Documents'
    'users/wine/My Videos'
    'users/wine/Desktop'
    'users/wine/Videos'
    'users/wine/My Pictures'
    'users/steamuser/Music'
    'users/steamuser/Favorites'
    'users/steamuser/Pictures'
    'users/steamuser/Downloads'
    'users/steamuser/Links'
    'users/steamuser/Searches'
    'users/steamuser/AppData/LocalLow'
    'users/steamuser/AppData/Local/Microsoft/Windows/History'
    'users/steamuser/AppData/Local/Microsoft/Windows/INetCookies'
    'users/steamuser/AppData/Local/Microsoft/Windows/INetCache'
    'users/steamuser/AppData/Roaming/Microsoft/Windows/Templates'
    'users/steamuser/AppData/Roaming/Microsoft/Windows/Themes'
    'users/steamuser/AppData/Roaming/Microsoft/Windows/Printer Shortcuts'
    'users/steamuser/AppData/Roaming/Microsoft/Windows/Start Menu/Programs/Administrative Tools'
    'users/steamuser/AppData/Roaming/Microsoft/Windows/Start Menu/Programs/StartUp'
    'users/steamuser/AppData/Roaming/Microsoft/Windows/Recent'
    'users/steamuser/AppData/Roaming/Microsoft/Windows/SendTo'
    'users/steamuser/AppData/Roaming/Microsoft/Windows/Network Shortcuts'
    'users/steamuser/Contacts'
    'users/steamuser/Temp'
    'users/steamuser/Saved Games'
    'users/steamuser/Documents/Templates'
    'users/steamuser/Documents/Music'
    'users/steamuser/Documents/Pictures'
    'users/steamuser/Documents/Downloads'
    'users/steamuser/Documents/Videos'
    'users/steamuser/Desktop'
    'users/steamuser/Videos'
    'users/Public/Music'
    'users/Public/Pictures'
    'users/Public/Documents'
    'users/Public/Desktop'
    'users/Public/Videos'
    'users/0/Templates'
    'users/0/Application Data/Microsoft/Windows/Themes'
    'users/0/My Music'
    'users/0/Downloads'
    'users/0/My Documents'
    'users/0/AppData/Local/Microsoft/Windows/History'
    'users/0/AppData/Local/Microsoft/Windows/INetCookies'
    'users/0/AppData/Local/Microsoft/Windows/INetCache'
    'users/0/Temp'
    'users/0/My Videos'
    'users/0/Desktop'
    'users/0/My Pictures'
    'users/root/Templates'
    'users/root/Music'
    'users/root/Application Data/Microsoft/Windows/Themes'
    'users/root/Favorites'
    'users/root/Pictures'
    'users/root/My Music'
    'users/root/Downloads'
    'users/root/Links'
    'users/root/Searches'
    'users/root/My Documents'
    'users/root/AppData/LocalLow'
    'users/root/AppData/Local/Microsoft/Windows/History'
    'users/root/AppData/Local/Microsoft/Windows/INetCookies'
    'users/root/AppData/Local/Microsoft/Windows/INetCache'
    'users/root/AppData/Roaming/Microsoft/Windows/Templates'
    'users/root/AppData/Roaming/Microsoft/Windows/Themes'
    'users/root/AppData/Roaming/Microsoft/Windows/Printer Shortcuts'
    'users/root/AppData/Roaming/Microsoft/Windows/Start Menu/Programs/Administrative Tools'
    'users/root/AppData/Roaming/Microsoft/Windows/Start Menu/Programs/StartUp'
    'users/root/AppData/Roaming/Microsoft/Windows/Recent'
    'users/root/AppData/Roaming/Microsoft/Windows/SendTo'
    'users/root/AppData/Roaming/Microsoft/Windows/Network Shortcuts'
    'users/root/Contacts'
    'users/root/Temp'
    'users/root/Saved Games'
    'users/root/Documents'
    'users/root/My Videos'
    'users/root/Desktop'
    'users/root/Videos'
    'users/root/My Pictures'

    # Importante, não remova.
    # Estas pastas não são criadas pelo wineboot mas são usadas no script do wine
    'users/0/Personal'
    'users/root/Personal'
)

################################################################################

##
## Cria a extrutuda de pastas para o save.
##

PROFILE_DIR="${1}"

if ! [ "${PROFILE_DIR}" ]
then
    PROFILE_DIR=/userdata/saves/windows/wine-profiles
fi

mkdir -p "${PROFILE_DIR}"

if ! [ -e "${PROFILE_DIR}" ]
then
    exit 1
fi

for FOLDER in "${FOLDERS[@]}"
do
    # A Pasta pode existir, talvez um link criado pelo usuário ou
    # por um outro script neste caso a pasta não será criada.
    if ! [ -e "${PROFILE_DIR}/${FOLDER}" ]
    then
        mkdir -p "${PROFILE_DIR}/${FOLDER}"
    fi
done

exit 0
