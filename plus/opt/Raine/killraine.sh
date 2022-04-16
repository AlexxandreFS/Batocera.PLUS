#!/bin/bash
###
### Batocera.PLUS
###

if pidof -s raine2020 > /dev/null
then
    killall -15 raine2020
fi 

if pidof -s raine2015 > /dev/null
then
    killall -15 raine2015
fi 

exit 0
