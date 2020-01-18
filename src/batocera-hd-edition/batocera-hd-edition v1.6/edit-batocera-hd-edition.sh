#!/bin/sh
mkdir boot
cp batocera-hd-edition.gz boot
cd boot
gunzip batocera-hd-edition.gz
cpio -id < batocera-hd-edition
rm batocera-hd-edition
nano init
find . | cpio --create --format='newc' > ../batocera-hd-edition.cpio
mv ../batocera-hd-edition.cpio batocera-hd-edition
gzip batocera-hd-edition
mv -f batocera-hd-edition.gz ..
cd ..
rm -r boot
