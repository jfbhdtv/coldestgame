#!/bin/bash

if [ $# != 2 ]
then
   echo "Usage: package.sh [linux|windows] [kit path]"
   exit 0
fi

if [ $1 == "linux" ]
then
   tar cjvf $2-`uname -m`.tar.bz2 $2
   cd $2
   tar cjvf ../$2-bin-`uname -m`.tar.bz2 coldest coldest.bin lib
   cd ..
else
   rm $2/coldest*
   rm $2/server*
   rm -rf $2/lib
   cp Coldest.exe $2
   cp windlls.zip $2
   cp vcredist_x86.exe $2
   cp doupdate.bat $2
   cd $2
   unzip windlls.zip
   rm windlls.zip
   cd ..
   zip -r $2.zip $2
   cd $2
   zip ../$2-bin.zip Coldest.exe *.dll vcredist_x86.exe
   cd ..
fi
