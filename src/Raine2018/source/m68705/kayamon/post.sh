
#ifdef __cplusplus
extern "C" {
#endif
#!/bin/sh

if [ "$1" == "" ]; then
  echo Usage: post filename.c
  exit
fi

echo Optimising file $1
mv -f $1 input.tmp
awk -f post1.awk input.tmp >mcu.tmp
awk -f post2.awk p=1 mcu.tmp p=2 input.tmp >$1
rm -f input.tmp
rm -f mcu.tmp


#ifdef __cplusplus
}
#endif
