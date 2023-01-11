aclocal
autoconf
automake --add-missing
./configure --with-precision=3
if test "`command -v gmake`"; then
	gmake
else
	make
fi
