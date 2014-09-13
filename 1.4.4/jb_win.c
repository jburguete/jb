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
 * \file jb_win.c
 * \brief Source file with useful display functions.
 * \author Javier Burguete Tolosa.
 * \copyright Copyright 2005-2014, Javier Burguete Tolosa.
 */
#include "jb_win.h"

#if JBW==JBW_GTK
GtkWindow *window_parent;
#endif

#if JBW_GRAPHIC==JBW_GRAPHIC_GLUT
GQueue jbw_graphic_queue = G_QUEUE_INIT;
void (*jbw_graphic_draw)();
#endif

#if !INLINE_JBW_SHOW_MESSAGE
void jbw_show_message(char *title,char *message,char *image)
{_jbw_show_message(title,message,image);}
#endif

#if !INLINE_JBW_SHOW_ERROR
void jbw_show_error(char *message) {_jbw_show_error(message);}
#endif

#if !INLINE_JBW_SHOW_ERROR2
void jbw_show_error2(char *message1,char* message2)
{_jbw_show_error2(message1,message2);}
#endif

#if !INLINE_JBW_SHOW_ERROR3
void jbw_show_error3(char *message1,char* message2,char *message3)
{_jbw_show_error3(message1,message2,message3);}
#endif

#if !INLINE_JBW_SHOW_WARNING
void jbw_show_warning(char *message) {_jbw_show_warning(message);}
#endif

#if JBW==JBW_GTK

GtkWindow *window_parent;

#if JBW_GRAPHIC == JBW_GRAPHIC_GLUT
void (*jbw_graphic_draw)();
#endif

#if !INLINE_JBW_COMBO_BOX_SET_STRINGS
void jbw_combo_box_set_strings(GtkComboBoxText *combo,char **strings,int n)
{_jbw_combo_box_set_strings(combo,strings,n);}
#endif

#if !INLINE_JBW_COMBO_BOX_NEW_WITH_STRINGS
GtkComboBoxText* jbw_combo_box_new_with_strings(char **string,int n)
{return _jbw_combo_box_new_with_strings(string,n);}
#endif

#if !INLINE_JBW_BUTTON_NEW_FROM_STOCK
JBWButton* jbw_button_new_from_stock(char *image)
{return _jbw_button_new_from_stock(char *image);}
#endif

#if !INLINE_JBW_ARRAY_RADIO_BUTTONS_SET_ACTIVE
void jbw_array_radio_buttons_set_active
	(GtkRadioButton **array,int n,int is_active)
{_jbw_array_radio_buttons_set_active(array,n,is_active);}
#endif

#if !INLINE_JBW_ARRAY_RADIO_BUTTONS_GET_ACTIVE
int jbw_array_radio_buttons_get_active(GtkRadioButton **array)
{return _jbw_array_radio_buttons_get_active(array);}
#endif

#if !INLINE_JBW_INT_ENTRY_SET_VALUE_WITH_FORMAT
void jbw_int_entry_set_value_with_format
	(JBWIntEntry *entry,char *format,long value)
{_jbw_int_entry_set_value_with_format(entry,format,value);}
#endif

#if !INLINE_JBW_INT_ENTRY_SET_VALUE
void jbw_int_entry_set_value(JBWIntEntry *entry,long value)
{_jbw_int_entry_set_value(entry,value);}
#endif

#if !INLINE_JBW_INT_ENTRY_GET_VALUE
long jbw_int_entry_get_value(JBWIntEntry *entry)
{return _jbw_int_entry_get_value(entry);}
#endif

#if !INLINE_JBW_FLOAT_ENTRY_SET_VALUE_WITH_FORMAT
void jbw_float_entry_set_value_with_format
	(JBWFloatEntry *entry,char *format,JBDOUBLE value)
{_jbw_float_entry_set_value_with_format(entry,format,value);}
#endif

#if !INLINE_JBW_FLOAT_ENTRY_SET_VALUE
void jbw_float_entry_set_value(JBWFloatEntry *entry,JBDOUBLE value)
{_jbw_float_entry_set_value(entry,value);}
#endif

#if !INLINE_JBW_FLOAT_ENTRY_GET_VALUE
JBDOUBLE jbw_float_entry_get_value(JBWFloatEntry *entry)
{return _jbw_float_entry_get_value(entry);}
#endif

#if !INLINE_JBW_MENU_ITEM_NEW
JBWMenuItem* jbw_menu_item_new(char *string,char *image)
{return _jbw_menu_item_new(string,image);}
#endif

#if JBW_DRAW == JBW_DRAW_CAIRO

#if !INLINE_JBW_DRAW_RECTANGLE
void jbw_draw_rectangle(cairo_t *cr,double red,double green,
	double blue,double x,double y,double width,double height)
{_jbw_draw_rectangle(cr,red,green,blue,x,y,width,height);}
#endif

#if !INLINE_JBW_DRAW_BAR
void jbw_draw_bar(cairo_t *cr,double red,double green,
	double blue,double x,double y,double width,double height)
{_jbw_draw_bar(cr,red,green,blue,x,y,width,height);}
#endif

#if !INLINE_JBW_DRAW_CLEAR
void jbw_draw_clear
	(cairo_t *cr,double red,double green,double blue,double width,double height)
{_jbw_draw_clear(cairo_t *cr,red,green,blue,width,height);}
#endif

#if !INLINE_JBW_DRAW_LINE
void jbw_draw_line
	(cairo_t *cr,double red,double green,double blue,JBFLOAT *x,JBFLOAT *y,int n)
{_jbw_draw_line(cr,red,green,blue,x,y,n);}
#endif

#if !INLINE_JBW_DRAW_LINEV
void jbw_draw_linev(cairo_t *cr,
	double red,double green,double blue,void *x,void *y,int size,int n)
{_jbw_draw_linev(cr,red,green,blue,x,y,size,n);}
#endif

#if !INLINE_JBW_DRAW_SEGMENT_WITH_LIMITS
void jbw_draw_segment_with_limits(cairo_t *cr,double xmin,
	double ymin,double xmax,double ymax,double x1,double y1,double x2,double y2)
{_jbw_draw_segment_with_limits(cr,xmin,ymin,xmax,ymax,x1,y1,x2,y2);}
#endif

#if !INLINE_JBW_DRAW_LINE_WITH_LIMITS
void jbw_draw_line_with_limits(cairo_t *cr,
	double red,double green,double blue,
	double xmin,double ymin,double xmax,double ymax,
	double x1,double y1,double x2,double y2,
	JBFLOAT *x,JBFLOAT *y,int n)
{
	_jbw_draw_line_with_limits(cr,red,green,blue,xmin,ymin,xmax,ymax,
		x1,y1,x2,y2,x,y,n);
}
#endif

#if !INLINE_JBW_DRAW_LINE_WITH_LIMITSV
void jbw_draw_line_with_limitsv(cairo_t *cr,
	double red,double green,double blue,
	double xmin,double ymin,double xmax,double ymax,
	double x1,double y1,double x2,double y2,
	void *x,void *y,int size,int n)
{
	_jbw_draw_line_with_limitsv(cr,red,green,blue,xmin,ymin,xmax,ymax,
		x1,y1,x2,y2,x,y,size,n);
}
#endif

#if !INLINE_JBW_DRAW_LINES_WITH_LIMITS
void jbw_draw_lines_with_limits
(
	cairo_t *cr,
	double red1,double green1,double blue1,
	double red2,double green2,double blue2,
	double xmin,double ymin,double xmax,double ymax,
	double x1,double y1,double x2,double y2,
	JBFLOAT *x,JBFLOAT *y,JBFLOAT *yy,int n
)
{
	_jbw_draw_lines_with_limits(cr,red1,green1,blue1,red2,green2,blue2,
		xmin,ymin,xmax,ymax,x1,y1,x2,y2,x,y,yy,n);
}
#endif

#if !INLINE_JBW_DRAW_LINES_WITH_LIMITSV
void jbw_draw_lines_with_limitsv
(
	cairo_t *cr,
	double red1,double green1,double blue1,
	double red2,double green2,double blue2,
	double xmin,double ymin,double xmax,double ymax,
	double x1,double y1,double x2,double y2,
	void *x,void *y,void *yy,int size,int n
)
{
	_jbw_draw_lines_with_limitsv(cr,red1,green1,blue1,red2,green2,blue2,
		xmin,ymin,xmax,ymax,x1,y1,x2,y2,x,y,yy,size,n);
}
#endif

#if !INLINE_JBW_DRAW_SEGMENT
void jbw_draw_segment
	(cairo_t *cr,double red,double green,double blue,JBFLOAT *x,JBFLOAT *y,int n)
{_jbw_draw_segment(cr,red,green,blue,x,y,n);}
#endif

#if !INLINE_JBW_DRAW_STRING
void jbw_draw_string(cairo_t *cr,char *string,double x,double y)
{_jbw_draw_string(cr,string,x,y);}
#endif

#elif JBW_DRAW == JBW_DRAW_OPENGL

#if !INLINE_JBW_DRAW_RECTANGLEF
void jbw_draw_rectanglef
	(float red,float green,float blue,float x1,float y1,float x2,float y2)
{_jbw_draw_rectanglef(red,green,blue,x1,y1,x2,y2);}
#endif

#if !INLINE_JBW_DRAW_RECTANGLED
void jbw_draw_rectangled
	(float red,float green,float blue,double x1,double y1,double x2,double y2)
{_jbw_draw_rectangled(red,green,blue,x1,y1,x2,y2);}
#endif

#if !INLINE_JBW_DRAW_CLEAR
void jbw_draw_clear
	(cairo_t *cr,float red,float green,float blue,int width,int height)
{_jbw_draw_clear(cr,red,green,blue,width,height);}
#endif

#if !INLINE_JBW_DRAW_RECTANGLE
void jbw_draw_rectangle(cairo_t *cr,float red,float green,float blue,int x,
	int y,int width,int height)
{_jbw_draw_rectangle(cr,red,green,blue,x,y,width,height);}
#endif

#if !INLINE_JBW_DRAW_POINTSF
void jbw_draw_pointsf
	(float red,float green,float blue,JBFLOAT *x,JBFLOAT *y,int n)
{_jbw_draw_pointsf(red,green,blue,x,y,n);}
#endif

#if !INLINE_JBW_DRAW_POINTSD
void jbw_draw_pointsd
	(float red,float green,float blue,JBFLOAT *x,JBFLOAT *y,int n)
{_jbw_draw_pointsd(red,green,blue,x,y,n);}
#endif

#if !INLINE_JBW_DRAW_LINESF
void jbw_draw_linesf
	(float red,float green,float blue,JBFLOAT *x,JBFLOAT *y,int n)
{_jbw_draw_linesf(red,green,blue,x,y,n);}
#endif

#if !INLINE_JBW_DRAW_LINESD
void jbw_draw_linesd
	(float red,float green,float blue,JBFLOAT *x,JBFLOAT *y,int n)
{_jbw_draw_linesd(red,green,blue,x,y,n);}
#endif

#if !INLINE_JBW_DRAW_SEGMENTSF
void jbw_draw_segmentsf
	(float red,float green,float blue,JBFLOAT *x,JBFLOAT *y,int n)
{_jbw_draw_segmentsf(red,green,blue,x,y,n);}
#endif

#if !INLINE_JBW_DRAW_SEGMENTSD
void jbw_draw_segmentsd
	(float red,float green,float blue,JBFLOAT *x,JBFLOAT *y,int n)
{_jbw_draw_segmentsd(red,green,blue,x,y,n);}
#endif

#if !INLINE_JBW_DRAW_CLEAR
void jbw_draw_clear(float red,float green,float blue,float alpha)
{_jbw_draw_clear(red,green,blue,alpha);}
#endif

#if !INLINE_JBW_DRAW_POINTS
void jbw_draw_points
(
	float red1,float green1,float blue1,float red2,float green2,float blue2,
	JBDOUBLE xmin,JBDOUBLE xmax,JBDOUBLE ymin,JBDOUBLE ymax,
	JBFLOAT *x,JBFLOAT *y1,JBFLOAT *y2,int n
)
{
	_jbw_draw_points
		(red1,green1,blue1,red2,green2,blue2,xmin,xmax,ymin,ymax,x,y1,y2,n);
}
#endif

#if !INLINE_JBW_DRAW_POINTSVF
void jbw_draw_pointsvf
	(float red,float green,float blue,void *x,void *y,int size,int n)
{_jbw_draw_pointsvf(red,green,blue,x,y,size,n);}
#endif

#if !INLINE_JBW_DRAW_POINTSVD
void jbw_draw_pointsvd
	(float red,float green,float blue,void *x,void *y,int size,int n)
{_jbw_draw_pointsvd(red,green,blue,x,y,size,n);}
#endif

#if !INLINE_JBW_DRAW_POINTSV
void jbw_draw_pointsv
(
	float red1,float green1,float blue1,float red2,float green2,float blue2,
	JBDOUBLE xmin,JBDOUBLE xmax,JBDOUBLE ymin,JBDOUBLE ymax,void *x,void *y1,void *y2,
	int size,int n
)
{
	_jbw_draw_pointsv(red1,green1,blue1,red2,green2,blue2,xmin,xmax,ymin,ymax,
		x,y1,y2,size,n);
}
#endif

#if !INLINE_JBW_DRAW_LINES
void jbw_draw_lines
(
	JBFLOAT *x,JBFLOAT *y1,JBFLOAT *y2,
	float red1,float green1,float blue1,float red2,float green2,float blue2,
	JBDOUBLE xmin,JBDOUBLE xmax,JBDOUBLE ymin,JBDOUBLE ymax,int n
)
{
	_jbw_draw_lines
		(x,y1,y2,red1,green1,blue1,red2,green2,blue2,xmin,xmax,ymin,ymax,n);
}
#endif

#if !INLINE_JBW_DRAW_LINESVF
void jbw_draw_linesvf
	(float red,float green,float blue,void *x,void *y,int size,int n)
{_jbw_draw_linesvf(red,green,blue,x,y,size,n);}
#endif

#if !INLINE_JBW_DRAW_LINESVD
void jbw_draw_linesvd
	(float red,float green,float blue,void *x,void *y,int size,int n)
{_jbw_draw_linesvd(red,green,blue,x,y,size,n);}
#endif

#if !INLINE_JBW_DRAW_LINESV
void jbw_draw_linesv
(
	float red1,float green1,float blue1,float red2,float green2,float blue2,
	JBDOUBLE xmin,JBDOUBLE xmax,JBDOUBLE ymin,JBDOUBLE ymax,void *x,void *y1,void *y2,
	int size,int n
)
{
	_jbw_draw_linesv(red1,green1,blue1,red2,green2,blue2,xmin,xmax,ymin,ymax,
		x,y1,y2,size,n);
}
#endif

#if !INLINE_JBW_DRAW_STRING
void jbw_draw_string(char *string,double x,double y,int font_list_base)
{_jbw_draw_string(string,x,y,font_list_base);}
#endif

#endif

#if !INLINE_JBW_DRAW_RANGE
void jbw_draw_range(JBDOUBLE *xmin,JBDOUBLE *xmax) {_jbw_draw_range(xmin,xmax);}
#endif

#if !INLINE_JBW_DRAW_TICS
void jbw_draw_tics(JBDOUBLE xmin,JBDOUBLE xmax,int nlabels,int *n,JBDOUBLE *tic)
{_jbw_draw_tics(xmin,xmax,nlabels,n,tic);}
#endif

#if !INLINE_JBW_LOGO_DESTROY
void jbw_logo_destroy(JBWLogo *logo) {_jbw_logo_destroy(logo);}
#endif

#if !INLINE_JBW_LOGO_NEW
JBWLogo* jbw_logo_new(char *name) {return _jbw_logo_new(name);}
#endif

#if !INLINE_JBW_GRAPHIC_STRING
char* jbw_graphic_string(char *str) {return _jbw_graphic_string(str);}
#endif

#if !INLINE_JBW_GRAPHIC_SET_GRID
void jbw_graphic_set_grid(JBWGraphic *graphic,int grid)
{_jbw_graphic_set_grid(graphic,grid);}
#endif

#if !INLINE_JBW_GRAPHIC_SET_TITLE
void jbw_graphic_set_title(JBWGraphic *graphic,char *title)
{_jbw_graphic_set_title(graphic,title);}
#endif

#if !INLINE_JBW_GRAPHIC_SET_XLABEL
void jbw_graphic_set_xlabel(JBWGraphic *graphic,char *xlabel)
{_jbw_graphic_set_xlabel(graphic,xlabel);}
#endif

#if !INLINE_JBW_GRAPHIC_SET_YLABEL
void jbw_graphic_set_ylabel(JBWGraphic *graphic,char *ylabel)
{_jbw_graphic_set_ylabel(graphic,ylabel);}
#endif

#if !INLINE_JBW_GRAPHIC_SET_YYLABEL
void jbw_graphic_set_yylabel(JBWGraphic *graphic,char *yylabel)
{_jbw_graphic_set_yylabel(graphic,yylabel);}
#endif

#if !INLINE_JBW_GRAPHIC_SET_ZLABEL
void jbw_graphic_set_zlabel(JBWGraphic *graphic,char *zlabel)
{_jbw_graphic_set_zlabel(graphic,zlabel);}
#endif

#if !INLINE_JBW_GRAPHIC_SET_ZZLABEL
void jbw_graphic_set_zzlabel(JBWGraphic *graphic,char *zzlabel)
{_jbw_graphic_set_zzlabel(graphic,zzlabel);}
#endif

#if !INLINE_JBW_GRAPHIC_SET_LOGO
void jbw_graphic_set_logo(JBWGraphic *graphic,char *name)
{_jbw_graphic_set_logo(graphic,name);}
#endif

#if !INLINE_JBW_GRAPHIC_DRAW_STRING
void jbw_graphic_draw_string
	(JBWGraphic *graphic, char *string, double x, double y)
{_jbw_graphic_draw_string(graphic,string,x,y);}
#endif

#if !INLINE_JBW_GRAPHIC_LABELS
void jbw_graphic_labels(JBWGraphic *graphic) {_jbw_graphic_labels(graphic);}
#endif

#if !INLINE_JBW_GRAPHIC_MAP_RESIZE
void jbw_graphic_map_resize(JBWGraphic *graphic)
{_jbw_graphic_map_resize(graphic);}
#endif

#if !INLINE_JBW_GRAPHIC_DRAW_RESIZE
void jbw_graphic_draw_resize
	(JBWGraphic *graphic,JBFLOAT *x,JBFLOAT *y1,JBFLOAT *y2,JBFLOAT *z1,JBFLOAT *z2,int n)
{_jbw_graphic_draw_resize(graphic,x,y1,y2,z1,z2,n);}
#endif

#if !INLINE_JBW_GRAPHIC_DRAW_LINE
void jbw_graphic_draw_line(JBWGraphic *graphic,
	double red,double green,double blue,JBFLOAT *x,JBFLOAT *y1,int n)
{_jbw_graphic_draw_line(graphic,red,green,blue,x,y1,n);}
#endif

#if !INLINE_JBW_GRAPHIC_DRAW_LINES
void jbw_graphic_draw_lines
	(JBWGraphic *widget,JBFLOAT *x,JBFLOAT *y1,JBFLOAT *y2,JBFLOAT *z1,JBFLOAT *z2,int n)
{_jbw_graphic_draw_lines(widget,x,y1,y2,z1,z2,n);}
#endif

#if !INLINE_JBW_GRAPHIC_DRAW_LINESV
void jbw_graphic_draw_linesv(JBWGraphic *widget,void *x,void *y1,void *y2,
	void *z1,void *z2,int size,int n)
{_jbw_graphic_draw_linesv(widget,x,y1,y2,z1,z2,size,n);}
#endif

#if !INLINE_JBW_GRAPHIC_DRAW_LOGO
void jbw_graphic_draw_logo(JBWGraphic *graphic)
{_jbw_graphic_draw_logo(graphic);}
#endif

#if !INLINE_JBW_GRAPHIC_REALIZE
#if JBW_GRAPHIC == JBW_GRAPHIC_CAIRO || JBW_GRAPHIC == JBW_GRAPHIC_GTKGLEXT
void jbw_graphic_realize(GtkWidget *widget,JBWGraphic *graphic)
{_jbw_graphic_realize(widget,graphic);}
#elif JBW_GRAPHIC == JBW_GRAPHIC_GLUT
void jbw_graphic_realize(JBWGraphic *graphic); {_jbw_graphic_realize(*graphic);}
#endif
#endif

#if !INLINE_JBW_GRAPHIC_EXPOSE_EVENT
#if JBW_GRAPHIC == JBW_GRAPHIC_CAIRO || JBW_GRAPHIC == JBW_GRAPHIC_GTKGLEXT
void jbw_graphic_expose_event
	(GtkWidget *widget,GdkEventExpose *event,JBWGraphic *graphic)
{_jbw_graphic_expose_event(widget,event,graphic);}
#elif JBW_GRAPHIC == JBW_GRAPHIC_GLUT
void jbw_graphic_expose_event() {_jbw_graphic_expose_event();}
#endif
#endif

#if !INLINE_JBW_GRAPHIC_SAVE
void jbw_graphic_save(JBWGraphic *widget,char *file_name,JBWGraphicType type)
{_jbw_graphic_save(widget,file_name,type);}
#endif

#if !INLINE_JBW_GRAPHIC_DESTROY
void jbw_graphic_destroy(JBWGraphic *widget) {_jbw_graphic_destroy(widget);}
#endif

#if !INLINE_JBW_GRAPHIC_NEW
#if JBW_GRAPHIC == JBW_GRAPHIC_GTKGLEXT
JBWGraphic *jbw_graphic_new
	(GdkGLConfig *glconfig,char *font,int nx,int ny,int nz,void (*draw)())
{return _jbw_graphic_new(glconfig,font,nx,ny,nz,draw);}
#else
JBWGraphic *jbw_graphic_new(char *font,int nx,int ny,int nz,void (*draw)())
{return _jbw_graphic_new(font,nx,ny,nz,draw);}
#endif
#endif

#if !INLINE_JBW_GRAPHIC_INIT
#if JBW_GRAPHIC == JBW_GRAPHIC_GTKGLEXT
int jbw_graphic_init(int *argn,char ***argc,GdkGLConfig **glconfig)
{return _jbw_graphic_int(argn,argc,glconfig);}
#else
int jbw_graphic_init(int *argn,char ***argc)
{return _jbw_graphic_int(argn,argc);}
#endif
#endif

#if !INLINE_JBW_GRAPHIC_DIALOG_SAVE
void jbw_graphic_dialog_save(JBWGraphic *graphic)
{_jbw_graphic_dialog_save(graphic);}
#endif

#if !INLINE_JBW_ARRAY_EDITOR_SET_ELEMENT
void jbw_array_editor_set_element
	(JBWArrayEditor *editor,int row,int column,char* str)
{_jbw_array_editor_set_element(editor,row,column,str);}
#endif

#if !INLINE_JBW_ARRAY_EDITOR_GET_ELEMENT
char* jbw_array_editor_get_element(JBWArrayEditor *editor,int row,int column)
{return _jbw_array_editor_get_element(editor,row,column);}
#endif

#if !INLINE_JBW_ARRAY_EDITOR_SET_ELEMENT_INT
void jbw_array_editor_set_element_int
	(JBWArrayEditor *editor,int row,int column,long int x)
{_jbw_array_editor_set_element_int(editor,row,column,x);}
#endif

#if !INLINE_JBW_ARRAY_EDITOR_GET_ELEMENT_INT
long int jbw_array_editor_get_element_int
	(JBWArrayEditor *editor,int row,int column)
{return _jbw_array_editor_get_element_int(editor,row,column);}
#endif

#if !INLINE_JBW_ARRAY_EDITOR_SET_ELEMENT_FLOAT
void jbw_array_editor_set_element_float
	(JBWArrayEditor *editor,int row,int column,JBDOUBLE x)
{_jbw_array_editor_set_element_float(editor,row,column,x);}
#endif

#if !INLINE_JBW_ARRAY_EDITOR_GET_ELEMENT_FLOAT
JBDOUBLE jbw_array_editor_get_element_float
	(JBWArrayEditor *editor,int row,int column)
{return _jbw_array_editor_get_element_float(editor,row,column);}
#endif

#if !INLINE_JBW_ARRAY_EDITOR_SET_COLUMN
void jbw_array_editor_set_column(JBWArrayEditor *editor,int column,char **c)
{_jbw_array_editor_set_column(editor,column,c);}
#endif

#if !INLINE_JBW_ARRAY_EDITOR_GET_COLUMN
void jbw_array_editor_get_column(JBWArrayEditor *editor,int column,char **c)
{_jbw_array_editor_get_column(editor,column,c);}
#endif

#if !INLINE_JBW_ARRAY_EDITOR_SET_COLUMN_INT
void jbw_array_editor_set_column_int(JBWArrayEditor *editor,int column,int *x)
{_jbw_array_editor_set_column_int(editor,column,x);}
#endif

#if !INLINE_JBW_ARRAY_EDITOR_GET_COLUMN_INT
void jbw_array_editor_get_column_int(JBWArrayEditor *editor,int column,int *x)
{_jbw_array_editor_get_column_int(editor,column,x);}
#endif

#if !INLINE_JBW_ARRAY_EDITOR_SET_COLUMN_FLOAT
void jbw_array_editor_set_column_float
	(JBWArrayEditor *editor,int column,JBFLOAT *x)
{_jbw_array_editor_set_column_float(editor,column,x);}
#endif

#if !INLINE_JBW_ARRAY_EDITOR_GET_COLUMN_FLOAT
void jbw_array_editor_get_column_float
	(JBWArrayEditor *editor,int column,JBFLOAT *x)
{_jbw_array_editor_get_column_float(editor,column,x);}
#endif

#if !INLINE_JBW_ARRAY_EDITOR_SET_COLUMN_SENSITIVE
void jbw_array_editor_set_column_sensitive
	(JBWArrayEditor *editor,int column,int sensitive)
{_jbw_array_editor_set_column_sensitive(editor,column,sensitive);}
#endif

#if !INLINE_JBW_ARRAY_EDITOR_SHOW_COLUMN
void jbw_array_editor_show_column(JBWArrayEditor *editor,int column)
{_jbw_array_editor_show_column(editor,column);}
#endif

#if !INLINE_JBW_ARRAY_EDITOR_HIDE_COLUMN
void jbw_array_editor_hide_column(JBWArrayEditor *editor,int column)
{_jbw_array_editor_hide_column(editor,column);}
#endif

#if !INLINE_JBW_ARRAY_EDITOR_INSERT_BUTTON
void jbw_array_editor_insert_button(JBWArrayEditor *editor,int row)
{_jbw_array_editor_insert_button(editor,row);}
#endif

#if !INLINE_JBW_ARRAY_EDITOR_INSERT_ENTRY
void jbw_array_editor_insert_entry(JBWArrayEditor *editor,int i,int j,int k)
{_jbw_array_editor_insert_entry(editor,i,j,k);}
#endif

#if !INLINE_JBW_ARRAY_EDITOR_INSERT
void jbw_array_editor_insert(JBWArrayEditor *editor)
{_jbw_array_editor_insert(editor);}
#endif

#if !INLINE_JBW_ARRAY_EDITOR_UP_ROWS
void jbw_array_editor_up_rows(JBWArrayEditor *editor,int i,int row,int n)
{_jbw_array_editor_up_rows(editor,i,row,n);}
#endif

#if !INLINE_JBW_ARRAY_EDITOR_INSERT_ROW
void jbw_array_editor_insert_row(JBWArrayEditor *editor,int row)
{_jbw_array_editor_insert_row(editor,row);}
#endif

#if !INLINE_JBW_ARRAY_EDITOR_REMOVE_ENTRY
void jbw_array_editor_remove_entry(JBWArrayEditor *editor,int i,int j)
{_jbw_array_editor_remove_entry(editor,i,j);}
#endif

#if !INLINE_JBW_ARRAY_EDITOR_REMOVE
void jbw_array_editor_remove(JBWArrayEditor *editor)
{_jbw_array_editor_remove(editor);}
#endif

#if !INLINE_JBW_ARRAY_EDITOR_DOWN_ROWS
void jbw_array_editor_down_rows(JBWArrayEditor *editor,int i,int row,int n)
{_jbw_array_editor_down_rows(editor,i,row,n);}
#endif

#if !INLINE_JBW_ARRAY_EDITOR_REMOVE_ROW
void jbw_array_editor_remove_row(JBWArrayEditor *editor,int row)
{_jbw_array_editor_remove_row(editor,row);}
#endif

#if !INLINE_JBW_ARRAY_EDITOR_SET_ROWS
void jbw_array_editor_set_rows(JBWArrayEditor *editor,int n)
{_jbw_array_editor_set_rows(editor,n);}
#endif

#if !INLINE_JBW_ARRAY_EDITOR_SET_TITLE
void jbw_array_editor_set_title(JBWArrayEditor *editor,int i,char *title)
{_jbw_array_editor_set_title(editor,i,title);}
#endif

#if !INLINE_JBW_ARRAY_EDITOR_DESTROY
void jbw_array_editor_destroy(JBWArrayEditor *editor)
{_jbw_array_editor_destroy(editor);}
#endif

#if !INLINE_JBW_ARRAY_EDITOR_NEW
JBWArrayEditor* jbw_array_editor_new(int ncolumn,int d,int n,char **label)
{return _jbw_array_editor_new(ncolumn,d,n,label);}
#endif

#endif
