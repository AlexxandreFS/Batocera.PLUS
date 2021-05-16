#!/bin/bash
#
# Isto NÃO é um script, estes são os comando que eu rodei no
# terminal em uma distribuição debian para criar as imagens do
# BatoceraZero
#

exit 0

su # Minha senha de root
#PATH=$PATH:/sbin:/usr/sbin

BATOCERA_IMG=batocera-5.27-x86_64-20210515.img
LOOP=$(losetup -f)

gunzip -k ${BATOCERA_IMG}.gz
mv ${BATOCERA_IMG} BatoceraZero.img

losetup -o $((2048 * 512)) ${LOOP} BatoceraZero.img

fsck.vfat ${LOOP} # pressione 1 e depois y

mkdir -p x
mount ${LOOP} x

rm -r 'x/EFI' 'x/tools' \
      'x/batocera-boot.conf' \
      'x/boot/batocera' \
      'x/boot/initrd.gz' \
      'x/boot/linux' \
      'x/boot/syslinux/ldlinux.c32' \
      'x/boot/syslinux/libutil.c32' \
      'x/boot/syslinux/menu.c32' \
      'x/boot/syslinux/syslinux.cfg'

dd if=/dev/zero of=x/Batocera.PLUS.1  bs=512 status=progress
dd if=/dev/zero of=x/Batocera.PLUS.2  bs=512 status=progress
dd if=/dev/zero of=x/Batocera.PLUS.3  bs=512 status=progress
sync

rm x/Batocera.PLUS.1
rm x/Batocera.PLUS.2
rm x/Batocera.PLUS.3
sync

umount ${LOOP}
losetup -d ${LOOP}
rmdir x

7zr a -mmt=4 -mx=9 ${BATOCERA_IMG}.7z BatoceraZero.img

rm BatoceraZero.img
chown alexandre:alexandre ${BATOCERA_IMG}.7z

exit

