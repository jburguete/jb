JB (1.10.0 version)
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

1. Linking the latest version on a jb directory i.e.:
> $ cd YOUR_PROGRAM_PATH
>
> $ ln -s PATH_TO_THE_JB_LIBRARY/1.10.0 jb

2. Include the config and the used utility headers on your source code i.e.:
> \#include \<jb/jb_config.h\>
>
> \#include \<jb/jb_math.h\>

3. Build the used utility source code i.e.:
> $ gcc -c jb/jb_math.c -o jb_math.o

4. Link the used utility object file to your executable i.e.:
> $ gcc YOUR_SOURCE_CODE.c jb_math.o -o YOUR_EXECUTABLE_FILE

MAKING REFERENCE MANUAL INSTRUCTIONS (doc/latex/refman.pdf file)
----------------------------------------------------------------

Execute on a terminal:
> $ cd PATH_TO_JB_LIBRARY/1.10.0
>
> $ doxygen
>
> $ cd doc/latex
>
> $ make
