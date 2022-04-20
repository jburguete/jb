JB (2.4.16 version)
==================

:uk:[english](README.md) :es:[español](README.es.md)
:fr:[français](README.fr.md)

A library with some useful functions of mathematics, graphics, widgets and XML
input/output.

AUTHORS
-------

* Javier Burguete Tolosa
  [jburguete@eead.csic.es](mailto:jburguete@eead.csic.es).

FILES
-----

* TODO: list of tasks to do.
* jb\*.h: header code files.
* jb\*.c: source code files.
* Doxyfile: configuration file to generate doxygen documentation.
* build.sh: default build script.
* configure.ac: to configure the Makefile building.
* Makefile.in: template to generate the Makefile.
* Doxyfile: to configure the documentation building.
* test.png: figure to check graphical functions.
* text\*.c: test source files.
* locale/\*/LC\_MESSAGES/jb.po: translation files.

BUILDING THIS LIBRARY ON OTHER PROGRAMS
---------------------------------------

REQUIRED LIBRARIES AND UTILITIES
________________________________

Mandatory:
* [gcc](https://gcc.gnu.org) or [clang](http://clang.llvm.org) to compile the
  source code.
* [make](http://www.gnu.org/software/make) to build the executable file.
* [autoconf](http://www.gnu.org/software/autoconf) to generate the Makefile in
  different operating systems.
* [automake](http://www.gnu.org/software/automake) to check the operating
  system.
* [pkg-config](http://www.freedesktop.org/wiki/Software/pkg-config) to find the
  libraries to compile.
* [glib](https://developer.gnome.org/glib) extended utilities of C to work with
  data, lists, mapped files, regular expressions, using multicores in shared
  memory machines, ...
* [gettext](http://www.gnu.org/software/gettext) to work with different
  international locales and languages.

Optional to get the processor properties:
* [libgtop](https://github.com/GNOME/libgtop) to get the processors number.

Required if including jb\_xml utilites:
* [libxml](http://xmlsoft.org) to deal with XML files.

Needed if including jb\_win utilities and compiling with -DJBW=2 flag.
* [png](http://libpng.sourceforge.net) to work with PNG files.
* [gtk3](http://www.gtk.org) to work with interactive windows.
* [glew](http://glew.sourceforge.net) high level OpenGL functions.

The following optional libraries can be used as alternative to the GtkGLArea
widget of the GTK library to interact with OpenGL to draw graphs.
* [freeglut](http://freeglut.sourceforge.net)
* [sdl2](https://www.libsdl.org)
* [glfw](http://www.glfw.org)

Optional to build documentation:
* [doxygen](http://www.stack.nl/~dimitri/doxygen) standard comments format to
  generate documentation.
* [latex](https://www.latex-project.org/) to build the PDF manuals.

COMPILING FLAGS
_______________

To compile with JB library you has to define the JBW flag. They are 2 options:
* -DJBW=1: for terminal applications.
* -DJBW=2: for graphical applications.

It is also needed to set the precision level flag:
* -DJBM\_PRECISION=1: all math variables are defined as float.
* -DJBM\_PRECISION=2: math variables are defined as float or double.
* -DJBM\_PRECISION=3: all math variables are defined as double.
* -DJBM\_PRECISION=4: math variables are defined as double or long double.
* -DJBM\_PRECISION=5: all math variables are defined as long double.

In default building shared libraries are using the precision level 2.

OPERATIVE SYSTEMS
_________________

You can install all required utilities and libraries using the instructions of
[install-unix](https://github.com/jburguete/install-unix).

This software has been built and tested in the following operative systems:
* Arch Linux
* Debian 11 (Linux)
* Devuan Linux 4
* Dragonfly BSD 6.2.1
* Fedora Linux 35
* FreeBSD 13.0
* Gentoo Linux
* Linux Mint 4
* MacOS Catalina + Homebrew
* Manjaro Linux
* Microsoft Windows 10
* NetBSD 9.2
* OpenBSD 7.0
* OpenInidiana Hipster
* OpenSUSE Linux 15.3
* Ubuntu Linux 21.04

On Microsoft Windows systems you have to install
[MSYS2](http://sourceforge.net/projects/msys2) and the required
libraries and utilities. You can follow detailed instructions in
[install-unix](https://github.com/jburguete/install-unix/blob/master/tutorial.pdf)
tutorial.

On NetBSD 9.2, to use the last GCC version, you have to do first on the
building terminal:
> $ export PATH="/usr/pkg/gcc9/bin:$PATH"

To do permanent this change the following line can be added to the ".profile"
file in the user root directory:
> PATH="/usr/pkg/gcc9/bin:$PATH"

On OpenBSD 7.0 you have to do first on the building terminal:
> $ export AUTOCONF\_VERSION=2.69 AUTOMAKE\_VERSION=1.16

COMMON BUILDING INSTRUCTIONS
____________________________

1. Load the last library version:
> $ git clone https://github.com/jburguete/jb

2. Link the latest version on a jb directory i.e.:
> $ cd YOUR\_PROGRAM\_PATH
>
> $ ln -s PATH\_TO\_THE\_JB\_LIBRARY/2.4.16 jb

3. Include the config and the used utility headers on your source code i.e.:
> \#include "jb/jb\_config.h"
>
> \#include "jb/jb\_math.h"
>
> \#include "jb/jb\_win.h"
>
> \#include "jb/jb\_xml.h"

BUILDING STATICALLY
___________________

4. Build the used utility source codes i.e.:
> $ gcc -c -DJBW=2 -DJBM\_PRECISION=2 jb/jb\_def.c -o jb\_def.o
> \`pkg-config --cflags glib-2.0 libxml-2.0 gtk+-3.0 glew\`
>
> $ gcc -c -DJBW=2 -DJBM\_PRECISION=2 jb/jb\_math.c -o jb\_math.o
> \`pkg-config --cflags glib-2.0 libxml-2.0 gtk+-3.0 glew\`
>
> $ gcc -c -DJBW=2 -DJBM\_PRECISION=2 jb/jb\_win.c -o jb\_win.o
> \`pkg-config --cflags glib-2.0 libxml-2.0 gtk+-3.0 glew\`
>
> $ gcc -c -DJBW=2 -DJBM\_PRECISION=2 jb/jb\_xml.c -o jb\_xml.o
> \`pkg-config --cflags glib-2.0 libxml-2.0 gtk+-3.0 glew\`

5. Link the used utility object file to your executable i.e.:
> $ gcc -DJBW=2 -DJBM\_PRECISION=2 YOUR\_SOURCE\_CODE.c jb\_def.o jb\_math.o
> jb\_win.o jb\_xml.o -o YOUR\_EXECUTABLE\_FILE
> \`pkg-config --cflags glib-2.0 libxml-2.0 gtk+-3.0 glew\`

Note that your code could also need additional libraries to "pkg-config"
command.

Note also that you can set another precision level (JBM\_PRECISION).

BUILDING DINAMICALLY
____________________

4. Build the used utility source codes with absolute paths i.e.:
> $ gcc -c -fPIC -DJBW=2 -DJBM\_PRECISION=2 jb/jb\_def.c -o jb\_def.o
> \`pkg-config --cflags glib-2.0 libxml-2.0 gtk+-3.0 glew\`
>
> $ gcc -c -fPIC -DJBW=2 -DJBM\_PRECISION=2 jb/jb\_math.c -o jb\_math.o
> \`pkg-config --cflags glib-2.0 libxml-2.0 gtk+-3.0 glew\`
>
> $ gcc -c -fPIC -DJBW=2 -DJBM\_PRECISION=2 jb/jb\_win.c -o jb\_win.o
> \`pkg-config --cflags glib-2.0 libxml-2.0 gtk+-3.0 glew\`

5. Build the shared library:
> $ gcc -shared -DJBW=2 -DJBM\_PRECISION=2 jb\_def.o jb\_win.o jb\_math.o
> -o libjb.so
> \`pkg-config --cflags glib-2.0 libxml-2.0 gtk+-3.0 glew\`

6. Link the shared library to your executable i.e.:
> $ gcc -DJBW=2 -DJBM\_PRECISION=2 YOUR\_SOURCE\_CODE.c
> -o YOUR\_EXECUTABLE\_FILE -L. -Wl,-rpath=. -ljb
> \`pkg-config --cflags glib-2.0 libxml-2.0 gtk+-3.0 glew\`

INSTRUCTIONS TO MAKE THE REFERENCE MANUAL (doc/latex/refman.pdf file)
---------------------------------------------------------------------

Execute on a terminal:
> $ cd PATH\_TO\_JB\_LIBRARY/2.4.16
>
> $ doxygen
>
> $ cd doc/latex
>
> $ make
