JB (versión 2.0.0)
==================

[english](README.md) [español](README.es.md)

Una biblioteca con funciones útiles de matemáticas, gráficos, widgets y
entrada/salida XML.

AUTORES
-------

* Javier Burguete Tolosa (jburguete@eead.csic.es).

FICHEROS
--------

* TODO: lista de tareas a realizar.
* jb\*.h: ficheros de código de cabecera.
* jb\*.c: ficheros de código fuente.
* Doxyfile: fichero de configuración para generar documentación doxygen.
* build.sh: script de construcción por defecto.
* configure.ac: para configurar la construcción del Makefile.
* Makefile.in: plantilla para generar del Makefile.
* Doxyfile: para configurar la construcción de la documentación.
* test.png: figura para probar funciones gráficas.
* text\*.c: ficheros fuente de prueba.
* locale/\*/LC\_MESSAGES/jb.po: ficheros de traducción.

CONSTRUYENDO LA BIBLITECA EN OTROS PROGRAMAS
--------------------------------------------

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

Opcional si se incluye las utilidades jb\_xml:
* [libxml](http://xmlsoft.org) para trabajar con ficheros XML.

Opcional si se incluyen las utilidades jb\_win y se compila usando el flag
-DJBW=2.
* [png](http://libpng.sourceforge.net) para trabajar con ficheros PNG.
* [gtk3](http://www.gtk.org) para trabajar con ventanas interactivas.
* [glew](http://glew.sourceforge.net) funciones OpenGL de alto nivel.

Opcional para construir la documentación:
* [doxygen](http://www.stack.nl/~dimitri/doxygen) formato de comentarios
  estándar para generar documentación.
* [latex](https://www.latex-project.org/) para construir los manuales PDF.

FLAGS DE COMPILACIÓN
____________________

Para compilar con la biblioteca JB hay que definir el flag JBW. Hay 2 opciones:
* -DJBW=1: para aplicaciones de terminal.
* -DJBW=2: para aplicaciones gráficas.

Se necesita también definir el flag de nivel de precisión:
* -DJBM\_PRECISION=1: todas variables matemáticas se definen como float.
* -DJBM\_PRECISION=2: las variables matemáticas se definen como float o double.
* -DJBM\_PRECISION=3: todas variables matemáticas se definen como double.
* -DJBM\_PRECISION=4: las variables matemáticas se definen como double o long
  double.
* -DJBM\_PRECISION=5: todas variables matemáticas se definen como long double.

Las bibliotecas construidas por defecto usan el nivel de precisión 2.

SISTEMAS OPERATIVOS
___________________

Puede instalarse todas las bibliotecas y utilidades requeridas usando las
instrucciones de [install-unix](https://github.com/jburguete/install-unix).

En sistemas Microsoft Windows hay que instalar
[MSYS2](http://sourceforge.net/projects/msys2) además de las bibliotecas y
utilidades requeridas. Puede seguir instrucciones detalladas en el tutorial
[install-unix](https://github.com/jburguete/install-unix/blob/master/tutorial.pdf).

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

INSTRUCCIONES DE CONSTRUCCIÓN COMUNES
_____________________________________

1. Descargar la última versión de la biblioteca:
> $ git clone https://github.com/jburguete/jb

2. Enlazar la última versión de una carpeta jb p.e.:
> $ cd CARPETA_DE_SU_PROGRAMA
>
> $ ln -s RUTA_DE_LA_BIBLIOTECA_JB/2.0.0 jb

3. Incluir el fichero de configuración y las utilidades requeridas en su código
   fuente p.e.:
> \#include "jb/jb_config.h"
>
> \#include "jb/jb_math.h"
>
> \#include "jb/jb_win.h"
>
> \#include "jb/jb_xml.h"

CONSTRUCCIÓN ESTÁTICA
_____________________

4. Compilar los códigos fuente de las utilidades usadas p.e.:
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

5. Enlazar los ficheros objeto de las utilidades usadas en su ejecutable p.e.:
> $ gcc -DJBW=2 -DJBM_PRECISION=2 SU_CÓDIGO_FUENTE.c jb_def.o jb_math.o
> jb_win.o jb_xml.o -o SU_FICHERO_EJECUTABLE
> \`pkg-config --cflags glib-2.0 libxml-2.0 gtk+-3.0 glew\`

Nótese que su código podría también necesitar bibliotecas adicionales en el
comando "pkg-config"

Nótese asimismo que se puede usar otro nivel de precisión (JBM\_PRECISION).

CONSTRUCCIÓN DINÁMICA
_____________________

4. Compilar los códigos fuente de las utilidades usadas con rutas absolutas
   p.e.:
> $ gcc -c -fPIC -DJBW=2 -DJBM_PRECISION=2 jb/jb_def.c -o jb_def.o
> \`pkg-config --cflags glib-2.0 libxml-2.0 gtk+-3.0 glew\`
>
> $ gcc -c -fPIC -DJBW=2 -DJBM_PRECISION=2 jb/jb_math.c -o jb_math.o
> \`pkg-config --cflags glib-2.0 libxml-2.0 gtk+-3.0 glew\`
>
> $ gcc -c -fPIC -DJBW=2 -DJBM_PRECISION=2 jb/jb_win.c -o jb_win.o
> \`pkg-config --cflags glib-2.0 libxml-2.0 gtk+-3.0 glew\`

5. Construir la biblioteca compartida:
> $ gcc -shared -DJBW=2 -DJBM_PRECISION=2 jb_def.o jb_win.o jb_math.o
> -o libjb.so
> \`pkg-config --cflags glib-2.0 libxml-2.0 gtk+-3.0 glew\`

6. Enlazar la biblioteca compartida en su ejecutable p.e.: 
> $ gcc -DJBW=2 -DJBM_PRECISION=2 SU_CÓDIGO_FUENTE.c -o SU_FICHERO_EJECUTABLE
> -L. -Wl,-rpath=. -ljb
> \`pkg-config --cflags glib-2.0 libxml-2.0 gtk+-3.0 glew\`

INSTRUCCIONES PARA HACER EL MANUAL DE REFERENCIA (fichero doc/latex/refman.pdf)
-------------------------------------------------------------------------------

Ejecutar en un terminal:
> $ cd RUTA_DE_LA_BIBLIOTECA_JB/2.0.0
>
> $ doxygen
>
> $ cd doc/latex
>
> $ make
