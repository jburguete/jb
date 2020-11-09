aclocal
autoconf
automake --add-missing
./configure --with-pgo
if test "`command -v gmake`"; then
	gmake
else
	make
fi
