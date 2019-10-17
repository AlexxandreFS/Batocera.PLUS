@echo off
if "%1"=="" goto usage
echo Optimising file %1
ren %1 input.tmp
awk -f post1.awk input.tmp >mcu.tmp
awk -f post2.awk p=1 mcu.tmp p=2 input.tmp >%1
del input.tmp
del mcu.tmp
goto end

:usage
echo Usage: POST filename.c
:end
