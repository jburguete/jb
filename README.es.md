JB (versión 5.3.3)
==================

:gb:[english](README.md) :es:[español](README.es.md)
:fr:[français](README.fr.md)

Una biblioteca con funciones útiles de matemáticas, gráficos, widgets y
entrada/salida XML y JSON.

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
* build\_without\_gui.sh: script de construcción para aplicaciones de terminal.
* configure.ac: para configurar la construcción del Makefile.
* Makefile.in: plantilla para generar del Makefile.
* Doxyfile: para configurar la construcción de la documentación.
* test.png: figura para probar funciones gráficas.
* test\_data: fichero de datos para las pruebas.
* test\*.c: ficheros fuente de prueba.
* locale/\*/LC\_MESSAGES/jb.po: ficheros de traducción.

CONSTRUYENDO LA BIBLIOTECA
--------------------------

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

Obligatorio si se incluyen las utilidades jb\_json:
* [json-glib](https://gitlab.gnome.org/GNOME/json-glib) para trabajar con
  ficheros JSON.

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

SISTEMAS OPERATIVOS
___________________

Pueden instalarse todas las bibliotecas y utilidades requeridas usando las
instrucciones de [install-unix](https://github.com/jburguete/install-unix).

Este programa ha sido construido y probado en los siguientes sistemas
operativos:
* Arch Linux
* Debian Linux 11
* Devuan Linux 4
* Dragonfly BSD 6.4
* Fedora Linux 37
* FreeBSD 13.1
* Gentoo Linux
* Linux Mint DE 5
* MacOS Catalina + Homebrew
* Manjaro Linux
* Microsoft Windows 10 + MSYS2
* NetBSD 9.3
* OpenBSD 7.2
* OpenInidiana Hipster
* OpenSUSE Linux 15.4
* Ubuntu Linux 22.10

En sistemas Microsoft Windows hay que instalar
[MSYS2](http://sourceforge.net/projects/msys2) además de las bibliotecas y
utilidades requeridas. Puede seguir instrucciones detalladas en el tutorial
[install-unix](https://github.com/jburguete/install-unix/blob/master/tutorial.pdf).

En NetBSD 9.3, para usar la última versión del compilador GCC, hay que hacer
primero en el terminal:
> $ export PATH="/usr/pkg/gcc12/bin:$PATH"

Si se quiere hacer permanente tambien se puede añadir en el fichero ".profile"
de la carpeta raíz del usuario la línea:
> PATH="/usr/pkg/gcc12/bin:$PATH"

En OpenBSD 7.2 hay que hacer antes en el terminal:
> $ export AUTOCONF\_VERSION=2.69 AUTOMAKE\_VERSION=1.16

INSTRUCCIONES DE CONSTRUCCIÓN
_____________________________

1. Descárgase la última versión de la biblioteca:
> $ git clone https://github.com/jburguete/jb

2. Si sólo se requiere para aplicaciones de terminal compile los códigos fuente
   con el script:
> $ cd 5.3.3
> $ ./build\_wihtout_\gui.sh

2. O si se quiere interfaz gráfica compile los códigos fuente con el script:
> $ cd 5.3.3
> $ ./build.sh

ENLAZANDO LA BIBLIOTECA EN OTROS PROGRAMAS
---------------------------------------------

1. Enlácese la última versión en una carpeta jb p.ej.:
> $ cd CARPETA\_DE\_SU\_PROGRAMA
>
> $ ln -s RUTA\_DE\_LA\_BIBLIOTECA\_JB/5.3.3 jb

2. Incluya el fichero de configuración y las utilidades requeridas en su código
   fuente p.ej.:
> \#include "jb/src/jb\_config.h"
>
> \#include "jb/src/jb\_math.h"
>
> \#include "jb/src/jb\_win.h"
>
> \#include "jb/src/jb\_xml.h"

3. Copie las bibliotecas usadas en la carpeta de su ejecutable (ficheros
   libjb\*.so en sistemas UNIX, ficheros libjb\*.dll en sistemas Microsoft
   Windows)

4. Enlace las bibliotecas compartidas en su ejecutable p.ej.: 
> $ gcc -DJBW=2 -DJBM\_PRECISION=2 SU\_CÓDIGO\_FUENTE.c
> -o SU\_FICHERO\_EJECUTABLE -L. -Wl,-rpath=. -ljbwin-2 -ljbxml-2 -ljbm-2
> -ljb-2 \`pkg-config --cflags --libs glib-2.0 libxml-2.0 gtk+-3.0 glew\`
