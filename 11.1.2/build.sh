#!/usr/bin/env bash
if [[ `uname -s` = "OpenBSD" ]]; then
	export AUTOCONF_VERSION=2.71
	export AUTOMAKE_VERSION=1.16
fi
if [[ $# != 7 ]]; then
	echo "The syntax is: ./build.sh A B C D E F G"
	echo "A: 1 on native"
	echo "B: 1 on PGO"
	echo "C: JB precision (1-7)"
	echo "D: 3 on GTK3, 4 on GTK4, 0 without GUI"
	echo "E: 1 on FreeGLUT, 2 on GLFW, 3 on SDL, 4 on GtkGLArea"
	echo "G: 1 on Vulkan, 0 on OpenGL"
	echo "F: 1 on strip"
	exit 1
fi
if [[ $1 = 1 ]]; then
	a1="--with-native"
fi
if [[ $2 = 1 ]]; then
	a2="--with-pgo"
fi
if [[ $3 = 1 || $3 = 2 || $3 = 3 || $3 = 4 || $3 = 5 || $3 = 6 || $3 = 7 ]];
then
	a3="--with-precision=$3"
else
	echo "Unknown option"
	exit 2
fi
if [[ $4 = 3 || $4 = 4 ]]; then
	a4="--with-gtk=$4"
	if [[ $5 = 1 ]]; then
		a5="--with-freeglut"
	elif [[ $5 = 2 ]]; then
		a5="--with-glfw"
	elif [[ $5 = 3 ]]; then
		a5="--with-sdl"
	elif [[ $5 = 4 ]]; then
		a5="--with-gtkglarea"
	else
		echo "Unknown option"
		exit 2
	fi
elif [[ $4 != 0 ]]; then
	echo "Unknown option"
	exit 2
fi
if [[ $6 = 1 ]]; then
	a6="--with-vulkan"
fi
if [[ $7 = 1 ]]; then
	a7="strip"
fi
aclocal
autoconf
automake --add-missing
./configure $a1 $a2 $a3 $a4 $a5 $a6
if test -x "`command -v gmake`"; then
	gmake $a7
else
	make $a7
fi
