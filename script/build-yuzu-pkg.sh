#/bin/bash
###
### Batocera.PLUS
### Alexandre Freire dos Santos
###
### Compila o yuzu mainline e Early Acess usando o docker
###
set -e

################################################################################

### MAINLINE

# Download

git clone --recursive https://github.com/yuzu-emu/yuzu-mainline.git

# Fix

cd yuzu-mainline

sed -i 's/YUZU_USE_EXTERNAL_SDL2/TRUE/'         externals/CMakeLists.txt
sed -i '/add_library(SDL2 ALIAS SDL2-static)/d' externals/CMakeLists.txt

echo 'cp -r /usr/local/lib/libboost_context.so.?.* AppDir/usr/lib' >> .ci/scripts/linux/docker.sh

chmod +x .ci/scripts/linux/exec.sh

# Build

.ci/scripts/linux/exec.sh

cd ..

################################################################################

### EA

# Download

git clone --recursive https://github.com/pineappleEA/pineapple-src.git

MODULES=$(cat yuzu-mainline/.gitmodules | grep -E '^*path[ ]*=[ ]*' | cut -d '/' -f 2-)

for MODULE in ${MODULES}
do
    cp -af yuzu-mainline/externals/${MODULE} pineapple-src/externals/$(dirname ${MODULE})
done

# Fix

cd pineapple-src

sed -i 's/YUZU_USE_EXTERNAL_SDL2/TRUE/'         externals/CMakeLists.txt
sed -i '/add_library(SDL2 ALIAS SDL2-static)/d' externals/CMakeLists.txt
sed -i '/-DYUZU_USE_EXTERNAL_SDL2=/d'           .github/workflows/docker.sh

chmod +x .github/workflows/docker.sh
chmod +x .github/workflows/appimage.sh

# Build

sudo chown -R 1027 ./

docker run -e AZURECIREPO \
           -e TITLEBARFORMATIDLE \
           -e TITLEBARFORMATRUNNING \
           -e DISPLAYVERSION \
           -e ENABLE_COMPATIBILITY_REPORTING \
           -e CCACHE_DIR=/yuzu/ccache \
           -v "$(pwd):/yuzu" \
           -w /yuzu yuzuemu/build-environments:linux-fresh /bin/bash .github/workflows/docker.sh "$1" || true

sudo chown -R $UID ./

cd ..

################################################################################

### BATOCERA.PLUS PKG

YUZU_PKG="yuzu-$(date +%F)"

mkdir -p "${YUZU_PKG}/opt/Yuzu/yuzu-mainline/bin" \
         "${YUZU_PKG}/opt/Yuzu/yuzu-early-access/bin" \
         "${YUZU_PKG}/opt/Yuzu/lib" \
         "${YUZU_PKG}/opt/Yuzu/plugins"

cp  -f yuzu-mainline/build/bin/yuzu "${YUZU_PKG}/opt/Yuzu/yuzu-mainline/bin"
strip "${YUZU_PKG}/opt/Yuzu/yuzu-mainline/bin/yuzu"
chmod +x "${YUZU_PKG}/opt/Yuzu/yuzu-mainline/bin/yuzu"

cp  -f pineapple-src/build/bin/yuzu "${YUZU_PKG}/opt/Yuzu/yuzu-early-access/bin"
strip "${YUZU_PKG}/opt/Yuzu/yuzu-early-access/bin/yuzu"
chmod +x "${YUZU_PKG}/opt/Yuzu/yuzu-early-access/bin/yuzu"

for i in libQt5DBus.so.5 \
         libQt5Core.so.5 \
         libicui18n.so.60 \
         libicuuc.so.60 \
         libicudata.so.60 \
         libQt5Gui.so.5 \
         libQt5XcbQpa.so.5 \
         libxcb-render-util.so.0 \
         libQt5Widgets.so.5 \
         libboost_context.so.?.*
do
    cp  -f yuzu-mainline/build/AppDir/usr/lib/${i} "${YUZU_PKG}/opt/Yuzu/lib"
done

cp  -f yuzu-mainline/build/AppDir/usr/optional/libstdc++/* "${YUZU_PKG}/opt/Yuzu/lib"

cp -rf yuzu-mainline/build/AppDir/usr/plugins/*            "${YUZU_PKG}/opt/Yuzu/plugins"

7zr a "${YUZU_PKG}.7z" "${YUZU_PKG}"

exit 0

