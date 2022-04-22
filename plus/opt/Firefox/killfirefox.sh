#!/bin/bash
##
## Batocera.PLUS
## Alexxandre Freire dos Santos
##
## Encerra a execução do firefox.
## 

if pidof -s firefox > /dev/null
then
    killall -15 firefox
fi 

if pidof -s firefox > /dev/null
then
    killall -15 firefox
fi 

exit 0

