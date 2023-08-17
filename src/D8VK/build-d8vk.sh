#!/bin/bash
# set -e
# Script de compilação para o D8V 

# Batocera.PLUS PKG Version
PKG_VERSION=$(date +'%F')-1

# branch master - Jul 15, 2023
D8VK_VERSION=1a039a4729b9a8f0440739eec4cedf59e79a3aa0

# branch d3v7 - May 10, 2023
D3V7_VERSION=ba50c209de70b590286706927c662e1bf58bacfa

################################################################################

git clone --recursive https://github.com/AlpyneDreams/d8vk.git
cd d8vk

################################################################################

# BUILD D8VK

git checkout ${D8VK_VERSION}
mkdir -p build

./package-release.sh master build --no-package

mkdir -p ../d8vk-${PKG_VERSION}/opt/Wine/apps/d8vk/x32
mkdir -p ../d8vk-${PKG_VERSION}/opt/Wine/apps/d8vk/x64

mv -f build/dxvk-master/x32/d3d8.dll ../d8vk-${PKG_VERSION}/opt/Wine/apps/d8vk/x32
mv -f build/dxvk-master/x64/d3d8.dll ../d8vk-${PKG_VERSION}/opt/Wine/apps/d8vk/x64

rm -rf build

################################################################################

# BUILD D3V7

git checkout ${D3V7_VERSION}
mkdir build

./package-release.sh master build --no-package

mv -f build/dxvk-master/x32/ddraw.dll ../d8vk-${PKG_VERSION}/opt/Wine/apps/d8vk/x32
mv -f build/dxvk-master/x64/ddraw.dll ../d8vk-${PKG_VERSION}/opt/Wine/apps/d8vk/x64

rm -r build

################################################################################

cd ..

7zr a d8vk-${PKG_VERSION}.7z d8vk-${PKG_VERSION}

rm-r d8vk-${PKG_VERSION}

exit 0

