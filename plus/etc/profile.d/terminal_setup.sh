###
### Profile for Batocera.PLUS
###

# Set vt100 as terminal enviroment
TERM=vt100

# ---- ALIAS VALUES ----
alias mc='mc -x'
alias batocera-check-updates='batocera-es-swissknife --update'

if [ "$PS1" ]; then
	if [ "`id -u`" -eq 0 ]; then
                export PS1="[\[\e[1;32m\]Batocera\[\e[0;38m\].\[\e[1;33m\]PLUS\[\e[1;36m\]:\[\e[0;37m\]\w]# \[\e[m\]"
	else
                export PS1="[\[\e[1;32m\]Batocera\[\e[0;38m\].\[\e[1;33m\]PLUS\[\e[1;36m\]:\[\e[0;37m\]\w]$ \[\e[m\]"
	fi
fi

JAVA_HOME='/opt/Java'
PATH="${PATH}:${JAVA_HOME}/bin"
CLASSPATH="${JAVA_HOME}/lib/tools.jar"
CLASSPATH=".:${CLASSPATH}"
export JAVA_HOME PATH CLASSPATH

BATOCERA_VERSION='/usr/share/batocera/batocera.version'
RECALBOX_VERSION='/usr/share/batocera/recalbox.version'
RECALBOX_ARCH='/usr/share/batocera/batocera.arch'

clear
echo '  ___.             __                                               
  \_ |__  _____  _/  |_  ____    ____   ____ _______ _____
   | __ \ \__  \ \   __\/  _ \ _/ ___\_/ __ \\_  __ \\__  \
   | \_\ \ / __ \_|  | (  <_> )\  \___\  ___/ |  | \/ / __ \
   |___  /(____  /|__|  \____/  \___  >\___  >|__|   (____  /
       \/      \/                   \/     \/             \/.__
                                                          __|  |___
   BY ALEXANDRE FREIRE DOS SANTOS                        /__    __/
   AND SERGIO DE CARVALHO JUNIOR                            |__|'
echo -n "   Version: $(cat $BATOCERA_VERSION | cut -d' ' -f 1)"
echo -n "   Release: $(cat $BATOCERA_VERSION | cut -d' ' -f 2)"
echo -n "   Arch: $(cat $RECALBOX_ARCH)"
echo ' '
echo -n "   Based on version $(cat $RECALBOX_VERSION | cut -d' ' -f 1) of the batocera.linux"
echo

BATOCERA_INFO="$(env DISPLAY= batocera-info 2>/dev/null)"

echo    "   $(echo "${BATOCERA_INFO}" | grep '^Cpu model:')"
echo -n "   $(echo "${BATOCERA_INFO}" | grep '^Cpu number:')"
echo    "   $(echo "${BATOCERA_INFO}" | grep '^Cpu max frequency:')"
#echo -n "   $(echo "${BATOCERA_INFO}" | grep '^OpenGL:')"
#echo    "   $(echo "${BATOCERA_INFO}" | grep '^Vulkan:')"
echo    "   $(echo "${BATOCERA_INFO}" | grep '^Available memory:')"
echo

unset BATOCERA_VERSION
unset RECALBOX_VERSION
unset RECALBOX_ARCH
