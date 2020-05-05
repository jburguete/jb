#!/bin/bash
gsed -i "s/"$1"\."$2"\."$3"/"$4"\."$5"\."$6"/g" $1.$2.$3/configure.ac $1.$2.$3/Doxyfile $1.$2.$3/locales/*/*/*.po README.*
git mv $1.$2.$3 $4.$5.$6
ln -sf $4.$5.$6 jb
