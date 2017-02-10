AC_PREREQ([2.67])
AC_INIT([jb], [1.18.0], [https://github.com/jburguete/jb])

# Checks for operative systems
AC_CANONICAL_SYSTEM
AM_INIT_AUTOMAKE
AC_MSG_NOTICE([Build: $build])
AC_MSG_NOTICE([Host: $host])
win=0
if test $host = "x86_64-w64-mingw32"; then
	AC_MSG_NOTICE([Microsoft Windows 64 bits])
	win=1
elif test $host = "i686-w64-mingw32"; then
	AC_MSG_NOTICE([Microsoft Windows 32 bits])
	win=1
fi

# Checks for programs
AC_PROG_CC([egcc gcc clang])
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
AC_ARG_WITH([gtk], AS_HELP_STRING([--with-gtk], [Build with GTK+ interface]))
if test "x$with_gtk" = "xyes"; then
	PKG_CHECK_MODULES([GTK], [gtk+-3.0])
	AC_SUBST(JBW, [-DJBW=2])
	gtk=1
else
	AC_SUBST(JBW, [-DJBW=1])
	gtk=0
fi

# Checks for graphic interface
AC_ARG_WITH([sdl], AS_HELP_STRING([--with-sdl], 
	    [Build with SDL graphic interface]))
AC_ARG_WITH([glfw], AS_HELP_STRING([--with-glfw], 
	    [Build with GLFW graphic interface]))
if test $gtk = 1; then
	PKG_CHECK_MODULES([GLEW], [glew])
	if test "x$with_sdl" = "xyes"; then
		AC_SUBST(GRAPHIC, "-DJBW_GRAPHIC=2")
		PKG_CHECK_MODULES([SDL], [sdl2])
	else
		if test "x$with_glfw" = "xyes"; then
			AC_SUBST(GRAPHIC, "-DJBW_GRAPHIC=3")
			PKG_CHECK_MODULES([GLFW], [glfw3])
		else
			AC_SEARCH_LIBS([glutInit], [freeglut glut], glut="yes", 
				       glut="no")
			if test $glut = "yes"; then
				AC_SUBST(GRAPHIC, "-DJBW_GRAPHIC=1")
			else
				PKG_CHECK_MODULES([SDL], [sdl2], sdl="yes", 
						  sdl="no")
				if test $sdl = "yes"; then
					AC_SUBST(GRAPHIC, "-DHAVE_SDL=2")
				else
					PKG_CHECK_MODULES([GLFW], [glfw3])
					AC_SUBST(GRAPHIC, "-DHAVE_GLFW=3")
				fi
			fi
		fi
	fi
fi

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
AC_FUNC_MALLOC
AC_FUNC_REALLOC
AC_FUNC_ALLOCA
AC_CHECK_FUNCS([strtoul])

# Final output
AC_CONFIG_FILES([Makefile])
AC_OUTPUT
