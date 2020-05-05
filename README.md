JB (2.0.0 version)
==================

:uk:[english](README.md) :es:[español](README.es.md)

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
  different operative systems.
* [automake](http://www.gnu.org/software/automake) to check the operative
  system.
* [pkg-config](http://www.freedesktop.org/wiki/Software/pkg-config) to find the
  libraries to compile.
* [glib](https://developer.gnome.org/glib) extended utilities of C to work with
  data, lists, mapped files, regular expressions, using multicores in shared
  memory machines, ...
* [gettext](http://www.gnu.org/software/gettext) to work with different
  international locales and languages.

Optional if including jb\_xml utilites:
* [libxml](http://xmlsoft.org) to deal with XML files.

Optional if including jb\_win utilities and compiling with -DJBW=2 flag.
* [png](http://libpng.sourceforge.net) to work with PNG files.
* [gtk3](http://www.gtk.org) to work with interactive windows.
* [glew](http://glew.sourceforge.net) high level OpenGL functions.

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

On Microsoft Windows systems you have to install
[MSYS2](http://sourceforge.net/projects/msys2) and the required
libraries and utilities. You can follow detailed instructions in
[install-unix](https://github.com/jburguete/install-unix/blob/master/tutorial.pdf)
tutorial.

On NetBSD 7.0 you have to do first on the building terminal:
> $ export PATH=/usr/pkg/gcc5/bin:$PATH"

On OpenBSD 6.4 you have to do first on the building terminal:
> $ export AUTOCONF_VERSION=2.69 AUTOMAKE_VERSION=1.16

This software has been built and tested in the following operative systems:
* Debian 9 (Linux, kFreeBSD and Hurd)
* DragonFly BSD 5.2
* Dyson Illumos
* Fedora Linux 29
* FreeBSD 11.2
* Manjaro Linux
* Microsoft Windows 7
* Microsoft Windows 10
* NetBSD 7.0 (with modular xorg)
* OpenBSD 6.4
* OpenInidiana Hipster
* OpenSUSE Linux Leap 15
* Xubuntu Linux 18.10

COMMON BUILDING INSTRUCTIONS
____________________________

1. Load the last library version:
> $ git clone https://github.com/jburguete/jb

2. Link the latest version on a jb directory i.e.:
> $ cd YOUR_PROGRAM_PATH
>
> $ ln -s PATH_TO_THE_JB_LIBRARY/2.0.0 jb

3. Include the config and the used utility headers on your source code i.e.:
> \#include "jb/jb_config.h"
>
> \#include "jb/jb_math.h"
>
> \#include "jb/jb_win.h"
>
> \#include "jb/jb_xml.h"

BUILDING STATICALLY
___________________

4. Build the used utility source codes i.e.:
> $ gcc -c -DJBW=2 -DJBM_PRECISION=2 jb/jb_def.c -o jb_def.o
> \`pkg-config --cflags glib-2.0 libxml-2.0 gtk+-3.0 glew\`
>
> $ gcc -c -DJBW=2 -DJBM_PRECISION=2 jb/jb_math.c -o jb_math.o
> \`pkg-config --cflags glib-2.0 libxml-2.0 gtk+-3.0 glew\`
>
> $ gcc -c -DJBW=2 -DJBM_PRECISION=2 jb/jb_win.c -o jb_win.o
> \`pkg-config --cflags glib-2.0 libxml-2.0 gtk+-3.0 glew\`
>
> $ gcc -c -DJBW=2 -DJBM_PRECISION=2 jb/jb_xml.c -o jb_xml.o
> \`pkg-config --cflags glib-2.0 libxml-2.0 gtk+-3.0 glew\`

5. Link the used utility object file to your executable i.e.:
> $ gcc -DJBW=2 -DJBM_PRECISION=2 YOUR_SOURCE_CODE.c jb_def.o jb_math.o
> jb_win.o jb_xml.o -o YOUR_EXECUTABLE_FILE
> \`pkg-config --cflags glib-2.0 libxml-2.0 gtk+-3.0 glew\`

Note that your code could also need additional libraries to "pkg-config"
command.

Note also that you can set another precision level (JBM\_PRECISION).

BUILDING DINAMICALLY
____________________

4. Build the used utility source codes with absolute paths i.e.:
> $ gcc -c -fPIC -DJBW=2 -DJBM_PRECISION=2 jb/jb_def.c -o jb_def.o
> \`pkg-config --cflags glib-2.0 libxml-2.0 gtk+-3.0 glew\`
>
> $ gcc -c -fPIC -DJBW=2 -DJBM_PRECISION=2 jb/jb_math.c -o jb_math.o
> \`pkg-config --cflags glib-2.0 libxml-2.0 gtk+-3.0 glew\`
>
> $ gcc -c -fPIC -DJBW=2 -DJBM_PRECISION=2 jb/jb_win.c -o jb_win.o
> \`pkg-config --cflags glib-2.0 libxml-2.0 gtk+-3.0 glew\`

5. Build the shared library:
> $ gcc -shared -DJBW=2 -DJBM_PRECISION=2 jb_def.o jb_win.o jb_math.o
> -o libjb.so
> \`pkg-config --cflags glib-2.0 libxml-2.0 gtk+-3.0 glew\`

6. Link the shared library to your executable i.e.:
> $ gcc -DJBW=2 -DJBM_PRECISION=2 YOUR_SOURCE_CODE.c -o YOUR_EXECUTABLE_FILE
> -L. -Wl,-rpath=. -ljb
> \`pkg-config --cflags glib-2.0 libxml-2.0 gtk+-3.0 glew\`

MAKING REFERENCE MANUAL INSTRUCTIONS (doc/latex/refman.pdf file)
----------------------------------------------------------------

Execute on a terminal:
> $ cd PATH_TO_JB_LIBRARY/2.0.0
>
> $ doxygen
>
> $ cd doc/latex
>
> $ make
