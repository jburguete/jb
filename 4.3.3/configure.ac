AC_PREREQ([2.69])
AC_INIT([jb],[4.3.3],[https://github.com/jburguete/jb])
AC_CONFIG_HEADERS([config.h])

# Checks for operative systems
AC_CANONICAL_TARGET
AM_INIT_AUTOMAKE
AC_MSG_NOTICE([Build: $build])
AC_MSG_NOTICE([Host: $host])
win=0
win32=0
native=1
haiku=0
mac=0
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
	AC_MSG_NOTICE([Remember:])
	AC_MSG_NOTICE("echo 'export PATH=''/usr/local/opt/llvm@13/bin:$PATH''' >> ./zshrc")
	LDFLAGS="$LDFLAGS -L/usr/local/opt/llvm@13/lib -L/System/Library/Frameworks -framework GLUT -framework OpenGL"
	CPPFLAGS="$CPPFLAGS -I/usr/local/opt/llvm@13/include"
	mac=1
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
elif test `uname -s` = "SunOS"; then
	AC_MSG_NOTICE([SunOS])
	AC_SUBST(gnu, [/usr/gnu/bin/])
elif test `uname -s` = "Haiku"; then
	AC_MSG_NOTICE([Haiku])
	haiku=1
fi
if test $mac = 0; then
	AC_SUBST(RPATH, [-rpath=])
	AC_SUBST(BIN, [bin/])
	AC_SUBST(BINPGO, [binpgo/])
	AC_SUBST(TEST_DATA_FILE, [../test_data])
	AC_SUBST(LOGO_FILE, [../test.png])
else
	AC_SUBST(RPATH, [-rpath,])
	AC_SUBST(BIN, [./])
	AC_SUBST(BINPGO, [./])
	AC_SUBST(TEST_DATA_FILE, [./test_data])
	AC_SUBST(LOGO_FILE, [./test.png])
fi

# Checks for programs
AC_PROG_CC([gcc-12 gcc12 gcc-11 gcc11 gcc-10 gcc10 egcc gcc clang])
AC_MSG_NOTICE([Compiler: $CC])
$CC -v
AC_PROG_MAKE_SET
AC_LANG([C])
PKG_PROG_PKG_CONFIG
if test $win = 1; then
	AC_SUBST(SO, [.dll])
	AC_SUBST(EXE, [.exe])
else
	AC_SUBST(SO, [.so])
fi
if test "`command -v gmake`"; then
	AC_SUBST(MAKE, [gmake])
else
	AC_SUBST(MAKE, [make])
fi
if test $CC = "clang"; then
	AC_CHECK_PROGS([LLVM_PROFDATA], [llvm-profdata llvm-profdata-15], 0)
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
	if test "x$native" = "x1"; then
		CC="$CC -march=native"
		AC_LINK_IFELSE([AC_LANG_PROGRAM([[]], [[]])], [arch=1], [arch=0])
		CC=$compiler
		if test $arch = 0; then
			AC_MSG_NOTICE([checking for -march=native... no])
			AC_SUBST(ARCH, "")
		else
			AC_MSG_NOTICE([checking for -march=native... yes])
			AC_SUBST(ARCH, "-march=native")
		fi
	fi
fi

# Checking -flto compiler flag
CC="$CC -flto"
AC_LINK_IFELSE([AC_LANG_PROGRAM([[]], [[]])], [lto=1], [lto=0])
CC=$compiler
if test $lto = 0; then
	AC_MSG_NOTICE([checking for -flto... no])
	AC_SUBST(LTO, "")
else
	AC_MSG_NOTICE([checking for -flto... yes])
	AC_SUBST(LTO, "-flto")
fi

# Checking PGO optimiztion
AC_ARG_WITH([pgo],
	AS_HELP_STRING([--with-pgo], [Build using PGO]))
pgo=0
if test "x$with_pgo" = "xyes"; then
	CC="$CC -fprofile-generate"
	AC_LINK_IFELSE([AC_LANG_PROGRAM([[]], [[]])], [pgo=1])
	CC=$compiler
	if test $pgo = 0; then
		CC="$CC -fprofile-instr-generate"
		AC_LINK_IFELSE([AC_LANG_PROGRAM([[]], [[]])], [pgo=1])
		CC=$compiler
	fi
fi
if test $pgo = 0; then
		AC_MSG_NOTICE("checking for PGO... no")
else
		AC_MSG_NOTICE("checking for PGO... yes")
fi
AC_SUBST(PGO, [$pgo])

# Checks for libraries
AC_SEARCH_LIBS([fmaxl], [m])
AC_SEARCH_LIBS([textdomain], [intl])
PKG_CHECK_MODULES([XML], [libxml-2.0])
PKG_CHECK_MODULES([GLIB], [glib-2.0])
PKG_CHECK_MODULES([GTHREAD], [gthread-2.0])
PKG_CHECK_MODULES([JSON], [json-glib-1.0])
PKG_CHECK_MODULES([GTOP], [libgtop-2.0], AC_DEFINE([HAVE_GTOP], [1]),
	AC_MSG_NOTICE([No gtop]))
PKG_CHECK_MODULES([GSL], [gsl])

# Checks for GTK+ interface
AC_ARG_WITH([gtk],
	AS_HELP_STRING([--with-gtk],
		[Build using a version of GTK (3 (--with-gtk=3) or 4 (--with-gtk=4))]))
gtk4=0
gtk3=0
gtk=0
if test "x$with_gtk" = "x4"; then
	PKG_CHECK_MODULES([GTK], [gtk4], [gtk4=1], [gtk4=0])
	gtk3=1
elif test "x$with_gtk" = "x3"; then
	gtk3=1
fi
if test $gtk4 = 1; then
	AC_SUBST(JBW, [-DJBW=2])
	gtk=1
elif test $gtk3 = 1; then
	PKG_CHECK_MODULES([GTK], [gtk+-3.0],
		[AC_MSG_NOTICE([With GTK])],
		[AC_MSG_NOTICE([Without GTK])])
	AC_SUBST(JBW, [-DJBW=2])
	gtk=1
else
	AC_SUBST(JBW, [-DJBW=1])
fi

# Checks for graphic interface
if test $gtk = 1; then
	AC_SEARCH_LIBS([glViewport], [GL opengl32], 
		AC_MSG_NOTICE([OpenGL OK]),
		AC_MSG_ERROR([OpenGL not found]))
	PKG_CHECK_MODULES([PNG], [libpng])
	PKG_CHECK_MODULES([FREETYPE], [freetype2])
	if test $haiku = 1; then
		AC_MSG_NOTICE([Haiku])
		AC_SUBST(GLEW_LIBS, "-lGLEW -lGLU")
	else
		PKG_CHECK_MODULES([GLEW], [glew])
	fi
	AC_ARG_WITH([vulkan],
		AS_HELP_STRING([--with-vulkan],
			[Build graphic window with Vulkan support]))
	if test "x$with_vulkan" = "xyes"; then
		PKG_CHECK_MODULES([VULKAN], [vulkan],
			AC_DEFINE([HAVE_VULKAN], [1])
			AC_SUBST(VULKAN, "1"),
			AC_MSG_NOTICE([No vulkan])
			AC_SUBST(VULKAN, "0"))
	fi
fi

# Checks for GtkGLArea, FreeGLUT, GLFW or SDL to draw the graphic window
if test $gtk = 1; then
	AC_ARG_WITH([gtkglarea],
		AS_HELP_STRING([--with-gtkglarea],
			[Build graphic window with GtkGLArea]))
	AC_ARG_WITH([freeglut],
		AS_HELP_STRING([--with-freeglut], [Build graphic window with FreeGLUT]))
	AC_ARG_WITH([glfw],
		AS_HELP_STRING([--with-glfw], [Build graphic window with GLFW]))
	AC_ARG_WITH([sdl],
		AS_HELP_STRING([--with-sdl], [Build graphic window with SDL]))
	if test "x$with_freeglut" = "xyes"; then
		AC_SUBST(GRAPHIC, "-DHAVE_FREEGLUT=1")
		PKG_CHECK_MODULES([GLUT], [glut])
	elif test "x$with_glfw" = "xyes"; then
		AC_SUBST(GRAPHIC, "-DHAVE_GLFW=1")
		PKG_CHECK_MODULES([GLFW], [glfw3])
	elif test "x$with_sdl" = "xyes"; then
		AC_SUBST(GRAPHIC, "-DHAVE_SDL=1")
		PKG_CHECK_MODULES([SDL], [sdl2])
	else
		AC_SUBST(GRAPHIC, "-DHAVE_GTKGLAREA=1")
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
if test $gtk = 1; then
	AC_MSG_NOTICE([Searching font...])
	if test $win = 1 || test $haiku = 1; then
		dir="/"
	else
		dir="/usr"
	fi
	font=`find $dir -type f -iname freemono.otf`
	if test "x$font" = "x"; then
		font=`find $dir -type f -iname freemono.ttf`
		if test "x$font" = "x"; then
			font=`find $dir -type f -iname NotoSansMono-Regular.ttf`
			if test "x$font" = "x"; then
				AC_MSG_ERROR([FreeMono font not found])
			fi
		fi
	fi
	AC_MSG_NOTICE([Font: $font])
	AC_SUBST(FONT, "-DFONT=\\\"$font\\\"")
fi

# Set precision
AC_ARG_WITH([precision],
	AS_HELP_STRING([--with-precision],
		[Build with precision degree (1-5), default=2]))
if test "x$with_precision" = "x1"; then
	AC_SUBST(PRECISION, "-DJBM_PRECISION=1")
	AC_SUBST(SUFFIX, [-1])
elif test "x$with_precision" = "x3"; then
	AC_SUBST(PRECISION, "-DJBM_PRECISION=3")
	AC_SUBST(SUFFIX, [-3])
elif test "x$with_precision" = "x4"; then
	AC_SUBST(PRECISION, "-DJBM_PRECISION=4")
	AC_SUBST(SUFFIX, [-4])
elif test "x$with_precision" = "x5"; then
	AC_SUBST(PRECISION, "-DJBM_PRECISION=5")
	AC_SUBST(SUFFIX, [-5])
else
	AC_SUBST(PRECISION, "-DJBM_PRECISION=2")
	AC_SUBST(SUFFIX, [-2])
fi

# Final output
AC_CONFIG_HEADERS([src/config.h])
AC_CONFIG_FILES([Makefile])
AC_OUTPUT
