AC_PREREQ([2.69])
AC_INIT([jb], [2.4.2], [https://github.com/jburguete/jb])
AC_CONFIG_HEADERS([config.h])

# Checks for operative systems
AC_CANONICAL_SYSTEM
AM_INIT_AUTOMAKE
AC_MSG_NOTICE([Build: $build])
AC_MSG_NOTICE([Host: $host])
win=0
win32=0
native=1
rpath="-rpath=."
if test $host = "x86_64-w64-mingw32"; then
	AC_MSG_NOTICE([Microsoft Windows 64 bits + MinGW])
	win=1
elif test $host = "i686-w64-mingw32"; then
	AC_MSG_NOTICE([Microsoft Windows 32 bits + MinGW])
	win=1
	win32=1
elif test $host = "x86_64-pc-cygwin"; then
	AC_MSG_NOTICE([Microsoft Windows 64 bits + Cygwin])
	win=1
elif test $host = "i686-pc-cygwin"; then
	AC_MSG_NOTICE([Microsoft Windows 32 bits + Cygwin])
	win=1
	win32=1
elif test `uname -s` = "Darwin"; then
	AC_MSG_NOTICE([MacOS])
	LDFLAGS="$LDFLAGS -L/System/Library/Frameworks -framework GLUT -framework OpenGL"
	rpath="-rpath,."
elif test `uname -s` = "FreeBSD"; then
	AC_MSG_NOTICE([FreeBSD])
	LDFLAGS="$LDFLAGS -L/usr/local/lib"
elif test `uname -s` = "NetBSD"; then
	AC_MSG_NOTICE([NetBSD])
	LDFLAGS="$LDFLAGS -L/usr/pkg/lib -L/usr/X11R7/lib"
	CPPFLAGS="$CPPFLAGS -I/usr/X11R7/include"
elif test `uname -s` = "OpenBSD"; then
	AC_MSG_NOTICE([OpenBSD])
	LDFLAGS="$LDFLAGS -L/usr/X11R6/lib"
	CPPFLAGS="$CPPFLAGS -I/usr/X11R6/include"
	native=0
elif test `uname -s` = "DragonFly"; then
	AC_MSG_NOTICE([DragonFly BSD])
	LDFLAGS="$LDFLAGS -L/usr/local/lib"
	CPPFLAGS="$CPPFLAGS -I/usr/local/include"
fi

# Checks for programs
AC_PROG_CC([gcc10 gcc9 gcc8 gcc7 egcc gcc clang])
AC_MSG_NOTICE([Compiler: $CC])
$CC -v
AC_PROG_MAKE_SET
AC_LANG([C])
PKG_PROG_PKG_CONFIG
if test $CC = "clang"; then
	rpath="-rpath,."
fi
AC_SUBST(RPATH,[$rpath])
if test $win = 1; then
	AC_SUBST(SO, [.dll])
	AC_SUBST(EXE, [.exe])
	native=0
else
	AC_SUBST(SO, [.so])
fi
if test "`command -v gmake`"; then
	AC_SUBST(MAKE, [gmake])
else
	AC_SUBST(MAKE, [make])
fi

# Checking -march=native compiler flag
if test "x$native" = "x1"; then
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

# Checking PGO optimiztion
AC_ARG_WITH([pgo],
	AS_HELP_STRING([--with-pgo], [Build using PGO]))
if test "x$with_pgo" = "xyes"; then
	CC="$CC -fprofile-generate"
	AC_TRY_LINK([], [int main(int argc, char **argv){return 0;}], [pgo=1],
		[pgo=0])
	CC=$compiler
	if test "x$pgo" = "x0"; then
		AC_MSG_NOTICE("checking for PGO... no")
		AC_SUBST(PGO, "0")
	else
		AC_MSG_NOTICE("checking for PGO... yes")
		AC_SUBST(PGO, "1")
	fi
fi

# Checks for libraries
AC_SEARCH_LIBS([fmaxl], [m])
AC_SEARCH_LIBS([textdomain], [intl])
PKG_CHECK_MODULES([XML], [libxml-2.0])
PKG_CHECK_MODULES([GLIB], [glib-2.0])
PKG_CHECK_MODULES([GTHREAD], [gthread-2.0])
PKG_CHECK_MODULES([GTOP], [libgtop-2.0],
	AC_DEFINE([HAVE_GTOP], [1]),
	AC_MSG_NOTICE([No gtop]))
PKG_CHECK_MODULES([GSL], [gsl])

# Checks for GTK+ interface
PKG_CHECK_MODULES([GTK], [gtk+-3.0])
AC_SUBST(JBW, [-DJBW=2])
gtk=1

# Checks for graphic interface
if test $gtk = 1; then
	AC_SEARCH_LIBS([glViewport], [GL opengl32], 
		       AC_MSG_NOTICE([OpenGL OK]),
		       AC_MSG_ERROR([OpenGL not found]))
fi
PKG_CHECK_MODULES([PNG], [libpng])
PKG_CHECK_MODULES([FREETYPE], [freetype2])
PKG_CHECK_MODULES([GLEW], [glew])

# Checks for GtkGLArea, FreeGLUT, GLFW or SDL to draw the graphic window
AC_ARG_WITH([gtkglarea],
	AS_HELP_STRING([--with-gtkglarea], [Build graphic window with GtkGLArea]))
AC_ARG_WITH([freeglut],
	AS_HELP_STRING([--with-freeglut], [Build graphic window with FreeGLUT]))
AC_ARG_WITH([glfw],
	AS_HELP_STRING([--with-glfw], [Build graphic window with GLFW]))
AC_ARG_WITH([sdl],
	AS_HELP_STRING([--with-sdl], [Build graphic window with SDL]))
if test "x$with_freeglut" = "xyes"; then
	AC_SUBST(GRAPHIC, "-DHAVE_FREEGLUT=1")
	AC_SEARCH_LIBS([glutLeaveMainLoop], [freeglut glut], glut="yes", glut="no")
else
	if test "x$with_glfw" = "xyes"; then
		AC_SUBST(GRAPHIC, "-DHAVE_GLFW=1")
		PKG_CHECK_MODULES([GLFW], [glfw3])
	else
		if test "x$with_sdl" = "xyes"; then
			AC_SUBST(GRAPHIC, "-DHAVE_SDL=1")
			PKG_CHECK_MODULES([SDL], [sdl2])
		else
			AC_SUBST(GRAPHIC, "-DHAVE_GTKGLAREA=1")
		fi
	fi
fi

# Checks for header files
AC_CHECK_HEADERS([stdlib.h string.h unistd.h],,
								 AC_MSG_ERROR([Missing standard headers]))
AC_CHECK_HEADER([sys/sysinfo.h], AC_DEFINE([HAVE_SYSINFO], [1]))

# Checks for library functions
AC_CHECK_FUNC([exp10], AC_DEFINE([HAVE_EXP10], [1]))
AC_CHECK_FUNC([fmemopen], AC_DEFINE([HAVE_FMEMOPEN], [1]))
AC_CHECK_FUNC([get_nprocs], AC_DEFINE([HAVE_GET_NPROCS], [1]))

# Check for font
AC_MSG_NOTICE([Searching font...])
font=`find /usr -type f -iname freemono.otf`
if test "x$font" = "x"; then
	font=`find /usr -type f -iname freemono.ttf`
	if test "x$font" = "x"; then
		AC_MSG_ERROR([FreeMono font not found])
	fi
fi
AC_MSG_NOTICE([Font: $font])
AC_SUBST(FONT, "-DFONT=\\\"$font\\\"")

# Set precision
AC_SUBST(PRECISION, "-DJBM_PRECISION=2")

# Final output
AC_CONFIG_FILES([Makefile tests/Makefile])
AC_OUTPUT
