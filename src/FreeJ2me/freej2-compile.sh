#!/bin/bash

cd "$(dirname ${0})"

if ! [ -e apache-ant.tar.gz ]
then
    curl -L -C - https://mirror.nbtelecom.com.br/apache/ant/binaries/apache-ant-1.9.15-bin.tar.gz -o apache-ant.tar.gz
fi

if ! [ -e java.tar.gz ]
then
    curl -L -C - https://javadl.oracle.com/webapps/download/AutoDL?BundleId=244575_d7fc238d0cbf4b0dac67be84580cfb4b -o java.tar.gz
fi

gunzip -k java.tar.gz -c | tar -xvC .
gunzip -k apache-ant.tar.gz  -c | tar -xvC .

cp -rf apache-ant-1.9.15/* jdk1.8.0_291
rm -r  apache-ant-1.9.15

JAVA_HOME="$(pwd)/jdk1.8.0_291"
PATH="${PATH}:${JAVA_HOME}/bin"
CLASSPATH="${JAVA_HOME}/lib/tools.jar"
CLASSPATH=".:${CLASSPATH}"
export JAVA_HOME PATH CLASSPATH

git clone https://github.com/hex007/freej2me.git
cd freej2me
git checkout 518cca4ae11260b7aeb4aafc128e560ac7f3e5b3

ant

mv -f build/freej2me.jar     ..

cd ..

rm -r jdk1.8.0_291
rm -r freej2me

exit 0
