#!/bin/sh
# BATOCERA.PLUS
# Este script aplica o patch do wine staging.
# Copie este script para a pasta do Wine Staging e execute.

WINE_DIR='../wine-5.0'

./patches/patchinstall.sh DESTDIR="$WINE_DIR" --all -W \
    ntdll-MemoryWorkingSetExInformation \
    ntdll-NtContinue \
    ntdll-RtlCreateUserThread \
    ntdll-SystemExtendedProcessInformation \
    ntdll-SystemModuleInformation \
    ntdll-User_Shared_Data \
    ntdll-Threading \
    ntdll-ThreadTime \
    winex11-ime-check-thread-data \
    wow64cpu-Wow64Transition

exit 0

