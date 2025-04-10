JB (11.1.0 version)
==================

:uk:[english](README.md) :es:[español](README.es.md)
:fr:[français](README.fr.md)

A library with some useful functions of mathematics, graphics, widgets and XML
and JSON input/output.

AUTHORS
-------

* Javier Burguete Tolosa
  [jburguete@eead.csic.es](mailto:jburguete@eead.csic.es).

FILES
-----

* TODO: list of tasks to do.
* src\*.h: header code files.
* src\*.c: source code files.
* Doxyfile: configuration file to generate doxygen documentation.
* build.sh: default build script.
* build\_without\_gui.sh: build script for terminal applications.
* configure.ac: to configure the Makefile building.
* Makefile.in: template to generate the Makefile.
* Doxyfile: to configure the documentation building.
* test.png: figure to check graphical functions.
* test\_data: data file for tests.
* test\*.c: test source files.
* locale/\*/LC\_MESSAGES/jb.po: translation files.

BUILDING THIS LIBRARY
---------------------

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

Required if including jb/xml utilites:
* [libxml](http://xmlsoft.org) to deal with XML files.

Required if including jb/json utilites:
* [json-glib](https://gitlab.gnome.org/GNOME/json-glib) to deal with JSON files.

Needed if including jb/win utilities and compiling with -DJBW=2 flag.
* [png](http://libpng.sourceforge.net) to work with PNG files.
* [gtk](http://www.gtk.org) to work with interactive windows.
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

OPERATIVE SYSTEMS
_________________

You can install all required utilities and libraries using the instructions of
[install-unix](https://github.com/jburguete/install-unix).

This software has been built and tested in the following operative systems:
* Arch Linux
* Debian 12 (Linux)
* Devuan Linux 5
* Dragonfly BSD 6.4.0
* Fedora Linux 40
* FreeBSD 14.1
* Gentoo Linux
* Linux Mint DE 6
* MacOS Sequoia + Homebrew
* Manjaro Linux
* Microsoft Windows 11 + MSYS2
* NetBSD 10.0
* OpenBSD 7.5
* OpenInidiana Hipster
* OpenSUSE Linux 15.5
* Ubuntu Linux 

On Microsoft Windows systems you have to install
[MSYS2](http://sourceforge.net/projects/msys2) and the required
libraries and utilities. You can follow detailed instructions in
[install-unix](https://github.com/jburguete/install-unix/blob/master/tutorial.pdf)
tutorial.

On NetBSD 10.0, to use the last GCC version, you have to do first on the
building terminal:
> $ export PATH="/usr/pkg/gcc12/bin:$PATH"

To do permanent this change the following line can be added to the ".profile"
file in the user root directory:
> PATH="/usr/pkg/gcc12/bin:$PATH"

On OpenBSD 7.5 you have to do first on the building terminal:
> $ export AUTOCONF\_VERSION=2.69 AUTOMAKE\_VERSION=1.16

BUILDING INSTRUCTIONS
_____________________

1. Load the last library version:
> $ git clone https://github.com/jburguete/jb

2. If only terminal applications are required compile the source codes with:
> $ cd 11.1.0
> $ ./build\_wihtout_\gui.sh

2. Or, if graphic interfaces are required, compile the source codes with:
> $ cd 11.1.0
> $ ./build.sh

LINKING THIS LIBRARY ON OTHER PROGRAMS
--------------------------------------

1. Link the latest version on a jb directory, i.e.:
> $ cd YOUR\_PROGRAM\_PATH
>
> $ ln -s PATH\_TO\_THE\_JB\_LIBRARY/11.1.0 jb

2. Include the config and the used utility headers on your source code i.e.:
> \#include "jb/src/math.h"
>
> \#include "jb/src/win.h"
>
> \#include "jb/src/xml.h"

3. Copy the used libraries in your executable directory (libjb\*.so files on
   UNIX systems or libjb\*.dll files on Microsoft Windows systems).

4. Link the shared libraries in your executable, i.e.: 
> $ gcc -DJBW=2 -DJBM\_PRECISION=2 YOUR\_SOURCE\_CODE.c
> -o YOUR\_EXECUTABLE\_FILE -L. -Wl,-rpath=. -ljbwin-2 -ljbxml-2 -ljbm-2
> -ljb-2 \`pkg-config --cflags --libs glib-2.0 libxml-2.0 gtk+-3.0 glew\`
