AC_PREREQ([2.67])
AC_INIT([jb], [2.0.0], [https://github.com/jburguete/jb])
AC_CONFIG_HEADERS([config.h])

# Checks for operative systems
AC_CANONICAL_SYSTEM
AM_INIT_AUTOMAKE
AC_MSG_NOTICE([Build: $build])
AC_MSG_NOTICE([Host: $host])
win=0
win32=0
if test $host = "x86_64-w64-mingw32"; then
	AC_MSG_NOTICE([Microsoft Windows 64 bits])
	win=1
elif test $host = "i686-w64-mingw32"; then
	AC_MSG_NOTICE([Microsoft Windows 32 bits])
	win=1
	win32=1
elif test `uname -s` = "OpenBSD"; then
	AC_MSG_NOTICE([OpenBSD])
	LDFLAGS="$LDFLAGS -L/usr/X11R6/lib"
	CPPFLAGS="$CPPFLAGS -I/usr/X11R6/include"
elif test `uname -s` = "DragonFly"; then
	AC_MSG_NOTICE([DragonFly BSD])
	LDFLAGS="$LDFLAGS -L/usr/local/lib"
	CPPFLAGS="$CPPFLAGS -I/usr/local/include"
fi

# Checks for programs
AC_PROG_CC([gcc8 gcc7 gcc6 gcc5 egcc gcc clang])
AC_MSG_NOTICE([Compiler: $CC])
AC_PROG_MAKE_SET
AC_LANG([C])
PKG_PROG_PKG_CONFIG
if test $win = 1; then
	AC_SUBST(SO, [.dll])
	AC_SUBST(EXE, [.exe])
else
	AC_SUBST(SO, [.so])
fi

# Checks for libraries
AC_SEARCH_LIBS([fmaxl], [m])
PKG_CHECK_MODULES([XML], [libxml-2.0])
PKG_CHECK_MODULES([GLIB], [glib-2.0])

# Checks for GTK+ interface
PKG_CHECK_MODULES([GTK], [gtk+-3.0])
AC_SUBST(JBW, [-DJBW=2])
gtk=1

# Checks for graphic interface
if test $win32 = 1; then
	LDFLAGS="$LDFLAGS -lopengl32"
elif test $gtk = 1; then
	AC_SEARCH_LIBS([glViewport], [GL opengl32], 
		       AC_MSG_NOTICE([OpenGL OK]),
		       AC_MSG_ERROR([OpenGL not found]))
fi
PKG_CHECK_MODULES([GLEW], [glew])

# Checks for header files
AC_CHECK_HEADERS([stdlib.h string.h unistd.h])

# Checking -march=native compiler flag
if test $win = 0; then
	compiler=$CC
	CC="$CC -march=native"
	AC_TRY_LINK([],
		[int main(int argc, char **argv){return 0;}], [arch=1], [arch=0])
	CC=$compiler
	if test $arch = 0; then
		AC_MSG_NOTICE([checking for -march=native... no])
		AC_SUBST(ARCH, "")
	else
		AC_MSG_NOTICE([checking for -march=native... yes])
		AC_SUBST(ARCH, "-march=native")
	fi
fi

# Checking -flto compiler flag
compiler=$CC
CC="$CC -flto"
AC_TRY_LINK([], [int main(int argc, char **argv){return 0;}], [lto=1], [lto=0])
CC=$compiler
if test $lto = 0; then
	AC_MSG_NOTICE([checking for -flto... no])
	AC_SUBST(LTO, "")
else
	AC_MSG_NOTICE([checking for -flto... yes])
	AC_SUBST(LTO, "-flto")
fi

# Checking -std compiler flag
compiler=$CC
CC="$CC -std=gnu11"
AC_TRY_LINK([], [int main(int argc, char **argv){return 0;}], [std=1], [std=0])
CC=$compiler
if test $std = 0; then
	AC_MSG_NOTICE("checking for -std=gnu11... no")
	CC="$CC -std=gnu99"
	AC_TRY_LINK([], [int main(int argc, char **argv){return 0;}], [std=1],
		[std=0])
	CC=$compiler
	if test $std = 0; then
		AC_MSG_NOTICE("checking for -std=gnu99... no")
		AC_SUBST(STD, "")
	else
		AC_MSG_NOTICE("checking for -std=gnu99... yes")
		AC_SUBST(STD, "-std=gnu99")
	fi
else
	AC_MSG_NOTICE("checking for -std=gnu11... yes")
	AC_SUBST(STD, "-std=gnu11")
fi

# Checks for library functions
AC_CHECK_FUNC([exp10], [AC_DEFINE([HAVE_EXP10], [1])])
AC_CHECK_FUNC([fmemopen], [AC_DEFINE([HAVE_FMEMOPEN], [1])])

# Check for font
font=`find /usr -type f -iname freemono.ttf`
if test "x$font" = "x"; then
	AC_MSG_ERROR([FreeMono font not found])
else
	AC_MSG_NOTICE([Font: $font])
	AC_SUBST(FONT, "-DFONT=\\\"$font\\\"")
fi

# Set precision
AC_SUBST(PRECISION, "-DJBM_PRECISION=4")

# Final output
AC_CONFIG_FILES([Makefile])
AC_OUTPUT
