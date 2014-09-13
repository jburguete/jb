libs = -lm `pkg-config --cflags --libs glib-2.0`
src = jb_config.h jb_def.h jb_def.c jb_math.h jb_math.c jb_win.h jb_win.c \
	jb_xml.h jb_xml.c

all: test_math test_win doc/latex/refman.pdf

test_math: test_math.c jb_math.h jb_math.c makefile
	gcc -g -Wall test_math.c jb_math.c jb_def.c -o test_math $(libs) -DJBW=1

test_win: test_win.c jb_win.h jb_win.c makefile
	gcc -g -Wall test_win.c jb_win.c jb_math.c jb_def.c -o test_win \
		-lm -lglut `pkg-config --cflags --libs gtk+-3.0 gl glu` \
		-DJBW=2 -DJBW_DRAW=2 -DJBW_GRAPHIC=3

doc/latex/refman.pdf: $(src) Doxyfile makefile
	doxygen
	cd doc/latex; pdflatex refman; pdflatex refman;
