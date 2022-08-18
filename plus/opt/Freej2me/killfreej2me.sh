#!/bin/bash
##
## Batocera.PLUS
## Alexandre Freire dos Santos
##
## Encerra a execução do freej2me
## 

FREEJ2ME_PID=$(/opt/Java/bin/jps -l | grep freej2me.jar | tail -n 1 | cut -d ' ' -f 1)


if [ -z "${FREEJ2ME_PID}" ]
then
    exit 0
fi

kill -15 ${FREEJ2ME_PID}
sleep 0.3

FREEJ2ME_PID=$(/opt/Java/bin/jps -l | grep freej2me.jar | tail -n 1 | cut -d ' ' -f 1)

if [ -z "${FREEJ2ME_PID}" ]
then
    echo 'Freej2me closed!'
else
    kill -9 ${FREEJ2ME_PID}
    echo 'Freej2me is dead!'
fi

exit 0
