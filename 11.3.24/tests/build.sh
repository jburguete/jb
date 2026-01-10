#!/usr/bin/env bash
if [[ `uname -s` = "OpenBSD" ]]; then
	export AUTOCONF_VERSION=2.71
	export AUTOMAKE_VERSION=1.16
fi
if [[ $# != 1 ]]; then
	echo "The syntax is: ./build.sh A"
	echo "A: 1 on native"
	exit 1
fi
if [[ $1 = 1 ]]; then
	a1="--with-native"
fi
aclocal
autoconf
automake --add-missing
./configure $a1
if test -x "`command -v gmake`"; then
	gmake
else
	make
fi
