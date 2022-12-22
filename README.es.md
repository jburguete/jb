JB (versión 3.1.3)
==================

:gb:[english](README.md) :es:[español](README.es.md)
:fr:[français](README.fr.md)

Una biblioteca con funciones útiles de matemáticas, gráficos, widgets y
entrada/salida XML.

AUTORES
-------

* Javier Burguete Tolosa
  [jburguete@eead.csic.es](mailto:jburguete@eead.csic.es).

FICHEROS
--------

* TODO: lista de tareas a realizar.
* src\*.h: ficheros de código de cabecera.
* src\*.c: ficheros de código fuente.
* Doxyfile: fichero de configuración para generar documentación doxygen.
* build.sh: script de construcción por defecto.
* configure.ac: para configurar la construcción del Makefile.
* Makefile.in: plantilla para generar del Makefile.
* Doxyfile: para configurar la construcción de la documentación.
* test.png: figura para probar funciones gráficas.
* test\*.c: ficheros fuente de prueba.
* locale/\*/LC\_MESSAGES/jb.po: ficheros de traducción.

CONSTRUYENDO LA BIBLIOTECA EN OTROS PROGRAMAS
---------------------------------------------

BIBLIOTECAS Y UTILIDADES REQUERIDAS
___________________________________

Obligatorio:
* [gcc](https://gcc.gnu.org) o [clang](http://clang.llvm.org) para compilar el
  código fuente.
* [make](http://www.gnu.org/software/make) para construir el fichero ejecutable.
* [autoconf](http://www.gnu.org/software/autoconf) para generar el Makefile en
  diferentes sistemas operativos.
* [automake](http://www.gnu.org/software/automake) para detectar el sistema
  operativo.
* [pkg-config](http://www.freedesktop.org/wiki/Software/pkg-config) para
  encontrar las bibliotecas para compilar.
* [glib](https://developer.gnome.org/glib) utilidades extendidas de C para
  trabajar con datos, listas, ficheros mapeados, expresiones regulares, usar
  multiprocesador en máquinas de memoria compartida, ...
* [gettext](http://www.gnu.org/software/gettext) para trabajar con diferentes
  códigos y lenguajes internacionales.

Opcional para detectar las características del procesador:
* [libgtop](https://github.com/GNOME/libgtop) para obtener las características
  de la máquina

Obligatorio si se incluyen las utilidades jb\_xml:
* [libxml](http://xmlsoft.org) para trabajar con ficheros XML.

Obligatorio si se incluyen las utilidades jb\_win y se compila usando el flag
-DJBW=2.
* [png](http://libpng.sourceforge.net) para trabajar con ficheros PNG.
* [gtk3](http://www.gtk.org) para trabajar con ventanas interactivas.
* [glew](http://glew.sourceforge.net) funciones OpenGL de alto nivel.

Bibliotecas opcionales que pueden usarse como alternativa al widget GtkGLArea de
la biblioteca GTK para interactuar con OpenGL para dibujar gráficos:
* [freeglut](http://freeglut.sourceforge.net)
* [sdl2](https://www.libsdl.org)
* [glfw](http://www.glfw.org)

Opcional para construir la documentación:
* [doxygen](http://www.stack.nl/~dimitri/doxygen) formato de comentarios
  estándar para generar documentación.
* [latex](https://www.latex-project.org/) para construir los manuales PDF.

OPCIONES DE COMPILACIÓN
_______________________

Para compilar con la biblioteca JB hay que definir la opción JBW. Hay 2
posibilidades:
* -DJBW=1: para aplicaciones de terminal.
* -DJBW=2: para aplicaciones gráficas.

Se necesita también definir la opción de nivel de precisión:
* -DJBM\_PRECISION=1: todas variables matemáticas se definen como float.
* -DJBM\_PRECISION=2: las variables matemáticas se definen como float o double.
* -DJBM\_PRECISION=3: todas variables matemáticas se definen como double.
* -DJBM\_PRECISION=4: las variables matemáticas se definen como double o long
  double.
* -DJBM\_PRECISION=5: todas variables matemáticas se definen como long double.

Las bibliotecas construidas por defecto usan el nivel de precisión 2.

SISTEMAS OPERATIVOS
___________________

Pueden instalarse todas las bibliotecas y utilidades requeridas usando las
instrucciones de [install-unix](https://github.com/jburguete/install-unix).

Este programa ha sido construido y probado en los siguientes sistemas
operativos:
* Arch Linux
* Debian 11 (Linux)
* Devuan Linux 4
* Dragonfly BSD 6.2.2
* Fedora Linux 37
* FreeBSD 13.0
* Gentoo Linux
* Linux Mint DE 5
* MacOS Catalina + Homebrew
* Manjaro Linux
* Microsoft Windows 10 + MSYS2
* NetBSD 9.2
* OpenBSD 7.0
* OpenInidiana Hipster
* OpenSUSE Linux 15.3
* Ubuntu Linux 21.04

En sistemas Microsoft Windows hay que instalar
[MSYS2](http://sourceforge.net/projects/msys2) además de las bibliotecas y
utilidades requeridas. Puede seguir instrucciones detalladas en el tutorial
[install-unix](https://github.com/jburguete/install-unix/blob/master/tutorial.pdf).

En NetBSD 9.2, para usar la última versión del compilador GCC, hay que hacer
primero en el terminal:
> $ export PATH="/usr/pkg/gcc9/bin:$PATH"

Si se quiere hacer permanente tambien se puede añadir en el fichero ".profile"
de la carpeta raíz del usuario la línea:
> PATH="/usr/pkg/gcc9/bin:$PATH"

En OpenBSD 7.0 hay que hacer antes en el terminal:
> $ export AUTOCONF\_VERSION=2.69 AUTOMAKE\_VERSION=1.16

INSTRUCCIONES DE CONSTRUCCIÓN COMUNES
_____________________________________

1. Descárgase la última versión de la biblioteca:
> $ git clone https://github.com/jburguete/jb

2. Enlácese la última versión en una carpeta jb p.ej.:
> $ cd CARPETA\_DE\_SU\_PROGRAMA
>
> $ ln -s RUTA\_DE\_LA\_BIBLIOTECA\_JB/3.1.3 jb

3. Incluya el fichero de configuración y las utilidades requeridas en su código
   fuente p.ej.:
> \#include "jb/jb\_config.h"
>
> \#include "jb/jb\_math.h"
>
> \#include "jb/jb\_win.h"
>
> \#include "jb/jb\_xml.h"

CONSTRUCCIÓN ESTÁTICA
_____________________

4. Compílese los códigos fuente de las utilidades usadas p.ej.:
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

5. Enlace los ficheros objeto de las utilidades usadas en su ejecutable p.ej.:
> $ gcc -DJBW=2 -DJBM\_PRECISION=2 SU\_CÓDIGO\_FUENTE.c jb\_def.o jb\_math.o
> jb\_win.o jb\_xml.o -o SU\_FICHERO\_EJECUTABLE
> \`pkg-config --cflags glib-2.0 libxml-2.0 gtk+-3.0 glew\`

Nótese que su código podría también necesitar bibliotecas adicionales en el
comando "pkg-config".

Nótese asimismo que se puede usar otro nivel de precisión (JBM\_PRECISION).

CONSTRUCCIÓN DINÁMICA
_____________________

4. Compile los códigos fuente de las utilidades usadas con rutas absolutas
   p.ej.:
> $ gcc -c -fPIC -DJBW=2 -DJBM\_PRECISION=2 jb/jb\_def.c -o jb\_def.o
> \`pkg-config --cflags glib-2.0 libxml-2.0 gtk+-3.0 glew\`
>
> $ gcc -c -fPIC -DJBW=2 -DJBM\_PRECISION=2 jb/jb\_math.c -o jb\_math.o
> \`pkg-config --cflags glib-2.0 libxml-2.0 gtk+-3.0 glew\`
>
> $ gcc -c -fPIC -DJBW=2 -DJBM\_PRECISION=2 jb/jb\_win.c -o jb\_win.o
> \`pkg-config --cflags glib-2.0 libxml-2.0 gtk+-3.0 glew\`

5. Construya la biblioteca compartida:
> $ gcc -shared -DJBW=2 -DJBM\_PRECISION=2 jb\_def.o jb\_win.o jb\_math.o
> -o libjb.so
> \`pkg-config --cflags glib-2.0 libxml-2.0 gtk+-3.0 glew\`

6. Enlace la biblioteca compartida en su ejecutable p.ej.: 
> $ gcc -DJBW=2 -DJBM\_PRECISION=2 SU\_CÓDIGO\_FUENTE.c
> -o SU\_FICHERO\_EJECUTABLE -L. -Wl,-rpath=. -ljb
> \`pkg-config --cflags glib-2.0 libxml-2.0 gtk+-3.0 glew\`

INSTRUCCIONES PARA HACER EL MANUAL DE REFERENCIA (fichero doc/latex/refman.pdf)
-------------------------------------------------------------------------------

Ejecute en un terminal:
> $ cd RUTA\_DE\_LA\_BIBLIOTECA\_JB/3.1.3
>
> $ doxygen
>
> $ cd doc/latex
>
> $ make
