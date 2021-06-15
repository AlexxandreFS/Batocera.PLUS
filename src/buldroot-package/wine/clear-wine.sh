#!/bin/bash

# Este script limpa a compilação do wine removendo coisas que não servem para nada.

rm -r include
rm -r share/applications
rm -r share/man

rm -f lib32/wine/*.def
rm -f lib32/wine/i386-unix/*.def
rm -f lib32/wine/*.a
rm -f lib32/wine/i386-unix/*.a

rm -f lib64/wine/*.def
rm -f lib64/wine/x86_64-unix/*.def
rm -f lib64/wine/*.a
rm -f lib64/wine/x86_64-unix/*.a

if [ -e 'lib32/libwine.so.1.0' ] && [ -e 'lib64/libwine.so.1.0' ]
then
    strip lib32/libwine.so.1.0
    strip lib32/wine/*.so

    strip lib64/libwine.so.1.0
    strip lib64/wine/*.so
else
    strip lib32/wine/i386-unix/*
    strip lib64/wine/x86_64-unix/*
fi

strip bin/wine
strip bin/wineserver
strip bin/wine-preloader

strip bin/wine64
strip bin/wine64-preloader

exit 0
