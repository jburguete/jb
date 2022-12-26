JB (version 3.1.4)
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
* src\*.h: fichiers de code d'en-tête.
* src\*.c: fichiers de code source.
* Doxyfile: fichier de configuration pour générer documentation doxygen.
* build.sh: script de construction par défaut.
* configure.ac: pour configurer la construction du Makefile.
* Makefile.in: modèle pour générer le Makefile.
* Doxyfile: pour configurer la construction de la documentation.
* test.png: figure pour vérifier les fonctions graphiques.
* test\*.c: fichier source de vérification.
* locale/\*/LC\_MESSAGES/jb.po: fichiers de traduction.

CONSTRUCTION DE LA BIBLIOTHÈQUE DANS AUTRES PROGRAMMES
------------------------------------------------------

BIBLIOTHÈQUES ET OUTILS REQUIS
______________________________

Obligatoire:
* [gcc](https://gcc.gnu.org) ou [clang](http://clang.llvm.org) pour compiler le
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

Optionnel pour détecter les characteristiques du processeur:
* [libgtop](https://github.com/GNOME/libgtop) pour obtenir le nombre de
  processeurs.

Obligatoire si les outils jb\_xml sont inclus:
* [libxml](http://xmlsoft.org) pour travailler avec fichiers XML.

Obligatoire si les outils jb\_win sont inclus et on compile en utilisant
l'option -DJBW=2.
* [png](http://libpng.sourceforge.net) pour travailler avec fichiers PNG.
* [gtk3](http://www.gtk.org) pour travailler avec fenêtres interactives.
* [glew](http://glew.sourceforge.net) functions OpenGL de haut niveau.

On peut utiliser les bibliothèques graphiques suivantes comme alternative au
widget GtkGLArea de la bibliothèque GTK pour interagir avec OpenGL pour dessiner
graphiques:
* [freeglut](http://freeglut.sourceforge.net)
* [sdl2](https://www.libsdl.org)
* [glfw](http://www.glfw.org)

Optionnel pour construire la documentation:
* [doxygen](http://www.stack.nl/~dimitri/doxygen) format de commentaires
  standard pour générer la documentation.
* [latex](https://www.latex-project.org/) pour construire les manuels PDF.

OPTIONS DE COMPILATION
______________________

Pour compiler la bibliothèque JB on doit définir l'option JBW. Il y a 2
possibilités:
* -DJBW=1: pour interfaces de terminal.
* -DJBW=2: pour interfaces graphiques.

On doit aussi définir l'option de niveau de précision:
* -DJBM\_PRECISION=1: tous les variables mathématiques sont définies comme
  float.
* -DJBM\_PRECISION=2: les variables mathématiques sont définies comme float ou
  double.
* -DJBM\_PRECISION=3: tous les variables mathématiques sont définies comme
  double.
* -DJBM\_PRECISION=4: les variables mathématiques sont définies comme double ou
  long double.
* -DJBM\_PRECISION=5: tous les variables mathématiques sont définies comme
  long double.

Les bibliothèques construites par défaut utilisent le niveau de précision 2.

SISTÈMES D'EXPLOITATION
_______________________

On peut installer tous les bibliothèques et les outils requis en utilisant les
instructions en [install-unix](https://github.com/jburguete/install-unix).

Ce programme a été construit et prouvé avec les suivants systèmes
d'exploitation:
* Arch Linux
* Debian 11 (Linux)
* Devuan Linux 4
* Dragonfly BSD 6.2.2
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

Avec systèmes Microsoft Windows on doit installer
[MSYS2](http://sourceforge.net/projects/msys2) et en plus les bibliothèques et
les outils requis. On peut suivre les instructions détaillées dans le
didacticiel
[install-unix](https://github.com/jburguete/install-unix/blob/master/tutorial.pdf).

Avec NetBSD 9.3, pour utiliser le derniére version du compilateur GCC, il faut
faire avant dans le terminal:
> $ export PATH="/usr/pkg/gcc12/bin:$PATH"

Pour faire le changement permanent on peut ajouter à la dernière ligne di
fichier ".profile" dans le répertoire racine du utilisateur:
> PATH="/usr/pkg/gcc12/bin:$PATH"

Avec OpenBSD 7.2 on doit faire avant dans le terminal:
> $ export AUTOCONF\_VERSION=2.69 AUTOMAKE\_VERSION=1.16

INSTRUCTIONS DE CONSTRUCTION COMMUNES
_____________________________________

1. Téléchargez la dernière version de la bibliothèque:
> $ git clone https://github.com/jburguete/jb

2. Liez la dernière version dans une répertoire jb, p.ex.:
> $ cd RÉPERTOIRE\_DE\_VÔTRE\_PROGRAMME
>
> $ ln -s CHEMIN\_DE\_LA\_BIBLIOTHÈQUE\_JB/3.1.4 jb

3. Incluez le fichier de configuration et les outils requis dans vôtre code
  source p.ex.:
> \#include "jb/jb\_config.h"
>
> \#include "jb/jb\_math.h"
>
> \#include "jb/jb\_win.h"
>
> \#include "jb/jb\_xml.h"

CONSTRUCTION STATIQUE
_____________________

4. Compilez les codes source des outils utilisés p.ex.:
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

5. Liez les fichiers objet des outils utilisés dans vôtre executable p.ex.:
> $ gcc -DJBW=2 -DJBM\_PRECISION=2 VÔTRE\_CODE\_SOURCE.c jb\_def.o jb\_math.o
> jb\_win.o jb\_xml.o -o VÔTRE\_FICHIER\_EXECUTABLE
> \`pkg-config --cflags glib-2.0 libxml-2.0 gtk+-3.0 glew\`

Notez que vôtre code peut aussi avoir besoin de bibliotèques additionnelles au
command "pkg-config".

Notez aussi qu'on peut utiliser un autre niveau de précision (JBM\_PRECISION).

CONSTRUCTION DYNAMIQUE
_______________________

4. Compilez les codes source des outils utilisés p.ex. avec chemins absolus
  p.ex.:
> $ gcc -c -fPIC -DJBW=2 -DJBM\_PRECISION=2 jb/jb\_def.c -o jb\_def.o
> \`pkg-config --cflags glib-2.0 libxml-2.0 gtk+-3.0 glew\`
>
> $ gcc -c -fPIC -DJBW=2 -DJBM\_PRECISION=2 jb/jb\_math.c -o jb\_math.o
> \`pkg-config --cflags glib-2.0 libxml-2.0 gtk+-3.0 glew\`
>
> $ gcc -c -fPIC -DJBW=2 -DJBM\_PRECISION=2 jb/jb\_win.c -o jb\_win.o
> \`pkg-config --cflags glib-2.0 libxml-2.0 gtk+-3.0 glew\`

5. Construisez la bibliothèqe partagée:
> $ gcc -shared -DJBW=2 -DJBM\_PRECISION=2 jb\_def.o jb\_win.o jb\_math.o
> -o libjb.so
> \`pkg-config --cflags glib-2.0 libxml-2.0 gtk+-3.0 glew\`

6. Liez la bibliothèque partagée dans vôtre executable p.ex.:
> $ gcc -DJBW=2 -DJBM\_PRECISION=2 VÔTRE\_CODE\_SOURCE.c
> -o VÔTRE\_FICHIER\_EXECUTABLE -L. -Wl,-rpath=. -ljb
> \`pkg-config --cflags glib-2.0 libxml-2.0 gtk+-3.0 glew\`
