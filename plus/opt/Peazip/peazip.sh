#!/bin/bash

export LD_LIBRARY_PATH="/lib32:${LD_LIBRARY_PATH}"

if [ -z "$@" ]
then 
    exec /opt/Peazip/peazip /userdata
else
    exec /opt/Peazip/peazip "$@"
fi
