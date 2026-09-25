# Header
AC_PREREQ([2.69])
AC_INIT([tests],[1],[https://github.com/jburguete/jb])

# Checks for operative systems
AC_CANONICAL_TARGET
AM_INIT_AUTOMAKE
AC_MSG_NOTICE([Build: $build])
AC_MSG_NOTICE([Host: $host])
win=0
if test $host = "x86_64-w64-mingw32"; then
	AC_MSG_NOTICE([Microsoft Windows 64 bits + MinGW])
	win=1
elif test $host = "i686-w64-mingw32"; then
	AC_MSG_NOTICE([Microsoft Windows 32 bits + MinGW])
	win=1
elif test `uname -s` = "Darwin"; then
	AC_MSG_NOTICE([MacOS])
	AC_MSG_NOTICE([Remember:])
	AC_MSG_NOTICE("echo 'export PATH=''/usr/local/opt/llvm/bin:$PATH''' >> ./zshrc")
	LDFLAGS="$LDFLAGS -L/usr/local/opt/llvm/lib"
	CPPFLAGS="$CPPFLAGS -I/usr/local/opt/llvm/include"
elif test `uname -s` = "FreeBSD"; then
	AC_MSG_NOTICE([FreeBSD])
	LDFLAGS="$LDFLAGS -L/usr/local/lib"
elif test `uname -s` = "NetBSD"; then
	AC_MSG_NOTICE([NetBSD])
	LDFLAGS="$LDFLAGS -L/usr/pkg/lib"
elif test `uname -s` = "OpenBSD"; then
	AC_MSG_NOTICE([OpenBSD])
elif test `uname -s` = "DragonFly"; then
	AC_MSG_NOTICE([DragonFly BSD])
	LDFLAGS="$LDFLAGS -L/usr/local/lib"
	CPPFLAGS="$CPPFLAGS -I/usr/local/include"
elif test `uname -s` = "SunOS"; then
	AC_MSG_NOTICE([SunOS])
	AC_SUBST(gnu, [/usr/gnu/bin/])
elif test `uname -s` = "Haiku"; then
	AC_MSG_NOTICE([Haiku])
fi

# Checks for programs
AC_PROG_CC([gcc-14 gcc14 gcc-13 gcc13 gcc-12 gcc12 gcc-11 gcc11 egcc gcc clang])
AC_MSG_NOTICE([Compiler: $CC])
$CC -v
AC_PROG_LN_S
AC_PROG_MAKE_SET
AC_LANG([C])
PKG_PROG_PKG_CONFIG
if test "`command -v gmake`"; then
	AC_SUBST(MAKE, [gmake])
else
	AC_SUBST(MAKE, [make])
fi
if test $win = 1; then
	AC_SUBST(SO, [.dll])
	AC_SUBST(EXE, [.exe])
else
	AC_SUBST(SO, [.so])
fi
if test $CC = "clang"; then
	AC_CHECK_PROGS([LLVM_PROFDATA], [llvm-profdata], 0)
	if test $LLVM_PROFDATA = 0; then
	      	AC_MSG_ERROR([No llvm-profdata])
	fi
	AC_MSG_NOTICE([llvm-profdata: $LLVM_PROFDATA])
fi

# Checks for compiler flags
compiler=$CC

# Checking -march=native compiler flag
AC_ARG_WITH([native], AS_HELP_STRING([--with-native],
	[Build using -march=native compiler flag]))
if test "x$with_native" = "xyes"; then
	CC="$CC -march=native"
	AC_LINK_IFELSE([AC_LANG_PROGRAM([[]], [[]])], [arch=1], [arch=0])
	CC=$compiler
	if test $arch = 0; then
		AC_MSG_NOTICE([checking for -march=native... no])
	else
		AC_MSG_NOTICE([checking for -march=native... yes])
		AC_SUBST(ARCH, "-march=native")
	fi
fi

# Checking -flto compiler flag
CC="$CC -flto"
AC_LINK_IFELSE([AC_LANG_PROGRAM([[]], [[]])], [lto=1], [lto=0])
CC=$compiler
if test $lto = 0; then
	AC_MSG_NOTICE([checking for -flto... no])
else
	AC_MSG_NOTICE([checking for -flto... yes])
	AC_SUBST(LTO, "-flto")
fi

# Checks for libraries
AC_SEARCH_LIBS([fmaxl], [m])
AC_SEARCH_LIBS([sinq], [quadmath])

# Checks for header files
AC_CHECK_HEADERS([stdlib.h string.h unistd.h],,
	AC_MSG_ERROR([Missing standard headers]))
AC_CHECK_HEADER([quadmath.h], AC_DEFINE([HAVE_QUADMATH], [1]))

# Checks for typedefs, structures, and compiler characteristics.
AC_C_INLINE
AC_TYPE_SIZE_T

# Checks for library functions
AC_CHECK_FUNC([exp10], AC_DEFINE([HAVE_EXP10], [1]))

# Final output
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([Makefile])
AC_OUTPUT
