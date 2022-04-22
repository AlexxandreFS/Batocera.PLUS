#!/bin/bash
##
## Batocera.PLUS
## Alexxandre Freire dos Santos
##
## Encerra a execução do pcsx2.
## 

if pidof -s PCSX2 > /dev/null
then
    killall -15 PCSX2
fi 

if pidof -s PCSX2 > /dev/null
then
    killall -15 PCSX2
fi 

exit 0

