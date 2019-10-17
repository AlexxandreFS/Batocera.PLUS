#!/bin/bash
set -e

OUTPUT='/home/batocera/batocera-5.21-src/output'


if [ -d "${OUTPUT}/target/opt/Wine/wine32" ]; then
    ARCH='32'
elif [ -d "${OUTPUT}/target/opt/Wine/wine64" ]; then
    ARCH='64'
else
    exit 1
fi


mkdir -p "${OUTPUT}/build/wine-pkg/opt/Wine/wine${ARCH}"
cd "${OUTPUT}/build/wine-pkg"

cp -r "${OUTPUT}/target/opt/Wine/wine${ARCH}/bin" \
      "opt/Wine/wine${ARCH}"

cp -r "${OUTPUT}/target/opt/Wine/wine${ARCH}/lib" \
      "opt/Wine/wine${ARCH}"


if [ "$ARCH" -eq "32" ]; then
    mkdir -p opt/Wine/share
    cp -r "${OUTPUT}/target/opt/Wine/share/wine" \
          "opt/Wine/share"

    for FILE in libncurses.so libnl-3.so libnl-genl-3.so libpcap.so libxml2.so; do
        cp    "${OUTPUT}/target/usr/lib/$(readlink ${OUTPUT}/target/usr/lib/${FILE})" \
              "opt/Wine/wine${ARCH}/lib"

        cp -P "${OUTPUT}/target/usr/lib/${FILE}" \
              "opt/Wine/wine${ARCH}/lib"
    done
fi


7zr a "Wine${ARCH}.7z" 'opt'

mv "Wine${ARCH}.7z" "${OUTPUT}/images"

cd ..
rm -r wine-pkg

exit 0
