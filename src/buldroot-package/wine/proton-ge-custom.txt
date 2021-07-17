#!/bin/bash

################################################################################

# Baixar e aplicar patch

git clone --recursive https://github.com/GloriousEggroll/wine-ge-custom.git

cd proton-ge-custom
./patches/protonprep.sh &> patchlog.txt

cd wine
./dlls/winevulkan/make_vulkan
./tools/make_requests
autoreconf -f

grep -i fail  ../patchlog.txt
grep -i error ../patchlog.txt

################################################################################

# Atualizar código anteriormente baixado

git pull
git reset --hard
git submodule sync
git submodule foreach git reset --hard HEAD
git submodule update
git submodule foreach "git checkout master; git pull"
git submodule foreach git clean -f
git submodule update
git pull
git status

################################################################################

# Pacotes para compilar o dxvk, dxvk-nvidia, vkd3d

apt-get install meson glslang-tools zstd
apt-get install gcc-mingw-w64-x86-64-posix gcc-mingw-w64-i686-posix g++-mingw-w64-x86-64-posix g++-mingw-w64-i686-posix mingw-w64-tools

# Escolha a opção posix se aparecer

update-alternatives --config x86_64-w64-mingw32-gcc
update-alternatives --config x86_64-w64-mingw32-g++
update-alternatives --config i686-w64-mingw32-gcc
update-alternatives --config i686-w64-mingw32-g++

# Comando para compilar

./package-release.sh master build


