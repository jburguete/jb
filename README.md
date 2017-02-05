JB (1.18.0 version)
==================

A library with some useful functions of mathematics, graphics, widgets and XML
input/output.

AUTHORS
-------

* Javier Burguete Tolosa (jburguete@eead.csic.es)

FILES
-----

* README.md: Readme file.
* TODO: List of tasks TO DO.
* *.h: Header files.
* *.c: Source files.
* Doxyfile: configuration file to generate doxygen documentation.
* makefile: to build the tests.

BUILDING THIS LIBRARY ON OTHER PROGRAMS
---------------------------------------

COMPILING FLAGS
_______________

To compile with JB library you has to define the JBW flag. They are 2 options:
* -DJBW=1: for terminal applications.
* -DJBW=2: for graphical applications.
  In this case you have to define the JBW_GRAPHIC flag to selec the graphical
  library to interact with OpenGL. They are 3 options:
  * -DJBW_GRAPHIC=1: FreeGLUT.
  * -DJBW_GRAPHIC=2: SDL.
  * -DJBW_GRAPHIC=3: GLFW.

COMMON BUILDING INSTRUCTIONS
____________________________

1. Load the last library version:
> $ git clone https://github.com/jburguete/jb

2. Link the latest version on a jb directory i.e.:
> $ cd YOUR_PROGRAM_PATH
>
> $ ln -s PATH_TO_THE_JB_LIBRARY/1.18.0 jb

3. Include the config and the used utility headers on your source code i.e.:
> \#include "jb/jb_config.h"
>
> \#include "jb/jb_math.h"

BUILDING STATICALLY
___________________

4. Build the used utility source codes i.e.:
> $ gcc -c -DJBW=1 jb/jb_def.c -o jb_def.o
> `pkg-config --cflags glib-2.0`
>
> $ gcc -c -DJBW=1 jb/jb_win.c -o jb_win.o
> `pkg-config --cflags glib-2.0`
>
> $ gcc -c -DJBW=1 jb/jb_math.c -o jb_math.o
> `pkg-config --cflags glib-2.0`

5. Link the used utility object file to your executable i.e.:
> $ gcc YOUR_SOURCE_CODE.c jb_def.o jb_win.o jb_math.o -o YOUR_EXECUTABLE_FILE 
> `pkg-config --libs glib-2.0`

BUILDING DINAMICALLY
____________________

4. Build the used utility source codes with absolute paths i.e.:
> $ gcc -c -fPIC jb/jb_def.c -o jb_def.o
> \`pkg-config --cflags glib-2.0\`
>
> $ gcc -c -fPIC jb/jb_win.c -o jb_win.o
> `pkg-config --cflags glib-2.0`
>
> $ gcc -c -fPIC jb/jb_math.c -o jb_math.o
> `pkg-config --cflags glib-2.0`

5. Build the shared library object:
> $ gcc -shared jb_def.o jb_win.o jb_math.o -o libjb.so
> `pkg-config --libs glib-2.0`

6. Link the shared library to your executable i.e.:
> $ gcc YOUR_SOURCE_CODE.c -o YOUR_EXECUTABLE_FILE -L. -Wl,-rpath=. -ljb
> `pkg-config --libs glib-2.0`


MAKING REFERENCE MANUAL INSTRUCTIONS (doc/latex/refman.pdf file)
----------------------------------------------------------------

Execute on a terminal:
> $ cd PATH_TO_JB_LIBRARY/1.18.0
>
> $ doxygen
>
> $ cd doc/latex
>
> $ make
