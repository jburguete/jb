/* JB - A library with useful mathematical, XML, GTK+ and OpenGL functions.
 *
 * Copyright 2005-2020, Javier Burguete Tolosa.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *   1. Redistributions of source code must retain the above copyright notice,
 *     this list of conditions and the following disclaimer.
 *
 *   2. Redistributions in binary form must reproduce the above copyright notice,
 *     this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
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
 * \copyright Copyright 2005-2020, Javier Burguete Tolosa.
 */
#ifndef JB_WIN__H
#define JB_WIN__H 1

#include "jb_math.h"

#if JBW == JBW_NO

static inline void
jbw_show_message (const char *title, const char *message)
{
  printf ("%s: %s\n", title, message);
}

static inline void
jbw_show_error (const char *message)
{
  jbw_show_message (_("Error!"), message);
}

static inline void
jbw_show_warning (const char *message)
{
  jbw_show_message (_("Warning!"), message);
}

/**
 * Function to display two error messages.
 */
static inline void
jbw_show_error2 (const char *message1,  ///< 1st error message.
                 const char *message2)  ///< 2nd error message.
{
  char buffer[1024];
  snprintf (buffer, 1024, "%s:\n%s", message1, message2);
  jbw_show_error (buffer);
}

/**
 * Function to display three error messages.
 */
static inline void
jbw_show_error3 (const char *message1,  ///< 1st error message.
                 const char *message2,  ///< 2nd error message.
                 const char *message3)  ///< 3rd error message.
{
  char buffer[1024];
  snprintf (buffer, 1024, "%s: %s\n%s", message1, message2, message3);
  jbw_show_error (buffer);
}

#elif JBW == JBW_GTK

#include <png.h>
#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_MODULE_H
#include <GL/glew.h>
#include <gtk/gtk.h>
#if HAVE_FREEGLUT
#include <GL/freeglut.h>
#elif HAVE_SDL
#include <SDL.h>
#elif HAVE_GLFW
#include <GLFW/glfw3.h>
#endif

/**
 * \def JBW_GRAPHIC_N_TYPES
 * \brief number of graphical file formats.
 * \def JBW_GRAPHIC_N_PATTERNS
 * \brief maximum number of graphical file format patterns.
 */
#if JBW_GRAPHIC_OUTPUT == JBW_GRAPHIC_OUTPUT_GDK_PIXBUF
#define JBW_GRAPHIC_N_TYPES 7
#define JBW_GRAPHIC_N_PATTERNS 4
#else
#define JBW_GRAPHIC_N_TYPES 1
#define JBW_GRAPHIC_N_PATTERNS 2
#endif

enum JBWEditorWidgetType
{
  JBW_EDITOR_WIDGET_TYPE_TEXT = 0,
  JBW_EDITOR_WIDGET_TYPE_INT = 1,
  JBW_EDITOR_WIDGET_TYPE_FLOAT = 2,
  JBW_EDITOR_WIDGET_TYPE_TIME = 3
};

typedef GtkSpinButton JBWFloatEntry;    ///< widget to work with float number.

typedef struct
{
  GLfloat matrix[16];           ///< projection matrix.
  GLfloat vertices[8];          ///< vertices.
  GLfloat square_texture[8];    ///< square texture vertices.
  GLushort elements[6];         ///< element indices.
  GLubyte *image;               ///< image bytes.
  GLint uniform_texture;        ///< texture constant.
  GLint attribute_texture;      ///< texture variable.
  GLint attribute_texture_position;     ///< texture variable position.
  GLint uniform_matrix;         ///< projection matrix.
  GLuint vbo;                   ///< vertices buffer object.
  GLuint ibo;                   ///< indices buffer object.
  GLuint vbo_texture;           ///< texture vertex buffer object.
  GLuint program_texture;       ///< texture program.
  GLuint id_texture;            ///< texture identifier.
  unsigned int width;           ///< image width.
  unsigned int height;          ///< image height.
  unsigned int nbytes;          ///< number of image bytes.
} JBWImage;                     ///< image widget.

/**
 * \struct JBWGraphic
 * \brief widget to drawing graphics.
 */
typedef struct _JBWGraphic JBWGraphic;
struct _JBWGraphic
{
  /* Involved macros */
  /* JBW_GRAPHIC_N_CHARS=Number of characters in an axis label */
  JBDOUBLE xtic[JBW_GRAPHIC_N_TICS];    ///< x-axis tics.
  JBDOUBLE ytic[JBW_GRAPHIC_N_TICS];    ///< y-axis tics.
  JBDOUBLE ztic[JBW_GRAPHIC_N_TICS];    ///< z-axis tics.
  void (*draw) (JBWGraphic * graphic);  ///< pointer to the draw function.
  int (*calculate) (JBWGraphic * graphic);
  ///< pointer to a calculate function.
  JBWImage *logo;               ///< logo.
#if HAVE_GTKGLAREA
  GtkWindow *window;            ///< GtkWindow window.
  GtkGLArea *widget;            ///< GtkGLArea widget.
#elif HAVE_FREEGLUT
  int window;                   ///< FreeGLUT window number.
#elif HAVE_SDL
  SDL_Window *window;           ///< SDL window.
#elif HAVE_GLFW
  GLFWwindow *window;           ///< GLFW window.
#endif
  FT_Library *ft;               ///< FreeType data.
  FT_Face *face;                ///< FreeType face to draw text.
  void *data;                   ///< user data.
  const char *str_title;        ///< title label.
  const char *str_x;            ///< x label.
  const char *str_y;            ///< 1st y label.
  const char *str_yy;           ///< 2nd y label.
  const char *str_z;            ///< 1st z label.
  const char *str_zz;           ///< 2nd z label.
  JBDOUBLE xmin;                ///< minimum x-range.
  JBDOUBLE xmax;                ///< maximum x-range.
  JBDOUBLE ymin;                ///< minimum y-range.
  JBDOUBLE ymax;                ///< maximum y-range.
  JBDOUBLE zmin;                ///< minimum y-range.
  JBDOUBLE zmax;                ///< maximum y-range.
  GLfloat sx;                   ///< x text scale factor.
  GLfloat sy;                   ///< y text scale factor.
  /* int type; ///< type of graphic (NOT IMPLEMENTED) */
  /* int legend; ///< legend drawing (NOT IMPLEMENTED) */
  int resize;
  ///< 1 if automatic range has to be set to extremal variable values.
  int grid;                     ///< 1 on grid drawing.
  int map;
  /// 1 if coordenates system has to be proportional to screen.
  int nx;                       ///< current number of x-axis labels.
  int ny;                       ///< current number of y-axis labels.
  int nz;                       ///< current number of z-axis labels.
  int nxmax;                    ///< maximum number of x-axis labels.
  int nymax;                    ///< maximum number of y-axis labels.
  int nzmax;                    ///< maximum number of z-axis labels.
  int x1;                       ///< minimum viewport x-coordinate.
  int x2;                       ///< maximum viewport x-coordinate.
  int y1;                       ///< minimum viewport y-coordinate.
  int y2;                       ///< maximum viewport y-coordinate.
  int minimum_width;            ///< minimum screen width.
  int minimum_height;           ///< maximum screen width.
  int width;                    ///< screen width.
  int height;                   ///< screen width.
  unsigned int char_width;      ///< character width.
  unsigned int char_height;     ///< character height.
  GLint in_2D_position;         ///< 2D position.
  GLint uniform_2D_color;       ///< 2D color.
  GLint uniform_2D_matrix;      ///< 2D matrix.
  GLint in_3D_position;         ///< 3D position.
  GLint uniform_3D_color;       ///< 3D color.
  GLint uniform_3D_matrix;      ///< 3D matrix.
  GLint in_2Dc_position;        ///< 2D with color position.
  GLint in_2Dc_color;           ///< 2D with color color.
  GLint uniform_2Dc_matrix;     ///< 2D with color matrix.
  GLint in_3Dc_position;        ///< 3D with color position.
  GLint in_3Dc_color;           ///< 3D with color color.
  GLint uniform_3Dc_matrix;     ///< 3D with color matrix.
  GLint in_text_position;       ///< text position.
  GLint uniform_text_color;     ///< text color.
  GLint uniform_text;           ///< text uniform.
  GLuint vbo_text;              ///< text vertex buffer object.
  GLuint program_2D;            ///< 2D program.
  GLuint program_3D;            ///< 3D program.
  GLuint program_2Dc;           ///< 2D program.
  GLuint program_3Dc;           ///< 3D program.
  GLuint program_text;          ///< text program.
};

typedef struct
{
  GtkScrolledWindow *scrolled;  ///< GtkScrolledWindow widget.
  GtkButton **button_numeric;   ///< array of row numeric GtkButton widgets.
  GtkButton **button_title;     ///< array of column title GtkButton widgets.
  GtkWidget ***matrix_entry;    ///< matrix of GtkWidget widgets.
  GtkGrid *table;               ///< GtkGrid widget.
  int *type;                    ///< array of widget types.
  int ncolumns;                 ///< number of columns.
  int nrows;                    ///< number of rows.
  int nfull;                    ///< number of full columns.
} JBWArrayEditor;               ///< widget to edit matrices.

#define jbw_signal_connect_swapped_after(instance, detailed_signal, c_handler, \
  data) \
      g_signal_connect_data((instance), (detailed_signal), (c_handler), \
      (data), 0, G_CONNECT_SWAPPED | G_CONNECT_AFTER)

#define jbw_float_entry_new (JBWFloatEntry*)gtk_entry_new

extern GtkWindow *window_parent;
extern const GLfloat jbw_black[4];
extern const GLfloat jbw_darkred[4];
extern const GLfloat jbw_darkgreen[4];
extern const GLfloat jbw_darkblue[4];
extern const GLfloat jbw_red[4];
extern const GLfloat jbw_brown[4];
extern const GLfloat jbw_green[4];
extern const GLfloat jbw_greenblue[4];
extern const GLfloat jbw_blue[4];
extern const GLfloat jbw_violet[4];
extern const GLfloat jbw_yellow[4];
extern const GLfloat jbw_pink[4];
extern const GLfloat jbw_lightblue[4];
extern const GLfloat jbw_starred[4];
extern const GLfloat jbw_stargreen[4];
extern const GLfloat jbw_starblue[4];
extern const GLfloat jbw_stargray[4];
extern const GLfloat jbw_white[4];

extern const GLfloat jbw_identity[16];

int jbw_init (int *argn, char ***argc);

void jbw_show_message (const char *title, const char *message,
                       GtkMessageType type);
void jbw_show_error (const char *message);
void jbw_show_error2 (const char *message1, const char *message2);
void jbw_show_error3 (const char *message1, const char *message2,
                      const char *message3);
void jbw_show_warning (const char *message);

void _jbw_combo_box_set_strings (GtkComboBoxText * combo, char **strings,
                                 int n);
GtkComboBoxText *jbw_combo_box_new_with_strings (char **strings, int n);

void jbw_array_radio_buttons_set_active (GtkRadioButton ** array, int n,
                                         int is_active);
int jbw_array_radio_buttons_get_active (GtkRadioButton ** array);

void jbw_float_entry_set_value_with_format (JBWFloatEntry * entry,
                                            char *format, JBDOUBLE value);
#if HIGH_PRECISION > 2
void jbw_float_entry_set_value (JBWFloatEntry * entry, JBDOUBLE value);
JBDOUBLE jbw_float_entry_get_value (JBWFloatEntry * entry);
#else
#define jbw_float_entry_set_value gtk_spin_button_set_value
#define jbw_float_entry_get_value gtk_spin_button_get_value
#endif

void jbw_draw_clear (GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
void jbw_draw_range (JBFLOAT * xmin, JBFLOAT * xmax);
void jbw_draw_rangel (JBDOUBLE * xmin, JBDOUBLE * xmax);
void jbw_draw_tics (JBFLOAT xmin, JBFLOAT xmax, int nlabels, int *n,
                    JBFLOAT * tic);
void jbw_draw_ticsl (JBDOUBLE xmin, JBDOUBLE xmax, int nlabels, int *n,
                     JBDOUBLE * tic);
void jbw_draw_orthogonal_matrix (GLint uniform, GLfloat x, GLfloat y,
                                 GLfloat w, GLfloat h);
void jbw_draw_orthogonal_matrixl (GLint uniform, GLdouble x, GLdouble y,
                                  GLdouble w, GLdouble h);

JBWImage *jbw_image_new (char *name);

#if HAVE_FREEGLUT
void jbw_freeglut_draw_resize (int width, int height);
void jbw_freeglut_draw ();
#endif

void jbw_graphic_destroy (JBWGraphic * graphic);
void jbw_graphic_init (JBWGraphic * graphic);
void jbw_graphic_resize (JBWGraphic * graphic, int width, int height);
void jbw_graphic_render (JBWGraphic * graphic);
void jbw_graphic_set_title (JBWGraphic *, const char *title);
void jbw_graphic_set_logo (JBWGraphic *, char *name);
JBWGraphic *jbw_graphic_new (unsigned int nx, unsigned int ny,
                             unsigned int nz,
                             void (*draw) (JBWGraphic * graphic),
                             const char *title);
void jbw_graphic_get_display_size (JBWGraphic * graphic);
void jbw_graphic_draw_text (JBWGraphic * graphic, const char *string,
                            GLfloat x, GLfloat y, const GLfloat * color);
void jbw_graphic_map_resize (JBWGraphic *);
void jbw_graphic_draw_resize (JBWGraphic * graphic, JBFLOAT * x, JBFLOAT * y1,
                              JBFLOAT * y2, JBFLOAT * z1, JBFLOAT * z2, int n);
void jbw_graphic_draw_resizel (JBWGraphic * graphic, JBDOUBLE * x,
                               JBDOUBLE * y1, JBDOUBLE * y2, JBDOUBLE * z1,
                               JBDOUBLE * z2, int n);
void jbw_graphic_draw_resizev (JBWGraphic * graphic, void *x, void *y1,
                               void *y2, void *z1, void *z2,
                               unsigned int size, int n);
void jbw_graphic_draw_resizevl (JBWGraphic * graphic, void *x, void *y1,
                                void *y2, void *z1, void *z2,
                                unsigned int size, int n);
void jbw_graphic_draw_rectangles_color (JBWGraphic * graphic,
                                        GLfloat * vertex, GLushort * index,
                                        unsigned int n);
void jbw_graphic_draw_farray (JBWGraphic * graphic, JBFLOAT * x, JBFLOAT * y,
                              unsigned int n, const GLfloat * color,
                              GLenum type);
void jbw_graphic_draw_darray (JBWGraphic * graphic, JBDOUBLE * x,
                              JBDOUBLE * y, unsigned int n,
                              const GLfloat * color, GLenum type);
void jbw_graphic_draw_rectangle (JBWGraphic * graphic, JBFLOAT x1, JBFLOAT y1,
                                 JBFLOAT x2, JBFLOAT y2, const GLfloat * color);
void jbw_graphic_draw_rectanglel (JBWGraphic * graphic, JBDOUBLE x1,
                                  JBDOUBLE y1, JBDOUBLE x2, JBDOUBLE y2,
                                  const GLfloat * color);
void jbw_graphic_draw_labels (JBWGraphic * graphic);
void jbw_graphic_draw_logo (JBWGraphic * graphic);
void jbw_graphic_draw_lines (JBWGraphic * graphic, JBFLOAT * x, JBFLOAT * y1,
                             JBFLOAT * y2, JBFLOAT * z1, JBFLOAT * z2, int n);
void jbw_graphic_draw_linesl (JBWGraphic * graphic, JBDOUBLE * x,
                              JBDOUBLE * y1, JBDOUBLE * y2, JBDOUBLE * z1,
                              JBDOUBLE * z2, int n);
void jbw_graphic_draw_linesv (JBWGraphic * graphic, void *x, void *y1,
                              void *y2, void *z1, void *z2, unsigned int size,
                              int n);
void jbw_graphic_draw_linesvl (JBWGraphic * graphic, void *x, void *y1,
                               void *y2, void *z1, void *z2,
                               unsigned int size, int n);
void jbw_graphic_save (JBWGraphic * graphic, char *file_name);
void jbw_graphic_dialog_save (JBWGraphic * graphic);
void jbw_graphic_main_loop (JBWGraphic * graphic);

void jbw_array_editor_check_column (JBWArrayEditor * editor, int column,
                                    int type);
void jbw_array_editor_set_element (JBWArrayEditor * editor, int row,
                                   int column, const char *str);
char *jbw_array_editor_get_element (JBWArrayEditor * editor, int row,
                                    int column);
void jbw_array_editor_set_element_int (JBWArrayEditor * editor, int row,
                                       int column, long int x);
long int jbw_array_editor_get_element_int (JBWArrayEditor * editor, int row,
                                           int column);
void jbw_array_editor_set_element_float (JBWArrayEditor * editor, int row,
                                         int column, JBDOUBLE x);
JBDOUBLE jbw_array_editor_get_element_float (JBWArrayEditor * editor, int row,
                                             int column);
void jbw_array_editor_set_element_time (JBWArrayEditor * editor, int row,
                                        int column, JBDOUBLE t);
JBDOUBLE jbw_array_editor_get_element_time (JBWArrayEditor * editor, int row,
                                            int column);
void jbw_array_editor_set_column (JBWArrayEditor * editor, int column,
                                  char **c);
void jbw_array_editor_get_column (JBWArrayEditor * editor, int column,
                                  char **c);
void jbw_array_editor_set_column_int (JBWArrayEditor * editor, int column,
                                      long int *x);
void jbw_array_editor_get_column_int (JBWArrayEditor * editor, int column,
                                      long int *x);
void jbw_array_editor_set_column_float (JBWArrayEditor * editor, int column,
                                        JBFLOAT * x);
void jbw_array_editor_set_column_floatl (JBWArrayEditor * editor, int column,
                                         JBDOUBLE * x);
void jbw_array_editor_get_column_float (JBWArrayEditor * editor, int column,
                                        JBFLOAT * x);
void jbw_array_editor_get_column_floatl (JBWArrayEditor * editor, int column,
                                         JBDOUBLE * x);
void jbw_array_editor_set_column_time (JBWArrayEditor * editor, int column,
                                       JBDOUBLE * t);
void jbw_array_editor_get_column_time (JBWArrayEditor * editor, int column,
                                       JBDOUBLE * t);
void jbw_array_editor_set_column_sensitive (JBWArrayEditor * editor,
                                            int column, int sensitive);
void jbw_array_editor_show_column (JBWArrayEditor * editor, int column);
void jbw_array_editor_hide_column (JBWArrayEditor * editor, int column);
void jbw_array_editor_insert_row (JBWArrayEditor * editor, int row);
void jbw_array_editor_remove_row (JBWArrayEditor * editor, int row);
void jbw_array_editor_set_rows (JBWArrayEditor * editor, int n);
void jbw_array_editor_set_title (JBWArrayEditor * editor, int column,
                                 char *title);
void jbw_array_editor_destroy (JBWArrayEditor * editor);
JBWArrayEditor *jbw_array_editor_new (int ncolumns, int nfull, int nrows,
                                      const int *types, const char **label);
/**
 * Function to set the resize property of a JBWGraphic widget.
 */
static inline void
jbw_graphic_set_resize (JBWGraphic * graphic,   ///< JBWGraphic widget.
                        int resize)     ///< 1 if automatic bounds resize.
{
  graphic->resize = resize;
}

/**
 * Function to set the grid property of a JBWGraphic widget.
 */
static inline void
jbw_graphic_set_grid (JBWGraphic * graphic,     ///< JBWGraphic widget.
                      int grid) ///< 1 if visible grid.
{
  graphic->grid = grid;
}

/**
 * Function to set the x label of a JBWGraphic widget.
 */
static inline void
jbw_graphic_set_xlabel (JBWGraphic * graphic,   ///< JBWGraphic widget.
                        const char *str_x)      ///< x label.
{
  graphic->str_x = str_x;
}

/**
 * Function to set the 1st y label of a JBWGraphic widget.
 */
static inline void
jbw_graphic_set_ylabel (JBWGraphic * graphic,   ///< JBWGraphic widget.
                        const char *str_y)      ///< 1st y label.
{
  graphic->str_y = str_y;
}

/**
 * Function to set the 2nd y label of a JBWGraphic widget.
 */
static inline void
jbw_graphic_set_yylabel (JBWGraphic * graphic,  ///< JBWGraphic widget.
                         const char *str_yy)    ///< 2nd y label.
{
  graphic->str_yy = str_yy;
}

/**
 * Function to set the 1st z label of a JBWGraphic widget.
 */
static inline void
jbw_graphic_set_zlabel (JBWGraphic * graphic,   ///< JBWGraphic widget.
                        const char *str_z)      ///< 1st z label.
{
  graphic->str_z = str_z;
}

/**
 * Function to set the 2nd z label of a JBWGraphic widget.
 */
static inline void
jbw_graphic_set_zzlabel (JBWGraphic * graphic,  ///< JBWGraphic widget.
                         const char *str_zz)    ///< 2nd z label.
{
  graphic->str_zz = str_zz;
}

/**
 * Function to set the draw function of a JBWGraphic widget.
 */
static inline void
jbw_graphic_set_draw (JBWGraphic * graphic,     ///< JBWGraphic widget.
                      void (*draw) (JBWGraphic *))
                      ///< draw function pointer.
{
  graphic->draw = draw;
}

/**
 * Function to set the minimum size allowed of a JBWGraphic widget.
 */
static inline void
jbw_graphic_set_size_request (JBWGraphic * graphic,     ///< JBWGraphic widget.
                              int width,        ///< minimum width.
                              int height)       ///< minimum height.
{
  graphic->minimum_width = width;
  graphic->minimum_height = height;
#if HAVE_GTKGLAREA
  gtk_widget_set_size_request (GTK_WIDGET (graphic->widget), width, height);
#elif HAVE_SDL
  SDL_SetWindowMinimumSize (graphic->window, width, height);
#elif HAVE_GLFW
  glfwSetWindowSizeLimits (graphic->window, width, height, GLFW_DONT_CARE,
                           GLFW_DONT_CARE);
#endif
}

/**
 * Function to set a calculate function on a JBWGraphic widget.
 */
static inline void
jbw_graphic_set_calculate (JBWGraphic * graphic,        ///< JBWGraphic widget.
                           int (*calculate) (JBWGraphic * graphic))
                                 ///< calculate function.
{
  graphic->calculate = calculate;
}

/**
 * Function to set user data on a JBWGraphic widget.
 */
static inline void
jbw_graphic_set_data (JBWGraphic * graphic,     ///< JBWGraphic widget.
                      void *data)       ///< user data.
{
  graphic->data = data;
}

/**
 * Function to quit a main loop in a JBWGraphic widget.
 */
static inline void
jbw_graphic_main_loop_quit (JBWGraphic * graphic __attribute__((unused)))
  ///< JBWGraphic struct.
{
#if HAVE_GTKGLAREA
  gtk_main_quit ();
#elif HAVE_FREEGLUT
  glutLeaveMainLoop ();
#elif HAVE_SDL
  SDL_Event event[1];
  event->type = SDL_QUIT;
  SDL_PushEvent (event);
#elif HAVE_GLFW
  glfwDestroyWindow (graphic->window);
#endif
}

/**
 * Function to show the JBWGraphic widget.
 */
#if HAVE_GTKGLAREA
static inline void
jbw_graphic_show (JBWGraphic * graphic) ///< JBWGraphic widget.
{
  GtkWidget *w;
  w = graphic->window ? GTK_WIDGET (graphic->window)
    : GTK_WIDGET (graphic->widget);
  gtk_widget_show_all (w);
}
#endif

#endif

#endif
