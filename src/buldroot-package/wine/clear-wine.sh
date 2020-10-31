#!/bin/bash

# Este script limpa a compilação do wine removendo coisas que não servem para nada.

rm -r include
rm    lib32/wine/*.def
rm    lib64/wine/*.def
rm -r share/applications
rm -r share/man

strip bin/wine bin/wine64 bin/wine64-preloader bin/wineserver
strip lib32/libwine.so.1.0 lib64/libwine.so.1.0
strip lib32/wine/*.so lib64/wine/*.so

stat -t  share/wine/wine.inf | awk '{print $13}' > .update-timestamp
unix2dos .update-timestamp

exit 0
