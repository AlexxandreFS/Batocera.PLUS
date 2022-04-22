#!/bin/bash
##
## Batocera.PLUS
## Alexxandre Freire dos Santos
##
## Encerra a execução do pcsx2.
## 

PCSX2_PID="$(pidof -s PCSX2)"

if [ -z "${PCSX2_PID}" ]
then
    exit 0
fi

kill -15 ${PCSX2_PID}
sleep 0.2

PCSX2_PID="$(pidof -s PCSX2)"

if [ -z "${PCSX2_PID}" ]
then
    echo 'PCSX2 closed!'
else
    sleep 0.5
    kill -9 ${PCSX2_PID}
    echo 'PCSX2 is dead!'
fi

exit 0