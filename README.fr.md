JB (version 11.3.15)
==================

:gb:[english](README.md) :es:[español](README.es.md)
:fr:[français](README.fr.md)

Une bibliothèque avec fonctions utiles de mathématiques, graphiques, widgets et
entrée/sortie XML et JSON.

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
* build\_without\_gui.sh: script de construction pour applications de terminal.
* configure.ac: pour configurer la construction du Makefile.
* Makefile.in: modèle pour générer le Makefile.
* Doxyfile: pour configurer la construction de la documentation.
* test.png: figure pour vérifier les fonctions graphiques.
* test\_data: fichier de données pour la vérification.
* test\*.c: fichier source de vérification.
* locale/\*/LC\_MESSAGES/jb.po: fichiers de traduction.

CONSTRUCTION DE LA BIBLIOTHÈQUE
-------------------------------

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

Obligatoire si les outils jb/xml sont inclus:
* [libxml](http://xmlsoft.org) pour travailler avec fichiers XML.

Obligatoire si les outils jb/json sont inclus:
* [json-glib](https://gitlab.gnome.org/GNOME/json-glib) pour travailler avec
  fichiers JSON.

Obligatoire si les outils jb/win sont inclus et on compile en utilisant
l'option -DJBW=2.
* [png](http://libpng.sourceforge.net) pour travailler avec fichiers PNG.
* [gtk](http://www.gtk.org) pour travailler avec fenêtres interactives.
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

SISTÈMES D'EXPLOITATION
_______________________

On peut installer tous les bibliothèques et les outils requis en utilisant les
instructions en [install-unix](https://github.com/jburguete/install-unix).

Ce programme a été construit et verifié avec les suivants systèmes
d'exploitation:
* Arch Linux
* Debian 12 (Linux)
* Devuan Linux 5
* Dragonfly BSD 6.4.1
* Fedora Linux 42
* FreeBSD 14.2
* Gentoo Linux
* Linux Mint DE 6
* MacOS Sequoia + Homebrew
* Manjaro Linux
* Microsoft Windows 11 + MSYS2
* NetBSD 10.1
* OpenBSD 7.7
* OpenInidiana Hipster
* OpenSUSE Linux 15.6
* Ubuntu Linux 25.04

Avec systèmes Microsoft Windows on doit installer
[MSYS2](http://sourceforge.net/projects/msys2) et en plus les bibliothèques et
les outils requis. On peut suivre les instructions détaillées dans le
didacticiel
[install-unix](https://github.com/jburguete/install-unix/blob/master/tutorial.pdf).

Avec NetBSD 10.1, pour utiliser le derniére version du compilateur GCC, il faut
faire avant dans le terminal:
> $ export PATH="/usr/pkg/gcc12/bin:$PATH"

Pour faire le changement permanent on peut ajouter à la dernière ligne du
fichier ".profile" dans le répertoire racine du utilisateur:
> PATH="/usr/pkg/gcc12/bin:$PATH"

Avec OpenBSD 7.7 on doit faire avant dans le terminal:
> $ export AUTOCONF\_VERSION=2.69 AUTOMAKE\_VERSION=1.16

INSTRUCTIONS DE CONSTRUCTION
____________________________

1. Téléchargez la dernière version de la bibliothèque:
> $ git clone https://github.com/jburguete/jb

2. Pour applications de terminal compilez les codes source avec:
> $ cd 11.3.15
> $ ./build\_wihtout_\gui.sh

2. Pour applications graphiques compilez les codes source avec:
> $ cd 11.3.15
> $ ./build.sh

LIEN LA BIBLIOTHÈQUE DANS AUTRES PROGRAMMES
-------------------------------------------

1. Liez la dernière version dans une répertoire jb, p.ex.:
> $ cd RÉPERTOIRE\_DE\_VÔTRE\_PROGRAMME
>
> $ ln -s CHEMIN\_DE\_LA\_BIBLIOTHÈQUE\_JB/11.3.15 jb

2. Incluez le fichier de configuration et les outils requis dans votre code
   source, p.ex.:
> \#include "jb/src/math.h"
>
> \#include "jb/src/win.h"
>
> \#include "jb/src/xml.h"

3. Copiez les bibliothèques utilisées dans la répertoire de votre exécutable
(fichiers libjb\*.so pour sistèmes UNIX, fichiers libjb\*.dll pour sistèmes
Microsoft Windows).

4. Liez les bibliothèques utilisées dans votre exécutable, p.ex.:
> $ gcc -DJBW=2 -DJBM\_PRECISION=2 VÔTRE\_CODE\_SOURCE.c
> -o VÔTRE\_FICHIER\_EXÉCUTABLE -L. -Wl,-rpath=. -ljbwin-2 -ljbxml-2 -ljbm-2
> -ljb-2 \`pkg-config --cflags --libs glib-2.0 libxml-2.0 gtk+-3.0 glew\`
