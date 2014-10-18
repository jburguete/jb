/* JB - A library with useful mathematical, XML, GTK+ and OpenGL functions.
 *
 * Copyright 2005-2014, Javier Burguete Tolosa.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 
 * 	1. Redistributions of source code must retain the above copyright notice,
 * 		this list of conditions and the following disclaimer.
 * 
 * 	2. Redistributions in binary form must reproduce the above copyright notice,
 * 		this list of conditions and the following disclaimer in the
 * 		documentation and/or other materials provided with the distribution.
 * 
 * THIS SOFTWARE IS PROVIDED BY Javier Burguete Tolosa ``AS IS'' AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO
 * EVENT SHALL Javier Burguete Tolosa OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * \file jb_win.h
 * \brief Header file with useful display functions.
 * \author Javier Burguete Tolosa.
 * \copyright Copyright 2005-2014, Javier Burguete Tolosa.
 */
#ifndef JB_WIN__H
#define JB_WIN__H 1

#include "jb_math.h"

#if JBW == JBW_NO

static inline void _jbw_show_message(char *title, char *message)
{printf("%s: %s\n", title, message);}
#if INLINE_JBW_SHOW_MESSAGE
	#define jbw_show_message _jbw_show_message
#else
	void jbw_show_message(char*, char*);
#endif

static inline void _jbw_show_error(char *message)
{jbw_show_message(gettext("Error!"), message);}
#if INLINE_JBW_SHOW_ERROR
	#define jbw_show_error _jbw_show_error
#else
	void jbw_show_error(char*);
#endif

static inline void _jbw_show_warning(char *message)
{jbw_show_message(gettext("Warning!"), message);}
#if INLINE_JBW_SHOW_WARNING
	#define jbw_show_warning _jbw_show_warning
#else
	void jbw_show_warning(char*);
#endif

#elif JBW == JBW_GTK

#include <gtk/gtk.h>

#if JBW_DRAW == JBW_DRAW_CAIRO
	#include <cairo.h>
#elif JBW_DRAW == JBW_DRAW_OPENGL
	#include <GL/gl.h>
	#include <GL/freeglut.h>
	#include <png.h>
#endif

#if JBW_GRAPHIC == JBW_GRAPHIC_CLUTTER
	#include <clutter/clutter.h>
	#include <clutter-gtk/clutter-gtk.h>
#endif

#if GTK_MAJOR_VERSION < 3

#define gtk_widget_get_allocated_width(widget) widget->allocation.width
#define gtk_widget_get_allocated_height(widget) widget->allocation.height

#if GTK_MINOR_VERSION < 24

typedef GtkComboBox GtkComboBoxText;
#define GTK_COMBO_BOX_TEXT GTK_COMBO_BOX
#define gtk_combo_box_text_new gtk_combo_box_new_text
#define gtk_combo_box_text_append_text gtk_combo_box_append_text
#define gtk_combo_box_text_prepend_text gtk_combo_box_prepend_text
#define gtk_combo_box_text_insert_text gtk_combo_box_insert_text
#define gtk_combo_box_text_remove gtk_combo_box_remove_text
#define gtk_combo_box_text_get_active_text gtk_combo_box_get_active_text

#endif

static inline void gtk_combo_box_text_remove_all(GtkComboBoxText *combo)
{
	do
	{
		gtk_combo_box_set_active(GTK_COMBO_BOX(combo), 0);
		if (gtk_combo_box_get_active(GTK_COMBO_BOX(combo))) break;
		gtk_combo_box_remove_text(GTK_COMBO_BOX(combo), 0);
	}
	while (1);
}

#endif

extern GtkWindow *window_parent;

#if JBW_GRAPHIC == JBW_GRAPHIC_GLUT
extern GQueue jbw_graphic_queue;
extern void (*jbw_graphic_draw)();
#endif

static inline void _jbw_combo_box_set_strings
	(GtkComboBoxText *combo, char **strings, int n)
{
	int i;
	gtk_combo_box_text_remove_all(combo);
	for (i=0; i<n; ++i) gtk_combo_box_text_append_text(combo, strings[i]);
}

#if INLINE_JBW_COMBO_BOX_SET_STRINGS
	#define jbw_combo_box_set_strings _jbw_combo_box_set_strings
#else
	void jbw_combo_box_set_strings(GtkComboBoxText*, char **, int);
#endif

static inline GtkComboBoxText*
	_jbw_combo_box_new_with_strings(char **string, int n)
{
	int i;
	GtkComboBoxText *combo=(GtkComboBoxText*)gtk_combo_box_text_new();
	if (!combo) return 0;
	for (i=0; i<n; ++i) gtk_combo_box_text_append_text(combo, string[i]);
	gtk_combo_box_set_active(GTK_COMBO_BOX(combo), 0);
	return combo;
}

#if INLINE_JBW_COMBO_BOX_NEW_WITH_STRINGS
	#define jbw_combo_box_new_with_strings _jbw_combo_box_new_with_strings
#else
	GtkComboBoxText* jbw_combo_box_new_with_strings(char**, int);
#endif

#define jbw_signal_connect_swapped_after(instance, detailed_signal, c_handler, \
	data) \
    	g_signal_connect_data((instance), (detailed_signal), (c_handler), \
			(data), 0, G_CONNECT_SWAPPED | G_CONNECT_AFTER)

#define JBWButton GtkButton

#define jbw_button_ok_new() \
	((JBWButton*)gtk_button_new_from_stock(GTK_STOCK_OK))
#define jbw_button_cancel_new() \
	((JBWButton*)gtk_button_new_from_stock(GTK_STOCK_CANCEL))

static inline JBWButton* _jbw_button_new_from_stock(char *image)
{
	register JBWButton *button;
	button=(JBWButton*)gtk_button_new();
	if (image) gtk_container_add((GtkContainer*)button,
		(GtkWidget*)gtk_image_new_from_stock(image,
			GTK_ICON_SIZE_SMALL_TOOLBAR));
	return button;
}

#if INLINE_JBW_BUTTON_NEW_FROM_STOCK
	#define jbw_button_new_from_stock _jbw_button_new_from_stock
#else
	JBWButton* jbw_button_new_from_stock(char*);
#endif

static inline void _jbw_array_radio_buttons_set_active
	(GtkRadioButton **array, int n, int is_active)
{gtk_toggle_button_set_active((GtkToggleButton*)array[n], is_active);}

#if INLINE_JBW_ARRAY_RADIO_BUTTONS_SET_ACTIVE
	#define jbw_array_radio_buttons_set_active \
		_jbw_array_radio_buttons_set_active
#else
	void jbw_array_radio_buttons_set_active(GtkRadioButton**, int, int);
#endif

static inline int _jbw_array_radio_buttons_get_active(GtkRadioButton **array)
{
	register int i=0;
	while (!gtk_toggle_button_get_active((GtkToggleButton*)array[i])) ++i;
	return i;
}

#if INLINE_JBW_ARRAY_RADIO_BUTTONS_GET_ACTIVE
	#define jbw_array_radio_buttons_get_active \
		_jbw_array_radio_buttons_get_active
#else
	int jbw_array_radio_buttons_get_active(GtkRadioButton**);
#endif

typedef GtkEntry JBWIntEntry;
#define jbw_int_entry_new (JBWIntEntry*)gtk_entry_new

static inline void _jbw_int_entry_set_value_with_format
	(JBWIntEntry *entry, char *format, long value)
{
	char buffer[64];
	snprintf(buffer, 64, format, value);
	gtk_entry_set_text((GtkEntry*)entry, buffer);
}

#if INLINE_JBW_INT_ENTRY_SET_VALUE_WITH_FORMAT
	#define jbw_int_entry_set_value_with_format \
		_jbw_int_entry_set_value_with_format
#else
	void jbw_int_entry_set_value_with_format(JBWIntEntry*, char*, long);
#endif

static inline void _jbw_int_entry_set_value(JBWIntEntry *entry, long value)
{
	jbw_int_entry_set_value_with_format(entry, "%ld", value);
}

#if INLINE_JBW_INT_ENTRY_SET_VALUE
	#define jbw_int_entry_set_value _jbw_int_entry_set_value
#else
	void jbw_int_entry_set_value(JBWIntEntry*, long);
#endif

static inline long _jbw_int_entry_get_value(JBWIntEntry *entry)
{
	long value;
	sscanf(gtk_entry_get_text((GtkEntry*)entry), "%ld", &value);
	return value;
}

#if INLINE_JBW_INT_ENTRY_GET_VALUE
	#define jbw_int_entry_get_value _jbw_int_entry_get_value
#else
	long jbw_int_entry_get_value(JBWIntEntry*);
#endif

typedef GtkEntry JBWFloatEntry;
#define jbw_float_entry_new (JBWFloatEntry*)gtk_entry_new

static inline void _jbw_float_entry_set_value_with_format
	(JBWFloatEntry *entry, char *format, JBDOUBLE value)
{
	char buffer[64];
	snprintf(buffer, 64, format, value);
	gtk_entry_set_text((GtkEntry*)entry, buffer);
}

#if INLINE_JBW_FLOAT_ENTRY_SET_VALUE_WITH_FORMAT
	#define jbw_float_entry_set_value_with_format \
		_jbw_float_entry_set_value_with_format
#else
	void jbw_float_entry_set_value_with_format
		(JBWFloatEntry*, char*, JBDOUBLE);
#endif

static inline void _jbw_float_entry_set_value
	(JBWFloatEntry *entry, JBDOUBLE value)
{
	jbw_float_entry_set_value_with_format(entry, FPL, value);
}

#if INLINE_JBW_FLOAT_ENTRY_SET_VALUE
	#define jbw_float_entry_set_value _jbw_float_entry_set_value
#else
	void jbw_float_entry_set_value(JBWFloatEntry*, JBDOUBLE);
#endif

static inline JBDOUBLE _jbw_float_entry_get_value(JBWFloatEntry *entry)
{
	JBDOUBLE value;
	sscanf(gtk_entry_get_text((GtkEntry*)entry), FRL, &value);
	return value;
}

#if INLINE_JBW_FLOAT_ENTRY_GET_VALUE
	#define jbw_float_entry_get_value _jbw_float_entry_get_value
#else
	JBDOUBLE jbw_float_entry_get_value(JBWFloatEntry*);
#endif

#define JBWMenuItem GtkImageMenuItem

static inline JBWMenuItem* _jbw_menu_item_new(char *string, char *image)
{
	register JBWMenuItem *item;
	if (!string && !image) return (JBWMenuItem*)gtk_separator_menu_item_new();
	item = (JBWMenuItem*)gtk_image_menu_item_new_with_mnemonic(string);
	if (image) gtk_image_menu_item_set_image((GtkImageMenuItem*)item,
		(GtkWidget*)gtk_image_new_from_stock(image, GTK_ICON_SIZE_MENU));
	return item;
}

#if INLINE_JBW_MENU_ITEM_NEW
	#define jbw_menu_item_new _jbw_menu_item_new
#else
	JBWMenuItem* jbw_menu_item_new(char*, char*);
#endif

static inline void
	_jbw_show_message(char *title, char *message, GtkMessageType type)
{
	register GtkMessageDialog *dlg;
	dlg=(GtkMessageDialog*)gtk_message_dialog_new
		(window_parent, GTK_DIALOG_MODAL, type, GTK_BUTTONS_OK, message);
	gtk_window_set_title((GtkWindow*)dlg, title);
	gtk_dialog_run((GtkDialog*)dlg);
	gtk_widget_destroy((GtkWidget*)dlg);
}

#if INLINE_JBW_SHOW_MESSAGE
	#define jbw_show_message _jbw_show_message
#else
	void jbw_show_message(char*, char*, char*);
#endif

static inline void _jbw_show_error(char *message)
{jbw_show_message(gettext("Error!"), message, GTK_MESSAGE_ERROR);}

#if INLINE_JBW_SHOW_ERROR
	#define jbw_show_error _jbw_show_error
#else
	void jbw_show_error(char*);
#endif

static inline void _jbw_show_warning(char *message)
{jbw_show_message(gettext("Warning!"), message, GTK_MESSAGE_WARNING);}

#if INLINE_JBW_SHOW_WARNING
	#define jbw_show_warning _jbw_show_warning
#else
	void jbw_show_warning(char*);
#endif

#if JBW_DRAW == JBW_DRAW_CAIRO

static inline void _jbw_draw_rectangle(cairo_t *cr, double red, double green,
	double blue, double x, double y, double width, double height)
{
	cairo_set_source_rgb(cr, red, green, blue);
	cairo_rectangle(cr, x, y, width, height);
	cairo_stroke(cr);
}

#if INLINE_JBW_DRAW_RECTANGLE
	#define jbw_draw_rectangle _jbw_draw_rectangle
#else
	void jbw_draw_rectangle
		(cairo_t*, double, double, double, double, double, double, double);
#endif

static inline void _jbw_draw_bar(cairo_t *cr, double red, double green,
	double blue, double x, double y, double width, double height)
{
	cairo_set_source_rgb(cr, red, green, blue);
	cairo_rectangle(cr, x, y, width, height);
	cairo_fill(cr);
}

#if INLINE_JBW_DRAW_BAR
	#define jbw_draw_bar _jbw_draw_bar
#else
	void jbw_draw_bar
		(cairo_t*, double, double, double, double, double, double, double);
#endif

static inline void _jbw_draw_clear
	(cairo_t *cr, double red, double green, double blue, double width, double height)
{
	jbw_draw_bar(cr, red, green, blue, 0, 0, width, height);
}

#if INLINE_JBW_DRAW_CLEAR
	#define jbw_draw_clear _jbw_draw_clear
#else
	void jbw_draw_clear(cairo_t*, double, double, double, double, double);
#endif

static inline void _jbw_draw_line
	(cairo_t *cr, double red, double green, double blue, JBFLOAT *x, JBFLOAT *y, int n)
{
	register int i;
	if (!x || !y) return;
	cairo_set_source_rgb(cr, red, green, blue);
	cairo_move_to(cr, x[0], y[0]);
	for (i=0; ++i<n;) cairo_line_to(cr, x[i], y[i]);
	cairo_stroke(cr);
}

#if INLINE_JBW_DRAW_LINE
	#define jbw_draw_line _jbw_draw_line
#else
	void jbw_draw_line(cairo_t*, double, double, double, JBFLOAT*, JBFLOAT*, int);
#endif

static inline void _jbw_draw_linev(cairo_t *cr,
	double red, double green, double blue, void *x, void *y, int size, int n)
{
	register int i;
	if (!x || !y) return;
	cairo_set_source_rgb(cr, red, green, blue);
	cairo_move_to(cr, *((JBFLOAT*)x), -*((JBFLOAT*)y));
	for (i=0; ++i<n;)
	{
		x+=size, y+=size;
		cairo_line_to(cr, *((JBFLOAT*)x), -*((JBFLOAT*)y));
	}
	cairo_stroke(cr);
}

#if INLINE_JBW_DRAW_LINEV
	#define jbw_draw_linev _jbw_draw_linev
#else
	void jbw_draw_linev(cairo_t*, double, double, double, void*, void*, int, int);
#endif

static inline void _jbw_draw_segment_with_limits(cairo_t *cr, double xmin,
	double ymin, double xmax, double ymax, double x1, double y1, double x2, double y2)
{
	double xa, ya, xb, yb, m;
	if (x1 == x2)
	{
		xa=xb=x1;
		ya=fmin(y1, ymax);
		ya=fmax(ya, ymin);
		yb=fmin(y2, ymax);
		yb=fmax(yb, ymin);
	}
	else if (y1 == y2)
	{
		ya=yb=y1;
		xa=fmin(x1, xmax);
		xa=fmax(xa, xmin);
		xb=fmin(x2, xmax);
		xb=fmax(xb, xmin);
	}
	else
	{
		m=(y2-y1)/(x2-x1);
		xa=x1+(ymin-y1)/m;
		if (xa<xmin)
		{
			xa=xmin;
			ya=y1+(xmin-x1)*m;
		}
		else ya=ymin;
		xb=x1+(ymax-y1)/m;
		if (xb>xmax)
		{
			xb=xmax;
			yb=y1+(xmax-x1)*m;
		}
		else yb=ymax;
		if (xa>xb)
		{
			JB_CHANGE(xa, xb, m);
			JB_CHANGE(ya, yb, m);
		}
		if (x1<xa)
		{
			if (x2<xa) return;
			if (x2<xb)
			{
				xb=x2;
				yb=y2;
			}
		}
		else if (x1<xb)
		{
			if (x2>xb)
			{
				xa=x1;
				ya=y1;
			}
			else if (x2>xa)
			{
				xa=x1;
				ya=y1;
				xb=x2;
				yb=y2;
			}
			else
			{
				xb=x1;
				yb=y1;
			}
		}
		else
		{
			if (x2>xb) return;
			if (x2>xa)
			{
				xa=x2;
				ya=y2;
			}
		}
	}
	if ((ya>ymax && yb>ymax) || (ya<ymin && yb<ymin)) return;
	cairo_move_to(cr, xa, ya);
	cairo_line_to(cr, xb, yb);
}

#if INLINE_JBW_DRAW_SEGMENT_WITH_LIMITS
	#define jbw_draw_segment_with_limits _jbw_draw_segment_with_limits
#else
	void jbw_draw_segment_with_limits
		(cairo_t*, double, double, double, double, double, double, double, double);
#endif

static inline void _jbw_draw_line_with_limits(cairo_t *cr,
	double red, double green, double blue,
	double xmin, double ymin, double xmax, double ymax,
	double x1, double y1, double x2, double y2,
	JBFLOAT *x, JBFLOAT *y, int n)
{
	register int i;
	double xx[n], yy[n];
	if (!x || !y) return;
	cairo_set_source_rgb(cr, red, green, blue);
	for (i=0; i<n; ++i)
	{
		xx[i]=jbm_extrapolate(x[i], xmin, xmax, x1, x2);
		yy[i]=jbm_extrapolate(y[i], ymin, ymax, y2, y1);
	}
	for (i=0; ++i<n;) jbw_draw_segment_with_limits
		(cr, x1, y1, x2, y2, xx[i-1], yy[i-1], xx[i], yy[i]);
	cairo_stroke(cr);
}

#if INLINE_JBW_DRAW_LINE_WITH_LIMITS
	#define jbw_draw_line_with_limits _jbw_draw_line_with_limits
#else
	void jbw_draw_line_with_limits(cairo_t*, double, double, double, double, double,
		double, double, double, double, double, double, JBFLOAT*, JBFLOAT*, int);
#endif

static inline void _jbw_draw_line_with_limitsv(cairo_t *cr,
	double red, double green, double blue,
	double xmin, double ymin, double xmax, double ymax,
	double x1, double y1, double x2, double y2,
	void *x, void *y, int size, int n)
{
	register int i;
	double xx[n], yy[n];
	if (!x || !y) return;
	cairo_set_source_rgb(cr, red, green, blue);
	for (i=0; i<n; ++i, x+=size, y+=size)
	{
		xx[i]=jbm_extrapolate(*((JBFLOAT*)x), xmin, xmax, x1, x2);
		yy[i]=jbm_extrapolate(*((JBFLOAT*)y), ymin, ymax, y2, y1);
	}
	for (i=0; ++i<n;) jbw_draw_segment_with_limits
		(cr, x1, y1, x2, y2, xx[i-1], yy[i-1], xx[i], yy[i]);
	cairo_stroke(cr);
}

#if INLINE_JBW_DRAW_LINE_WITH_LIMITSV
	#define jbw_draw_line_with_limitsv _jbw_draw_line_with_limitsv
#else
	void jbw_draw_line_with_limitsv(cairo_t*, double, double, double, double,
		double, double, double, double, double, double, double, void*, void*, int, int);
#endif

static inline void _jbw_draw_lines_with_limits
(
	cairo_t *cr,
	double red1, double green1, double blue1,
	double red2, double green2, double blue2,
	double xmin, double ymin, double xmax, double ymax,
	double x1, double y1, double x2, double y2,
	JBFLOAT *x, JBFLOAT *y, JBFLOAT *yy, int n
)
{
	jbw_draw_line_with_limits
		(cr, red1, green1, blue1, xmin, ymin, xmax, ymax, x1, y1, x2, y2, x, y, n);
	jbw_draw_line_with_limits
		(cr, red2, green2, blue2, xmin, ymin, xmax, ymax, x1, y1, x2, y2, x, yy, n);
}

#if INLINE_JBW_DRAW_LINES_WITH_LIMITS
	#define jbw_draw_lines_with_limits _jbw_draw_lines_with_limits
#else
	void jbw_draw_lines_with_limits(cairo_t*, double, double, double, double, double,
		double, double, double, double, double, double, double, double, double,
		JBFLOAT*, JBFLOAT*, JBFLOAT*, int);
#endif

static inline void _jbw_draw_lines_with_limitsv
(
	cairo_t *cr,
	double red1, double green1, double blue1,
	double red2, double green2, double blue2,
	double xmin, double ymin, double xmax, double ymax,
	double x1, double y1, double x2, double y2,
	void *x, void *y, void *yy, int size, int n
)
{
	jbw_draw_line_with_limitsv
		(cr, red1, green1, blue1, xmin, ymin, xmax, ymax, x1, y1, x2, y2, x, y, size, n);
	jbw_draw_line_with_limitsv
		(cr, red2, green2, blue2, xmin, ymin, xmax, ymax, x1, y1, x2, y2, x, yy, size, n);
}

#if INLINE_JBW_DRAW_LINES_WITH_LIMITSV
	#define jbw_draw_lines_with_limitsv _jbw_draw_lines_with_limitsv
#else
	void jbw_draw_lines_with_limitsv(cairo_t*, double, double, double, double,
		double, double, double, double, double, double, double, double, double, double,
		void*, void*, void*, int, int);
#endif

static inline void _jbw_draw_segment
	(cairo_t *cr, double red, double green, double blue, JBFLOAT *x, JBFLOAT *y, int n)
{
	register int i;
	if (!x || !y || n<2) return;

	cairo_set_source_rgb(cr, red, green, blue);
	cairo_move_to(cr, x[0], y[0]);
	cairo_line_to(cr, x[1], y[1]);
	for (i=2; i<n-1; ++i)
	{
		cairo_move_to(cr, x[i], y[i]);
		++i;
		cairo_line_to(cr, x[i], y[i]);
	}
	cairo_stroke(cr);
}

#if INLINE_JBW_DRAW_SEGMENT
	#define jbw_draw_segment _jbw_draw_segment
#else
	void jbw_draw_segment(cairo_t*, double, double, double, JBFLOAT*, JBFLOAT*, int);
#endif

static inline void _jbw_draw_string(cairo_t *cr, char *string, double x, double y)
{
	if (!string) return;
	cairo_move_to(cr, x, y);
	cairo_show_text(cr, string);
}

#if INLINE_JBW_DRAW_STRING
	#define jbw_draw_string _jbw_draw_string
#else
	void jbw_draw_string(cairo_t*, char*, double, double);
#endif

#elif JBW_DRAW == JBW_DRAW_OPENGL

static inline void _jbw_draw_rectanglef
	(float red, float green, float blue, float x1, float y1, float x2, float y2)
{
	glColor3f(red, green, blue);
	glBegin(GL_LINE_LOOP);
		glVertex2f(x1, y1);
		glVertex2f(x2, y1);
		glVertex2f(x2, y2);
		glVertex2f(x1, y2);
	glEnd();
}

#if INLINE_JBW_DRAW_RECTANGLEF
	#define jbw_draw_rectanglef _jbw_draw_rectanglef
#else
	void jbw_draw_rectanglef(float, float, float, float, float, float, float);
#endif

static inline void _jbw_draw_rectangled
	(float red, float green, float blue, double x1, double y1, double x2, double y2)
{
	glColor3f(red, green, blue);
	glBegin(GL_LINE_LOOP);
		glVertex2d(x1, y1);
		glVertex2d(x2, y1);
		glVertex2d(x2, y2);
		glVertex2d(x1, y2);
	glEnd();
}

#if INLINE_JBW_DRAW_RECTANGLED
	#define jbw_draw_rectangled _jbw_draw_rectangled
#else
	void jbw_draw_rectangled(float, float, float, double, double, double, double);
#endif

static inline void _jbw_draw_clear(float red, float green, float blue, float alpha)
{
	glClearColor(red, green, blue, alpha);
	glClear(GL_COLOR_BUFFER_BIT);
}

#if INLINE_JBW_DRAW_CLEAR
	#define jbw_draw_clear _jbw_draw_clear
#else
	void jbw_draw_clear(float, float, float, float);
#endif

static inline void _jbw_draw_pointsf
	(float red, float green, float blue, JBFLOAT *x, JBFLOAT *y, int n)
{
	register int i;
	if (!x || !y) return;
	glColor3f(red, green, blue);
	glBegin(GL_POINTS);
		for (i=n; --i>=0;) glVertex2f(x[i], y[i]);
	glEnd();
}

#if INLINE_JBW_DRAW_POINTSF
	#define jbw_draw_pointsf _jbw_draw_pointsf
#else
	void jbw_draw_pointsf(float, float, float, JBFLOAT*, JBFLOAT*, int);
#endif

static inline void _jbw_draw_pointsd
	(float red, float green, float blue, JBFLOAT *x, JBFLOAT *y, int n)
{
	register int i;
	if (!x || !y) return;
	glColor3f(red, green, blue);
	glBegin(GL_POINTS);
		for (i=n; --i>=0;) glVertex2d(x[i], y[i]);
	glEnd();
}

#if INLINE_JBW_DRAW_POINTSD
	#define jbw_draw_pointsd _jbw_draw_pointsd
#else
	void jbw_draw_pointsd(float, float, float, JBFLOAT*, JBFLOAT*, int);
#endif

static inline void _jbw_draw_linesf
	(float red, float green, float blue, JBFLOAT *x, JBFLOAT *y, int n)
{
	register int i;
	if (!x || !y) return;
	glColor3f(red, green, blue);
	glBegin(GL_LINE_STRIP);
		for (i=n; --i>=0;) glVertex2f(x[i], y[i]);
	glEnd();
}

#if INLINE_JBW_DRAW_LINESF
	#define jbw_draw_linesf _jbw_draw_linesf
#else
	void jbw_draw_linesf(float, float, float, JBFLOAT*, JBFLOAT*, int);
#endif

static inline void _jbw_draw_linesd
	(float red, float green, float blue, JBFLOAT *x, JBFLOAT *y, int n)
{
	register int i;
	if (!x || !y) return;
	glColor3f(red, green, blue);
	glBegin(GL_LINE_STRIP);
		for (i=n; --i>=0;) glVertex2d(x[i], y[i]);
	glEnd();
}

#if INLINE_JBW_DRAW_LINESD
	#define jbw_draw_linesd _jbw_draw_linesd
#else
	void jbw_draw_linesd(float, float, float, JBFLOAT*, JBFLOAT*, int);
#endif

static inline void _jbw_draw_segmentsf
	(float red, float green, float blue, JBFLOAT *x, JBFLOAT *y, int n)
{
	register int i;
	if (!x || !y) return;
	glColor3f(red, green, blue);
	glBegin(GL_LINES);
		for (i=n; --i>=0;) glVertex2f(x[i], y[i]);
	glEnd();
}

#if INLINE_JBW_DRAW_SEGMENTSF
	#define jbw_draw_segmentsf _jbw_draw_segmentsf
#else
	void jbw_draw_segmentsf(float, float, float, JBFLOAT*, JBFLOAT*, int);
#endif

static inline void _jbw_draw_segmentsd
	(float red, float green, float blue, JBFLOAT *x, JBFLOAT *y, int n)
{
	register int i;
	if (!x || !y) return;
	glColor3f(red, green, blue);
	glBegin(GL_LINES);
		for (i=n; --i>=0;) glVertex2d(x[i], y[i]);
	glEnd();
}

#if INLINE_JBW_DRAW_SEGMENTSD
	#define jbw_draw_segmentsd _jbw_draw_segmentsd
#else
	void jbw_draw_segmentsd(float, float, float, JBFLOAT*, JBFLOAT*, int);
#endif

static inline void _jbw_draw_points
(
	float red1, float green1, float blue1, float red2, float green2, float blue2,
	JBDOUBLE xmin, JBDOUBLE xmax, JBDOUBLE ymin, JBDOUBLE ymax,
	JBFLOAT *x, JBFLOAT *y1, JBFLOAT *y2, int n
)
{
	glLoadIdentity();
	glOrtho(xmin, xmax, ymin, ymax, -1., 1.);
	#if JB_PRECISION == 1
		jbw_draw_pointsf(red1, green1, blue1, x, y1, n);
		jbw_draw_pointsf(red2, green2, blue2, x, y2, n);
	#else
		jbw_draw_pointsd(red1, green1, blue1, x, y1, n);
		jbw_draw_pointsd(red2, green2, blue2, x, y2, n);
	#endif	
}

#if INLINE_JBW_DRAW_POINTS
	#define jbw_draw_points _jbw_draw_points
#else
	void jbw_draw_points(float, float, float, float, float, float,
		JBDOUBLE, JBDOUBLE, JBDOUBLE, JBDOUBLE, JBFLOAT*, JBFLOAT*, JBFLOAT*, int);
#endif

static inline void _jbw_draw_pointsvf
	(float red, float green, float blue, void *x, void *y, int size, int n)
{
	register int i;
	if (!x || !y) return;
	glColor3f(red, green, blue);
	glBegin(GL_POINTS);
		for (i=n; --i>=0; x+=size, y+=size)
			glVertex2f(*(JBFLOAT*)x, *(JBFLOAT*)y);
	glEnd();
}

#if INLINE_JBW_DRAW_POINTSVF
	#define jbw_draw_pointsvf _jbw_draw_pointsvf
#else
	void jbw_draw_pointsvf(float, float, float, void*, void*, int, int);
#endif

static inline void _jbw_draw_pointsvd
	(float red, float green, float blue, void *x, void *y, int size, int n)
{
	register int i;
	if (!x || !y) return;
	glColor3f(red, green, blue);
	glBegin(GL_POINTS);
		for (i=n; --i>=0; x+=size, y+=size)
			glVertex2d(*(JBFLOAT*)x, *(JBFLOAT*)y);
	glEnd();
}

#if INLINE_JBW_DRAW_POINTSVD
	#define jbw_draw_pointsvd _jbw_draw_pointsvd
#else
	void jbw_draw_pointsvd(float, float, float, void*, void*, int, int);
#endif

static inline void _jbw_draw_pointsv
(
	float red1, float green1, float blue1, float red2, float green2, float blue2,
	JBDOUBLE xmin, JBDOUBLE xmax, JBDOUBLE ymin, JBDOUBLE ymax,
	void *x, void *y1, void *y2, int size, int n
)
{
	glLoadIdentity();
	glOrtho(xmin, xmax, ymin, ymax, -1., 1.);
	#if JB_PRECISION == 1
		jbw_draw_pointsvf(red1, green1, blue1, x, y1, size, n);
		jbw_draw_pointsvf(red2, green2, blue2, x, y2, size, n);
	#else
		jbw_draw_pointsvd(red1, green1, blue1, x, y1, size, n);
		jbw_draw_pointsvd(red2, green2, blue2, x, y2, size, n);
	#endif	
}

#if INLINE_JBW_DRAW_POINTSV
	#define jbw_draw_pointsv _jbw_draw_pointsv
#else
	void jbw_draw_pointsv(float, float, float, float, float, float,
		JBDOUBLE, JBDOUBLE, JBDOUBLE, JBDOUBLE, void*, void*, void*, int, int);
#endif

static inline void _jbw_draw_lines
(
	float red1, float green1, float blue1, float red2, float green2, float blue2,
	JBDOUBLE xmin, JBDOUBLE xmax, JBDOUBLE ymin, JBDOUBLE ymax,
	JBFLOAT *x, JBFLOAT *y1, JBFLOAT *y2, int n
)
{
	glLoadIdentity();
	glOrtho(xmin, xmax, ymin, ymax, -1., 1.);
	#if JB_PRECISION == 1
		jbw_draw_linesf(red1, green1, blue1, x, y1, n);
		jbw_draw_linesf(red2, green2, blue2, x, y2, n);
	#else
		jbw_draw_linesd(red1, green1, blue1, x, y1, n);
		jbw_draw_linesd(red2, green2, blue2, x, y2, n);
	#endif	
}

#if INLINE_JBW_DRAW_LINES
	#define jbw_draw_lines _jbw_draw_lines
#else
	void jbw_draw_lines(float, float, float, float, float, float,
		JBDOUBLE, JBDOUBLE, JBDOUBLE, JBDOUBLE, JBFLOAT*, JBFLOAT*, JBFLOAT*, int);
#endif

static inline void _jbw_draw_linesvf
	(float red, float green, float blue, void *x, void *y, int size, int n)
{
	register int i;
	if (!x || !y) return;
	glColor3f(red, green, blue);
	glBegin(GL_LINE_STRIP);
		for (i=n; --i>=0; x+=size, y+=size)
			glVertex2f(*(JBFLOAT*)x, *(JBFLOAT*)y);
	glEnd();
}

#if INLINE_JBW_DRAW_LINESVF
	#define jbw_draw_linesvf _jbw_draw_linesvf
#else
	void jbw_draw_linesvf(float, float, float, void*, void*, int, int);
#endif

static inline void _jbw_draw_linesvd
	(float red, float green, float blue, void *x, void *y, int size, int n)
{
	register int i;
	if (!x || !y) return;
	glColor3f(red, green, blue);
	glBegin(GL_LINE_STRIP);
		for (i=n; --i>=0; x+=size, y+=size)
			glVertex2d(*(JBFLOAT*)x, *(JBFLOAT*)y);
	glEnd();
}

#if INLINE_JBW_DRAW_LINESVD
	#define jbw_draw_linesvd _jbw_draw_linesvd
#else
	void jbw_draw_linesvd(float, float, float, void*, void*, int, int);
#endif

static inline void _jbw_draw_linesv
(
	float red1, float green1, float blue1, float red2, float green2, float blue2,
	JBDOUBLE xmin, JBDOUBLE xmax, JBDOUBLE ymin, JBDOUBLE ymax,
	void *x, void *y1, void *y2, int size, int n
)
{
	glLoadIdentity();
	glOrtho(xmin, xmax, ymin, ymax, -1., 1.);
	#if JB_PRECISION == 1
		jbw_draw_linesvf(red1, green1, blue1, x, y1, size, n);
		jbw_draw_linesvf(red2, green2, blue2, x, y2, size, n);
	#else
		jbw_draw_linesvd(red1, green1, blue1, x, y1, size, n);
		jbw_draw_linesvd(red2, green2, blue2, x, y2, size, n);
	#endif	
}

#if INLINE_JBW_DRAW_LINESV
	#define jbw_draw_linesv _jbw_draw_linesv
#else
	void jbw_draw_linesv(float, float, float, float, float, float,
		JBDOUBLE, JBDOUBLE, JBDOUBLE, JBDOUBLE, void*, void*, void*, int, int);
#endif

static inline void _jbw_draw_string
	(char *string, double x, double y, int font_list_base)
{
	if (!string) return;
	glRasterPos2d(x, y);
	glListBase(font_list_base);
	glCallLists(strlen(string), GL_UNSIGNED_BYTE, string);
}

#if INLINE_JBW_DRAW_STRING
	#define jbw_draw_string _jbw_draw_string
#else
	void jbw_draw_string(char*, double, double, int);
#endif

#elif JBW_DRAW == JBW_DRAW_COGL

static inline void _jbw_draw_rectanglef
	(float red, float green, float blue, float x1, float y1, float x2, float y2)
{
	ClutterColor color[1]={256*red, 256*green, 256*blue, 0};
	ClutterStage *stage;
	ClutterActor *actor;
	stage = clutter_stage_get_default();
	clutter_stage_set_color(stage, color);
	actor = clutter_actor_new();
	clutter_container_add(CLUTTER_CONTAINER(stage),
	glBegin(GL_LINE_LOOP);
		glVertex2f(x1, y1);
		glVertex2f(x2, y1);
		glVertex2f(x2, y2);
		glVertex2f(x1, y2);
	glEnd();
}

#if INLINE_JBW_DRAW_RECTANGLEF
	#define jbw_draw_rectanglef _jbw_draw_rectanglef
#else
	void jbw_draw_rectanglef(float, float, float, float, float, float, float);
#endif

static inline void _jbw_draw_rectangled
	(float red, float green, float blue, double x1, double y1, double x2, double y2)
{
	glColor3f(red, green, blue);
	glBegin(GL_LINE_LOOP);
		glVertex2d(x1, y1);
		glVertex2d(x2, y1);
		glVertex2d(x2, y2);
		glVertex2d(x1, y2);
	glEnd();
}

#if INLINE_JBW_DRAW_RECTANGLED
	#define jbw_draw_rectangled _jbw_draw_rectangled
#else
	void jbw_draw_rectangled(float, float, float, double, double, double, double);
#endif

static inline void _jbw_draw_clear(float red, float green, float blue, float alpha)
{
	glClearColor(red, green, blue, alpha);
	glClear(GL_COLOR_BUFFER_BIT);
}

#if INLINE_JBW_DRAW_CLEAR
	#define jbw_draw_clear _jbw_draw_clear
#else
	void jbw_draw_clear(float, float, float, float);
#endif

static inline void _jbw_draw_pointsf
	(float red, float green, float blue, JBFLOAT *x, JBFLOAT *y, int n)
{
	register int i;
	if (!x || !y) return;
	glColor3f(red, green, blue);
	glBegin(GL_POINTS);
		for (i=n; --i>=0;) glVertex2f(x[i], y[i]);
	glEnd();
}

#if INLINE_JBW_DRAW_POINTSF
	#define jbw_draw_pointsf _jbw_draw_pointsf
#else
	void jbw_draw_pointsf(float, float, float, JBFLOAT*, JBFLOAT*, int);
#endif

static inline void _jbw_draw_pointsd
	(float red, float green, float blue, JBFLOAT *x, JBFLOAT *y, int n)
{
	register int i;
	if (!x || !y) return;
	glColor3f(red, green, blue);
	glBegin(GL_POINTS);
		for (i=n; --i>=0;) glVertex2d(x[i], y[i]);
	glEnd();
}

#if INLINE_JBW_DRAW_POINTSD
	#define jbw_draw_pointsd _jbw_draw_pointsd
#else
	void jbw_draw_pointsd(float, float, float, JBFLOAT*, JBFLOAT*, int);
#endif

static inline void _jbw_draw_linesf
	(float red, float green, float blue, JBFLOAT *x, JBFLOAT *y, int n)
{
	register int i;
	if (!x || !y) return;
	glColor3f(red, green, blue);
	glBegin(GL_LINE_STRIP);
		for (i=n; --i>=0;) glVertex2f(x[i], y[i]);
	glEnd();
}

#if INLINE_JBW_DRAW_LINESF
	#define jbw_draw_linesf _jbw_draw_linesf
#else
	void jbw_draw_linesf(float, float, float, JBFLOAT*, JBFLOAT*, int);
#endif

static inline void _jbw_draw_linesd
	(float red, float green, float blue, JBFLOAT *x, JBFLOAT *y, int n)
{
	register int i;
	if (!x || !y) return;
	glColor3f(red, green, blue);
	glBegin(GL_LINE_STRIP);
		for (i=n; --i>=0;) glVertex2d(x[i], y[i]);
	glEnd();
}

#if INLINE_JBW_DRAW_LINESD
	#define jbw_draw_linesd _jbw_draw_linesd
#else
	void jbw_draw_linesd(float, float, float, JBFLOAT*, JBFLOAT*, int);
#endif

static inline void _jbw_draw_segmentsf
	(float red, float green, float blue, JBFLOAT *x, JBFLOAT *y, int n)
{
	register int i;
	if (!x || !y) return;
	glColor3f(red, green, blue);
	glBegin(GL_LINES);
		for (i=n; --i>=0;) glVertex2f(x[i], y[i]);
	glEnd();
}

#if INLINE_JBW_DRAW_SEGMENTSF
	#define jbw_draw_segmentsf _jbw_draw_segmentsf
#else
	void jbw_draw_segmentsf(float, float, float, JBFLOAT*, JBFLOAT*, int);
#endif

static inline void _jbw_draw_segmentsd
	(float red, float green, float blue, JBFLOAT *x, JBFLOAT *y, int n)
{
	register int i;
	if (!x || !y) return;
	glColor3f(red, green, blue);
	glBegin(GL_LINES);
		for (i=n; --i>=0;) glVertex2d(x[i], y[i]);
	glEnd();
}

#if INLINE_JBW_DRAW_SEGMENTSD
	#define jbw_draw_segmentsd _jbw_draw_segmentsd
#else
	void jbw_draw_segmentsd(float, float, float, JBFLOAT*, JBFLOAT*, int);
#endif

static inline void _jbw_draw_points
(
	float red1, float green1, float blue1, float red2, float green2, float blue2,
	JBDOUBLE xmin, JBDOUBLE xmax, JBDOUBLE ymin, JBDOUBLE ymax,
	JBFLOAT *x, JBFLOAT *y1, JBFLOAT *y2, int n
)
{
	glLoadIdentity();
	glOrtho(xmin, xmax, ymin, ymax, -1., 1.);
	#if JB_PRECISION == 1
		jbw_draw_pointsf(red1, green1, blue1, x, y1, n);
		jbw_draw_pointsf(red2, green2, blue2, x, y2, n);
	#else
		jbw_draw_pointsd(red1, green1, blue1, x, y1, n);
		jbw_draw_pointsd(red2, green2, blue2, x, y2, n);
	#endif	
}

#if INLINE_JBW_DRAW_POINTS
	#define jbw_draw_points _jbw_draw_points
#else
	void jbw_draw_points(float, float, float, float, float, float,
		JBDOUBLE, JBDOUBLE, JBDOUBLE, JBDOUBLE, JBFLOAT*, JBFLOAT*, JBFLOAT*, int);
#endif

static inline void _jbw_draw_pointsvf
	(float red, float green, float blue, void *x, void *y, int size, int n)
{
	register int i;
	if (!x || !y) return;
	glColor3f(red, green, blue);
	glBegin(GL_POINTS);
		for (i=n; --i>=0; x+=size, y+=size)
			glVertex2f(*(JBFLOAT*)x, *(JBFLOAT*)y);
	glEnd();
}

#if INLINE_JBW_DRAW_POINTSVF
	#define jbw_draw_pointsvf _jbw_draw_pointsvf
#else
	void jbw_draw_pointsvf(float, float, float, void*, void*, int, int);
#endif

static inline void _jbw_draw_pointsvd
	(float red, float green, float blue, void *x, void *y, int size, int n)
{
	register int i;
	if (!x || !y) return;
	glColor3f(red, green, blue);
	glBegin(GL_POINTS);
		for (i=n; --i>=0; x+=size, y+=size)
			glVertex2d(*(JBFLOAT*)x, *(JBFLOAT*)y);
	glEnd();
}

#if INLINE_JBW_DRAW_POINTSVD
	#define jbw_draw_pointsvd _jbw_draw_pointsvd
#else
	void jbw_draw_pointsvd(float, float, float, void*, void*, int, int);
#endif

static inline void _jbw_draw_pointsv
(
	float red1, float green1, float blue1, float red2, float green2, float blue2,
	JBDOUBLE xmin, JBDOUBLE xmax, JBDOUBLE ymin, JBDOUBLE ymax,
	void *x, void *y1, void *y2, int size, int n
)
{
	glLoadIdentity();
	glOrtho(xmin, xmax, ymin, ymax, -1., 1.);
	#if JB_PRECISION == 1
		jbw_draw_pointsvf(red1, green1, blue1, x, y1, size, n);
		jbw_draw_pointsvf(red2, green2, blue2, x, y2, size, n);
	#else
		jbw_draw_pointsvd(red1, green1, blue1, x, y1, size, n);
		jbw_draw_pointsvd(red2, green2, blue2, x, y2, size, n);
	#endif	
}

#if INLINE_JBW_DRAW_POINTSV
	#define jbw_draw_pointsv _jbw_draw_pointsv
#else
	void jbw_draw_pointsv(float, float, float, float, float, float,
		JBDOUBLE, JBDOUBLE, JBDOUBLE, JBDOUBLE, void*, void*, void*, int, int);
#endif

static inline void _jbw_draw_lines
(
	float red1, float green1, float blue1, float red2, float green2, float blue2,
	JBDOUBLE xmin, JBDOUBLE xmax, JBDOUBLE ymin, JBDOUBLE ymax,
	JBFLOAT *x, JBFLOAT *y1, JBFLOAT *y2, int n
)
{
	glLoadIdentity();
	glOrtho(xmin, xmax, ymin, ymax, -1., 1.);
	#if JB_PRECISION == 1
		jbw_draw_linesf(red1, green1, blue1, x, y1, n);
		jbw_draw_linesf(red2, green2, blue2, x, y2, n);
	#else
		jbw_draw_linesd(red1, green1, blue1, x, y1, n);
		jbw_draw_linesd(red2, green2, blue2, x, y2, n);
	#endif	
}

#if INLINE_JBW_DRAW_LINES
	#define jbw_draw_lines _jbw_draw_lines
#else
	void jbw_draw_lines(float, float, float, float, float, float,
		JBDOUBLE, JBDOUBLE, JBDOUBLE, JBDOUBLE, JBFLOAT*, JBFLOAT*, JBFLOAT*, int);
#endif

static inline void _jbw_draw_linesvf
	(float red, float green, float blue, void *x, void *y, int size, int n)
{
	register int i;
	if (!x || !y) return;
	glColor3f(red, green, blue);
	glBegin(GL_LINE_STRIP);
		for (i=n; --i>=0; x+=size, y+=size)
			glVertex2f(*(JBFLOAT*)x, *(JBFLOAT*)y);
	glEnd();
}

#if INLINE_JBW_DRAW_LINESVF
	#define jbw_draw_linesvf _jbw_draw_linesvf
#else
	void jbw_draw_linesvf(float, float, float, void*, void*, int, int);
#endif

static inline void _jbw_draw_linesvd
	(float red, float green, float blue, void *x, void *y, int size, int n)
{
	register int i;
	if (!x || !y) return;
	glColor3f(red, green, blue);
	glBegin(GL_LINE_STRIP);
		for (i=n; --i>=0; x+=size, y+=size)
			glVertex2d(*(JBFLOAT*)x, *(JBFLOAT*)y);
	glEnd();
}

#if INLINE_JBW_DRAW_LINESVD
	#define jbw_draw_linesvd _jbw_draw_linesvd
#else
	void jbw_draw_linesvd(float, float, float, void*, void*, int, int);
#endif

static inline void _jbw_draw_linesv
(
	float red1, float green1, float blue1, float red2, float green2, float blue2,
	JBDOUBLE xmin, JBDOUBLE xmax, JBDOUBLE ymin, JBDOUBLE ymax,
	void *x, void *y1, void *y2, int size, int n
)
{
	glLoadIdentity();
	glOrtho(xmin, xmax, ymin, ymax, -1., 1.);
	#if JB_PRECISION == 1
		jbw_draw_linesvf(red1, green1, blue1, x, y1, size, n);
		jbw_draw_linesvf(red2, green2, blue2, x, y2, size, n);
	#else
		jbw_draw_linesvd(red1, green1, blue1, x, y1, size, n);
		jbw_draw_linesvd(red2, green2, blue2, x, y2, size, n);
	#endif	
}

#if INLINE_JBW_DRAW_LINESV
	#define jbw_draw_linesv _jbw_draw_linesv
#else
	void jbw_draw_linesv(float, float, float, float, float, float,
		JBDOUBLE, JBDOUBLE, JBDOUBLE, JBDOUBLE, void*, void*, void*, int, int);
#endif

static inline void _jbw_draw_string
	(char *string, double x, double y, int font_list_base)
{
	if (!string) return;
	glRasterPos2d(x, y);
	glListBase(font_list_base);
	glCallLists(strlen(string), GL_UNSIGNED_BYTE, string);
}

#if INLINE_JBW_DRAW_STRING
	#define jbw_draw_string _jbw_draw_string
#else
	void jbw_draw_string(char*, double, double, int);
#endif

#endif

static inline void _jbw_draw_range(JBDOUBLE *xmin, JBDOUBLE *xmax)
{
	register JBDOUBLE m;
	m = fmaxl(fabsl(*xmax), fabsl(*xmin));
	if (m == 0.)
	{
		*xmin=-1.;
		*xmax=1.;
	}
	else if ((*xmax - *xmin) / m < 0.0001)
	{
		*xmin *= 0.9999;
		*xmax *= 1.0001;
	}
}

#if INLINE_JBW_DRAW_RANGE
	#define jbw_draw_range _jbw_draw_range
#else
	void jbw_draw_range(JBDOUBLE*, JBDOUBLE*);
#endif

static inline void _jbw_draw_tics
	(JBDOUBLE xmin, JBDOUBLE xmax, int nlabels, int *n, JBDOUBLE *tic)
{
	int k1, k2;
	JBDOUBLE h, s, k;
	*n=0;
	h=(xmax-xmin)/(nlabels-1);
	if (h<=0.) return;
	s=exp10(floor(log10(h)));
	k=h/s;
	if (k>5.) s*=10.;
	else if (k>2.5) s*=5.;
	else if (k>2.) s*=2.5;
	else if (k>1.) s+=s;
	for (k1=(int)ceil(xmin/s), k2=(int)floor(xmax/s); k1<=k2; ++k1, ++tic)
	{
		++(*n);
		*tic = k1 * s;
	}
}

#if INLINE_JBW_DRAW_TICS
	#define jbw_draw_tics _jbw_draw_tics
#else
	void jbw_draw_tics(JBDOUBLE xmin, JBDOUBLE xmax, int nlabels, int *n, JBDOUBLE *tic);
#endif

typedef struct
{
	int width, height;
	GLubyte *image;
} JBWLogo;

static inline void _jbw_logo_destroy(JBWLogo *logo)
{
	g_free(logo->image);
	g_free(logo);
}

#if INLINE_JBW_LOGO_DESTROY
	#define jbw_logo_destroy _jbw_logo_destroy
#else
	void jbw_logo_destroy(JBWLogo*);
#endif

static inline JBWLogo* _jbw_logo_new(char *name)
{
	unsigned int row_bytes;
    int i;
    FILE *file;
    png_struct *png;
    png_info *info;
    png_byte **row_pointers;
	JBWLogo *logo = NULL;

	// starting png structs
	png = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    info= png_create_info_struct(png);

	// opening file
	file = fopen(name, "rb");
	if (!file) goto error1;

	// reading file and transforming to 8 bits RGBA format
	if (setjmp(png_jmpbuf(png))) goto error2;
	png_init_io(png, file);
	if (setjmp(png_jmpbuf(png))) goto error2;
	png_read_png(png,
		info,
		PNG_TRANSFORM_STRIP_16 | PNG_TRANSFORM_PACKING | PNG_TRANSFORM_EXPAND,
		NULL);

	// creating the logo struct data
	logo = g_try_malloc(sizeof(JBWLogo));
	if (!logo) goto error2;

	// copying pixels in the OpenGL order
	logo->width = png_get_image_width(png, info);
	logo->height = png_get_image_height(png, info);
	row_bytes = png_get_rowbytes(png, info);
	logo->image = (GLubyte*)g_try_malloc(row_bytes * logo->height);
	if (!logo->image)
	{
		jb_free_null((void**)&logo);
		goto error2;
	}
	row_pointers = png_get_rows(png, info);
	for (i = 0; i < logo->height; i++)
		memcpy(logo->image + (row_bytes * (logo->height - 1 - i)),
			row_pointers[i],
			row_bytes);

	// closing file
error2:
	fclose(file);

	// freeing memory
error1:
	png_destroy_read_struct(&png, &info, NULL);

	return logo;
}

#if INLINE_JBW_LOGO_NEW
	#define jbw_logo_new _jbw_logo_new
#else
	JBWLogo* jbw_logo_new(char*);
#endif

typedef enum
{
	JBW_GRAPHIC_TYPE_JPG=0,
	JBW_GRAPHIC_TYPE_PNG=1,
	JBW_GRAPHIC_TYPE_XPM=2,
	JBW_GRAPHIC_TYPE_TIFF=3,
	JBW_GRAPHIC_TYPE_BMP=4,
	JBW_GRAPHIC_TYPE_GIF=5
} JBWGraphicType;

typedef struct
{
	/* Macros */
	/* JBW_GRAPHIC_N_CHARS=Number of characters in an axis label */
	/* JBW_GRAPHIC_FONT=Default font (eg "courier 8") */

	/* Properties */
	/* type: type of graphic (NOT IMPLEMENTED) */
	/* resize: automatic range set to extremal variable values */
	/* grid: grid drawing */
	/* map: coordenates system proportional to screen */
	/* legend: legend drawing (NOT IMPLEMENTED) */
	/* wchar: pixels width of a character */
	/* hchar: pixels height of a character */
	/* nx: number of x axis labels */
	/* ny: number of y axis labels */
	/* nz: number of z axis labels */
	/* nxmax: maximum number of x axis labels */
	/* nymax: maximum number of y axis labels */
	/* nzmax: maximum number of z axis labels */
	/* xtic: x axis tics */
	/* ytic: y axis tics */
	/* ztic: z axis tics */
	/* font: font description (default JBW_GRAPHIC_FONT) */
	int type, resize, grid, map, legend, legend_z, wchar, hchar, nx, ny, nz,
		nxmax, nymax, nzmax;
	JBDOUBLE xtic[JBW_GRAPHIC_N_LABELS], ytic[JBW_GRAPHIC_N_LABELS],
		ztic[JBW_GRAPHIC_N_LABELS];

	char *font;

#if JBW_DRAW == JBW_DRAW_CAIRO
	cairo_t *cr;
#elif JBW_DRAW == JBW_DRAW_OPENGL
	/* font_list_base: OpenGL font list base */
	int font_list_base;
#endif

	/* Ranges */
	JBDOUBLE xmin, xmax, ymin, ymax, zmin, zmax;

	/* Labels */
	char *str_title, *str_x, *str_y, *str_yy, *str_z, *str_zz;

	/* Util variables (Viewport coordinates) */
#if JBW_DRAW == JBW_DRAW_CAIRO
	double x1, x2, y1, y2;
#elif JBW_DRAW == JBW_DRAW_OPENGL
	int x1, x2, y1, y2;
#endif

	/* Logo */
	JBWLogo *logo;
	
	/* Pointer to draw function */
	void (*draw)();

#if JBW_GRAPHIC == JBW_GRAPHIC_GLUT
	/* Glut window */
	int window;
#elif JBW_GRAPHIC == JBW_GRAPHIC_CLUTTER
	/* clutter stage */
	ClutterStage *stage;
	/* Gtk+ Widget */
	GtkClutterEmbed *drawing_area;
#endif
} JBWGraphic;

static inline char* _jbw_graphic_string(char *str)
{
	if (!str) return 0;
	return g_convert(str, -1, "ISO-8859-1", "UTF-8", 0, 0, 0);
}

#if INLINE_JBW_GRAPHIC_STRING
	#define jbw_graphic_string _jbw_graphic_string
#else
	char* jbw_graphic_string(char*);
#endif

static inline void _jbw_graphic_set_grid(JBWGraphic *graphic, int grid)
{
	graphic->grid = grid;
}

#if INLINE_JBW_GRAPHIC_SET_GRID
	#define jbw_graphic_set_grid _jbw_graphic_set_grid
#else
	void jbw_graphic_set_grid(JBWGraphic*, int);
#endif

static inline void _jbw_graphic_set_title(JBWGraphic *graphic, char *title)
{
	jb_free_null((void**)&graphic->str_title);
	if (title) graphic->str_title = jbw_graphic_string(title);
}

#if INLINE_JBW_GRAPHIC_SET_TITLE
	#define jbw_graphic_set_title _jbw_graphic_set_title
#else
	void jbw_graphic_set_title(JBWGraphic*graphic, char*);
#endif

static inline void _jbw_graphic_set_xlabel(JBWGraphic *graphic, char *str_x)
{
	jb_free_null((void**)&graphic->str_x);
	if (str_x) graphic->str_x = jbw_graphic_string(str_x);
}

#if INLINE_JBW_GRAPHIC_SET_XLABEL
	#define jbw_graphic_set_xlabel _jbw_graphic_set_xlabel
#else
	void jbw_graphic_set_xlabel(JBWGraphic*, char*);
#endif

static inline void _jbw_graphic_set_ylabel(JBWGraphic *graphic, char *str_y)
{
	jb_free_null((void**)&graphic->str_y);
	if (str_y) graphic->str_y = jbw_graphic_string(str_y);
}

#if INLINE_JBW_GRAPHIC_SET_YLABEL
	#define jbw_graphic_set_ylabel _jbw_graphic_set_ylabel
#else
	void jbw_graphic_set_ylabel(JBWGraphic*, char*);
#endif

static inline void _jbw_graphic_set_yylabel(JBWGraphic *graphic, char *str_yy)
{
	jb_free_null((void**)&graphic->str_yy);
	if (str_yy) graphic->str_yy = jbw_graphic_string(str_yy);
}

#if INLINE_JBW_GRAPHIC_SET_YYLABEL
	#define jbw_graphic_set_yylabel _jbw_graphic_set_yylabel
#else
	void jbw_graphic_set_yylabel(JBWGraphic*, char*);
#endif

static inline void _jbw_graphic_set_zlabel(JBWGraphic *graphic, char *str_z)
{
	jb_free_null((void**)&graphic->str_z);
	if (str_z) graphic->str_z = jbw_graphic_string(str_z);
}

#if INLINE_JBW_GRAPHIC_SET_ZLABEL
	#define jbw_graphic_set_zlabel _jbw_graphic_set_zlabel
#else
	void jbw_graphic_set_zlabel(JBWGraphic*, char*);
#endif

static inline void _jbw_graphic_set_zzlabel(JBWGraphic *graphic, char *str_zz)
{
	jb_free_null((void**)&graphic->str_zz);
	if (str_zz) graphic->str_zz = jbw_graphic_string(str_zz);
}

#if INLINE_JBW_GRAPHIC_SET_ZZLABEL
	#define jbw_graphic_set_zzlabel _jbw_graphic_set_zzlabel
#else
	void jbw_graphic_set_zzlabel(JBWGraphic*, char*);
#endif

static inline void _jbw_graphic_set_logo(JBWGraphic *graphic, char *name)
{
	graphic->logo = jbw_logo_new(name);
}

#if INLINE_JBW_GRAPHIC_SET_LOGO
	#define jbw_graphic_set_logo _jbw_graphic_set_logo
#else
	void jbw_graphic_set_logo(JBWGraphic*, char*);
#endif

static inline void _jbw_graphic_draw_string
	(JBWGraphic *graphic, char *string, double x, double y)
{
#if JBW_DRAW == JBW_DRAW_CAIRO
	jbw_draw_string(graphic->cr, string, x, y);
#elif JBW_DRAW == JBW_DRAW_OPENGL
	jbw_draw_string(string, x, y, graphic->font_list_base);
#endif
}

#if INLINE_JBW_GRAPHIC_DRAW_STRING
	#define jbw_graphic_draw_string _jbw_graphic_draw_string
#else
void jbw_graphic_draw_string
	(JBWGraphic *graphic, char *string, double x, double y);
#endif

static inline void _jbw_graphic_labels(JBWGraphic *graphic)
{
	int i;
	JBDOUBLE k;
#if JBW_DRAW == JBW_DRAW_OPENGL
	JBDOUBLE w, h, x1, x2, y1, y2;
#endif
	char buffer[512];
	graphic->x1 = graphic->y1 = 0;
#if JBW_GRAPHIC == JBW_GRAPHIC_CAIRO || JBW_GRAPHIC == JBW_GRAPHIC_CLUTTER
	graphic->x2 =
		gtk_widget_get_allocated_width(GTK_WIDGET(graphic->drawing_area));
	graphic->y2 =
		gtk_widget_get_allocated_height(GTK_WIDGET(graphic->drawing_area));
#elif JBW_GRAPHIC == JBW_GRAPHIC_GLUT
	graphic->x2 = glutGet(GLUT_WINDOW_WIDTH);
	graphic->y2 = glutGet(GLUT_WINDOW_HEIGHT);
#endif
#if JBW_DRAW == JBW_DRAW_CAIRO
	cairo_select_font_face(graphic->cr, "Courier",
		CAIRO_FONT_SLANT_NORMAL,
		CAIRO_FONT_WEIGHT_BOLD);
	cairo_set_font_size(graphic->cr, 10);
	jbw_draw_clear(graphic->cr, 1., 1., 1., graphic->x2, graphic->y2);
	cairo_set_source_rgb(graphic->cr, 0., 0., 0.);
	if (graphic->str_x)
		jbw_graphic_draw_string(graphic, graphic->str_x,
			0.5 * (graphic->x2 - graphic->wchar * strlen(graphic->str_x)),
			graphic->y2 - 0.5 * graphic->hchar);
	if (graphic->str_title)
	{
		graphic->y1 += graphic->hchar;
		jbw_graphic_draw_string(graphic, graphic->str_title,
			0.5 * (graphic->x2 - graphic->wchar * strlen(graphic->str_title)),
			0.);
	}
	if (graphic->str_y || graphic->str_z)
	{
		graphic->y1 += graphic->hchar;
		cairo_set_source_rgb(graphic->cr, 0., 0., 1.);
		jbw_graphic_draw_string(graphic, graphic->str_y, 0., graphic->y1);
		if (graphic->str_z)
		{
			cairo_set_source_rgb(graphic->cr, 1., 0., 0.);
			jbw_graphic_draw_string(graphic, graphic->str_z,
				graphic->x2 - graphic->wchar * (1. + strlen(graphic->str_z)),
				graphic->y1);
		}
	}
	if (graphic->str_yy || graphic->str_zz)
	{
		graphic->y1 += graphic->hchar;
		cairo_set_source_rgb(graphic->cr, 0., 1., 0.);
		jbw_graphic_draw_string(graphic, graphic->str_yy, 0., graphic->y1);
		if (graphic->str_zz)
		{
			cairo_set_source_rgb(graphic->cr, 0.5, 0.5, 0.);
			jbw_graphic_draw_string(graphic, graphic->str_zz,
				graphic->x2 - graphic->wchar * (1. + strlen(graphic->str_zz)),
				graphic->y1);
		}
	}
	graphic->y2 -= 2.5 * graphic->hchar;
	graphic->y1 += 0.5 * graphic->hchar;
	if (graphic->str_y || graphic->str_yy)
		graphic->x1 = (JBW_GRAPHIC_N_CHARS + 1) * graphic->wchar;
	if (graphic->str_z || graphic->str_zz)
		graphic->x2 -= (JBW_GRAPHIC_N_CHARS + 1) * graphic->wchar;
	else 
		graphic->x2 -= 0.5 * JBW_GRAPHIC_N_CHARS * graphic->wchar;
	jbw_draw_range(&graphic->xmin, &graphic->xmax);
	jbw_draw_tics
		(graphic->xmin, graphic->xmax, graphic->nxmax, &graphic->nx, graphic->xtic);
	jbw_draw_range(&graphic->ymin, &graphic->ymax);
	jbw_draw_tics
		(graphic->ymin, graphic->ymax, graphic->nymax, &graphic->ny, graphic->ytic);
	jbw_draw_range(&graphic->zmin, &graphic->zmax);
	jbw_draw_tics
		(graphic->zmin, graphic->zmax, graphic->nzmax, &graphic->nz, graphic->ztic);
	if (!graphic->str_x) graphic->nx = 0;
	if (!graphic->str_y && !graphic->str_yy) graphic->ny = 0;
	if (!graphic->str_z && !graphic->str_zz) graphic->nz = 0;
	cairo_set_source_rgb(graphic->cr, 0., 0., 0.);
	for (i=0; i<graphic->nx; ++i)
	{
		sprintf(buffer, FGL, graphic->xtic[i]);
		k = jbm_extrapolate(graphic->xtic[i], graphic->xmin, graphic->xmax,
			graphic->x1, graphic->x2);
		jbw_graphic_draw_string(graphic, buffer,
			k - 0.5 * graphic->wchar * strlen(buffer),
			graphic->y2 + graphic->hchar);
	}
	cairo_set_source_rgb(graphic->cr, 0., 0., 1.);
	for (i=0; i<graphic->ny; ++i)
	{
		sprintf(buffer, FGL, graphic->ytic[i]);
		k = jbm_extrapolate(graphic->ytic[i], graphic->ymin, graphic->ymax,
			graphic->y2, graphic->y1);
		jbw_graphic_draw_string(graphic, buffer,
			graphic->x1 - graphic->wchar * (1. + strlen(buffer)),
			k + 0.3 * graphic->hchar);
	}
	cairo_set_source_rgb(graphic->cr, 1., 0., 0.);
	for (i=0; i<graphic->nz; ++i)
	{
		sprintf(buffer, FGL, graphic->ztic[i]);
		k = jbm_extrapolate(graphic->ztic[i], graphic->zmin, graphic->zmax,
			graphic->y2, graphic->y1);
		jbw_graphic_draw_string(graphic, buffer, graphic->x2 + graphic->wchar,
			k + 0.3 * graphic->hchar);
	}
	if (graphic->grid)
	{
		cairo_set_source_rgb(graphic->cr, 0.9, 0.9, 0.9);
		for (i=0; i<graphic->nx; ++i)
		{
			k = jbm_extrapolate(graphic->xtic[i], graphic->xmin, graphic->xmax,
				graphic->x1, graphic->x2);
			cairo_move_to(graphic->cr, k, graphic->y1);
			cairo_line_to(graphic->cr, k, graphic->y2);
		}
		cairo_stroke(graphic->cr);
		cairo_set_source_rgb(graphic->cr, 0.85, 0.85, 1.);
		for (i=0; i<graphic->ny; ++i)
		{
			k = jbm_extrapolate(graphic->ytic[i], graphic->ymin, graphic->ymax,
				graphic->y2, graphic->y1);
			cairo_move_to(graphic->cr, graphic->x1, k);
			cairo_line_to(graphic->cr, graphic->x2, k);
		}
		cairo_stroke(graphic->cr);
		cairo_set_source_rgb(graphic->cr, 1., 0.85, 0.85);
		for (i=0; i<graphic->nz; ++i)
		{
			k = jbm_extrapolate(graphic->ztic[i], graphic->zmin, graphic->zmax,
				graphic->y2, graphic->y1);
			cairo_move_to(graphic->cr, graphic->x1, k);
			cairo_line_to(graphic->cr, graphic->x2, k);
		}
		cairo_stroke(graphic->cr);
	}
	else
	{
		cairo_set_source_rgb(graphic->cr, 0., 0., 0.);
		for (i=0; i<graphic->nx; ++i)
		{
			k = jbm_extrapolate(graphic->xtic[i], graphic->xmin, graphic->xmax,
				graphic->x1, graphic->x2);
			cairo_move_to(graphic->cr, k, graphic->y1);
			cairo_line_to(graphic->cr, k, graphic->y1+1.);
			cairo_move_to(graphic->cr, k, graphic->y2);
			cairo_line_to(graphic->cr, k, graphic->y2-1.);
		}
		for (i=0; i<graphic->ny; ++i)
		{
			k = jbm_extrapolate(graphic->ytic[i], graphic->ymin, graphic->ymax,
				graphic->y2, graphic->y1);
			cairo_move_to(graphic->cr, graphic->x1, k);
			cairo_line_to(graphic->cr, graphic->x1+1., k);
		}
		for (i=0; i<graphic->nz; ++i)
		{
			k = jbm_extrapolate(graphic->ztic[i], graphic->zmin, graphic->zmax,
				graphic->y2, graphic->y1);
			cairo_move_to(graphic->cr, graphic->x2, k);
			cairo_line_to(graphic->cr, graphic->x2-1., k);
		}
		cairo_stroke(graphic->cr);
	}
	jbw_draw_rectangle(graphic->cr, 0., 0., 0., graphic->x1, graphic->y1,
		graphic->x2-graphic->x1, graphic->y2-graphic->y1);
#elif JBW_DRAW == JBW_DRAW_OPENGL
	w = ((JBDOUBLE)graphic->x2) / graphic->wchar;
	h = ((JBDOUBLE)graphic->y2) / graphic->hchar;
	jbw_draw_clear(1., 1., 1., 0.);
	glViewport(0, 0, graphic->x2, graphic->y2);
	glLoadIdentity();
	glOrtho(0., w, 0., h, -1., 1.);
	glColor3f(0., 0., 0.);
	if (graphic->str_x)
		jbw_graphic_draw_string
			(graphic, graphic->str_x, 0.5 * (w - strlen(graphic->str_x)), 0.);
	k=h;
	if (graphic->str_title)
	{
		k-=1.;
		graphic->y2 -= graphic->hchar;
		jbw_graphic_draw_string(graphic, graphic->str_title,
			0.5 * (w - strlen(graphic->str_title)), k);
	}
	if (graphic->str_y || graphic->str_z)
	{
		k-=1.;
		graphic->y2 -= graphic->hchar;
		glColor3f(0., 0., 1.);
		jbw_graphic_draw_string(graphic, graphic->str_y, 0., k);
		if (graphic->str_z)
		{
			glColor3f(1., 0., 0.);
			jbw_graphic_draw_string
				(graphic, graphic->str_z, w - 1. - strlen(graphic->str_z), k);
		}
	}
	if (graphic->str_yy || graphic->str_zz)
	{
		k-=1.;
		graphic->y2 -= graphic->hchar;
		glColor3f(0., 1., 0.);
		jbw_graphic_draw_string(graphic, graphic->str_yy, 0., k);
		if (graphic->str_zz)
		{
			glColor3f(0.5, 0.5, 0.);
			jbw_graphic_draw_string
				(graphic, graphic->str_zz, w - 1. - strlen(graphic->str_zz), k);
		}
	}
	graphic->y1 = 2.5 * graphic->hchar;
	graphic->y2 -= 0.5 * graphic->hchar;
	if (graphic->str_y || graphic->str_yy)
		graphic->x1 = (JBW_GRAPHIC_N_CHARS + 1) * graphic->wchar;
	if (graphic->str_z || graphic->str_zz)
		graphic->x2 -= (JBW_GRAPHIC_N_CHARS + 1) * graphic->wchar;
	else 
		graphic->x2 -= 0.5 * JBW_GRAPHIC_N_CHARS * graphic->wchar;
	x1 = ((JBDOUBLE)graphic->x1) / graphic->wchar;
	x2 = ((JBDOUBLE)graphic->x2) / graphic->wchar;
	y1 = ((JBDOUBLE)graphic->y1) / graphic->hchar;
	y2 = ((JBDOUBLE)graphic->y2) / graphic->hchar;
	jbw_draw_range(&graphic->xmin, &graphic->xmax);
	jbw_draw_tics
		(graphic->xmin, graphic->xmax, graphic->nxmax, &graphic->nx, graphic->xtic);
	jbw_draw_range(&graphic->ymin, &graphic->ymax);
	jbw_draw_tics
		(graphic->ymin, graphic->ymax, graphic->nymax, &graphic->ny, graphic->ytic);
	jbw_draw_range(&graphic->zmin, &graphic->zmax);
	jbw_draw_tics
		(graphic->zmin, graphic->zmax, graphic->nzmax, &graphic->nz, graphic->ztic);
	if (!graphic->str_x) graphic->nx = 0;
	if (!graphic->str_y && !graphic->str_yy) graphic->ny = 0;
	if (!graphic->str_z && !graphic->str_zz) graphic->nz = 0;
	glColor3f(0., 0., 0.);
	for (i=0; i<graphic->nx; ++i)
	{
		sprintf(buffer, FGL, graphic->xtic[i]);
		k = jbm_extrapolate
			(graphic->xtic[i], graphic->xmin, graphic->xmax, x1, x2);
		jbw_graphic_draw_string(graphic, buffer, k - 0.5 * strlen(buffer), 1.);
	}
	glColor3f(0., 0., 1.);
	w=x1-1.;
	for (i=0; i<graphic->ny; ++i)
	{
		sprintf(buffer, FGL, graphic->ytic[i]);
		k = jbm_extrapolate
			(graphic->ytic[i], graphic->ymin, graphic->ymax, y1, y2);
		jbw_graphic_draw_string(graphic, buffer, w - strlen(buffer), k - 0.3);
	}
	glColor3f(1., 0., 0.);
	w=x2+1.;
	for (i=0; i<graphic->nz; ++i)
	{
		sprintf(buffer, FGL, graphic->ztic[i]);
		k = jbm_extrapolate
			(graphic->ztic[i], graphic->zmin, graphic->zmax, y1, y2);
		jbw_graphic_draw_string(graphic, buffer, w, k - 0.3);
	}
	if (graphic->grid)
	{
		glColor3f(0.9, 0.9, 0.9);
		glBegin(GL_LINES);
			for (i=0; i<graphic->nx; ++i)
			{
				k = jbm_extrapolate
					(graphic->xtic[i], graphic->xmin, graphic->xmax, x1, x2);
				glVertex2d(k, y1);
				glVertex2d(k, y2);
			}
			glColor3f(0.85, 0.85, 1.);
			for (i=0; i<graphic->ny; ++i)
			{
				k = jbm_extrapolate
					(graphic->ytic[i], graphic->ymin, graphic->ymax, y1, y2);
				glVertex2d(x1, k);
				glVertex2d(x2, k);
			}
			glColor3f(1., 0.85, 0.85);
			for (i=0; i<graphic->nz; ++i)
			{
				k = jbm_extrapolate
					(graphic->ztic[i], graphic->zmin, graphic->zmax, y1, y2);
				glVertex2d(x1, k);
				glVertex2d(x2, k);
			}
		glEnd();
	}
	else
	{
		glColor3f(0., 0., 0.);
		glBegin(GL_LINES);
			for (i=0; i<graphic->nx; ++i)
			{
				k = jbm_extrapolate
					(graphic->xtic[i], graphic->xmin, graphic->xmax, x1, x2);
				glVertex2d(k, y1);
				glVertex2d(k, y1+0.5);
				glVertex2d(k, y2);
				glVertex2d(k, y2-0.5);
			}
			for (i=0; i<graphic->ny; ++i)
			{
				k = jbm_extrapolate
					(graphic->ytic[i], graphic->ymin, graphic->ymax, y1, y2);
				glVertex2d(x1, k);
				glVertex2d(x1+0.5, k);
			}
			for (i=0; i<graphic->nz; ++i)
			{
				k = jbm_extrapolate
					(graphic->ztic[i], graphic->zmin, graphic->zmax, y1, y2);
				glVertex2d(x2, k);
				glVertex2d(x2-0.5, k);
			}
		glEnd();
	}
	jbw_draw_rectangled(0., 0., 0., x1, y1, x2, y2);
	glViewport(graphic->x1, graphic->y1, graphic->x2 - graphic->x1,
		graphic->y2 - graphic->y1);
#endif
}

#if INLINE_JBW_GRAPHIC_LABELS
	#define jbw_graphic_labels _jbw_graphic_labels
#else
	void jbw_graphic_labels(JBWGraphic *graphic);
#endif

static inline void _jbw_graphic_map_resize(JBWGraphic *graphic)
{
	register JBDOUBLE vw, vh, cw, ch;
	vw = graphic->x2 - graphic->x1;
	vh = graphic->y2 - graphic->y1;
	cw = graphic->xmax - graphic->xmin;
	ch = graphic->ymax - graphic->ymin;
	vw /= cw;
	vh /= ch;
	vw /= vh;
	if (vw>1.)
	{
		vw-=1.;
		vw/=2;
		vw*=cw;
		graphic->xmax += vw;
		graphic->xmin -= vw;
	}
	else
	{
		vh=1./vw;
		vh-=1.;
		vh/=2;
		vh*=ch;
		graphic->ymax += vh;
		graphic->ymin -= vh;
	}
}

#if INLINE_JBW_GRAPHIC_MAP_RESIZE
	#define jbw_graphic_map_resize _jbw_graphic_map_resize
#else
	void jbw_graphic_map_resize(JBWGraphic*);
#endif

static inline void _jbw_graphic_draw_resize
	(JBWGraphic *graphic, JBFLOAT *x, JBFLOAT *y1, JBFLOAT *y2, JBFLOAT *z1, JBFLOAT *z2, int n)
{
	JBDOUBLE k1, k2;
	int i=n-1;
	jbm_farray_maxmin(x, i, &graphic->xmax, &graphic->xmin);
	if (y1) jbm_farray_maxmin(y1, i, &graphic->ymax, &graphic->ymin);
	if (y2)
	{
		jbm_farray_maxmin(y2, i, &k2, &k1);
		graphic->ymax = fmaxl(graphic->ymax, k2);
		graphic->ymin = fminl(graphic->ymin, k1);
	}
	if (z1) jbm_farray_maxmin(z1, i, &graphic->zmax, &graphic->zmin);
	if (z2)
	{
		jbm_farray_maxmin(z2, i, &k2, &k1);
		graphic->zmax = fmaxl(graphic->zmax, k2);
		graphic->zmin = fminl(graphic->zmin, k1);
	}
}

#if INLINE_JBW_GRAPHIC_DRAW_RESIZE
	#define jbw_graphic_draw_resize _jbw_graphic_draw_resize
#else
	void jbw_graphic_draw_resize
		(JBWGraphic*, JBFLOAT*, JBFLOAT*, JBFLOAT*, JBFLOAT*, JBFLOAT*, int);
#endif

static inline void _jbw_graphic_draw_line(JBWGraphic *graphic,
	double red, double green, double blue, JBFLOAT *x, JBFLOAT *y1, int n)
{
	if (!x)
	{
		jbw_graphic_labels(graphic);
		return;
	}
	if (graphic->resize) jbw_graphic_draw_resize(graphic, x, y1, 0, 0, 0, n);
	if (graphic->map) jbw_graphic_map_resize(graphic);
	jbw_graphic_labels(graphic);
#if JBW_DRAW == JBW_DRAW_CAIRO
	jbw_draw_lines_with_limits(graphic->cr, red, green, blue, 0., 0., 0.,
		graphic->xmin, graphic->ymin, graphic->xmax, graphic->ymax,
		graphic->x1, graphic->y1, graphic->x2, graphic->y2, x, y1, 0, n);
#elif JBW_DRAW == JBW_DRAW_OPENGL
	jbw_draw_lines(red, green, blue, 0., 0., 0.,
		graphic->xmin, graphic->xmax, graphic->ymin, graphic->ymax, x, y1, 0, n);
#endif
}

#if INLINE_JBW_GRAPHIC_DRAW_LINE
	#define jbw_graphic_draw_line _jbw_graphic_draw_line
#else
	void jbw_graphic_draw_line
		(JBWGraphic*, double, double, double, JBFLOAT*, JBFLOAT*, int);
#endif

static inline void _jbw_graphic_draw_lines
	(JBWGraphic *graphic, JBFLOAT *x, JBFLOAT *y1, JBFLOAT *y2, JBFLOAT *z1, JBFLOAT *z2, int n)
{
	if (!x)
	{
		jbw_graphic_labels(graphic);
		return;
	}
	if (graphic->resize) jbw_graphic_draw_resize(graphic, x, y1, y2, z1, z2, n);
	if (graphic->map) jbw_graphic_map_resize(graphic);
	jbw_graphic_labels(graphic);
#if JBW_DRAW == JBW_DRAW_CAIRO
	jbw_draw_lines_with_limits(graphic->cr, 0., 0., 1., 0., 1., 0.,
		graphic->xmin, graphic->ymin, graphic->xmax, graphic->ymax,
		graphic->x1, graphic->y1, graphic->x2, graphic->y2, x, y1, y2, n);
	jbw_draw_lines_with_limits(graphic->cr, 1., 0., 0., 0.5, 0.5, 0.,
		graphic->xmin, graphic->zmin, graphic->xmax, graphic->zmax,
		graphic->x1, graphic->y1, graphic->x2, graphic->y2, x, z1, z2, n);
#elif JBW_DRAW == JBW_DRAW_OPENGL
	jbw_draw_lines(0., 0., 1., 0., 1., 0.,
		graphic->xmin, graphic->xmax, graphic->ymin, graphic->ymax, x, y1, y2, n);
	jbw_draw_lines(1., 0., 0., 0.5, 0.5, 0.,
		graphic->xmin, graphic->xmax, graphic->zmin, graphic->zmax, x, z1, z2, n);
#endif
}

#if INLINE_JBW_GRAPHIC_DRAW_LINES
	#define jbw_graphic_draw_lines _jbw_graphic_draw_lines
#else
	void jbw_graphic_draw_lines
		(JBWGraphic*, JBFLOAT*, JBFLOAT*, JBFLOAT*, JBFLOAT*, JBFLOAT*, int);
#endif

static inline void _jbw_graphic_draw_linesv(JBWGraphic *graphic, void *x,
	void *y1, void *y2, void *z1, void *z2, int size, int n)
{
	JBDOUBLE k1, k2;
	if (!x) return;
	if (graphic->resize)
	{
		int i=n-1;
		jbm_varray_maxmin(x, size, i, &graphic->xmax, &graphic->xmin);
		if (y1) jbm_varray_maxmin(y1, size, i, &graphic->ymax, &graphic->ymin);
		if (y2)
		{
			jbm_varray_maxmin(y2, size, i, &k2, &k1);
			graphic->ymax = fmaxl(graphic->ymax, k2);
			graphic->ymin = fminl(graphic->ymin, k1);
		}
		if (z1) jbm_varray_maxmin(z1, size, i, &graphic->zmax, &graphic->zmin);
		if (z2)
		{
			jbm_varray_maxmin(z2, size, i, &k2, &k1);
			graphic->zmax = fmaxl(graphic->zmax, k2);
			graphic->zmin = fminl(graphic->zmin, k1);
		}
	}
	if (graphic->map) jbw_graphic_map_resize(graphic);
	jbw_graphic_labels(graphic);
#if JBW_DRAW == JBW_DRAW_CAIRO
	jbw_draw_lines_with_limitsv(graphic->cr, 0., 0., 1., 0., 1., 0.,
		graphic->xmin, graphic->ymin, graphic->xmax, graphic->ymax,
		graphic->x1, graphic->y1, graphic->x2, graphic->y2, x, y1, y2, size, n);
	jbw_draw_lines_with_limitsv(graphic->cr, 1., 0., 0., 0.5, 0.5, 0.,
		graphic->xmin, graphic->zmin, graphic->xmax, graphic->zmax,
		graphic->x1, graphic->y1, graphic->x2, graphic->y2, x, z1, z2, size, n);
#elif JBW_DRAW == JBW_DRAW_OPENGL
	jbw_draw_linesv(0., 0., 1., 0., 1., 0.,
		graphic->xmin, graphic->xmax, graphic->ymin, graphic->ymax, x, y1, y2, size, n);
	jbw_draw_linesv(1., 0., 0., 0.5, 0.5, 0.,
		graphic->xmin, graphic->xmax, graphic->zmin, graphic->zmax, x, z1, z2, size, n);
#endif
}

#if INLINE_JBW_GRAPHIC_DRAW_LINESV
	#define jbw_graphic_draw_linesv _jbw_graphic_draw_linesv
#else
	void jbw_graphic_draw_linesv
		(JBWGraphic*, void*, void*, void*, void*, void*, int, int);
#endif

static inline void _jbw_graphic_draw_logo(JBWGraphic *graphic)
{
	JBWLogo *logo = graphic->logo;
	if (!logo) return;
	glViewport(0, 0, graphic->x2, graphic->y2);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.f, 1.f, -1.f, 1.f, -1.f, 1.f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glRasterPos2f(-1.f, -1.f);
	glDrawPixels(logo->width, logo->height, GL_RGBA, GL_UNSIGNED_BYTE,
		logo->image);
}

#if INLINE_JBW_GRAPHIC_DRAW_LOGO
	#define jbw_graphic_draw_logo _jbw_graphic_draw_logo
#else
	void jbw_graphic_draw_logo(JBWGraphic *graphic);
#endif

#if JBW_GRAPHIC == JBW_GRAPHIC_CAIRO || JBW_GRAPHIC == JBW_GRAPHIC_CLUTTER
static inline void _jbw_graphic_realize(GtkWidget *widget, JBWGraphic *graphic)
#elif JBW_GRAPHIC == JBW_GRAPHIC_GLUT
static inline void _jbw_graphic_realize(JBWGraphic *graphic)
#endif
{
	int i;

	graphic->wchar = 8;
	graphic->hchar = 13;

#if JBW_DRAW == JBW_DRAW_OPENGL
	graphic->font_list_base = glGenLists(256);
	for (i=0; i<256; ++i)
	{
		glNewList(graphic->font_list_base + i, GL_COMPILE);
		glutBitmapCharacter(GLUT_BITMAP_8_BY_13, i);
		glEndList();
	}
#endif

#if JBW_GRAPHIC == JBW_GRAPHIC_CAIRO || JBW_GRAPHIC == JBW_GRAPHIC_CLUTTER
	gtk_widget_set_size_request((GtkWidget*)widget,
		(graphic->nxmax + 1) * FG_LENGTH * graphic->wchar,
		(jbm_max(graphic->nymax, graphic->nzmax) + 5) * graphic->hchar);
#elif JBW_GRAPHIC == JBW_GRAPHIC_GLUT
	glutReshapeWindow((graphic->nxmax + 1) * FG_LENGTH * graphic->wchar,
		(jbm_max(graphic->nymax, graphic->nzmax) + 5) * graphic->hchar);
#endif

}

#if INLINE_JBW_GRAPHIC_REALIZE
	#define jbw_graphic_realize _jbw_graphic_realize
#elif JBW_GRAPHIC == JBW_GRAPHIC_CAIRO 
	void jbw_graphic_realize(GtkWidget*, JBWGraphic*);
#elif JBW_GRAPHIC == JBW_GRAPHIC_GLUT
	void _jbw_graphic_realize(JBWGraphic *graphic);
#endif

#if JBW_GRAPHIC == JBW_GRAPHIC_CAIRO || JBW_GRAPHIC == JBW_GRAPHIC_CLUTTER
static inline void _jbw_graphic_expose_event
	(GtkWidget *widget, GdkEventExpose *event, JBWGraphic *graphic)
#elif JBW_GRAPHIC == JBW_GRAPHIC_GLUT
static inline void _jbw_graphic_expose_event()
#endif
{
#if JBW_GRAPHIC == JBW_GRAPHIC_CAIRO
	graphic->cr = gdk_cairo_create(((GtkWidget*)graphic->drawing_area)->window);
	graphic->draw();
	cairo_destroy(graphic->cr);
#elif JBW_GRAPHIC == JBW_GRAPHIC_GLUT
	jbw_graphic_draw();
	glutSwapBuffers();
#elif JBW_GRAPHIC == JBW_GRAPHIC_CLUTTER
	graphic->draw();
	glFlush();
#endif
}

#if INLINE_JBW_GRAPHIC_EXPOSE_EVENT
	#define jbw_graphic_expose_event _jbw_graphic_expose_event
#elif JBW_GRAPHIC == JBW_GRAPHIC_CAIRO || JBW_GRAPHIC == JBW_GRAPHIC_CLUTTER
	void jbw_graphic_expose_event(GtkWidget*, GdkEventExpose*, JBWGraphic*);
#elif JBW_GRAPHIC == JBW_GRAPHIC_GLUT
	void jbw_graphic_expose_event();
#endif

static inline void _jbw_graphic_save
	(JBWGraphic *graphic, char *file_name, JBWGraphicType type)
{
#if JBW_GRAPHIC == JBW_GRAPHIC_CAIRO || JBW_GRAPHIC == JBW_GRAPHIC_CLUTTER
	GdkPixbuf *pixbuf;
#if GTK_MAJOR_VERSION < 3
	pixbuf=gdk_pixbuf_get_from_drawable(0,
		gtk_widget_get_window(GTK_WIDGET(graphic->drawing_area)),
		0, 0, 0, 0, 0,
		gtk_widget_get_allocated_width(GTK_WIDGET(graphic->drawing_area)),
		gtk_widget_get_allocated_height(GTK_WIDGET(graphic->drawing_area)));
#else
	pixbuf=gdk_pixbuf_get_from_window(
		gtk_widget_get_window(GTK_WIDGET(graphic->drawing_area)),
		0, 0,
		gtk_widget_get_allocated_width(GTK_WIDGET(graphic->drawing_area)),
		gtk_widget_get_allocated_height(GTK_WIDGET(graphic->drawing_area)));
#endif
	switch (type)
	{
	case JBW_GRAPHIC_TYPE_JPG:
		gdk_pixbuf_save(pixbuf, file_name, "jpeg", 0, "quality", "100", NULL);
		break;
	case JBW_GRAPHIC_TYPE_PNG:
		gdk_pixbuf_save(pixbuf, file_name, "png", 0, "compression", "9", NULL);
		break;
	case JBW_GRAPHIC_TYPE_TIFF:
		gdk_pixbuf_save(pixbuf, file_name, "tiff", 0, NULL);
		break;
	case JBW_GRAPHIC_TYPE_BMP:
		gdk_pixbuf_save(pixbuf, file_name, "bmp", 0, NULL);
		break;
	case JBW_GRAPHIC_TYPE_GIF:
		gdk_pixbuf_save(pixbuf, file_name, "gif", 0, NULL);
		break;
	default:
		gdk_pixbuf_save(pixbuf, file_name, "xpm", 0, NULL);
	}
	g_object_unref(pixbuf);
#elif JBW_GRAPHIC == JBW_GRAPHIC_GLUT
	int i, x2, y2;
	unsigned int row_bytes;
	GLubyte *pixels;
	FILE *file;
	png_struct *png;
	png_info *info;
	png_byte **row_pointers;
	x2 = glutGet(GLUT_WINDOW_WIDTH);
	y2 = glutGet(GLUT_WINDOW_HEIGHT);
	png	= png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	if (!png) return;
	info = png_create_info_struct(png);
	if (!info) return;
	file = fopen(file_name, "wb");
	if (!file) return;
	if (setjmp(png_jmpbuf(png)))
	{
		printf("Error png_init_io\n");
		exit(0);
	}
	png_init_io(png, file);
	if (setjmp(png_jmpbuf(png)))
	{
		printf("Error png_set_IHDR\n");
		exit(0);
	}
	png_set_IHDR(
		png,
		info,
		x2,
		y2,
		8,
		PNG_COLOR_TYPE_RGBA,
		PNG_INTERLACE_NONE,
		PNG_COMPRESSION_TYPE_DEFAULT,
		PNG_FILTER_TYPE_DEFAULT);
	if (setjmp(png_jmpbuf(png)))
	{
		printf("Error png_write_info\n");
		exit(0);
	}
	png_write_info(png, info);
	glViewport(0, 0, x2, y2);
	row_bytes = 4 * x2;
	pixels = (GLubyte*)malloc(row_bytes * y2);
	glReadPixels
		(0, 0, x2, y2, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
	row_pointers = (png_byte**)malloc(y2 * sizeof(png_byte*));
	for (i = 0; i < y2; ++i)
	{
		row_pointers[i] = (png_byte*)malloc(row_bytes);
		memcpy(row_pointers[i], pixels + (y2 - 1 - i) * row_bytes,
			row_bytes);
	}
	if (setjmp(png_jmpbuf(png)))
	{
		printf("Error png_write_image\n");
		exit(0);
	}
	png_write_image(png, row_pointers);
	for (i = 0; i < y2; ++i) free(row_pointers[i]);
	free(row_pointers);
	free(pixels);
	if (setjmp(png_jmpbuf(png)))
	{
		printf("Error png_write_end\n");
		exit(0);
	}
	png_write_end(png, NULL);
	fclose(file);
	png_destroy_write_struct(&png, &info);
#endif
}

#if INLINE_JBW_GRAPHIC_SAVE
	#define jbw_graphic_save _jbw_graphic_save
#else
	void jbw_graphic_save(JBWGraphic*, char*, JBWGraphicType);
#endif

static inline void _jbw_graphic_dialog_save(JBWGraphic *graphic)
{
	char *buffer=NULL;
	GtkFileFilter *filter;
	GtkFileChooserDialog *dlg;
	filter = gtk_file_filter_new();
	gtk_file_filter_set_name(filter, "PNG file");
	gtk_file_filter_add_pattern(filter, "*.png");
	gtk_file_filter_add_pattern(filter, "*.PNG");
	dlg = (GtkFileChooserDialog*)gtk_file_chooser_dialog_new
		(gettext("Save graphical"), window_parent,
		GTK_FILE_CHOOSER_ACTION_SAVE,
		GTK_STOCK_OK, GTK_RESPONSE_OK, GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL, NULL);
	gtk_file_chooser_add_filter(GTK_FILE_CHOOSER(dlg), filter);
	gtk_file_chooser_set_do_overwrite_confirmation(GTK_FILE_CHOOSER(dlg), 1);
	if (gtk_dialog_run((GtkDialog*)dlg) == GTK_RESPONSE_OK)
		buffer=gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dlg));
	gtk_widget_destroy((GtkWidget*)dlg);
	if (buffer)
	{
#if JBW_GRAPHIC == JBW_GRAPHIC_CAIRO || JBW_GRAPHIC == JBW_GRAPHIC_CLUTTER
		jbw_graphic_expose_event((GtkWidget*)graphic->drawing_area, 0, graphic);
#elif JBW_GRAPHIC == JBW_GRAPHIC_GLUT
		jbw_graphic_expose_event();
#endif
		while (gtk_events_pending()) gtk_main_iteration();
		jbw_graphic_save(graphic, buffer, JBW_GRAPHIC_TYPE_PNG);
		g_free(buffer);
	}
}

#if INLINE_JBW_GRAPHIC_DIALOG_SAVE
	#define jbw_graphic_dialog_save _jbw_graphic_dialog_save
#else
	void jbw_graphic_dialog_save(JBWGraphic*);
#endif

static inline void _jbw_graphic_destroy(JBWGraphic *graphic)
{
#if JBW_GRAPHIC == JBW_GRAPHIC_GLUT
	JBWGraphic *graphic_old;
#endif
	g_free(graphic->str_title);
	g_free(graphic->str_x);
	g_free(graphic->str_y);
	g_free(graphic->str_yy);
	g_free(graphic->str_z);
	g_free(graphic->str_zz);
	g_free(graphic->logo);
#if JBW_GRAPHIC == JBW_GRAPHIC_CAIRO || JBW_GRAPHIC == JBW_GRAPHIC_CLUTTER
	gtk_widget_destroy((GtkWidget*)graphic->drawing_area);
#elif JBW_GRAPHIC == JBW_GRAPHIC_GLUT
	g_queue_pop_head(&jbw_graphic_queue);
	if (jbw_graphic_queue.head)
	{
		graphic_old = (JBWGraphic*)jbw_graphic_queue.head->data;
		jbw_graphic_draw = graphic_old->draw;
		jbw_graphic_realize(graphic_old);
	}
	else glutDestroyWindow(graphic->window);
#endif
	g_free(graphic);
}

#if INLINE_JBW_GRAPHIC_DESTROY
	#define jbw_graphic_destroy _jbw_graphic_destroy
#else
	void jbw_graphic_destroy(JBWGraphic*);
#endif

static inline JBWGraphic* _jbw_graphic_new
	(char *font, int nx, int ny, int nz, void (*draw)())
{
	register JBWGraphic *graphic;

	graphic=(JBWGraphic*)g_malloc(sizeof(JBWGraphic));

	graphic->resize = graphic->grid = 1;
	graphic->map = 0;

	graphic->str_title = graphic->str_x = graphic->str_y = graphic->str_yy =
		graphic->str_z = graphic->str_zz = NULL; 

	graphic->logo = NULL;

	graphic->nxmax = nx;
	graphic->nymax = ny;
	graphic->nzmax = nz;

	if (font) graphic->font = font; else graphic->font = JBW_GRAPHIC_FONT;

	graphic->draw = draw;

#if JBW_GRAPHIC == JBW_GRAPHIC_CAIRO

	graphic->drawing_area=(GtkDrawingArea*)gtk_drawing_area_new();
	g_signal_connect_after(graphic->drawing_area,
		"realize", (void(*)())jbw_graphic_realize, graphic);
	g_signal_connect(graphic->drawing_area, "expose_event",
		(void(*)())jbw_graphic_expose_event, graphic);

#elif JBW_GRAPHIC == JBW_GRAPHIC_GLUT

	if (!jbw_graphic_queue.head) graphic->window = glutCreateWindow("");
	jbw_graphic_draw = draw;
	jbw_graphic_realize(graphic);
	glutDisplayFunc(jbw_graphic_expose_event);
	g_queue_push_head(&jbw_graphic_queue, graphic);

#elif JBW_GRAPHIC == JBW_GRAPHIC_CLUTTER

	graphic->drawing_area=(GtkClutterEmbed*)gtk_clutter_embed_new();
	graphic->stage =
		(ClutterStage*)gtk_clutter_embed_get_stage(graphic->drawing_area);
	g_signal_connect_after(graphic->drawing_area,
		"realize", (void(*)())jbw_graphic_realize, graphic);
	g_signal_connect(graphic->drawing_area, "expose_event",
		(void(*)())jbw_graphic_expose_event, graphic);
	gtk_widget_show(GTK_WIDGET(graphic->drawing_area));
	clutter_actor_show(CLUTTER_ACTOR(graphic->stage));

#endif

	return graphic;
}

#if INLINE_JBW_GRAPHIC_NEW
	#define jbw_graphic_new _jbw_graphic_new
#else
	JBWGraphic* jbw_graphic_new(char*, int, int, int, void (*)());
#endif

static inline int _jbw_graphic_init(int *argn, char ***argc)
{
	gtk_disable_setlocale();
#if JBW_DRAW == JBW_DRAW_OPENGL
	glutInit(argn, *argc);
#endif
#if JBW_GRAPHIC == JBW_GRAPHIC_CLUTTER
	gtk_clutter_init(argn, argc);
#else
	gtk_init(argn, argc);
#endif
#if JBW_GRAPHIC == JBW_GRAPHIC_GLUT
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION);
	glutInitWindowSize(640, 480);
#endif
	return 1;
}

#if INLINE_JBW_GRAPHIC_INIT
	#define jbw_graphic_init _jbw_graphic_init
#else
	int jbw_graphic_init(int*, char***);
#endif

typedef struct _JBWArrayEditor
{
	GtkScrolledWindow *scrolled;
	GtkButton **button_numeric, **button_title;
	GtkEntry ***matrix_entry;
	GtkTable *table;
	int ncolumn, d, n;
} JBWArrayEditor;

static inline void _jbw_array_editor_set_element
	(JBWArrayEditor *editor, int row, int column, char* str)
{
	GtkEntry *element = editor->matrix_entry[column][row];
	gtk_entry_set_text(element, str);
}

#if INLINE_JBW_ARRAY_EDITOR_SET_ELEMENT
	#define jbw_array_editor_set_element _jbw_array_editor_set_element
#else
	void jbw_array_editor_set_element(JBWArrayEditor*, int, int, char*);
#endif

static inline char* _jbw_array_editor_get_element
	(JBWArrayEditor *editor, int row, int column)
{
	GtkEntry *element = editor->matrix_entry[column][row];
	return g_strdup(gtk_entry_get_text(element));
}

#if INLINE_JBW_ARRAY_EDITOR_GET_ELEMENT
	#define jbw_array_editor_get_element _jbw_array_editor_get_element
#else
	char* jbw_array_editor_get_element(JBWArrayEditor*, int, int);
#endif

static inline void _jbw_array_editor_set_element_int
	(JBWArrayEditor *editor, int row, int column, long int x)
{
	JBWIntEntry *element = editor->matrix_entry[column][row];
	jbw_int_entry_set_value(element, x);
}

#if INLINE_JBW_ARRAY_EDITOR_SET_ELEMENT_INT
	#define jbw_array_editor_set_element_int _jbw_array_editor_set_element_int
#else
	void jbw_array_editor_set_element_int(JBWArrayEditor*, int, int, long int);
#endif

static inline long int _jbw_array_editor_get_element_int
	(JBWArrayEditor *editor, int row, int column)
{
	JBWIntEntry *element = editor->matrix_entry[column][row];
	return jbw_int_entry_get_value(element);
}

#if INLINE_JBW_ARRAY_EDITOR_GET_ELEMENT_INT
	#define jbw_array_editor_get_element_int _jbw_array_editor_get_element_int
#else
	long int jbw_array_editor_get_element_int(JBWArrayEditor*, int, int);
#endif

static inline void _jbw_array_editor_set_element_float
	(JBWArrayEditor *editor, int row, int column, JBDOUBLE x)
{
	JBWFloatEntry *element = editor->matrix_entry[column][row];
	jbw_float_entry_set_value(element, x);
}

#if INLINE_JBW_ARRAY_EDITOR_SET_ELEMENT_FLOAT
	#define jbw_array_editor_set_element_float \
		_jbw_array_editor_set_element_float
#else
	void jbw_array_editor_set_element_float(JBWArrayEditor*, int, int, JBDOUBLE);
#endif

static inline JBDOUBLE _jbw_array_editor_get_element_float
	(JBWArrayEditor *editor, int row, int column)
{
	JBWFloatEntry *element = editor->matrix_entry[column][row];
	return jbw_float_entry_get_value(element);
}

#if INLINE_JBW_ARRAY_EDITOR_GET_ELEMENT_FLOAT
	#define jbw_array_editor_get_element_float \
		_jbw_array_editor_get_element_float
#else
	JBDOUBLE jbw_array_editor_get_element_float(JBWArrayEditor*, int, int);
#endif

static inline void _jbw_array_editor_set_column
	(JBWArrayEditor *editor, int column, char **c)
{
	register int i, j;
	JBWIntEntry **array;
	array = editor->matrix_entry[column];
	j=editor->n;
	if (column >= editor->d) --j;
	for (i=0; ++i<=j;) gtk_entry_set_text(*(array++), *(c++));
}

#if INLINE_JBW_ARRAY_EDITOR_SET_COLUMN
	#define jbw_array_editor_set_column _jbw_array_editor_set_column
#else
	void jbw_array_editor_set_column(JBWArrayEditor*, int, char**);
#endif

static inline void _jbw_array_editor_get_column
	(JBWArrayEditor *editor, int column, char **c)
{
	register int i, j;
	JBWIntEntry **array;
	array = editor->matrix_entry[column];
	j=editor->n;
	if (column >= editor->d) --j;
	for (i=0; ++i<=j;) *(c++)=(char*)gtk_entry_get_text(*(array++));
}

#if INLINE_JBW_ARRAY_EDITOR_GET_COLUMN
	#define jbw_array_editor_get_column _jbw_array_editor_get_column
#else
	void jbw_array_editor_get_column(JBWArrayEditor*, int, char**);
#endif

static inline void
	_jbw_array_editor_set_column_int(JBWArrayEditor *editor, int column, int *x)
{
	register int i, j;
	JBWIntEntry **array;
	array = editor->matrix_entry[column];
	j=editor->n;
	if (column >= editor->d) --j;
	for (i=0; ++i<=j;) jbw_int_entry_set_value(*(array++), *(x++));
}

#if INLINE_JBW_ARRAY_EDITOR_SET_COLUMN_INT
	#define jbw_array_editor_set_column_int _jbw_array_editor_set_column_int
#else
	void jbw_array_editor_set_column_int(JBWArrayEditor*, int, int*);
#endif

static inline void _jbw_array_editor_get_column_int
	(JBWArrayEditor *editor, int column, int *x)
{
	register int i, j;
	JBWIntEntry **array;
	array = editor->matrix_entry[column];
	j=editor->n;
	if (column >= editor->d) --j;
	for (i=0; ++i<=j;) *(x++)=jbw_int_entry_get_value(*(array++));
}

#if INLINE_JBW_ARRAY_EDITOR_GET_COLUMN_INT
	#define jbw_array_editor_get_column_int _jbw_array_editor_get_column_int
#else
	void jbw_array_editor_get_column_int(JBWArrayEditor*, int, int*);
#endif

static inline void _jbw_array_editor_set_column_float
	(JBWArrayEditor *editor, int column, JBFLOAT *x)
{
	register int i, j;
	JBWFloatEntry **array;
	array = editor->matrix_entry[column];
	j=editor->n;
	if (column >= editor->d) --j;
	for (i=0; ++i<=j;) jbw_float_entry_set_value(*(array++), *(x++));
}

#if INLINE_JBW_ARRAY_EDITOR_SET_COLUMN_FLOAT
	#define jbw_array_editor_set_column_float _jbw_array_editor_set_column_float
#else
	void jbw_array_editor_set_column_float(JBWArrayEditor*, int, JBFLOAT*);
#endif

static inline void _jbw_array_editor_get_column_float
	(JBWArrayEditor *editor, int column, JBFLOAT *x)
{
	register int i, j;
	JBWFloatEntry **array;
	array = editor->matrix_entry[column];
	j=editor->n;
	if (column >= editor->d) --j;
	for (i=0; ++i<=j;) *(x++)=jbw_float_entry_get_value(*(array++));
}

#if INLINE_JBW_ARRAY_EDITOR_GET_COLUMN_FLOAT
	#define jbw_array_editor_get_column_float _jbw_array_editor_get_column_float
#else
	void jbw_array_editor_get_column_float(JBWArrayEditor*, int, JBFLOAT*);
#endif

static inline void _jbw_array_editor_set_column_sensitive
	(JBWArrayEditor *editor, int column, int sensitive)
{
	register int i, j;
	JBWFloatEntry **array;
	array = editor->matrix_entry[column];
	j=editor->n;
	if (column >= editor->d) --j;
	for (i=0; ++i<=j;)
		gtk_widget_set_sensitive((GtkWidget*)*(array++), sensitive);
}

#if INLINE_JBW_ARRAY_EDITOR_SET_COLUMN_SENSITIVE
	#define jbw_array_editor_set_column_sensitive \
		_jbw_array_editor_set_column_sensitive
#else
	void jbw_array_editor_set_column_sensitive(JBWArrayEditor*, int, int);
#endif

static inline void _jbw_array_editor_show_column
	(JBWArrayEditor *editor, int column)
{
	register int i, j;
	JBWIntEntry **array;
	gtk_widget_show((GtkWidget*)editor->button_title[column]);
	array = editor->matrix_entry[column];
	j=editor->n;
	if (column >= editor->d) --j;
	for (i=0; ++i<=j;) gtk_widget_show((GtkWidget*)*(array++));
}

#if INLINE_JBW_ARRAY_EDITOR_SHOW_COLUMN
	#define jbw_array_editor_show_column _jbw_array_editor_show_column
#else
	void jbw_array_editor_show_column(JBWArrayEditor*, int);
#endif

static inline void _jbw_array_editor_hide_column
	(JBWArrayEditor *editor, int column)
{
	register int i, j;
	JBWIntEntry **array;
	gtk_widget_hide((GtkWidget*)editor->button_title[column]);
	array = editor->matrix_entry[column];
	j=editor->n;
	if (column >= editor->d) --j;
	for (i=0; ++i<=j;) gtk_widget_hide((GtkWidget*)*(array++));
}

#if INLINE_JBW_ARRAY_EDITOR_HIDE_COLUMN
	#define jbw_array_editor_hide_column _jbw_array_editor_hide_column
#else
	void jbw_array_editor_hide_column(JBWArrayEditor*, int);
#endif

static inline void _jbw_array_editor_insert_button
	(JBWArrayEditor *editor, int row)
{
	register int k;
	char buffer[32];
	k=row+1;
	sprintf(buffer, "%d", k);
	editor->button_numeric =
		(GtkButton**)jb_realloc(editor->button_numeric, k*sizeof(GtkButton*));
	editor->button_numeric[row]=(GtkButton*)gtk_button_new_with_label(buffer);
	gtk_widget_set_sensitive((GtkWidget*)editor->button_numeric[row], 0);
	k=row+row;
	gtk_table_attach(editor->table, (GtkWidget*)editor->button_numeric[row],
		0, 1, k+1, k+3, GTK_FILL, GTK_FILL, 0, 0);
}

#if INLINE_JBW_ARRAY_EDITOR_INSERT_BUTTON
	#define jbw_array_editor_insert_button _jbw_array_editor_insert_button
#else
	void jbw_array_editor_insert_button(JBWArrayEditor*, int);
#endif

static inline void _jbw_array_editor_insert_entry
	(JBWArrayEditor *editor, int i, int j, int k)
{
	editor->matrix_entry[i]=(GtkEntry**)
		jb_realloc(editor->matrix_entry[i], (j+1)*sizeof(GtkEntry*));
	editor->matrix_entry[i][j]=(GtkEntry*)gtk_entry_new();
	gtk_entry_set_text(editor->matrix_entry[i][j], "0");
	gtk_table_attach_defaults(editor->table,
		(GtkWidget*)editor->matrix_entry[i][j], i+1, i+2, k, k+2);
}

#if INLINE_JBW_ARRAY_EDITOR_INSERT_ENTRY
	#define jbw_array_editor_insert_entry _jbw_array_editor_insert_entry
#else
	void jbw_array_editor_insert_entry(JBWArrayEditor*, int, int, int);
#endif

static inline void _jbw_array_editor_insert(JBWArrayEditor *editor)
{
	register int i, j, k;
	j = editor->n++;
	jbw_array_editor_insert_button(editor, j);
	k=j+j;
	for (i=0; i<editor->d; ++i) jbw_array_editor_insert_entry(editor, i, j, k+1);
	if (j>0) for (; i<editor->ncolumn; ++i)
		jbw_array_editor_insert_entry(editor, i, j-1, k);
	gtk_table_resize(editor->table, i+1, k+3);
	gtk_widget_show_all((GtkWidget*)editor->table);
}

#if INLINE_JBW_ARRAY_EDITOR_INSERT
	#define jbw_array_editor_insert _jbw_array_editor_insert
#else
	void jbw_array_editor_insert(JBWArrayEditor*);
#endif

static inline void _jbw_array_editor_up_rows
	(JBWArrayEditor *editor, int i, int row, int n)
{
	GtkEntry **entry1, **entry2;
	entry1 = editor->matrix_entry[i] + (--n);
	for (; --n>=row;)
	{
		entry2 = entry1--;
		gtk_entry_set_text(*entry2, gtk_entry_get_text(*entry1));
	}
	gtk_entry_set_text(*entry1, "0");
}

#if INLINE_JBW_ARRAY_EDITOR_UP_ROWS
	#define jbw_array_editor_up_rows _jbw_array_editor_up_rows
#else
	void jbw_array_editor_up_rows(JBWArrayEditor*, int, int, int);
#endif

static inline void _jbw_array_editor_insert_row(JBWArrayEditor *editor, int row)
{
	register int i;
	jbw_array_editor_insert(editor);
	for (i=0; i<editor->d; ++i)
		jbw_array_editor_up_rows(editor, i, row, editor->n);
	for (; i<editor->ncolumn; ++i)
		jbw_array_editor_up_rows(editor, i, row, editor->n-1);
}

#if INLINE_JBW_ARRAY_EDITOR_INSERT_ROW
	#define jbw_array_editor_insert_row _jbw_array_editor_insert_row
#else
	void jbw_array_editor_insert_row(JBWArrayEditor*, int);
#endif

static inline void _jbw_array_editor_remove_entry
	(JBWArrayEditor *editor, int i, int j)
{
	gtk_widget_destroy((GtkWidget*)editor->matrix_entry[i][j]);
	editor->matrix_entry[i]=
		(GtkEntry**)jb_realloc(editor->matrix_entry[i], j*sizeof(GtkEntry*));
}

#if INLINE_JBW_ARRAY_EDITOR_REMOVE_ENTRY
	#define jbw_array_editor_remove_entry _jbw_array_editor_remove_entry
#else
	void jbw_array_editor_remove_entry(JBWArrayEditor*, int, int);
#endif

static inline void _jbw_array_editor_remove(JBWArrayEditor *editor)
{
	register int i, j;
	if (editor->n<=0) return;
	j = --editor->n;
	gtk_widget_destroy((GtkWidget*)editor->button_numeric[j]);
	for (i=0; i<editor->d; ++i) jbw_array_editor_remove_entry(editor, i, j);
	if (--j>=0) for (; i<editor->ncolumn; ++i)
		jbw_array_editor_remove_entry(editor, i, j);
}

#if INLINE_JBW_ARRAY_EDITOR_REMOVE
	#define jbw_array_editor_remove _jbw_array_editor_remove
#else
	void jbw_array_editor_remove(JBWArrayEditor*);
#endif

static inline void _jbw_array_editor_down_rows
	(JBWArrayEditor *editor, int i, int row, int n)
{
	GtkEntry **entry1, **entry2;
	entry1 = editor->matrix_entry[i] + row;
	for (; ++row<n;)
	{
		entry2 = entry1++;
		gtk_entry_set_text(*entry2, gtk_entry_get_text(*entry1));
	}
}

#if INLINE_JBW_ARRAY_EDITOR_DOWN_ROWS
	#define jbw_array_editor_down_rows _jbw_array_editor_down_rows
#else
	void jbw_array_editor_down_rows(JBWArrayEditor*, int, int, int);
#endif

static inline void _jbw_array_editor_remove_row(JBWArrayEditor *editor, int row)
{
	register int i;
	for (i=0; i<editor->d; ++i)
		jbw_array_editor_down_rows(editor, i, row, editor->n);
	for (; i<editor->ncolumn; ++i)
		jbw_array_editor_down_rows(editor, i, row, editor->n-1);
	jbw_array_editor_remove(editor);
}

#if INLINE_JBW_ARRAY_EDITOR_REMOVE_ROW
	#define jbw_array_editor_remove_row _jbw_array_editor_remove_row
#else
	void jbw_array_editor_remove_row(JBWArrayEditor*, int);
#endif

static inline void _jbw_array_editor_set_rows(JBWArrayEditor *editor, int n)
{
	register int i;
	for (i=editor->n; i>n; --i) jbw_array_editor_remove(editor);
	for (; i<n; ++i) jbw_array_editor_insert(editor);
	gtk_widget_show_all((GtkWidget*)editor->table);
}

#if INLINE_JBW_ARRAY_EDITOR_SET_ROWS
	#define jbw_array_editor_set_rows _jbw_array_editor_set_rows
#else
	void jbw_array_editor_set_rows(JBWArrayEditor*, int);
#endif

static inline void _jbw_array_editor_set_title
	(JBWArrayEditor *editor, int i, char *title)
{
	gtk_button_set_label(editor->button_title[i], title);
}

#if INLINE_JBW_ARRAY_EDITOR_SET_TITLE
	#define jbw_array_editor_set_title _jbw_array_editor_set_title
#else
	void jbw_array_editor_set_title(JBWArrayEditor*, int, char*);
#endif

static inline void _jbw_array_editor_destroy(JBWArrayEditor *editor)
{
	register int i;
	gtk_widget_destroy((GtkWidget*)editor->scrolled);
	for (i=editor->ncolumn; --i>=0;)
		jb_free_null((void**)&editor->matrix_entry[i]);
	jb_free_null((void**)&editor->button_numeric);
	g_free(editor);
}

#if INLINE_JBW_ARRAY_EDITOR_DESTROY
	#define jbw_array_editor_destroy _jbw_array_editor_destroy
#else
	void jbw_array_editor_destroy(JBWArrayEditor*);
#endif

static inline JBWArrayEditor* _jbw_array_editor_new
	(int ncolumn, int d, int n, char **label)
{
	register int i;
	JBWArrayEditor *editor;
	editor=(JBWArrayEditor*)g_malloc(sizeof(JBWArrayEditor));
	editor->scrolled=(GtkScrolledWindow*)gtk_scrolled_window_new(0, 0);
	editor->table=(GtkTable*)gtk_table_new(0, 0, 0);
	editor->matrix_entry=(GtkEntry***)g_malloc(ncolumn*sizeof(GtkEntry**));
	editor->button_title=(GtkButton**)g_malloc(ncolumn*sizeof(GtkButton*));
	for (i=0; i<ncolumn; ++i)
	{
		editor->matrix_entry[i]=0;
		editor->button_title[i]=(GtkButton*)gtk_button_new_with_label(label[i]);
		gtk_widget_set_sensitive((GtkWidget*)editor->button_title[i], 0);
		gtk_table_attach(editor->table, (GtkWidget*)editor->button_title[i],
			i+1, i+2, 0, 1, GTK_EXPAND|GTK_FILL, GTK_FILL, 0, 0);
	}
	editor->button_numeric=0;
	editor->ncolumn = ncolumn;
	editor->d = d;
	editor->n = 0;
	jbw_array_editor_set_rows(editor, n);
	gtk_scrolled_window_add_with_viewport((GtkScrolledWindow*)editor->scrolled,
		(GtkWidget*)editor->table);
	gtk_scrolled_window_set_policy(editor->scrolled,
		GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
	return editor;
}

#if INLINE_JBW_ARRAY_EDITOR_NEW
	#define jbw_array_editor_new _jbw_array_editor_new
#else
	JBWArrayEditor* jbw_array_editor_new(int, int, int, char**);
#endif

#endif

static inline void _jbw_show_error2(char *message1, char *message2)
{
	char buffer[1024];
	snprintf(buffer, 1024, "%s:\n%s", message1, message2);
	jbw_show_error(buffer);
}

#if INLINE_JBW_SHOW_ERROR2
	#define jbw_show_error2 _jbw_show_error2
#else
	void jbw_show_error2(char*, char*);
#endif

static inline void _jbw_show_error3
	(char *message1, char *message2, char *message3)
{
	char buffer[1024];
	snprintf(buffer, 1024, "%s: %s\n%s", message1, message2, message3);
	jbw_show_error(buffer);
}

#if INLINE_JBW_SHOW_ERROR3
	#define jbw_show_error3 _jbw_show_error3
#else
	void jbw_show_error3(char*, char*, char*);
#endif

#endif
