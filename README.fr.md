JB (version 2.0.1)
==================

:gb:[english](README.md) :es:[español](README.es.md)
:fr:[français](README.fr.md)

Une bibliothèque avec fonctions utiles de mathématiques, graphiques, widgets et
entrée/sortie XML.

AUTEURS
-------

* Javier Burguete Tolosa
  [jburguete@eead.csic.es](mailto:jburguete@eead.csic.es).

FICHIERS
--------

* TODO: liste de tâches pour réaliser.
* jb\*.h: fichiers de code d'en-tête.
* jb\*.c: fichiers de code source.
* Doxyfile: fichero de configuration pour générer documentation doxygen.
* build.sh: script de construction par défaut.
* configure.ac: pour configurer la construction du Makefile.
* Makefile.in: modèle pour générer le Makefile.
* Doxyfile: pour configurer la construction de la documentation.
* test.png: figure pour vérifier les fonctions graphiques.
* text\*.c: fichier source de vérification.
* locale/\*/LC\_MESSAGES/jb.po: fichiers de traduction.

CONSTRUCTION DE LA BIBLIOTHÈQUE DANS AUTRES PROGRAMMES
------------------------------------------------------

BIBLIOTHÈQUES ET OUTILS REQUIS
______________________________

Obligatoire:
* [gcc](https://gcc.gnu.org) o [clang](http://clang.llvm.org) pour compiler le
  code source.
* [make](http://www.gnu.org/software/make) pour construire le fichier
  executable.
* [autoconf](http://www.gnu.org/software/autoconf) pour générer le Makefile en
  differents systèmes d'exploitation.
* [automake](http://www.gnu.org/software/automake) pour détecter le système
  d'exploitation.
* [pkg-config](http://www.freedesktop.org/wiki/Software/pkg-config) pour trouver
  les bibliothèques pour compiler.
* [glib](https://developer.gnome.org/glib) outils étendues de C pour travailler
  avec données, listes, fichiers mappés, expressions régulières, utiliser
  multiprocesseurs en machines à mémoire partagée, ...
* [gettext](http://www.gnu.org/software/gettext) pour travailler avec differents
  codes et langues internationaux.

Optionnel si les outils jb\_xml sont inclus:
* [libxml](http://xmlsoft.org) pour travailler avec fichiers XML.

Optionnel si les outils jb\_win sont inclus et on compile en utilisent l'option
-DJBW=2.
* [png](http://libpng.sourceforge.net) pour travailler avec fichiers PNG.
* [gtk3](http://www.gtk.org) pour travailler avec fenêtres interactives.
* [glew](http://glew.sourceforge.net) functions OpenGL de haut niveau.

Optionnel pour construire la documentation:
* [doxygen](http://www.stack.nl/~dimitri/doxygen) format de commentaires
  standard pour générer la documentation.
* [latex](https://www.latex-project.org/) pour construire les manuels PDF.

OPTIONS DE COMPILATION
______________________

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
> $ export AUTOCONF\_VERSION=2.69 AUTOMAKE\_VERSION=1.16

This software has been built and tested in the following operative systems:
* Debian 9 (Linux, kFreeBSD and Hurd)
* DragonFly BSD 5.2
* Dyson Illumos
* Fedora Linux 29
* FreeBSD 11.2
* Manjaro Linux
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
> $ cd CARPETA\_DE\_SU\_PROGRAMA
>
> $ ln -s RUTA\_DE\_LA\_BIBLIOTECA\_JB/2.0.1 jb

3. Incluir el fichero de configuración y las utilidades requeridas en su código
   fuente p.e.:
> \#include "jb/jb\_config.h"
>
> \#include "jb/jb\_math.h"
>
> \#include "jb/jb\_win.h"
>
> \#include "jb/jb\_xml.h"

CONSTRUCCIÓN ESTÁTICA
_____________________

4. Compilar los códigos fuente de las utilidades usadas p.e.:
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

5. Enlazar los ficheros objeto de las utilidades usadas en su ejecutable p.e.:
> $ gcc -DJBW=2 -DJBM\_PRECISION=2 SU\_CÓDIGO\_FUENTE.c jb\_def.o jb\_math.o
> jb\_win.o jb\_xml.o -o SU\_FICHERO\_EJECUTABLE
> \`pkg-config --cflags glib-2.0 libxml-2.0 gtk+-3.0 glew\`

Nótese que su código podría también necesitar bibliotecas adicionales en el
comando "pkg-config"

Nótese asimismo que se puede usar otro nivel de precisión (JBM\_PRECISION).

CONSTRUCCIÓN DINÁMICA
_____________________

4. Compilar los códigos fuente de las utilidades usadas con rutas absolutas
   p.e.:
> $ gcc -c -fPIC -DJBW=2 -DJBM\_PRECISION=2 jb/jb\_def.c -o jb\_def.o
> \`pkg-config --cflags glib-2.0 libxml-2.0 gtk+-3.0 glew\`
>
> $ gcc -c -fPIC -DJBW=2 -DJBM\_PRECISION=2 jb/jb\_math.c -o jb\_math.o
> \`pkg-config --cflags glib-2.0 libxml-2.0 gtk+-3.0 glew\`
>
> $ gcc -c -fPIC -DJBW=2 -DJBM\_PRECISION=2 jb/jb\_win.c -o jb\_win.o
> \`pkg-config --cflags glib-2.0 libxml-2.0 gtk+-3.0 glew\`

5. Construir la biblioteca compartida:
> $ gcc -shared -DJBW=2 -DJBM\_PRECISION=2 jb\_def.o jb\_win.o jb\_math.o
> -o libjb.so
> \`pkg-config --cflags glib-2.0 libxml-2.0 gtk+-3.0 glew\`

6. Enlazar la biblioteca compartida en su ejecutable p.e.: 
> $ gcc -DJBW=2 -DJBM\_PRECISION=2 SU\_CÓDIGO\_FUENTE.c
> -o SU\_FICHERO\_EJECUTABLE -L. -Wl,-rpath=. -ljb
> \`pkg-config --cflags glib-2.0 libxml-2.0 gtk+-3.0 glew\`

INSTRUCCIONES PARA HACER EL MANUAL DE REFERENCIA (fichero doc/latex/refman.pdf)
-------------------------------------------------------------------------------

Ejecutar en un terminal:
> $ cd RUTA\_DE\_LA\_BIBLIOTECA\_JB/2.0.1
>
> $ doxygen
>
> $ cd doc/latex
>
> $ make
