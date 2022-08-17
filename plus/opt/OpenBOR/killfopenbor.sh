#!/bin/bash
##
## Batocera.PLUS
## Alexxandre Freire dos Santos
##
## Encerra a execução do OpenBOR
## 

OPENBOR_PID=''

for OPENBOR in 7142 6330 4432
do
    OPENBOR_PID=$(pidof -s "OpenBOR_v${OPENBOR}")

    if [ "${OPENBOR_PID}" ]
    then
        break
    fi
done

if [ -z "${OPENBOR_PID}" ]
then
    exit 0
fi

kill -15 ${OPENBOR_PID}

exit 0
