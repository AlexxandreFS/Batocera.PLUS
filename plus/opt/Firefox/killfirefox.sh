#!/bin/bash
##
## Batocera.PLUS
## Alexxandre Freire dos Santos
##
## Encerra a execução do firefox.
## 

FIREFOX_PID="$(pidof -s firefox)"

if [ -z "${FIREFOX_PID}" ]
then
    exit 0
fi

kill -15 ${FIREFOX_PID}
sleep 0.2

FIREFOX_PID="$(pidof -s firefox)"

if [ -z "${FIREFOX_PID}" ]
then
    echo 'Firefox closed!'
else
    sleep 0.5
    kill -9 ${FIREFOX_PID}
    echo 'Firefox is dead!'
fi

exit 0