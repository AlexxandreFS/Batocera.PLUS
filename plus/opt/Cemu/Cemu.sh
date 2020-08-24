#!/bin/sh

# Parametros externos
JOGO="$1"
CORE="$2"

# Variáveis da instalação do Cemu
CEMU_DIR='/opt/Cemu'

# Variáveis pra configuração do Cemu
CEMU="$HOME/configs/cemu"
SAVE="$HOME/../saves/wiiu"
OPT="$HOME/batocera.conf"
RUN="$HOME/configs/cemu/runcheck.ini"

# Instala o Cemu
if [ ! -d "$CEMU" ] || [ -z "$(ls -A "$CEMU")" ] || [ ! -d "$SAVE" ] || [ -z "$(ls -A "$SAVE")" ]; then
	# Montando o cemu em "system/configs/cemu"
	    mkdir -p "$(dirname "$RUN")" "$(dirname "$CEMU/log.txt")" "$(dirname "$HOME/logs/cemu.txt")"
		echo 'run=1' > "$RUN"
		ln -s "$CEMU/log.txt" "$HOME/logs/cemu.log"
	    cp -r "$CEMU_DIR/emulator/resources" "$CEMU" || exit $?
        cp -r "$CEMU_DIR/cemuextras/sharedFonts" "$CEMU" || exit $?	    
	    cp -r "$CEMU_DIR/cemuhook/keystone.dll" "$CEMU" || exit $?
	    cp -r "$CEMU_DIR/emulator/Cemu.exe" "$CEMU" || exit $?
		cp -r "$CEMU_DIR/cemuextras/cemuhook.ini" "$CEMU" || exit $?
		cp -r "$CEMU_DIR/cemuhook/dbghelp.dll" "$CEMU" || exit $?
        cp -r "$CEMU_DIR/cemuextras/keys.txt" "$CEMU" || exit $?
		cp -r "$CEMU_DIR/fakefiles/otp.bin" "$CEMU" || exit $?
		cp -r "$CEMU_DIR/fakefiles/seeprom.bin" "$CEMU" || exit $?
	    cp -r "$CEMU_DIR/cemuextras/settings.xml" "$CEMU" || exit $?
		
	# Montando o cemu em "share/save/wiiu"
	    mkdir -p "$SAVE/hfiomlc01"
	    cp -r "$CEMU_DIR/cemuextras/controllerProfiles" "$SAVE" || exit $?
	    cp -r "$CEMU_DIR/emulator/gameProfiles" "$SAVE" || exit $?
	    cp -r "$CEMU_DIR/emulator/graphicPacks" "$SAVE" || exit $?
		cp -r "$CEMU_DIR/cemuhook/graphicPacks" "$SAVE" || exit $?
		cp -r "$CEMU_DIR/cemuextras/graphicPacks" "$SAVE" || exit $?
	    cp -r "$CEMU_DIR/fakefiles/mlc01" "$SAVE" || exit $?
	    cp -r "$CEMU_DIR/emulator/shaderCache" "$SAVE"	|| exit $?
		
    # Criando links simbólicos para a pasta "system/configs/cemu"
	    ln -s "$SAVE/"* "$CEMU"
fi

# Checa se a interface foi executada de forma correta na ultima vez, 
# se o script for interrompido durante a sua execução o Cemu.exe não 
# inicia mais se o runcheck.ini possuir "run=1", descobri isso por 
# conta de uma queda de luz em minha residência
if ! [ "$(pidof wineserver)" ] && [ "$(grep '^run=1' "$RUN")" ]; then
    mkdir -p "$(dirname "$RUN")"
	echo 'run=0' > "$RUN"
	sed -i 's/<check_update>true<\/check_update>/<check_update>false<\/check_update>/' "$CEMU/settings.xml"
fi
	
# Habilita as dependências necessárias para a execução do Cemu no wine
export WINEDLLOVERRIDES="keystone.dll=n,b;dbghelp.dll=n,b"

# Checa se as otimizações foram ativadas no emulationstation ALTAMENTE EXPERIMENTAL!
if [ "${CORE}" == 'cemu-nvidia' ] ; then
	export mesa_glthread=true
    export vblank_mode=0
    export WINEESYNC=1
elif [ "${CORE}" == 'cemu-amd' ] ; then
    export R600_DEBUG=nohyperz
    export mesa_glthread=true
    export vblank_mode=0
    export WINEESYNC=1
fi

# Checa se tem uma rom válida na variável JOGO
# Este também é o gatilho pra decidir se o GUI será aberto ou se o jogo será executado em linha de comando
EXT='.wud .wux .iso .wad .rpx .elf .WUD .WUX .ISO .WAD .RPX .ELF'
for i in $EXT; do
	if [ "$(echo "$JOGO" | grep "${i}")" ]; then
        CMD=1
		JOGO="$(echo "Z:$JOGO" | sed -e 's#/#\\#g')"
		break
    else
	    CMD=0
	fi
done

# Ativa autoupdate do Cemu se ele for executado pelo menu F1
if [ "$(grep '<check_update>false<\/check_update>' "$CEMU/settings.xml" )" ] && [ "$CMD" == 0 ]; then
    sed -i 's/<check_update>false<\/check_update>/<check_update>true<\/check_update>/' "$CEMU/settings.xml"
fi

# É sempre bom avisar ao usuário porque o controle dele não funciona
if ! [ "$(ls -1 "$CEMU/controllerProfiles" | grep '.txt' | tail -n 1)" ]; then
    /bin/echo -e "\nAviso\nConfigure um controle\nPara o Cemu no menu F1" | LC_ALL=C HOME=/userdata/system DISPLAY=:0.0 osd_cat -f -*-*-bold-*-*-*-32-120-*-*-*-*-*-* -s 2 -l 100 -A center -ccyan
fi

RES_START="$(batocera-resolution currentMode)"

# Executa o Cemu.exe se ele não estiver sendo executado
if ! [ "$(pidof wineserver)" ] && [ "$(grep '^run=0' "$RUN")" ]; then  
    if [ "$CMD" == 0 ]; then
	    echo 'run=1' > "$RUN"
        wine "$CEMU/Cemu.exe"	    
		# Aguarda o Cemu encerrar a execução ###
		while [ "$(pidof wineserver)" ]; do
            sleep 1
        done
		echo 'run=0' > "$RUN"
		sed -i 's/<check_update>true<\/check_update>/<check_update>false<\/check_update>/' "$CEMU/settings.xml"
	elif [ "$CMD" == 1 ]; then
		echo 'run=1' > "$RUN"
        wine "$CEMU/Cemu.exe" -f -g "$JOGO"
	    # Aguarda o Cemu encerrar a execução ###
		while [ "$(pidof wineserver)" ]; do
            sleep 1
        done
		echo 'run=0' > "$RUN"
	fi
else
    exit 0
fi

# Restaura a resolução, caso o jogo tenha mudado ###	
RES_STOP="$(batocera-resolution currentResolution)"

if [ "${RES_START}" != "${RES_STOP}" ]; then
    batocera-resolution setMode "${RES_START}"
fi
