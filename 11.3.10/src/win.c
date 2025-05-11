/* JB - A library with useful mathematical, XML, GTK and OpenGL functions.
 *
 * Copyright 2005-2025, Javier Burguete Tolosa.
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
 * \file win.c
 * \brief Source file with useful display functions.
 * \author Javier Burguete Tolosa.
 * \copyright Copyright 2005-2025, Javier Burguete Tolosa.
 */
#include "win.h"

#if JBW == JBW_NO

static void
jbw_show_message (const char *title, const char *message)
{
  printf ("%s: %s\n", title, message);
}

void
jbw_error_show_terminal (void)
{
  jbw_show_message (_("Error!"), jb_error_message);
}

void
jbw_warning_show_terminal (void)
{
  jbw_show_message (_("Warning!"), jb_warning_message);
}

#elif JBW == JBW_GTK

GdkGLContext *jbw_gdk_gl_context;
///< GdkGLContext OpenGL context used in GTK widgets.
JBWGraphic *jbw_graphic_pointer;
///< pointer to the JBWGraphic current widget.

#if HAVE_VULKAN

#define DEBUG_VULKAN 1          ///< macro to debug Vulkan functions.

const char *jbw_required_device_extensions[JBW_VK_N_DEVICE_EXTENSIONS]
  = { VK_KHR_SWAPCHAIN_EXTENSION_NAME };
///< required Vulkan device extensions.

#if DEBUG_VULKAN
const char *jbw_required_validation_layers[JBW_VK_N_VALIDATION_LAYERS] =
  { "VK_LAYER_KHRONOS_validation" };
///< required validation layers.
#endif

#endif

GtkWindow *window_parent;       ///< pointer to the parent GtkWindow struct.

///> black color intensities array.
const GLfloat jbw_black[4] = { 0.f, 0.f, 0.f, 1.f };

///> dark red color intensities array.
const GLfloat jbw_darkred[4] = { 0.5f, 0.f, 0.f, 1.f };

///> dark green color intensities array.
const GLfloat jbw_darkgreen[4] = { 0.f, 0.5f, 0.f, 1.f };

///> dark blue color intensities array.
const GLfloat jbw_darkblue[4] = { 0.f, 0.f, 0.5f, 1.f };

///> red color intensities array.
const GLfloat jbw_red[4] = { 1.f, 0.f, 0.f, 1.f };

///> brown color intensities array.
const GLfloat jbw_brown[4] = { 0.5f, 0.5f, 0.f, 1.f };

///> green color intensities array.
const GLfloat jbw_green[4] = { 0.f, 1.f, 0.f, 1.f };

///> green-blue color intensities array.
const GLfloat jbw_greenblue[4] = { 0.f, 1.f, 0.f, 1.f };

///> blue color intensities array.
const GLfloat jbw_blue[4] = { 0.f, 0.f, 1.f, 1.f };

///> violet color intensities array.
const GLfloat jbw_violet[4] = { 0.5f, 0.f, 0.5f, 1.f };

///> yellow color intensities array.
const GLfloat jbw_yellow[4] = { 1.f, 1.f, 0.f, 1.f };

///> pink color intensities array.
const GLfloat jbw_pink[4] = { 1.f, 0.f, 1.f, 1.f };

///> light blue color intensities array.
const GLfloat jbw_lightblue[4] = { 0.f, 1.f, 1.f, 1.f };

///> very light red
const GLfloat jbw_starred[4] = { 1.f, 0.85f, 0.85f, 1.f };

///> very light green
const GLfloat jbw_stargreen[4] = { 0.85f, 1.f, 0.85f, 1.f };

///> very light blue
const GLfloat jbw_starblue[4] = { 0.85f, 0.85f, 1.f, 1.f };

///> very light gray
const GLfloat jbw_stargray[4] = { 0.9f, 0.9f, 0.9f, 1.f };

///> white color intensities array.
const GLfloat jbw_white[4] = { 1.f, 1.f, 1.f, 1.f };

const GLfloat jbw_identity[16] = {
  1.f, 0.f, 0.f, 0.f,
  0.f, 1.f, 0.f, 0.f,
  0.f, 0.f, 1.f, 0.f,
  0.f, 0.f, 0.f, 1.f
};                              ///< identity matrix.

#if HAVE_GTKGLAREA
int (*jbw_graphic_loop_idle) (void) = NULL;
GMainLoop *jbw_graphic_loop_pointer = NULL;
///< pointer to the idle function on a main loop.
#elif HAVE_SDL
int (*jbw_graphic_loop_idle) (void) = NULL;
///< pointer to the idle function on a main loop.
void (*jbw_graphic_loop_resize) (int width, int height) = NULL;
///< pointer to the resize function on a main loop.
void (*jbw_graphic_loop_render) (void) = NULL;
///< pointer to the render function on a main loop.
#elif HAVE_GLFW
int (*jbw_graphic_loop_idle) (void) = NULL;
///< pointer to the idle function on a main loop.
void (*jbw_graphic_loop_render) (void) = NULL;
///< pointer to the render function on a main loop.
unsigned int jbw_graphic_loop_exit;
///< 1 on exit main loop, 0 on continue.
#endif

/**
 * Function to init locales in the JB library with GTK interface.
 *
 * \return 1 on success, 0 on error.
 */
int
jbw_init_gtk (int *argn __attribute__((unused)),
              ///< pointer to the number of command line arguments.
              char ***argc __attribute__((unused)))
  ///< pointer to the command line arguments.
{
  jb_init ();
#if HAVE_SDL
  if (SDL_Init (SDL_INIT_VIDEO))
    {
      printf ("%s:\n%s\n", _("unable to init SDL"), SDL_GetError ());
      return 0;
    }
#elif HAVE_GLFW
  if (!glfwInit ())
    {
      printf ("%s\n", _("unable to init GLFW"));
      return 0;
    }
#endif
  gtk_disable_setlocale ();
#if GTK_MAJOR_VERSION > 3
  gtk_init ();
#else
  gtk_init (argn, argc);
#endif
  jbw_graphic_pointer = NULL;
  return 1;
}

/**
 * Function to process events on long computation.
 */
void
jbw_process_pending (void)
{
  GMainContext *context = g_main_context_default ();
  while (g_main_context_pending (context))
    g_main_context_iteration (context, 0);
}

/**
 * Function to display a message.
 */
void
jbw_show_message_gtk (const char *title,        ///< message title.
                      const char *message,      ///< message.
                      GtkMessageType type)      ///< message type.
{
  GtkMessageDialog *dlg;
  GMainLoop *loop;
  dlg = (GtkMessageDialog *) gtk_message_dialog_new
    (window_parent, GTK_DIALOG_MODAL, type, GTK_BUTTONS_OK, "%s", message);
  gtk_window_set_title (GTK_WINDOW (dlg), title);
#if GTK_MAJOR_VERSION > 3
  gtk_window_present (GTK_WINDOW (dlg));
  g_signal_connect (GTK_WINDOW (dlg), "response",
                    G_CALLBACK (gtk_window_destroy), NULL);
#else
  gtk_widget_show_all (GTK_WIDGET (dlg));
  g_signal_connect (GTK_WIDGET (dlg), "response",
                    G_CALLBACK (gtk_widget_destroy), NULL);
#endif
  loop = g_main_loop_new (NULL, 0);
  g_signal_connect_swapped (dlg, "destroy", G_CALLBACK (g_main_loop_quit),
                            loop);
  g_main_loop_run (loop);
  g_main_loop_unref (loop);
}

/**
 * Function to display an error message.
 */
void
jbw_error_show_gtk (void)
{
  jbw_show_message_gtk (_("Error!"), jb_error_message, GTK_MESSAGE_ERROR);
}

/**
 * Function to display a warning message.
 */
void
jbw_warning_show_gtk (void)
{
  jbw_show_message_gtk (_("Warning!"), jb_warning_message, GTK_MESSAGE_WARNING);
}

/**
 * Function to set the strings of a GtkComboBoxText from an array of strings.
 */
void
jbw_combo_box_set_strings (GtkComboBoxText *combo,
                           ///< GtkComboBoxText struct.
                           char **strings,      ///< array of strings.
                           int n)       ///< strings number.
{
  int i;
  gtk_combo_box_text_remove_all (combo);
  for (i = 0; i < n; ++i)
    gtk_combo_box_text_append_text (combo, strings[i]);
}

/**
 * Function to create a GtkComboBoxText from an array of strings.
 *
 * \return new GtkComboBoxText struct data.
 */
GtkComboBoxText *
jbw_combo_box_new_with_strings (char **strings, ///< array of strings.
                                int n)  ///< strings number.
{
  int i;
  GtkComboBoxText *combo = (GtkComboBoxText *) gtk_combo_box_text_new ();
  if (!combo)
    return 0;
  for (i = 0; i < n; ++i)
    gtk_combo_box_text_append_text (combo, strings[i]);
  gtk_combo_box_set_active (GTK_COMBO_BOX (combo), 0);
  return combo;
}

/**
 * Function to set a JBWFloatEntry struct with a formated floating point value.
 */
void
jbw_float_entry_set_value_with_format (JBWFloatEntry *entry,
                                       ///< JBWFloatEntry struct.
                                       char *format,    ///< c-format string.
                                       JBDOUBLE value)
                                       ///< floating point value.
{
  char buffer[64];
  SNPRINTFL (buffer, 64, format, value);
  gtk_entry_set_text (GTK_ENTRY (entry), buffer);
}

#if JBM_HIGH_PRECISION > 2

/**
 * Function to set a JBWFloatEntry struct with a floating point value.
 */
void
jbw_float_entry_set_value (JBWFloatEntry *entry,
                           ///< JBWFloatEntry struct.
                           JBDOUBLE value)      ///< floating point value.
{
  jbw_float_entry_set_value_with_format (entry, FPL, value);
}

/**
 * Function to get a floating point value from a JBWFloatEntry struct.
 *
 * \return floating point value.
 */
JBDOUBLE
jbw_float_entry_get_value (JBWFloatEntry *entry)
///< JBWFloatEntry struct.
{
  JBDOUBLE value;
  jbm_get_double (gtk_entry_get_text ((GtkEntry *) entry), &value);
  return value;
}

#endif

/**
 * Function to get the active widget.
 *
 * \return index of the active widget.
 */
unsigned int
jbw_array_buttons_get_active (
#if GTK_MAJOR_VERSION > 3
                               GtkCheckButton *array[],
                               ///< array of GtkCheckButtons.
#else
                               GtkRadioButton *array[],
                               ///< array of GtkRadioButtons.
#endif
                               unsigned int n)  ///< number of widgets.
{
  unsigned int i;
  for (i = 0; i < n; ++i)
    if (gtk_check_button_get_active (array[i]))
      break;
  return i;
}

/**
 * Function to set the screen background.
 */
void
jbw_draw_clear (GLfloat red,    ///< red color intensity.
                GLfloat green,  ///< green color intensity.
                GLfloat blue,   ///< blue color intensity.
                GLfloat alpha)  ///< alpha color intensity.
{
  glClearColor (red, green, blue, alpha);
  glClear (GL_COLOR_BUFFER_BIT);
}

/**
 * Function to set minimum and maximum graphical values (JBFLOAT).
 */
void
jbw_draw_range (JBFLOAT *xmin,  ///< minimum graphical value.
                JBFLOAT *xmax)  ///< maximum graphical value.
{
  JBFLOAT m;
  m = FMAX (FABS (*xmax), FABS (*xmin));
  if (jbm_small (m))
    {
      *xmin = -1.;
      *xmax = 1.;
    }
  else if ((*xmax - *xmin) / m < 0.0001)
    {
      *xmin *= 0.9999;
      *xmax *= 1.0001;
    }
}

/**
 * Function to set minimum and maximum graphical values (JBDOUBLE).
 */
void
jbw_draw_rangel (JBDOUBLE *xmin,        ///< minimum graphical value.
                 JBDOUBLE *xmax)        ///< maximum graphical value.
{
  JBDOUBLE m;
  m = FMAXL (FABSL (*xmax), FABSL (*xmin));
  if (jbm_smalll (m))
    {
      *xmin = -1.L;
      *xmax = 1.L;
    }
  else if ((*xmax - *xmin) / m < 0.0001L)
    {
      *xmin *= 0.9999L;
      *xmax *= 1.0001L;
    }
}

/**
 * Function to set the tics on a graphical axis (JBFLOAT).
 */
void
jbw_draw_tics (JBFLOAT xmin,    ///< minimum axis value.
               JBFLOAT xmax,    ///< maximum axis value.
               int nlabels,     ///< maximum number of labels.
               int *n,          ///< number of tics.
               JBFLOAT *tic)    ///< array of tic values.
{
  int k1, k2;
  JBFLOAT h, s, k;
  *n = 0;
  h = (xmax - xmin) / (nlabels - 1);
  if (h <= 0.)
    return;
  s = EXP10 (FLOOR (LOG10 (h)));
  k = h / s;
  if (k > 5.)
    s *= 10.;
  else if (k > 2.5)
    s *= 5.;
  else if (k > 2.)
    s *= 2.5;
  else if (k > 1.)
    s += s;
  for (k1 = (int) CEIL (xmin / s), k2 =
       (int) FLOOR (xmax / s); k1 <= k2; ++k1, ++tic)
    {
      ++(*n);
      *tic = k1 * s;
    }
}

/**
 * Function to set the tics on a graphical axis (JBDOUBLE).
 */
void
jbw_draw_ticsl (JBDOUBLE xmin,  ///< minimum axis value.
                JBDOUBLE xmax,  ///< maximum axis value.
                int nlabels,    ///< maximum number of labels.
                int *n,         ///< number of tics.
                JBDOUBLE *tic)  ///< array of tic values.
{
  int k1, k2;
  JBDOUBLE h, s, k;
  *n = 0;
  h = (xmax - xmin) / (nlabels - 1);
  if (h <= 0.L)
    return;
  s = EXP10L (FLOORL (LOG10L (h)));
  k = h / s;
  if (k > 5.L)
    s *= 10.L;
  else if (k > 2.5L)
    s *= 5.L;
  else if (k > 2.L)
    s *= 2.5L;
  else if (k > 1.L)
    s += s;
  for (k1 = (int) CEILL (xmin / s), k2 =
       (int) FLOORL (xmax / s); k1 <= k2; ++k1, ++tic)
    {
      ++(*n);
      *tic = k1 * s;
    }
}

/**
 * Function to set an orthogonal 2D projection matrix.
 */
void
jbw_draw_orthogonal_matrix (GLint uniform_matrix,
                            ///< OpenGL uniform matrix.
                            GLfloat x,  ///< minimum x-coordinate.
                            GLfloat y,  ///< minimum y-coordinate.
                            GLfloat w,  ///< width.
                            GLfloat h)  ///< length.
{
  GLfloat matrix[16];
  matrix[1] = matrix[2] = matrix[3] = matrix[4] = matrix[6] = matrix[7]
    = matrix[8] = matrix[9] = matrix[10] = matrix[11] = matrix[14] = 0.f;
  matrix[15] = 1.f;
  matrix[0] = 2.f / w;
  matrix[12] = -1.f - matrix[0] * x;
  matrix[5] = 2.f / h;
  matrix[13] = -1.f - matrix[5] * y;
  glUniformMatrix4fv (uniform_matrix, 1, GL_FALSE, matrix);
}

/**
 * Function to set an orthogonal 2D projection matrix.
 */
void
jbw_draw_orthogonal_matrixl (GLint uniform_matrix,
                             ///< OpenGL uniform matrix.
                             GLdouble x,        ///< minimum x-coordinate.
                             GLdouble y,        ///< minimum y-coordinate.
                             GLdouble w,        ///< width.
                             GLdouble h)        ///< length.
{
#if JBW_OPEN_GL_OLD
  GLfloat matrix[16];
#else
  GLdouble matrix[16];
#endif
  matrix[1] = matrix[2] = matrix[3] = matrix[4] = matrix[6] = matrix[7]
    = matrix[8] = matrix[9] = matrix[10] = matrix[11] = matrix[14] = 0.;
  matrix[15] = 1.;
  matrix[0] = 2. / w;
  matrix[12] = -1. - matrix[0] * x;
  matrix[5] = 2. / h;
  matrix[13] = -1. - matrix[5] * y;
#if JBW_OPEN_GL_OLD
  glUniformMatrix4fv (uniform_matrix, 1, GL_FALSE, matrix);
#else
  glUniformMatrix4dv (uniform_matrix, 1, GL_FALSE, matrix);
#endif
}

/**
 * Function to show an error opening the JBWImage widget.
 */
static void
jbw_image_error (void)
{
  jb_error_add ("JBWImage", "\n", NULL);
  jb_error_show ();
  jb_error_destroy ();
}

/**
 * Function to free the memory used by a JBWImage widget.
 */
static void
jbw_image_delete (JBWImage *image)      ///< JBWImage widget.
{
  glDeleteProgram (image->program_texture);
  if (image->vbo_texture)
    glDeleteBuffers (1, &image->vbo_texture);
  if (image->ibo)
    glDeleteBuffers (1, &image->ibo);
  if (image->vbo)
    glDeleteBuffers (1, &image->vbo);
  if (image->id_texture)
    glDeleteTextures (1, &image->id_texture);
  g_free (image->image);
  g_free (image);
}

/**
 * Function to init the OpenGL functions on a JBWImage widget.
 */
static void
jbw_image_init (JBWImage *image,        ///< JBWImage widget.
                const char *gl_version) ///< OpenGL GLSL version string.
{
  const char *vs_texture_source =
    "in vec2 position;"
    "in vec2 texture_position;"
    "uniform mat4 matrix;"
    "out vec2 t_position;"
    "void main()"
    "{"
    "gl_Position=matrix*vec4 (position,0.f,1.f);"
    "t_position=texture_position;" "}";
  const char *fs_texture_source =
    "uniform sampler2D texture_image;"
    "out vec2 t_position;"
    "void main()" "{" "gl_FragColor=texture2D(texture_image,t_position);" "}";
  const char *vertex_name = "position";
  const char *texture_name = "texture_image";
  const char *texture_position_name = "texture_position";
  const char *matrix_name = "matrix";
  const char *vs_texture_sources[2] = { gl_version, vs_texture_source };
  const char *fs_texture_sources[2] = { gl_version, fs_texture_source };
  const GLfloat matrix[16] = {
    1.f, 0.f, 0.f, 0.f,
    0.f, 1.f, 0.f, 0.f,
    0.f, 0.f, 1.f, 0.f,
    0.f, 0.f, 0.f, 1.f
  };
  const GLfloat vertices[8] = {
    -1.f, 1.f,
    -1.f, -1.f,
    1.f, -1.f,
    1.f, 1.f
  };
  const GLfloat square_texture[8] = {
    0.0, 1.0,
    0.0, 0.0,
    1.0, 0.0,
    1.0, 1.0
  };
  const GLushort elements[6] = {
    0, 1, 2,
    2, 3, 0
  };
  GLint error_code;
  GLuint fs, vs;

  // setting up matrices and vertices
  image->id_texture = image->vbo = image->ibo = image->vbo_texture = 0;
  memcpy (image->matrix, matrix, 16 * sizeof (GLfloat));
  memcpy (image->vertices, vertices, 8 * sizeof (GLfloat));
  memcpy (image->square_texture, square_texture, 8 * sizeof (GLfloat));
  memcpy (image->elements, elements, 6 * sizeof (GLushort));

  // compiling texture fragment shader
  fs = glCreateShader (GL_FRAGMENT_SHADER);
  glShaderSource (fs, 2, fs_texture_sources, NULL);
  glCompileShader (fs);
  glGetShaderiv (fs, GL_COMPILE_STATUS, &error_code);
  if (!error_code)
    {
      glDeleteShader (fs);
      jb_error_add (_("unable to compile the texture fragment shader"), NULL);
      goto end;
    }

  // compiling vertex shader
  vs = glCreateShader (GL_VERTEX_SHADER);
  glShaderSource (vs, 2, vs_texture_sources, NULL);
  glCompileShader (vs);
  glGetShaderiv (vs, GL_COMPILE_STATUS, &error_code);
  if (!error_code)
    {
      glDeleteShader (fs);
      glDeleteShader (vs);
      jb_error_add (_("unable to compile the texture vertex shader"), NULL);
      goto end;
    }

  // linking texture program
  image->program_texture = glCreateProgram ();
  glAttachShader (image->program_texture, fs);
  glAttachShader (image->program_texture, vs);
  glLinkProgram (image->program_texture);
  glDetachShader (image->program_texture, vs);
  glDetachShader (image->program_texture, fs);
  glDeleteShader (fs);
  glDeleteShader (vs);
  glGetProgramiv (image->program_texture, GL_LINK_STATUS, &error_code);
  if (!error_code)
    {
      jb_error_add (_("unable to link the texture program"), NULL);
      goto end;
    }

  // setting up the texture
  glActiveTexture (GL_TEXTURE0);
  glGenTextures (1, &image->id_texture);
  glBindTexture (GL_TEXTURE_2D, image->id_texture);
  glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexImage2D (GL_TEXTURE_2D,  // target
                0,              // level, 0 = base, no minimap,
                GL_RGBA,        // internalformat
                image->width,   // width
                image->height,  // height
                0,              // border, always 0 in OpenGL ES
                GL_RGBA,        // format
                GL_UNSIGNED_BYTE,       // type
                image->image);  // image data

  // setting up the shader attributes
  image->attribute_texture
    = glGetAttribLocation (image->program_texture, vertex_name);
  if (image->attribute_texture == -1)
    {
      jb_error_add (_("could not bind texture attribute"), NULL);
      goto end;
    }
  image->attribute_texture_position
    = glGetAttribLocation (image->program_texture, texture_position_name);
  if (image->attribute_texture_position == -1)
    {
      jb_error_add (_("could not bind texture position attribute"), NULL);
      goto end;
    }
  image->uniform_texture
    = glGetUniformLocation (image->program_texture, texture_name);
  if (image->uniform_texture == -1)
    {
      jb_error_add (_("could not bind texture uniform"), NULL);
      goto end;
    }
  image->uniform_matrix
    = glGetUniformLocation (image->program_texture, matrix_name);
  if (image->uniform_matrix == -1)
    {
      jb_error_add (_("could not bind matrix uniform"), NULL);
      goto end;
    }

  // setting up the OpenGL buffers
  glGenBuffers (1, &image->vbo);
  glBindBuffer (GL_ARRAY_BUFFER, image->vbo);
  glBufferData (GL_ARRAY_BUFFER, sizeof (image->vertices), image->vertices,
                GL_STATIC_DRAW);
  glGenBuffers (1, &image->ibo);
  glBindBuffer (GL_ELEMENT_ARRAY_BUFFER, image->ibo);
  glBufferData (GL_ELEMENT_ARRAY_BUFFER, sizeof (image->elements),
                image->elements, GL_STATIC_DRAW);
  glGenBuffers (1, &image->vbo_texture);
  glBindBuffer (GL_ARRAY_BUFFER, image->vbo_texture);
  glBufferData (GL_ARRAY_BUFFER, sizeof (image->square_texture),
                image->square_texture, GL_STATIC_DRAW);

  // ending on success
  return;

  // ending on error
end:
  if (jb_error_message)
    {
      jbw_image_error ();
      exit (0);
    }
}

/**
 * Function to create a new JBWImage widget from a PNG file.
 */
JBWImage *
jbw_image_new (const char *name)        ///< PNG file name.
{
  JBWImage *image = NULL;
  png_struct *png;
  png_info *info;
  png_byte **row_pointers;
  FILE *file;
  unsigned int i, row_bytes;

  // starting png structs
  png = png_create_read_struct (PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
  info = png_create_info_struct (png);

  // opening file
  file = fopen (name, "rb");
  if (!file)
    {
      jb_error_add (_("unable to open the file"), NULL);
      goto error1;
    }

  // reading file and transforming to 8 bits RGBA format
  if (setjmp (png_jmpbuf (png)))
    {
      jb_error_add (_("unable to open the PNG file"), NULL);
      goto error2;
    }
  png_init_io (png, file);
  if (setjmp (png_jmpbuf (png)))
    {
      jb_error_add (_("unable to open the PNG file"), NULL);
      goto error2;
    }
  png_read_png (png,
                info,
                PNG_TRANSFORM_STRIP_16 |
                PNG_TRANSFORM_PACKING | PNG_TRANSFORM_EXPAND, NULL);

  // creating the image struct data
  image = (JBWImage *) g_try_malloc (sizeof (JBWImage));
  if (!image)
    {
      jb_error_add (_("not enough memory to open the widget"), NULL);
      goto error2;
    }

  // copying pixels in the OpenGL order
  image->width = png_get_image_width (png, info);
  image->height = png_get_image_height (png, info);
  row_bytes = png_get_rowbytes (png, info);
  image->nbytes = row_bytes * image->height;
  image->image = (GLubyte *) g_try_malloc (image->nbytes);
  if (!image->image)
    {
      g_free (image);
      image = NULL;
      jb_error_add (_("not enough memory to open the image"), NULL);
      goto error2;
    }
  row_pointers = png_get_rows (png, info);
  for (i = 0; i < image->height; i++)
    memcpy (image->image +
            (row_bytes * (image->height - 1 - i)), row_pointers[i], row_bytes);

error2:
  // closing file
  fclose (file);

error1:
  // freeing png memory
  png_destroy_read_struct (&png, &info, NULL);

  // showing error message
  if (!image)
    jbw_image_error ();

  return image;
}

/**
 * Function to draw a JBWImage widget.
 */
void
jbw_image_draw (JBWImage *image,        ///< JBWImage struct.
                unsigned int x, ///< image x-coordinate. 
                unsigned int y, ///< image y-coordinate. 
                unsigned int width,     ///< window width.
                unsigned int height)    ///< window height.
{
  float cp, sp;

  // enabling OpenGL properties
  glEnable (GL_BLEND);
  glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glViewport (0, 0, width, height);

  // setting up the projection matrix
  cp = ((float) image->width) / width;
  sp = ((float) image->height) / height;
  image->matrix[0] = cp;
  image->matrix[5] = sp;
  image->matrix[12] = cp - 1.f + (2.f * x) / width;
  image->matrix[13] = sp - 1.f + (2.f * y) / height;

  // rendering
  glUseProgram (image->program_texture);
  glUniformMatrix4fv (image->uniform_matrix, 1, GL_FALSE, image->matrix);
  glUniform1i (image->uniform_texture, 0);
  glBindTexture (GL_TEXTURE_2D, image->id_texture);
  glBindBuffer (GL_ARRAY_BUFFER, image->vbo_texture);
  glEnableVertexAttribArray (image->attribute_texture_position);
  glVertexAttribPointer (image->attribute_texture_position,
                         2, GL_FLOAT, GL_FALSE, 0, 0);
  glBindBuffer (GL_ARRAY_BUFFER, image->vbo);
  glEnableVertexAttribArray (image->attribute_texture);
  glVertexAttribPointer (image->attribute_texture, 2, GL_FLOAT, GL_FALSE, 0, 0);
  glBindBuffer (GL_ELEMENT_ARRAY_BUFFER, image->ibo);
  glDrawElements (GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);

  // freeing memory
  glDisableVertexAttribArray (image->attribute_texture);
  glDisableVertexAttribArray (image->attribute_texture_position);

  // enabling OpenGL properties
  glDisable (GL_BLEND);
}

#if HAVE_VULKAN

#if DEBUG_VULKAN

/**
 * Function to check the Vulkan validation layers.
 *
 * \return 1 on available all validation layers, 0 otherwise.
 */
static int
jbw_validation_layer_check_support (void)
{
  VkLayerProperties *available_layers;
  int err;
  uint32_t i, j, n;
  unsigned int layer_found;
  vkEnumerateInstanceLayerProperties (&n, NULL);
  available_layers
    = (VkLayerProperties *) malloc (n * sizeof (VkLayerProperties));
  vkEnumerateInstanceLayerProperties (&n, available_layers);
  for (i = 0; i < n; ++i)
    printf ("Vulkan validation layer %s\n", available_layers[i].layerName);
  err = 1;
  for (j = 0; j < JBW_VK_N_VALIDATION_LAYERS; ++j)
    {
      layer_found = 0;
      for (i = 0; i < n; ++i)
        if (!strcmp (jbw_required_validation_layers[j],
                     available_layers[i].layerName))
          {
            layer_found = 1;
            break;
          }
      if (!layer_found)
        {
          free (available_layers);
          err = 0;
          break;
        }
    }
  free (available_layers);
  return err;
}

#endif

/**
 * Function to create a Vulkan instance.
 *
 * \return 0 on success, error code on error.
 */
static int
jbw_vk_create_instance (JBWVK *vk)      ///< JBWVK struct.
{
  VkApplicationInfo application_info = { 0 };
  VkInstanceCreateInfo create_info = { 0 };
#if DEBUG_VULKAN
  VkExtensionProperties *extensions;
#endif
  const char **window_extensions;
#if HAVE_GLFW
  const char **glfw_extensions;
#endif
  int err;
  uint32_t i, count;
  // Checking for extension support
  vkEnumerateInstanceExtensionProperties (NULL, &count, NULL);
  if (!count)
    {
      vk->error_message = _("no Vulkan instance extensions supported");
      return JBW_VK_ERROR_NO_VULKAN_INSTANCE_EXTENSIONS;
    }
#if DEBUG_VULKAN
  extensions
    = (VkExtensionProperties *) malloc (count * sizeof (VkExtensionProperties));
  vkEnumerateInstanceExtensionProperties (NULL, &count, extensions);
  for (i = 0; i < count; ++i)
    fprintf (stderr, "Vulkan available instance extension: %s\n",
             extensions[i].extensionName);
  free (extensions);
#endif
  // Creating an instance
  err = 0;
  application_info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
  application_info.pApplicationName = "Check Vulkan";
  application_info.applicationVersion = VK_MAKE_VERSION (1, 0, 0);
  application_info.pEngineName = "No Engine";
  application_info.engineVersion = VK_MAKE_VERSION (1, 0, 0);
  application_info.apiVersion = VK_API_VERSION_1_0;
  create_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
  create_info.pApplicationInfo = &application_info;
#if HAVE_GLFW
  glfw_extensions = glfwGetRequiredInstanceExtensions (&count);
  window_extensions = (const char **) malloc (count * sizeof (const char *));
  memcpy (window_extensions, glfw_extensions, count * sizeof (const char *));
#elif HAVE_SDL
  SDL_Vulkan_GetInstanceExtensions (vk->window, &count, NULL);
  window_extensions = (const char **) malloc (count * sizeof (const char *));
  SDL_Vulkan_GetInstanceExtensions (vk->window, &count, window_extensions);
#endif
#if DEBUG_VULKAN
  for (i = 0; i < count; ++i)
    fprintf (stderr, "Window extension %u: %s\n", i + 1, window_extensions[i]);
#endif
  for (i = 0; i < count; ++i)
    if (!strcmp (window_extensions[i], "VK_KHR_surface"))
      break;
  if (i == count)
    {
      vk->error_message = _("no VK_KHR_surface Vulkan extension");
      err = JBW_VK_ERROR_NO_VULKAN_SURFACE_EXTENSION;
      goto exit_on_error;
    }
  // Using validation layers
#if DEBUG_VULKAN
  if (jbw_validation_layer_check_support ())
    {
      create_info.enabledLayerCount = JBW_VK_N_VALIDATION_LAYERS;
      create_info.ppEnabledLayerNames = jbw_required_validation_layers;
      ++count;
      window_extensions
        = realloc (window_extensions, count * sizeof (const char *));
      window_extensions[count - 1] = VK_EXT_DEBUG_UTILS_EXTENSION_NAME;
    }
  else
    {
      vk->error_message = _("no available Vulkan validation layers");
      err = JBW_VK_ERROR_NO_AVAILABLE_VULKAN_VALIDATION_LAYERS;
      goto exit_on_error;
    }
#endif
  create_info.enabledExtensionCount = count;
  create_info.ppEnabledExtensionNames = window_extensions;
  if (vkCreateInstance (&create_info, NULL, &vk->instance) != VK_SUCCESS)
    {
      vk->error_message = _("failed to create Vulkan instance");
      err = JBW_VK_ERROR_FAILED_TO_CREATE_VULKAN_INSTANCE;
      goto exit_on_error;
    }
  vk->created_instance = 1;
exit_on_error:
  free (window_extensions);
  return err;
}

/**
 * Function to create a Vulkan surface.
 *
 * \return 0 on success, error code on error.
 */
static int
jbw_vk_create_surface (JBWVK *vk)       ///< JBWVK data struct.
{
#if HAVE_GLFW
  if (glfwCreateWindowSurface (vk->instance, vk->window, NULL, &vk->surface)
      != VK_SUCCESS)
#elif HAVE_SDL
  if (SDL_Vulkan_CreateSurface (vk->window, (SDL_vulkanInstance) vk->instance,
                                (SDL_vulkanSurface *) & vk->surface)
      != SDL_TRUE)
#endif
    {
      vk->error_message = _("unable to create a Vulkan surface");
      return JBW_VK_ERROR_NO_VULKAN_SURFACE;
    }
  vk->created_surface = 1;
  return 0;
}

/**
 * Function to select a graphic card.
 *
 * \return 0 on success, error code on error.
 */
static int
jbw_vk_select_physical_device (JBWVK *vk)       ///< JBWVK data struct.
{
  VkPhysicalDevice device;
  VkPhysicalDeviceProperties device_properties;
  VkPhysicalDeviceFeatures device_features;
  VkPhysicalDevice *devices;
  VkResult result;
  int err;
  uint32_t i, count, limits;
  vkEnumeratePhysicalDevices (vk->instance, &count, NULL);
  if (!count)
    {
      vk->error_message = _("failed to find a GPU with Vulkan support");
      return JBW_VK_ERROR_NO_VULKAN_PHYSICAL_DEVICES;
    }
  err = 0;
#if DEBUG_VULKAN
  fprintf (stderr, "Number of Vulkan physical devices: %u\n",
           (unsigned int) count);
#endif
  devices = (VkPhysicalDevice *) malloc (count * sizeof (VkPhysicalDevice));
  result = vkEnumeratePhysicalDevices (vk->instance, &count, devices);
  if (result != VK_SUCCESS)
    {
      vk->error_message = _("bad Vulkan physical devices");
      err = JBW_VK_ERROR_BAD_VULKAN_PHYSICAL_DEVICES;
      goto exit_on_error;
    }
  for (i = 0; i < count; ++i)
    if (devices[i])
      {
        vkGetPhysicalDeviceProperties (devices[i], &device_properties);
#if DEBUG_VULKAN
        fprintf (stderr, "Vulkan physical device: %s\n",
                 device_properties.deviceName);
#endif
      }
#if DEBUG_VULKAN
  fprintf (stderr, "Selecting Vulkan physical device\n");
#endif
  for (limits = i = 0; i < count; ++i)
    {
      device = devices[i];
      if (!device)
        continue;
      vkGetPhysicalDeviceProperties (device, &device_properties);
      vkGetPhysicalDeviceFeatures (device, &device_features);
#if DEBUG_VULKAN
      fprintf (stderr, "Vulkan physical device: %u\n", i + 1);
      fprintf (stderr, "Vulkan physical device type: %u\n",
               device_properties.deviceType);
      fprintf (stderr, "Vulkan physical geometry shader: %u\n",
               device_features.geometryShader);
#endif
      if ((device_properties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU
           || device_properties.deviceType
           == VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU)
          && device_features.geometryShader
          && device_properties.limits.maxImageDimension2D > limits
          && device_features.samplerAnisotropy)
        {
          vk->physical_device = device;
          limits = device_properties.limits.maxImageDimension2D;
        }
    }
  if (!limits)
    {
      vk->error_message = _("no suitable Vulkan physical devices");
      err = JBW_VK_ERROR_NO_SUITABLE_VULKAN_PHYSICAL_DEVICES;
      goto exit_on_error;
    }
exit_on_error:
  free (devices);
  return err;
}

/**
 * Function to check the Vulkan extensions.
 *
 * \return 0 on success, error code on error.
 */
static int
jbw_vk_check_extensions (JBWVK *vk)     ///< JBWVK struct.
{
  VkExtensionProperties *available_extensions;
  const char *buffer;
  int err;
  uint32_t i, j, k, count;
  err = 0;
  vkEnumerateDeviceExtensionProperties (vk->physical_device, NULL, &count,
                                        NULL);
  available_extensions = (VkExtensionProperties *)
    malloc (count * sizeof (VkExtensionProperties));
  vkEnumerateDeviceExtensionProperties (vk->physical_device, NULL, &count,
                                        available_extensions);
#if DEBUG_VULKAN
  fprintf (stderr, "Number of Vulkan available extensions: %u\n", count);
  for (i = 0; i < count; ++i)
    fprintf (stderr, "Vulkan extension: %s\n",
             available_extensions[i].extensionName);
#endif
  for (j = 0; j < JBW_VK_N_DEVICE_EXTENSIONS; ++j)
    {
      k = 0;
      buffer = jbw_required_device_extensions[j];
      for (i = 0; i < count; ++i)
        if (!strcmp (available_extensions[i].extensionName, buffer))
          k = 1;
      if (!k)
        {
          vk->error_message = _("no available Vulkan extension");
          err = JBW_VK_ERROR_NO_AVAILABLE_VULKAN_EXTENSION;
          break;
        }
    }
  free (available_extensions);
  return err;
}

/**
 * Function to create the logical device and queues.
 *
 * \return ERROR_CODE_NONE on succes, error code on error.
 */
static int
jbw_vk_create_logical_device (JBWVK *vk)        ///< JBWVK struct.
{
  VkDeviceCreateInfo create_info = { 0 };
  VkBool32 present_support;
  VkDeviceQueueCreateInfo queue_create_infos[2] = { 0 };
  VkPhysicalDeviceFeatures device_features = { 0 };
  VkQueueFamilyProperties *queue_families;
  const float queue_priority = 1.0f;
  uint32_t count, i;
  // Default window size.
  vk->extent.width = JBW_WINDOW_WIDTH;
  vk->extent.height = JBW_WINDOW_HEIGHT;
  // Queue families
  vkGetPhysicalDeviceQueueFamilyProperties (vk->physical_device, &count, NULL);
#if VULKAN_DEBUG
  fprintf (stderr,
           "Number of Vulkan physical device queue family properties: %u\n",
           (unsigned int) count);
#endif
  queue_families = (VkQueueFamilyProperties *)
    malloc (count * sizeof (VkQueueFamilyProperties));
  vkGetPhysicalDeviceQueueFamilyProperties (vk->physical_device, &count,
                                            queue_families);
  for (i = 0; i < count; ++i)
    if (queue_families[i].queueFlags & VK_QUEUE_GRAPHICS_BIT)
      break;
  free (queue_families);
  if (i == count)
    {
      vk->error_message = _("no suitable Vulkan physical device queue family");
      return JBW_VK_ERROR_NO_SUITABLE_VULKAN_QUEUE_FAMILY;
    }
  vk->graphics_index = i;
  // Querying for presentation support
  present_support = 0;
  for (i = 0; i < count; ++i)
    {
      vkGetPhysicalDeviceSurfaceSupportKHR (vk->physical_device, i, vk->surface,
                                            &present_support);
      if (present_support)
        break;
    }
  if (!present_support)
    {
      vk->error_message = _("Vulkan device does not support surfaces");
      return JBW_VK_ERROR_UNSUPPORTED_VULKAN_SURFACES;
    }
  vk->present_index = i;
  vk->queue_family_indices[0] = vk->graphics_index;
  vk->queue_family_indices[1] = vk->present_index;
  // Specifying the queues to be created
  queue_create_infos[0].sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
  queue_create_infos[0].queueFamilyIndex = vk->graphics_index;
  queue_create_infos[0].queueCount = 1;
  queue_create_infos[0].pQueuePriorities = &queue_priority;
  // Creating the presentation queue
  queue_create_infos[1].sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
  queue_create_infos[1].queueFamilyIndex = vk->present_index;
  queue_create_infos[1].queueCount = 1;
  queue_create_infos[1].pQueuePriorities = &queue_priority;
  // Anisotropy device feature
  device_features.samplerAnisotropy = VK_TRUE;
  // Creating the logical device
  create_info.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
  create_info.pQueueCreateInfos = queue_create_infos;
  create_info.queueCreateInfoCount = 1;
  create_info.pEnabledFeatures = &device_features;
  create_info.enabledExtensionCount = JBW_VK_N_DEVICE_EXTENSIONS;
  create_info.ppEnabledExtensionNames = jbw_required_device_extensions;
  if (vkCreateDevice (vk->physical_device, &create_info, NULL, &vk->device)
      != VK_SUCCESS)
    {
      vk->error_message = _("unable to create the Vulkan logical device");
      return JBW_VK_ERROR_NO_VULKAN_DEVICE;
    }
  vkGetDeviceQueue (vk->device, vk->graphics_index, 0, &vk->graphics_queue);
  vkGetDeviceQueue (vk->device, vk->present_index, 0, &vk->present_queue);
  vk->created_device = 1;
  return 0;
}

/**
 * Function to create the swap chain.
 *
 * \return ERROR_CODE_NONE on succes, error code on error.
 */
int
jbw_vk_create_swap_chain (JBWVK *vk)    ///< JBWVK struct.
{
  JBWVKSwapChainSupportDetails details = { 0 };
  VkPresentModeKHR present_mode;
  VkSwapchainCreateInfoKHR create_info = { 0 };
  int width, height, err;
  uint32_t count, i;
  // Querying details of swap chain support
  vkGetPhysicalDeviceSurfaceCapabilitiesKHR (vk->physical_device, vk->surface,
                                             &details.capabilities);
  vkGetPhysicalDeviceSurfaceFormatsKHR (vk->physical_device, vk->surface,
                                        &count, NULL);
  if (count)
    {
      details.formats = (VkSurfaceFormatKHR *)
        malloc (count * sizeof (VkSurfaceFormatKHR));
      vkGetPhysicalDeviceSurfaceFormatsKHR (vk->physical_device, vk->surface,
                                            &count, details.formats);
    }
  for (i = 0; i < count; ++i)
    {
      vk->surface_format = details.formats[i];
      if (vk->surface_format.format == VK_FORMAT_B8G8R8A8_SRGB
          && vk->surface_format.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR)
        break;
    }
  if (i == count)
    vk->surface_format = details.formats[0];
  vkGetPhysicalDeviceSurfacePresentModesKHR (vk->physical_device, vk->surface,
                                             &count, NULL);
  if (count)
    {
      details.present_modes = (VkPresentModeKHR *)
        malloc (count * sizeof (VkPresentModeKHR));
      vkGetPhysicalDeviceSurfacePresentModesKHR (vk->physical_device,
                                                 vk->surface,
                                                 &count, details.present_modes);
    }
  present_mode = VK_PRESENT_MODE_FIFO_KHR;
  for (i = 0; i < count; ++i)
    {
      if (details.present_modes[i] == VK_PRESENT_MODE_MAILBOX_KHR)
        {
          present_mode = VK_PRESENT_MODE_MAILBOX_KHR;
          break;
        }
    }
#if HAVE_GLFW
  glfwGetFramebufferSize (vk->window, &width, &height);
#elif HAVE_SDL
  SDL_Vulkan_GetDrawableSize (vk->window, &width, &height);
#endif
  vk->extent.width = width;
  vk->extent.height = height;
  i = details.capabilities.maxImageExtent.width;
  if (i < vk->extent.width)
    vk->extent.width = i;
  i = details.capabilities.minImageExtent.width;
  if (i > vk->extent.width)
    vk->extent.width = i;
  i = details.capabilities.maxImageExtent.height;
  if (i < vk->extent.height)
    vk->extent.height = i;
  i = details.capabilities.minImageExtent.height;
  if (i > vk->extent.height)
    vk->extent.height = i;
  count = details.capabilities.minImageCount + 1;
  if (details.capabilities.maxImageCount > 0
      && details.capabilities.maxImageCount < count)
    count = details.capabilities.maxImageCount;
  create_info.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
  create_info.surface = vk->surface;
  create_info.minImageCount = count;
  create_info.imageFormat = vk->surface_format.format;
  create_info.imageColorSpace = vk->surface_format.colorSpace;
  create_info.imageExtent = vk->extent;
  create_info.imageArrayLayers = 1;
  create_info.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
  if (vk->graphics_index != vk->present_index)
    {
      create_info.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
      create_info.queueFamilyIndexCount = 2;
      create_info.pQueueFamilyIndices = vk->queue_family_indices;
    }
  else
    {
      create_info.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
      create_info.queueFamilyIndexCount = 0;
      create_info.pQueueFamilyIndices = NULL;
    }
  create_info.preTransform = details.capabilities.currentTransform;
  create_info.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
  create_info.presentMode = present_mode;
  create_info.clipped = VK_TRUE;
  create_info.oldSwapchain = VK_NULL_HANDLE;
  err = 0;
  if (vkCreateSwapchainKHR (vk->device, &create_info, NULL,
                            &vk->swap_chain) != VK_SUCCESS)
    {
      vk->error_message = _("unable to create the Vulkan swap chain");
      err = JBW_VK_ERROR_NO_VULKAN_SWAP_CHAIN;
      goto exit_on_error;
    }
  // Retrieving the swap chain images
  vkGetSwapchainImagesKHR (vk->device, vk->swap_chain, &count, NULL);
  vk->swap_chain_images = (VkImage *) malloc (count * sizeof (VkImage));
  vkGetSwapchainImagesKHR (vk->device, vk->swap_chain, &count,
                           vk->swap_chain_images);
  vk->n_image_views = count;
  vk->created_swap_chain = 1;
exit_on_error:
  free (details.present_modes);
  free (details.formats);
  return err;
}

/**
 * Function to create a Vulkan swap chain image view.
 *
 * \return 0 on success, error code on error.
 */
int
jbw_vk_create_image_view (JBWVK *vk,    ///< JBWVK struct.
                          VkImage image,        ///< Vulkan image struct.
                          VkFormat format,      ///< Vulkan image format.
                          VkImageAspectFlags aspect_flags,
                          ///< Vulkan image aspect flags.
                          VkImageView *image_view)
                          ///< Vulkan image view pointer.
{
  VkImageViewCreateInfo view_info = { 0 };
  view_info.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
  view_info.image = image;
  view_info.viewType = VK_IMAGE_VIEW_TYPE_2D;
  view_info.format = format;
  view_info.subresourceRange.aspectMask = aspect_flags;
  view_info.subresourceRange.baseMipLevel = 0;
  view_info.subresourceRange.levelCount = 1;
  view_info.subresourceRange.baseArrayLayer = 0;
  view_info.subresourceRange.layerCount = 1;
  if (vkCreateImageView (vk->device, &view_info, NULL, image_view)
      != VK_SUCCESS)
    {
      vk->error_message
        = _("unable to create the Vulkan swap chain image view");
      return JBW_VK_ERROR_FAILED_TO_CREATE_VULKAN_IMAGE_VIEW;
    }
  return 0;
}

/**
 * Function to create the Vulkan swap chain image views.
 *
 * \return 0 on success, error code on error.
 */
int
jbw_vk_create_image_views (JBWVK *vk)   ///< JBWVK struct.
{
  uint32_t i;
  int j;
  // Image views
  vk->swap_chain_image_views
    = (VkImageView *) malloc (vk->n_image_views * sizeof (VkImageView));
  vk->created_image_views = 1;
  for (i = 0; i < vk->n_image_views; ++i)
    {
      j = jbw_vk_create_image_view (vk,
                                    vk->swap_chain_images[i],
                                    vk->surface_format.format,
                                    VK_IMAGE_ASPECT_COLOR_BIT,
                                    vk->swap_chain_image_views + i);
      if (j)
        {
          vk->n_image_views = i;
          return j;
        }
    }
  return 0;
}

/**
 * Function to find a supported Vulkan format.
 *
 * \return supported Vulkan format on success, 0 on error.
 */
static VkFormat
jbw_vk_find_supported_format (JBWVK *vk,        ///< JBWVK struct.
                              const VkFormat *candidates,
                              ///< Array of Vulkan format candidates.
                              unsigned int n_candidates,
                              ///< Number of Vulkan format candidates.
                              VkImageTiling tiling,
                              ///< Vulkan image tiling.
                              VkFormatFeatureFlags features)
                              ///< Vulkan format feature flags.
{
  VkFormat format;
  VkFormatProperties props;
  unsigned int i;
  for (i = 0; i < n_candidates; ++i)
    {
      format = candidates[i];
      vkGetPhysicalDeviceFormatProperties (vk->physical_device, format, &props);
      if (tiling == VK_IMAGE_TILING_LINEAR
          && (props.linearTilingFeatures & features) == features)
        return format;
      if (tiling == VK_IMAGE_TILING_OPTIMAL
          && (props.optimalTilingFeatures & features) == features)
        return format;
    }
  vk->error_message = _("failed to find supported format");
  return 0;
}

/**
 * Function to find the Vulkan depth format.
 *
 * \return Vulkan depth format on success, 0 on error.
 */
static VkFormat
jbw_vk_find_depth_format (JBWVK *vk)    ///< JBWVK struct.
{
  const VkFormat formats[3] = {
    VK_FORMAT_D32_SFLOAT,
    VK_FORMAT_D32_SFLOAT_S8_UINT,
    VK_FORMAT_D24_UNORM_S8_UINT
  };
  return jbw_vk_find_supported_format
    (vk,
     formats,
     3,
     VK_IMAGE_TILING_OPTIMAL, VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT);
}

/**
 * Function to create the Vulkan render pass.
 *
 * \return ERROR_CODE_NONE on success, error code on error.
 */
static int
jbw_vk_create_render_pass (JBWVK *vk)   ///< JBWVK struct.
{
  VkAttachmentDescription color_attachment = { 0 };
  VkAttachmentReference color_attachment_ref = { 0 };
  VkSubpassDescription subpass = { 0 };
  VkSubpassDependency dependency = { 0 };
  VkRenderPassCreateInfo render_pass_info = { 0 };
  VkAttachmentDescription depth_attachment = { 0 };
  VkAttachmentReference depth_attachment_ref = { 0 };
  VkAttachmentDescription attachments[2];
  // Color attachment description
  color_attachment.format = vk->surface_format.format;
  color_attachment.samples = VK_SAMPLE_COUNT_1_BIT;
  color_attachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
  color_attachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
  color_attachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
  color_attachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
  color_attachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
  color_attachment.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
  // Depth attachment description
  depth_attachment.format = jbw_vk_find_depth_format (vk);
  depth_attachment.samples = VK_SAMPLE_COUNT_1_BIT;
  depth_attachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
  depth_attachment.storeOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
  depth_attachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
  depth_attachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
  depth_attachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
  depth_attachment.finalLayout
    = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
  // Subpasses and attachment references
  color_attachment_ref.attachment = 0;
  color_attachment_ref.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
  depth_attachment_ref.attachment = 1;
  depth_attachment_ref.layout
    = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
  subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
  subpass.colorAttachmentCount = 1;
  subpass.pColorAttachments = &color_attachment_ref;
  subpass.pDepthStencilAttachment = &depth_attachment_ref;
  // Subpass dependencies
  dependency.srcSubpass = VK_SUBPASS_EXTERNAL;
  dependency.dstSubpass = 0;
  dependency.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
  dependency.srcAccessMask = 0;
  dependency.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
  dependency.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
  // Render pass
  attachments[0] = color_attachment;
  attachments[1] = depth_attachment;
  render_pass_info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
  render_pass_info.attachmentCount = 2;
  render_pass_info.pAttachments = attachments;
  render_pass_info.subpassCount = 1;
  render_pass_info.pSubpasses = &subpass;
  render_pass_info.dependencyCount = 1;
  render_pass_info.pDependencies = &dependency;
  if (vkCreateRenderPass (vk->device, &render_pass_info, NULL, &vk->render_pass)
      != VK_SUCCESS)
    {
      vk->error_message = _("failed to create the Vulkan render pass");
      return JBW_VK_ERROR_FAILED_TO_CREATE_VULKAN_RENDER_PASS;
    }
  vk->created_render_pass = 1;
  return 0;
}

/**
 * Function to create the Vulkan descriptor set layout.
 *
 * \return 0 on success, error code on error.
 */
static int
jbw_vk_create_descriptor_set_layout (JBWVK *vk)
///< Graphics data struct.
{
  VkDescriptorSetLayoutBinding ubo_layout_binding = { 0 };
  VkDescriptorSetLayoutBinding sampler_layout_binding = { 0 };
  VkDescriptorSetLayoutBinding bindings[2];
  VkDescriptorSetLayoutCreateInfo layout_info = { 0 };
  ubo_layout_binding.binding = 0;
  ubo_layout_binding.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
  ubo_layout_binding.descriptorCount = 1;
  ubo_layout_binding.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;
  ubo_layout_binding.pImmutableSamplers = NULL;
  sampler_layout_binding.binding = 1;
  sampler_layout_binding.descriptorCount = 1;
  sampler_layout_binding.descriptorType
    = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
  sampler_layout_binding.pImmutableSamplers = NULL;
  sampler_layout_binding.stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT;
  bindings[0] = ubo_layout_binding;
  bindings[1] = sampler_layout_binding;
  layout_info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
  layout_info.bindingCount = 2;
  layout_info.pBindings = bindings;
  if (vkCreateDescriptorSetLayout (vk->device, &layout_info, NULL,
                                   &vk->descriptor_set_layout) != VK_SUCCESS)
    {
      vk->error_message
        = _("failed to create the Vulkan descriptor set layout");
      return JBW_VK_ERROR_CODE_FAILED_TO_CREATE_VULKAN_DESCRIPTOR_SET_LAYOUT;
    }
  vk->created_descriptor_set_layout = 1;
  return 0;
}

/**
 * Function to create a Vulkan shader module.
 *
 * \return 0 on success, error code on error.
 */
static int
jbw_vk_create_shader_module (JBWVK *vk, ///< JBWVK struct.
                             const char *name,  ///< shader file name.
                             VkShaderModule *shader_module)
                             ///< VkShaderModule struct.
{
  VkShaderModuleCreateInfo create_info = { 0 };
  char *code;
  long int size;
  int err;
  err = 0;
  code = jbw_read_file (name, &size);
  if (!code)
    {
      vk->error_message = _("failed to open the shader file");
      err = JBW_VK_ERROR_FAILED_TO_OPEN_SHADER_FILE;
      goto exit_on_error;
    }
  create_info.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
  create_info.codeSize = size;
  create_info.pCode = (const uint32_t *) code;
  if (vkCreateShaderModule (vk->device, &create_info, NULL, shader_module)
      != VK_SUCCESS)
    {
      vk->error_message = _("failed to create the Vulkan shader module");
      err = JBW_VK_ERROR_FAILED_TO_CREATE_VULKAN_SHADER_MODULE;
    }
exit_on_error:
  free (code);
  return err;
}

/**
 * Function to create the Vulkan shader modules.
 *
 * \return 0 on success, error code on error.
 */
static int
jbw_vk_create_shader_modules (JBWVK *vk)        ///< JBWVK struct.
{
  int i;
  // Initing shader handles
  vk->vert_2D_shader_module = vk->vert_2Dc_shader_module
    = vk->vert_3D_shader_module = vk->vert_3Dc_shader_module
    = vk->frag_color_shader_module = vk->vert_text_shader_module
    = vk->frag_text_shader_module = vk->vert_image_shader_module
    = vk->frag_image_shader_module = VK_NULL_HANDLE;
  // Creating shader modules
  vk->created_shader_modules = 1;
  i = jbw_vk_create_shader_module (vk, "shaders/2D.spv",
                                   &vk->vert_2D_shader_module);
  if (i)
    return i;
  i = jbw_vk_create_shader_module (vk, "shaders/2Dc.spv",
                                   &vk->vert_2Dc_shader_module);
  if (i)
    return i;
  i = jbw_vk_create_shader_module (vk, "shaders/3D.spv",
                                   &vk->vert_3D_shader_module);
  if (i)
    return i;
  i = jbw_vk_create_shader_module (vk, "shaders/3Dc.spv",
                                   &vk->vert_3Dc_shader_module);
  if (i)
    return i;
  i = jbw_vk_create_shader_module (vk, "shaders/color.spv",
                                   &vk->frag_color_shader_module);
  if (i)
    return i;
  i = jbw_vk_create_shader_module (vk, "shaders/text-vert.spv",
                                   &vk->vert_text_shader_module);
  if (i)
    return i;
  i = jbw_vk_create_shader_module (vk, "shaders/text-frag.spv",
                                   &vk->frag_text_shader_module);
  if (i)
    return i;
  i = jbw_vk_create_shader_module (vk, "shaders/image-vert.spv",
                                   &vk->vert_image_shader_module);
  if (i)
    return i;
  i = jbw_vk_create_shader_module (vk, "shaders/image-frag.spv",
                                   &vk->frag_image_shader_module);
  if (i)
    return i;
  return 0;
}

/**
 * Function to free the memory used by the Vulkan swap chain.
 */
static void
jbw_vk_destroy_swap_chain (JBWVK *vk)   ///< JBWVK struct.
{
  uint32_t i;
  if (vk->created_render_pass)
    {
      vkDestroyRenderPass (vk->device, vk->render_pass, NULL);
      vk->created_render_pass = 0;
    }
  if (vk->created_image_views)
    {
      for (i = 0; i < vk->n_image_views; ++i)
        vkDestroyImageView (vk->device, vk->swap_chain_image_views[i], NULL);
      free (vk->swap_chain_image_views);
    }
  if (vk->created_swap_chain)
    {
      free (vk->swap_chain_images);
      vkDestroySwapchainKHR (vk->device, vk->swap_chain, NULL);
      vk->created_swap_chain = 0;
    }
}

/**
 * Function to free the memory used by a JBWVK struct.
 */
static void
jbw_vk_destroy (JBWVK *vk)      ///< JBWVK struct.
{
  jbw_vk_destroy_swap_chain (vk);
  if (vk->created_shader_modules)
    {
      vkDestroyShaderModule (vk->device, vk->frag_image_shader_module, NULL);
      vkDestroyShaderModule (vk->device, vk->vert_image_shader_module, NULL);
      vkDestroyShaderModule (vk->device, vk->frag_text_shader_module, NULL);
      vkDestroyShaderModule (vk->device, vk->vert_text_shader_module, NULL);
      vkDestroyShaderModule (vk->device, vk->frag_color_shader_module, NULL);
      vkDestroyShaderModule (vk->device, vk->vert_3Dc_shader_module, NULL);
      vkDestroyShaderModule (vk->device, vk->vert_3D_shader_module, NULL);
      vkDestroyShaderModule (vk->device, vk->vert_2Dc_shader_module, NULL);
      vkDestroyShaderModule (vk->device, vk->vert_2D_shader_module, NULL);
      vk->created_shader_modules = 0;
    }
  if (vk->created_descriptor_set_layout)
    {
      vkDestroyDescriptorSetLayout (vk->device, vk->descriptor_set_layout,
                                    NULL);
      vk->created_descriptor_set_layout = 0;
    }
  if (vk->created_device)
    {
      vkDestroyDevice (vk->device, NULL);
      vk->created_device = 0;
    }
  if (vk->created_surface)
    {
      vkDestroySurfaceKHR (vk->instance, vk->surface, NULL);
      vk->created_surface = 0;
    }
  if (vk->created_instance)
    {
      vkDestroyInstance (vk->instance, NULL);
      vk->created_instance = 0;
    }
}

/**
 * Function to init the Vulkan resources.
 *
 * \return 0 on success, error code on error.
 */
static int
jbw_vk_init (JBWVK *vk)         ///< JBWVK struct.
{
  int i;
  // Initing creation flags
  vk->created_instance = vk->created_surface = vk->created_device
    = vk->created_swap_chain = vk->created_image_views
    = vk->created_render_pass = vk->created_descriptor_set_layout
    = vk->created_shader_modules = 0;
  // Creating a Vulkan instance
  i = jbw_vk_create_instance (vk);
  if (i)
    goto exit_on_error;
  // Creating a Vulkan window surface
  i = jbw_vk_create_surface (vk);
  if (i)
    goto exit_on_error;
  // Selecting a graphics card
  i = jbw_vk_select_physical_device (vk);
  if (i)
    goto exit_on_error;
  // Checking the Vulkan extensions
  i = jbw_vk_check_extensions (vk);
  if (i)
    goto exit_on_error;
  // Creating the Vulkan logical device and queues
  i = jbw_vk_create_logical_device (vk);
  if (i)
    goto exit_on_error;
  // Creating the Vulkan swap chain
  i = jbw_vk_create_swap_chain (vk);
  if (i)
    goto exit_on_error;
  // Creating the Vulkan image views
  i = jbw_vk_create_image_views (vk);
  if (i)
    goto exit_on_error;
  // Creating the Vulkan render pass
  i = jbw_vk_create_render_pass (vk);
  if (i)
    goto exit_on_error;
  // Creating the Vulkan descriptor set layout
  i = jbw_vk_create_descriptor_set_layout (vk);
  if (i)
    goto exit_on_error;
  // Creating the Vulkan shader modules
  i = jbw_vk_create_shader_modules (vk);
  if (i)
    goto exit_on_error;
  // Exit on success
  return 0;

  // Exit on error
exit_on_error:
  jbw_vk_destroy (vk);
  return i;
}

#endif

/**
 * Function to free the memory used by the current JBWGraphic widget.
 */
static inline void
jbw_graphic_delete (JBWGraphic *graphic)        ///< current JBWGraphic widget.
{
  if (graphic->vbo_text)
    glDeleteBuffers (1, &graphic->vbo_text);
  if (graphic->face)
    {
      FT_Done_Face (*graphic->face);
      g_free (graphic->face);
    }
  if (graphic->ft)
    {
      FT_Done_FreeType (*graphic->ft);
      g_free (graphic->ft);
    }
  if (graphic->program_text)
    glDeleteProgram (graphic->program_text);
  if (graphic->program_3Dc)
    glDeleteProgram (graphic->program_3D);
  if (graphic->program_2Dc)
    glDeleteProgram (graphic->program_2D);
  if (graphic->program_3D)
    glDeleteProgram (graphic->program_3D);
  if (graphic->program_2D)
    glDeleteProgram (graphic->program_2D);
  if (graphic->logo)
    jbw_image_delete (graphic->logo);
}

/**
 * Function to close and free the memory used by the current JBWGraphic widget.
 */
void
jbw_graphic_destroy (void)
{
  JBWGraphic *graphic = jbw_graphic_pointer;
  if (graphic && graphic->window)
    {
      jbw_graphic_delete (graphic);
#if HAVE_GTKGLAREA
      gtk_window_destroy (graphic->window);
#elif HAVE_SDL
      SDL_DestroyWindow (graphic->window);
#elif HAVE_GLFW
      glfwDestroyWindow (graphic->window);
#endif
    }
  g_free (graphic);
  jbw_graphic_pointer = NULL;
}

/**
 * Function to init the OpenGL functions on the current JBWGraphic widget.
 */
void
jbw_graphic_init (void)
{
  const char *gl_version_120 =
    "#version 120\n" "#define in attribute\n" "#define out varying\n";
  const char *gl_version_130 = "#version 130\n";
  const char *fs_source =
    "out vec3 fcolor;" "void main()" "{" "gl_FragColor=vec4(fcolor,1.f);" "}";
  const char *vs_2D_source =
    "in vec2 position;"
    "uniform vec3 color;"
    "uniform mat4 matrix;"
    "out vec3 fcolor;"
    "void main()"
    "{" "gl_Position=matrix*vec4(position,0.f,1.f);" "fcolor=color;" "}";
  const char *vs_3D_source =
    "in vec3 position;"
    "uniform vec3 color;"
    "uniform mat4 matrix;"
    "out vec3 fcolor;"
    "void main()"
    "{" "gl_Position=matrix*vec4(position,1.f);" "fcolor=color;" "}";
  const char *vs_2Dc_source =
    "in vec2 position;"
    "in vec3 color;"
    "uniform mat4 matrix;"
    "out vec3 fcolor;"
    "void main()"
    "{" "gl_Position=matrix*vec4(position,0.f,1.f);" "fcolor=color;" "}";
  const char *vs_3Dc_source =
    "in vec3 position;"
    "in vec3 color;"
    "uniform mat4 matrix;"
    "out vec3 fcolor;"
    "void main()"
    "{" "gl_Position=matrix*vec4(position,1.f);" "fcolor=color;" "}";
  const char *vs_text_source =
    "in vec4 position;"
    "out vec2 textcoord;"
    "void main()"
    "{" "gl_Position=vec4(position.xy,0.f,1.f);" "textcoord=position.zw;" "}";
  const char *fs_text_source =
    "uniform sampler2D text;"
    "uniform vec4 color;"
    "out vec2 textcoord;"
    "void main()"
    "{" "gl_FragColor=vec4(1.f,1.f,1.f,texture2D(text,textcoord).a)*color;" "}";
  const char *position_name = "position";
  const char *color_name = "color";
  const char *matrix_name = "matrix";
  const char *text_name = "text";
  const char *fs_sources[2];
  const char *vs_2D_sources[2];
  const char *vs_3D_sources[2];
  const char *vs_2Dc_sources[2];
  const char *vs_3Dc_sources[2];
  const char *fs_text_sources[2];
  const char *vs_text_sources[2];
  JBWGraphic *graphic;
  const char *gl_version;
  const char *error_msg;
  GLint error_code;
  GLuint fs, vs;
  GLenum glew_status;

  // Current JBWGraphic widget
  graphic = jbw_graphic_pointer;

  // Initing GLEW library
  glew_status = glewInit ();
  if (glew_status != GLEW_OK)
    {
      error_msg = (const char *) glewGetErrorString (glew_status);
      goto end2;
    }
  if (glewIsSupported ("GL_VERSION_3_0"))
    gl_version = gl_version_130;
  else if (glewIsSupported ("GL_VERSION_2_1"))
    gl_version = gl_version_120;
  else
    {
      error_msg = _("OpenGL 2.1 is not supported");
      goto end2;
    }

  // Initing variables
init:
  graphic->vbo_text = graphic->program_2D = graphic->program_3D
    = graphic->program_2Dc = graphic->program_3Dc = graphic->program_text = 0;
  fs_sources[0] = vs_2D_sources[0] = vs_3D_sources[0] = vs_2Dc_sources[0]
    = vs_3Dc_sources[0] = fs_text_sources[0] = vs_text_sources[0] = gl_version;
  fs_sources[1] = fs_source;
  vs_2D_sources[1] = vs_2D_source;
  vs_3D_sources[1] = vs_3D_source;
  vs_2Dc_sources[1] = vs_2Dc_source;
  vs_3Dc_sources[1] = vs_3Dc_source;
  fs_text_sources[1] = fs_text_source;
  vs_text_sources[1] = vs_text_source;

  // Compiling the fragment shader
  fs = glCreateShader (GL_FRAGMENT_SHADER);
  glShaderSource (fs, 2, fs_sources, NULL);
  glCompileShader (fs);
  glGetShaderiv (fs, GL_COMPILE_STATUS, &error_code);
  if (!error_code)
    {
      error_msg = _("unable to compile the fragment shader");
      goto end;
    }

  // Compiling the 2D vertex shader
  vs = glCreateShader (GL_VERTEX_SHADER);
  glShaderSource (vs, 2, vs_2D_sources, NULL);
  glCompileShader (vs);
  glGetShaderiv (vs, GL_COMPILE_STATUS, &error_code);
  if (!error_code)
    {
      glDeleteShader (fs);
      error_msg = _("unable to compile the 2D vertex shader");
      goto end;
    }

  // Linking the 2D program
  graphic->program_2D = glCreateProgram ();
  glAttachShader (graphic->program_2D, fs);
  glAttachShader (graphic->program_2D, vs);
  glLinkProgram (graphic->program_2D);
  glDetachShader (graphic->program_2D, vs);
  glDetachShader (graphic->program_2D, fs);
  glDeleteShader (vs);
  glGetProgramiv (graphic->program_2D, GL_LINK_STATUS, &error_code);
  if (!error_code)
    {
      graphic->program_2D = 0;
      glDeleteShader (fs);
      error_msg = _("unable to link the 2D program");
      goto end;
    }

  // Compiling the 3D vertex shader
  vs = glCreateShader (GL_VERTEX_SHADER);
  glShaderSource (vs, 2, vs_3D_sources, NULL);
  glCompileShader (vs);
  glGetShaderiv (vs, GL_COMPILE_STATUS, &error_code);
  if (!error_code)
    {
      glDeleteShader (fs);
      error_msg = _("unable to compile the 3D vertex shader");
      goto end;
    }

  // Linking the 3D program
  graphic->program_3D = glCreateProgram ();
  glAttachShader (graphic->program_3D, fs);
  glAttachShader (graphic->program_3D, vs);
  glLinkProgram (graphic->program_3D);
  glDetachShader (graphic->program_3D, vs);
  glDetachShader (graphic->program_3D, fs);
  glDeleteShader (vs);
  glGetProgramiv (graphic->program_3D, GL_LINK_STATUS, &error_code);
  if (!error_code)
    {
      glDeleteShader (fs);
      graphic->program_3D = 0;
      error_msg = _("unable to link the 3D program");
      goto end;
    }

  // Compiling the 2D with color vertex shader
  vs = glCreateShader (GL_VERTEX_SHADER);
  glShaderSource (vs, 2, vs_2Dc_sources, NULL);
  glCompileShader (vs);
  glGetShaderiv (vs, GL_COMPILE_STATUS, &error_code);
  if (!error_code)
    {
      glDeleteShader (fs);
      error_msg = _("unable to compile the 2D with color vertex shader");
      goto end;
    }

  // Linking the 2D with color program
  graphic->program_2Dc = glCreateProgram ();
  glAttachShader (graphic->program_2Dc, fs);
  glAttachShader (graphic->program_2Dc, vs);
  glLinkProgram (graphic->program_2Dc);
  glDetachShader (graphic->program_2Dc, vs);
  glDetachShader (graphic->program_2Dc, fs);
  glDeleteShader (vs);
  glGetProgramiv (graphic->program_2Dc, GL_LINK_STATUS, &error_code);
  if (!error_code)
    {
      graphic->program_2Dc = 0;
      glDeleteShader (fs);
      error_msg = _("unable to link the 2D with color program");
      goto end;
    }

  // Compiling the 3D vertex shader
  vs = glCreateShader (GL_VERTEX_SHADER);
  glShaderSource (vs, 2, vs_3Dc_sources, NULL);
  glCompileShader (vs);
  glGetShaderiv (vs, GL_COMPILE_STATUS, &error_code);
  if (!error_code)
    {
      glDeleteShader (fs);
      error_msg = _("unable to compile the 3D with color vertex shader");
      goto end;
    }

  // Linking the 3D program
  graphic->program_3Dc = glCreateProgram ();
  glAttachShader (graphic->program_3Dc, fs);
  glAttachShader (graphic->program_3Dc, vs);
  glLinkProgram (graphic->program_3Dc);
  glDetachShader (graphic->program_3Dc, vs);
  glDetachShader (graphic->program_3Dc, fs);
  glDeleteShader (vs);
  glDeleteShader (fs);
  glGetProgramiv (graphic->program_3D, GL_LINK_STATUS, &error_code);
  if (!error_code)
    {
      graphic->program_3Dc = 0;
      error_msg = _("unable to link the 3D with color program");
      goto end;
    }

  // Compiling the text fragment shader
  fs = glCreateShader (GL_FRAGMENT_SHADER);
  glShaderSource (fs, 2, fs_text_sources, NULL);
  glCompileShader (fs);
  glGetShaderiv (fs, GL_COMPILE_STATUS, &error_code);
  if (!error_code)
    {
      glDeleteShader (vs);
      error_msg = _("unable to compile the text fragment shader");
      goto end;
    }

  // Compiling the text vertex shader
  vs = glCreateShader (GL_VERTEX_SHADER);
  glShaderSource (vs, 2, vs_text_sources, NULL);
  glCompileShader (vs);
  glGetShaderiv (vs, GL_COMPILE_STATUS, &error_code);
  if (!error_code)
    {
      error_msg = _("unable to compile the text vertex shader");
      goto end;
    }

  // Linking the text program
  graphic->program_text = glCreateProgram ();
  glAttachShader (graphic->program_text, fs);
  glAttachShader (graphic->program_text, vs);
  glLinkProgram (graphic->program_text);
  glDetachShader (graphic->program_text, vs);
  glDetachShader (graphic->program_text, fs);
  glDeleteShader (vs);
  glDeleteShader (fs);
  glGetProgramiv (graphic->program_text, GL_LINK_STATUS, &error_code);
  if (!error_code)
    {
      graphic->program_text = 0;
      error_msg = _("unable to link the text program");
      goto end;
    }

  // Setting up 2D attributes
  graphic->in_2D_position
    = glGetAttribLocation (graphic->program_2D, position_name);
  if (graphic->in_2D_position == -1)
    {
      error_msg = _("could not bind 2D position attribute");
      goto end;
    }
  graphic->uniform_2D_color
    = glGetUniformLocation (graphic->program_2D, color_name);
  if (graphic->uniform_2D_color == -1)
    {
      error_msg = _("could not bind 2D color");
      goto end;
    }
  graphic->uniform_2D_matrix
    = glGetUniformLocation (graphic->program_2D, matrix_name);
  if (graphic->uniform_2D_matrix == -1)
    {
      error_msg = _("could not bind 2D matrix");
      goto end;
    }

  // Setting up 3D attributes
  graphic->in_3D_position
    = glGetAttribLocation (graphic->program_3D, position_name);
  if (graphic->in_3D_position == -1)
    {
      error_msg = _("could not bind 3D position attribute");
      goto end;
    }
  graphic->uniform_3D_color
    = glGetUniformLocation (graphic->program_3D, color_name);
  if (graphic->uniform_3D_color == -1)
    {
      error_msg = _("could not bind 3D color");
      goto end;
    }
  graphic->uniform_3D_matrix
    = glGetUniformLocation (graphic->program_3D, matrix_name);
  if (graphic->uniform_3D_matrix == -1)
    {
      error_msg = _("could not bind 3D matrix");
      goto end;
    }

  // Setting up 2D with color attributes
  graphic->in_2Dc_position
    = glGetAttribLocation (graphic->program_2Dc, position_name);
  if (graphic->in_2Dc_position == -1)
    {
      error_msg = _("could not bind 2D with color position attribute");
      goto end;
    }
  graphic->in_2Dc_color
    = glGetAttribLocation (graphic->program_2Dc, color_name);
  if (graphic->in_2Dc_color == -1)
    {
      error_msg = _("could not bind 2D with color color");
      goto end;
    }
  graphic->uniform_2Dc_matrix
    = glGetUniformLocation (graphic->program_2Dc, matrix_name);
  if (graphic->uniform_2Dc_matrix == -1)
    {
      error_msg = _("could not bind 2D with color matrix");
      goto end;
    }

  // Setting up 3D with color attributes
  graphic->in_3Dc_position
    = glGetAttribLocation (graphic->program_3Dc, position_name);
  if (graphic->in_3Dc_position == -1)
    {
      error_msg = _("could not bind 3D with color position attribute");
      goto end;
    }
  graphic->in_3Dc_color
    = glGetAttribLocation (graphic->program_3Dc, color_name);
  if (graphic->in_3Dc_color == -1)
    {
      error_msg = _("could not bind 3D with color color");
      goto end;
    }
  graphic->uniform_3Dc_matrix
    = glGetUniformLocation (graphic->program_3Dc, matrix_name);
  if (graphic->uniform_3Dc_matrix == -1)
    {
      error_msg = _("could not bind 3D with color matrix");
      goto end;
    }

  // Setting up logo
  if (graphic->logo)
    jbw_image_init (graphic->logo, gl_version);

  // Setting up text attributes
  graphic->in_text_position
    = glGetAttribLocation (graphic->program_text, position_name);
  if (graphic->in_text_position == -1)
    {
      error_msg = _("could not bind text position attribute");
      goto end;
    }
  graphic->uniform_text
    = glGetUniformLocation (graphic->program_text, text_name);
  if (graphic->uniform_text == -1)
    {
      error_msg = _("could not bind text uniform");
      goto end;
    }
  graphic->uniform_text_color
    = glGetUniformLocation (graphic->program_text, color_name);
  if (graphic->uniform_text_color == -1)
    {
      error_msg = _("could not bind text color uniform");
      goto end;
    }

  // Initing FreeType
  graphic->ft = (FT_Library *) g_try_malloc (sizeof (FT_Library));
  if (!graphic->ft)
    {
      error_msg = _("not enough memory to init the FreeType library");
      goto end;
    }
  if (FT_Init_FreeType (graphic->ft))
    {
      error_msg = _("could not init the FreeType library");
      goto end;
    }
  graphic->face = (FT_Face *) g_try_malloc (sizeof (FT_Face));
  if (!graphic->face)
    {
      error_msg = _("not enough memory to open the font");
      goto end;
    }
  if (FT_New_Face (*graphic->ft, FONT, 0, graphic->face))
    {
      error_msg = _("could not open font");
      goto end;
    }
  FT_Select_Charmap (*graphic->face, ft_encoding_unicode);
  FT_Set_Pixel_Sizes (*graphic->face, 0, JBW_GRAPHIC_FONT_SIZE);
  FT_Load_Char (*graphic->face, '0', FT_LOAD_RENDER);
  glGenBuffers (1, &graphic->vbo_text);

  // setting char and window sizes
  graphic->char_width = (*graphic->face)->glyph->advance.x >> 6;
  graphic->char_height = JBW_GRAPHIC_FONT_SIZE;
  jbw_graphic_set_size_request (graphic,
                                ((1 + graphic->nxmax) * JBW_GRAPHIC_N_CHARS +
                                 1) * graphic->char_width,
                                (5 + graphic->nymax) * graphic->char_height);

  // ending on success
  graphic->init = 1;
  return;

  // ending on error
end:
  if (gl_version != gl_version_120)
    {
      gl_version = gl_version_120;
      goto init;
    }
end2:
  jb_error_add ("JBWGraphic", error_msg, NULL);
  jb_error_show ();
  jb_error_destroy ();
  return;
}

/**
 * Function to resize the current JBWGraphic widget.
 */
void
jbw_graphic_resize (int width,  ///< new screen width.
                    int height) ///< new screen height.
{
  JBWGraphic *graphic = jbw_graphic_pointer;
  width = JBM_MAX (width, graphic->minimum_width);
  height = JBM_MAX (height, graphic->minimum_height);
  graphic->width = width;
  graphic->height = height;
  glViewport (0, 0, width, height);
}

/**
 * Function to render the current JBWGraphic widget.
 */
void
jbw_graphic_render (void)
{
  JBWGraphic *graphic = jbw_graphic_pointer;
  if (graphic->draw)
    graphic->draw (graphic);
#if HAVE_GTKGLAREA
  gtk_widget_queue_draw (GTK_WIDGET (graphic->widget));
#elif HAVE_SDL
  SDL_GL_SwapWindow (graphic->window);
#elif HAVE_GLFW
  glfwSwapBuffers (graphic->window);
#endif
}

#if HAVE_GTKGLAREA

static void
jbw_graphic_init_gtk (GtkGLArea *widget)
{
  gtk_gl_area_make_current (widget);
  jbw_graphic_init ();
}

static void
jbw_graphic_resize_gtk (GtkGLArea *widget, int width, int height)
{
  jbw_graphic_resize (width, height);
  gtk_widget_queue_draw (GTK_WIDGET (widget));
}

#elif HAVE_GLFW

static void
jbw_graphic_resize_glfw (GLFWwindow *window __attribute__((unused)),
                         int width, int height)
{
  jbw_graphic_resize (width, height);
}

static void
jbw_graphic_render_glfw (GLFWwindow *window __attribute__((unused)))
{
  jbw_graphic_render ();
}

#endif

/**
 * Function to do a main loop on the current JBWGraphic widget.
 */
void
jbw_graphic_loop (void)
{
#if HAVE_GTKGLAREA

  if (jbw_graphic_loop_idle)
    g_idle_add ((GSourceFunc) jbw_graphic_loop_idle, NULL);
  g_main_loop_run (jbw_graphic_loop_pointer);
  g_main_loop_unref (jbw_graphic_loop_pointer);

#elif HAVE_SDL

  SDL_Event event[1];
  GMainContext *context = g_main_context_default ();
  jbw_graphic_loop_render ();
  while (1)
    {
      if (jbw_gdk_gl_context)
        gdk_gl_context_make_current (jbw_gdk_gl_context);
      while (g_main_context_pending (context))
        g_main_context_iteration (context, 0);
      if (jbw_graphic_pointer)
        {
          SDL_GL_MakeCurrent (jbw_graphic_pointer->window,
                              jbw_graphic_pointer->sdl_context);
          while (SDL_PollEvent (event))
            {
              switch (event->type)
                {
                case SDL_QUIT:
                  return;
                case SDL_WINDOWEVENT:
                  if (event->window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
                    {
                      if (jbw_graphic_loop_resize)
                        jbw_graphic_loop_resize (event->window.data1,
                                                 event->window.data2);
                    }
                  else if (jbw_graphic_loop_render)
                    jbw_graphic_loop_render ();
                }
            }
          if (jbw_graphic_loop_idle && !jbw_graphic_loop_idle ())
            jbw_graphic_loop_idle = NULL;
        }
    }

#elif HAVE_GLFW

  GMainContext *context = g_main_context_default ();
  jbw_graphic_loop_render ();
  jbw_graphic_loop_exit = 0;
  while (!jbw_graphic_loop_exit)
    {
      if (jbw_gdk_gl_context)
        gdk_gl_context_make_current (jbw_gdk_gl_context);
      while (g_main_context_pending (context))
        g_main_context_iteration (context, 0);
      if (jbw_graphic_pointer)
        {
          glfwMakeContextCurrent (jbw_graphic_pointer->window);
          glfwPollEvents ();
          if (jbw_graphic_loop_idle && !jbw_graphic_loop_idle ())
            jbw_graphic_loop_idle = NULL;
        }
    }

#endif
}

/**
 * Function to set the title label of the current JBWGraphic widget.
 */
void
jbw_graphic_set_title (const char *title)       ///< title label.
{
  JBWGraphic *graphic = jbw_graphic_pointer;
  graphic->str_title = title;
#if HAVE_GTKGLAREA
  gtk_window_set_title (graphic->window, title);
#elif HAVE_SDL
  SDL_SetWindowTitle (graphic->window, title);
#elif HAVE_GLFW
  glfwSetWindowTitle (graphic->window, title);
#endif
}

/**
 * Function to set the logo on the current JBWGraphic widget.
 *
 * \return 1 on success opening the logo, 0 on error.
 */
int
jbw_graphic_set_logo (const char *name) ///< logo PNG file name.
{
  JBWGraphic *graphic = jbw_graphic_pointer;
  if (graphic->logo)
    jbw_image_delete (graphic->logo);
  graphic->logo = jbw_image_new (name);
  if (graphic->logo)
    return 1;
  return 0;
}

/**
 * Function to create a new JBWGraphic widget.
 */
JBWGraphic *
jbw_graphic_new (unsigned int nx,       ///< maximum number of x-tics.
                 unsigned int ny,       ///< maximum number of x-tics.
                 unsigned int nz,       ///< maximum number of x-tics.
                 void (*draw) (JBWGraphic *graphic),
                 ///< pointer to the render function.
                 const char *title)     ///< title.
{
  const char *error_msg;
  JBWGraphic *graphic;

  // Checking tic numbers
  if (nx > JBW_GRAPHIC_N_TICS || ny > JBW_GRAPHIC_N_TICS
      || nz > JBW_GRAPHIC_N_TICS)
    {
      error_msg = _("bad tics number");
      goto error1;
    }

  // Allocating memory
  graphic = (JBWGraphic *) g_try_malloc (sizeof (JBWGraphic));
  if (!graphic)
    {
      error_msg = _("not enough memory to open the graphic area");
      goto error1;
    }

  // Setting default properties
  graphic->calculate = NULL;
  graphic->data = NULL;
  graphic->resize = graphic->grid = 1;
  graphic->map = 0;
  graphic->str_x = graphic->str_y = graphic->str_yy = graphic->str_z
    = graphic->str_zz = NULL;
  graphic->str_title = title;
  graphic->logo = NULL;
  graphic->nxmax = nx;
  graphic->nymax = ny;
  graphic->nzmax = nz;
  graphic->draw = draw;
  graphic->program_2D = graphic->program_3D = graphic->program_text = 0;
  graphic->ft = NULL;
  graphic->face = NULL;
  graphic->init = 0;
  jbw_graphic_set_draw (graphic, draw);

  // Setting up the new window
#if HAVE_GTKGLAREA
  graphic->widget = (GtkGLArea *) gtk_gl_area_new ();
  if (!graphic->widget)
    {
      error_msg = _("unable to open the graphic area widget");
      goto error2;
    }
  g_signal_connect (graphic->widget, "realize",
                    (GCallback) jbw_graphic_init_gtk, NULL);
  g_signal_connect (graphic->widget, "resize",
                    (GCallback) jbw_graphic_resize_gtk, NULL);
  g_signal_connect (graphic->widget, "render",
                    (GCallback) jbw_graphic_render, NULL);
#if GTK_MAJOR_VERSION > 3
  graphic->window = (GtkWindow *) gtk_window_new ();
#else
  graphic->window = (GtkWindow *) gtk_window_new (GTK_WINDOW_TOPLEVEL);
#endif
  gtk_window_set_child (graphic->window, GTK_WIDGET (graphic->widget));
  gtk_window_set_title (graphic->window, title);
  g_signal_connect_swapped (graphic->window, "destroy",
                            (GCallback) jbw_graphic_destroy, graphic);
#elif HAVE_SDL
  graphic->window
    = SDL_CreateWindow (title,
                        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                        JBW_WINDOW_WIDTH, JBW_WINDOW_HEIGHT,
                        SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);
  if (!graphic->window)
    {
      error_msg = SDL_GetError ();
      goto error2;
    }
  SDL_GL_SetAttribute (SDL_GL_CONTEXT_MAJOR_VERSION, 2);
  graphic->sdl_context = SDL_GL_CreateContext (graphic->window);
  if (!graphic->sdl_context)
    {
      error_msg = SDL_GetError ();
      goto error2;
    }
#elif HAVE_GLFW
  graphic->window
    = glfwCreateWindow (JBW_WINDOW_WIDTH, JBW_WINDOW_HEIGHT, title, NULL, NULL);
  if (!graphic->window)
    {
      error_msg = _("unable to open the window");
      glfwTerminate ();
      goto error2;
    }
  glfwMakeContextCurrent (graphic->window);
  glfwSetFramebufferSizeCallback (graphic->window, jbw_graphic_resize_glfw);
  glfwSetWindowRefreshCallback (graphic->window, jbw_graphic_render_glfw);
#endif

  // Return the widget pointer
  jbw_graphic_pointer = graphic;
  return graphic;

  // Exit and show an error message on error
error2:
  jbw_graphic_destroy ();
error1:
  jb_error_add (error_msg, NULL);
  jb_error_show ();
  jb_error_destroy ();
  return NULL;
}

/**
 * Function to get the graphical size of the current JBWGraphic widget.
 */
void
jbw_graphic_get_display_size (void)
{
  JBWGraphic *graphic = jbw_graphic_pointer;
#if HAVE_GTKGLAREA
  graphic->width
    = gtk_widget_get_allocated_width (GTK_WIDGET (graphic->widget));
  graphic->height
    = gtk_widget_get_allocated_height (GTK_WIDGET (graphic->widget));
#elif HAVE_SDL
  SDL_GetWindowSize (graphic->window, &graphic->width, &graphic->height);
#elif HAVE_GLFW
  glfwGetFramebufferSize (graphic->window, &graphic->width, &graphic->height);
#endif
}

/**
 * Function to draw a string in the current JBWGraphic widget.
 */
void
jbw_graphic_draw_text (const char *string,      ///< string.
                       GLfloat x,       ///< x initial position.
                       GLfloat y,       ///< y initial position.
                       const GLfloat *color)    ///< color intensities array.
{
  GLfloat box[16];
  JBWGraphic *graphic;
  FT_Face *face;
  GLfloat x2, y2, w, h, sx, sy;
  GLuint id;
  FT_UInt glyph;
  gunichar c;

  // current JBWGraphic widget
  graphic = jbw_graphic_pointer;

  // enabling OpenGL properties
  glEnable (GL_BLEND);
  glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  // setting box coordinates
  box[2] = 0.f;
  box[3] = 0.f;
  box[6] = 1.f;
  box[7] = 0.f;
  box[10] = 0.f;
  box[11] = 1.f;
  box[14] = 1.f;
  box[15] = 1.f;

  // setting scale factors
  sx = 2.f / graphic->width;
  sy = 2.f / graphic->height;

  // setting up texture
  glUseProgram (graphic->program_text);
  glGenTextures (1, &id);
  glBindTexture (GL_TEXTURE_2D, id);
  glUniform1i (graphic->uniform_text, 0);
  glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glPixelStorei (GL_UNPACK_ALIGNMENT, 1);
  glUniform4fv (graphic->uniform_text_color, 1, color);
  glEnableVertexAttribArray (graphic->in_text_position);
  glBindBuffer (GL_ARRAY_BUFFER, graphic->vbo_text);
  glVertexAttribPointer (graphic->in_text_position, 4, GL_FLOAT, GL_FALSE, 0,
                         0);

  // drawing string
  face = graphic->face;
  for (; *string; string = g_utf8_next_char (string))
    {
      c = g_utf8_get_char (string);
      glyph = FT_Get_Char_Index (*face, c);
      if (FT_Load_Glyph (*face, glyph, FT_LOAD_RENDER))
        continue;
      glTexImage2D (GL_TEXTURE_2D,
                    0,
                    GL_ALPHA,
                    (*face)->glyph->bitmap.width,
                    (*face)->glyph->bitmap.rows,
                    0,
                    GL_ALPHA, GL_UNSIGNED_BYTE, (*face)->glyph->bitmap.buffer);
      x2 = x + (*face)->glyph->bitmap_left * sx;
      y2 = -y - (*face)->glyph->bitmap_top * sy;
      w = (*face)->glyph->bitmap.width * sx;
      h = (*face)->glyph->bitmap.rows * sy;
      box[0] = x2;
      box[1] = -y2;
      box[4] = x2 + w;
      box[5] = -y2;
      box[8] = x2;
      box[9] = -y2 - h;
      box[12] = x2 + w;
      box[13] = -y2 - h;
      glBufferData (GL_ARRAY_BUFFER, sizeof (box), box, GL_DYNAMIC_DRAW);
      glDrawArrays (GL_TRIANGLE_STRIP, 0, 4);
      x += ((*face)->glyph->advance.x >> 6) * sx;
      y += ((*face)->glyph->advance.y >> 6) * sy;
    }

  // freeing memory
  glDisableVertexAttribArray (graphic->in_text_position);
  glDeleteTextures (1, &id);

  // disabling OpenGL features
  glDisable (GL_BLEND);
}

/**
 * Function to resize the graphic limits if map on the current JBWGraphic 
 * widget.
 */
void
jbw_graphic_map_resize (void)
{
  JBWGraphic *graphic = jbw_graphic_pointer;
  JBDOUBLE vw, vh, cw, ch;
  vw = graphic->x2 - graphic->x1;
  vh = graphic->y2 - graphic->y1;
  cw = graphic->xmax - graphic->xmin;
  ch = graphic->ymax - graphic->ymin;
  vw /= cw;
  vh /= ch;
  vw /= vh;
  if (vw > 1.L)
    {
      vw -= 1.L;
      vw *= 0.5L;
      vw *= cw;
      graphic->xmax += vw;
      graphic->xmin -= vw;
    }
  else
    {
      vh = 1.L / vw;
      vh -= 1.L;
      vh *= 0.5L;
      vh *= ch;
      graphic->ymax += vh;
      graphic->ymin -= vh;
    }
}

/**
 * Function to get the limit coordinates on the current JBWGraphic widget from 4
 * tabular functions (JBFLOAT).
 */
void
jbw_graphic_draw_resize (JBFLOAT *x,    ///< x-coordinates array.
                         JBFLOAT *y1,   ///< 1st y-coordinates array.
                         JBFLOAT *y2,   ///< 2nd y-coordinates array.
                         JBFLOAT *z1,   ///< 1st z-coordinates array.
                         JBFLOAT *z2,   ///< 2nd z-coordinates array.
                         int n) ///< number of array elements.
{
  JBWGraphic *graphic = jbw_graphic_pointer;
  JBMFarray *f1, *f2;
  JBFLOAT k1, k2, kmin, kmax;
  f1 = jbm_farray_create (x, n);
  jbm_farray_maxmin (f1, &kmax, &kmin);
  jbm_farray_destroy (f1);
  graphic->xmax = (JBDOUBLE) kmax;
  graphic->xmin = (JBDOUBLE) kmin;
  if (y1)
    {
      f1 = jbm_farray_create (y1, n);
      jbm_farray_maxmin (f1, &kmax, &kmin);
      jbm_farray_destroy (f1);
      if (y2)
        {
          f2 = jbm_farray_create (y2, n);
          jbm_farray_maxmin (f2, &k2, &k1);
          jbm_farray_destroy (f2);
          kmax = FMAX (kmax, k2);
          kmin = FMIN (kmin, k1);
        }
      graphic->ymax = (JBDOUBLE) kmax;
      graphic->ymin = (JBDOUBLE) kmin;
    }
  if (z1)
    {
      f1 = jbm_farray_create (z1, n);
      jbm_farray_maxmin (f1, &kmax, &kmin);
      jbm_farray_destroy (f1);
      if (z2)
        {
          f2 = jbm_farray_create (z2, n);
          jbm_farray_maxmin (f2, &k2, &k1);
          jbm_farray_destroy (f2);
          kmax = FMAX (kmax, k2);
          kmin = FMIN (kmin, k1);
        }
      graphic->zmax = (JBDOUBLE) kmax;
      graphic->zmin = (JBDOUBLE) kmin;
    }
}

/**
 * Function to get the limit coordinates on the current JBWGraphic widget from 4
 * tabular functions (JBDOUBLE).
 */
void
jbw_graphic_draw_resizel (JBDOUBLE *x,  ///< x-coordinates array.
                          JBDOUBLE *y1, ///< 1st y-coordinates array.
                          JBDOUBLE *y2, ///< 2nd y-coordinates array.
                          JBDOUBLE *z1, ///< 1st z-coordinates array.
                          JBDOUBLE *z2, ///< 2nd z-coordinates array.
                          int n)        ///< number of array elements.
{
  JBWGraphic *graphic = jbw_graphic_pointer;
  JBDOUBLE k1, k2, kmin, kmax;
  jbm_darray_maxmin (x, n, &kmax, &kmin);
  graphic->xmax = kmax;
  graphic->xmin = kmin;
  if (y1)
    {
      jbm_darray_maxmin (y1, n, &kmax, &kmin);
      if (y2)
        {
          jbm_darray_maxmin (y2, n, &k2, &k1);
          kmax = FMAXL (kmax, k2);
          kmin = FMINL (kmin, k1);
        }
      graphic->ymax = kmax;
      graphic->ymin = kmin;
    }
  if (z1)
    {
      jbm_darray_maxmin (z1, n, &kmax, &kmin);
      if (z2)
        {
          jbm_darray_maxmin (z2, n, &k2, &k1);
          kmax = FMAXL (kmax, k2);
          kmin = FMINL (kmin, k1);
        }
      graphic->zmax = kmax;
      graphic->zmin = kmin;
    }
}

/**
 * Function to get the limit coordinates on the current JBWGraphic widget from 4
 * tabular functions defined by a struct array (JBFLOAT).
 */
void
jbw_graphic_draw_resizev (void *x,
                          ///< pointer to the first x-coordinate element.
                          void *y1,
                          ///< pointer to the first 1st y-coordinate element.
                          void *y2,
                          ///< pointer to the first 2nd y-coordinate element.
                          void *z1,
                          ///< pointer to the first 1st z-coordinate element.
                          void *z2,
                          ///< pointer to the first 2nd z-coordinate element.
                          unsigned int size,    ///< struct size.
                          int n)        ///< last arrays element number.
{
  JBWGraphic *graphic = jbw_graphic_pointer;
  JBFLOAT k1, k2, kmin, kmax;
  jbm_varray_maxmin (x, size, n, &kmax, &kmin);
  graphic->xmax = (JBDOUBLE) kmax;
  graphic->xmin = (JBDOUBLE) kmin;
  if (y1)
    {
      jbm_varray_maxmin (y1, size, n, &kmax, &kmin);
      if (y2)
        {
          jbm_varray_maxmin (y2, size, n, &k2, &k1);
          kmax = FMAX (kmax, k2);
          kmin = FMIN (kmin, k1);
        }
      graphic->ymax = (JBDOUBLE) kmax;
      graphic->ymin = (JBDOUBLE) kmin;
    }
  if (z1)
    {
      jbm_varray_maxmin (z1, size, n, &kmax, &kmin);
      if (z2)
        {
          jbm_varray_maxmin (z2, size, n, &k2, &k1);
          kmax = FMAX (kmax, k2);
          kmin = FMIN (kmin, k1);
        }
      graphic->zmax = kmax;
      graphic->zmin = kmin;
    }
}

/**
 * Function to get the limit coordinates on the current JBWGraphic widget from 4
 * tabular functions defined by a struct array (JBDOUBLE).
 */
void
jbw_graphic_draw_resizevl (void *x,
                           ///< pointer to the first x-coordinate element.
                           void *y1,
                           ///< pointer to the first 1st y-coordinate element.
                           void *y2,
                           ///< pointer to the first 2nd y-coordinate element.
                           void *z1,
                           ///< pointer to the first 1st z-coordinate element.
                           void *z2,
                           ///< pointer to the first 2nd z-coordinate element.
                           unsigned int size,   ///< struct size.
                           int n)       ///< last arrays element number.
{
  JBWGraphic *graphic = jbw_graphic_pointer;
  JBDOUBLE k1, k2, kmin, kmax;
  jbm_varray_maxminl (x, size, n, &kmax, &kmin);
  graphic->xmax = kmax;
  graphic->xmin = kmin;
  if (y1)
    {
      jbm_varray_maxminl (y1, size, n, &kmax, &kmin);
      if (y2)
        {
          jbm_varray_maxminl (y2, size, n, &k2, &k1);
          kmax = FMAXL (kmax, k2);
          kmin = FMINL (kmin, k1);
        }
      graphic->ymax = kmax;
      graphic->ymin = kmin;
    }
  if (z1)
    {
      jbm_varray_maxminl (z1, size, n, &kmax, &kmin);
      if (z2)
        {
          jbm_varray_maxminl (z2, size, n, &k2, &k1);
          kmax = FMAXL (kmax, k2);
          kmin = FMINL (kmin, k1);
        }
      graphic->zmax = kmax;
      graphic->zmin = kmin;
    }
}

/**
 * Function to draw rectangles with color in the current JBWGraphic widget.
 */
void
jbw_graphic_draw_rectangles_color (GLfloat *vertex,     ///< vertex array.
                                   GLushort *index,     ///< index array.
                                   unsigned int n)      ///< rectangles number.
{
  JBWGraphic *graphic = jbw_graphic_pointer;
  GLuint vao, ebo;
  glGenBuffers (1, &vao);
  glBindBuffer (GL_ARRAY_BUFFER, vao);
  glBufferData (GL_ARRAY_BUFFER, 4 * 5 * sizeof (GLfloat) * n, vertex,
                GL_DYNAMIC_DRAW);
  glEnableVertexAttribArray (graphic->in_2Dc_position);
  glVertexAttribPointer (graphic->in_2Dc_position, 2, GL_FLOAT, GL_FALSE,
                         5 * sizeof (GLfloat), NULL);
  glEnableVertexAttribArray (graphic->in_2Dc_color);
  glVertexAttribPointer (graphic->in_2Dc_color, 3, GL_FLOAT, GL_FALSE,
                         5 * sizeof (GLfloat), (void *) (2 * sizeof (GLfloat)));
  glGenBuffers (1, &ebo);
  glBindBuffer (GL_ELEMENT_ARRAY_BUFFER, ebo);
  glBufferData (GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof (GLushort) * n, index,
                GL_DYNAMIC_DRAW);
  glDrawElements (GL_TRIANGLES, 6 * n, GL_UNSIGNED_SHORT, 0);
  glDeleteBuffers (1, &ebo);
  glDeleteBuffers (1, &vao);
  glDisableVertexAttribArray (graphic->in_2Dc_color);
  glDisableVertexAttribArray (graphic->in_2Dc_position);
}


/**
 * Function to draw a tabuled function on the current JBWGraphic widget
 * (JBFLOAT).
 */
void
jbw_graphic_draw_farray (JBFLOAT *x,    ///< x-coordinates array.
                         JBFLOAT *y,    ///< y-coordinates array.
                         unsigned int n,        ///< number of array elements.
                         const GLfloat *color,  ///< RGB color.
                         GLenum type)   ///< draw type.
{
  JBWGraphic *graphic;
  GLfloat *vertex;
  GLuint v;
  unsigned int i;
  graphic = jbw_graphic_pointer;
  glUniform3fv (graphic->uniform_2D_color, 1, color);
  glGenBuffers (1, &v);
  glBindBuffer (GL_ARRAY_BUFFER, v);
  ++n;
  vertex = (GLfloat *) g_malloc (n * 2 * sizeof (GLfloat));
  for (i = 0; i < n; ++i)
    {
      vertex[2 * i] = (GLfloat) x[i];
      vertex[2 * i + 1] = (GLfloat) y[i];
    }
  glBufferData (GL_ARRAY_BUFFER, n * 2 * sizeof (GLfloat), vertex,
                GL_DYNAMIC_DRAW);
  glEnableVertexAttribArray (graphic->in_2D_position);
  glVertexAttribPointer (graphic->in_2D_position, 2, GL_FLOAT, GL_FALSE, 0,
                         NULL);
  glDrawArrays (type, 0, n);
  glDeleteBuffers (1, &v);
  glDisableVertexAttribArray (graphic->in_2D_position);
  g_free (vertex);
}

/**
 * Function to draw a tabuled function on the current JBWGraphic widget
 * (JBDOUBLE).
 */
void
jbw_graphic_draw_darray (JBDOUBLE *x,   ///< x-coordinates array.
                         JBDOUBLE *y,   ///< y-coordinates array.
                         unsigned int n,        ///< number of array elements.
                         const GLfloat *color,  ///< RGB color.
                         GLenum type)   ///< draw type.
{
  JBWGraphic *graphic;
  GLdouble *vertex;
  GLuint v;
  unsigned int i;
  graphic = jbw_graphic_pointer;
  glUniform3fv (graphic->uniform_2D_color, 1, color);
  glGenBuffers (1, &v);
  glBindBuffer (GL_ARRAY_BUFFER, v);
  ++n;
  vertex = (GLdouble *) g_malloc (n * 2 * sizeof (GLdouble));
  for (i = 0; i < n; ++i)
    {
      vertex[2 * i] = (GLdouble) x[i];
      vertex[2 * i + 1] = (GLdouble) y[i];
    }
  glBufferData (GL_ARRAY_BUFFER, n * 2 * sizeof (GLdouble), vertex,
                GL_DYNAMIC_DRAW);
  glEnableVertexAttribArray (graphic->in_2D_position);
  glVertexAttribPointer (graphic->in_2D_position, 2, GL_DOUBLE, GL_FALSE, 0,
                         NULL);
  glDrawArrays (type, 0, n);
  glDeleteBuffers (1, &v);
  glDisableVertexAttribArray (graphic->in_2D_position);
  g_free (vertex);
}

/**
 * Function to draw a tabuled function on the current JBWGraphic widget 
 * (JBFLOAT).
 */
void
jbw_graphic_draw_varray (void *x,       ///< x-coordinates array.
                         void *y,       ///< y-coordinates array.
                         unsigned int size,     ///< struct size.
                         unsigned int n,        ///< number of array elements.
                         const GLfloat *color,  ///< RGB color.
                         GLenum type)   ///< draw type.
{
  JBWGraphic *graphic = jbw_graphic_pointer;
  GLfloat *vertex;
  GLuint v;
  unsigned int i;
  glUniform3fv (graphic->uniform_2D_color, 1, color);
  glGenBuffers (1, &v);
  glBindBuffer (GL_ARRAY_BUFFER, v);
  ++n;
  vertex = (GLfloat *) g_malloc (n * 2 * sizeof (GLfloat));
  for (i = 0; i < n; ++i)
    {
      vertex[2 * i] = (GLfloat) * ((JBFLOAT *) ((char *) x + i * size));
      vertex[2 * i + 1] = (GLfloat) * ((JBFLOAT *) ((char *) y + i * size));
    }
  glBufferData (GL_ARRAY_BUFFER, n * 2 * sizeof (GLfloat), vertex,
                GL_DYNAMIC_DRAW);
  glEnableVertexAttribArray (graphic->in_2D_position);
  glVertexAttribPointer (graphic->in_2D_position, 2, GL_FLOAT, GL_FALSE, 0,
                         NULL);
  glDrawArrays (type, 0, n);
  glDeleteBuffers (1, &v);
  glDisableVertexAttribArray (graphic->in_2D_position);
  g_free (vertex);
}

/**
 * Function to draw a tabuled function on the current JBWGraphic widget (JBFLOAT).
 */
void
jbw_graphic_draw_varrayl (void *x,      ///< x-coordinates array.
                          void *y,      ///< y-coordinates array.
                          unsigned int size,    ///< struct size.
                          unsigned int n,       ///< number of array elements.
                          const GLfloat *color, ///< RGB color.
                          GLenum type)  ///< draw type.
{
  JBWGraphic *graphic;
  GLdouble *vertex;
  GLuint v;
  unsigned int i;
  graphic = jbw_graphic_pointer;
  glUniform3fv (graphic->uniform_2D_color, 1, color);
  glGenBuffers (1, &v);
  glBindBuffer (GL_ARRAY_BUFFER, v);
  ++n;
  vertex = (GLdouble *) g_malloc (n * 2 * sizeof (GLdouble));
  for (i = 0; i < n; ++i)
    {
      vertex[2 * i] = (GLdouble) * ((JBDOUBLE *) ((char *) x + i * size));
      vertex[2 * i + 1] = (GLdouble) * ((JBDOUBLE *) ((char *) y + i * size));
    }
  glBufferData (GL_ARRAY_BUFFER, n * 2 * sizeof (GLdouble), vertex,
                GL_DYNAMIC_DRAW);
  glEnableVertexAttribArray (graphic->in_2D_position);
  glVertexAttribPointer (graphic->in_2D_position, 2, GL_DOUBLE, GL_FALSE, 0,
                         NULL);
  glDrawArrays (type, 0, n);
  glDeleteBuffers (1, &v);
  glDisableVertexAttribArray (graphic->in_2D_position);
  g_free (vertex);
}

/**
 * Function to draw a rectangle on the current JBWGraphic widget (JBFLOAT).
 */
void
jbw_graphic_draw_rectangle (JBFLOAT x1, ///< 1st corner x-coordinate.
                            JBFLOAT y1, ///< 1st corner y-coordinate.
                            JBFLOAT x2, ///< 2nd corner x-coordinate.
                            JBFLOAT y2, ///< 2nd corner y-coordinate.
                            const GLfloat *color)       ///< RGB color.
{
  JBFLOAT x[4] = { x1, x2, x2, x1 };
  JBFLOAT y[4] = { y1, y1, y2, y2 };
  jbw_graphic_draw_farray (x, y, 3, color, GL_LINE_LOOP);
}

/**
 * Function to draw a rectangle on the current JBWGraphic widget (JBDOUBLE).
 */
void
jbw_graphic_draw_rectanglel (JBDOUBLE x1,       ///< 1st corner x-coordinate.
                             JBDOUBLE y1,       ///< 1st corner y-coordinate.
                             JBDOUBLE x2,       ///< 2nd corner x-coordinate.
                             JBDOUBLE y2,       ///< 2nd corner y-coordinate.
                             const GLfloat *color)      ///< RGB color.
{
  JBDOUBLE x[4] = { x1, x2, x2, x1 };
  JBDOUBLE y[4] = { y1, y1, y2, y2 };
  jbw_graphic_draw_darray (x, y, 3, color, GL_LINE_LOOP);
}

/**
 * Function to set the viewport and to draw labels, tics and grid on the current
 * JBWGraphic widget.
 */
void
jbw_graphic_draw_labels (void)
{
  JBDOUBLE xtic[JBW_GRAPHIC_N_TICS];
  JBDOUBLE ytic[JBW_GRAPHIC_N_TICS];
  JBDOUBLE ztic[JBW_GRAPHIC_N_TICS];
  JBFLOAT x[2 * JBW_GRAPHIC_N_TICS];
  JBFLOAT y[2 * JBW_GRAPHIC_N_TICS];
  char buffer[512];
  JBWGraphic *graphic;
  const GLfloat *color_x, *color_y, *color_z;
  JBFLOAT kx, ky, kz;
  GLfloat k, x1, x2, y1, y2, sx, sy, sa, sb;
  int i;
  graphic = jbw_graphic_pointer;
  jbw_graphic_get_display_size ();
  jbw_draw_clear (1.f, 1.f, 1.f, 0.f);
  glViewport (0, 0, graphic->width, graphic->height);
  sx = (2.f * graphic->char_width) / graphic->width;
  sy = (2.f * graphic->char_height) / graphic->height;
  sb = 0.2f * sy;
  sa = 0.2f * sx;
  graphic->x1 = graphic->y1 = 0;
  graphic->x2 = graphic->width;
  graphic->y2 = graphic->height;
  k = 1.f;
  if (graphic->str_title)
    {
      k -= sy;
      graphic->y2 -= graphic->char_height;
      jbw_graphic_draw_text (graphic->str_title,
                             -0.5f * sx * strlen (graphic->str_title), sb + k,
                             jbw_black);
    }
  if (!graphic->str_x)
    graphic->nx = 0;
  if (graphic->str_y || graphic->str_z)
    {
      k -= sy;
      graphic->y2 -= graphic->char_height;
      if (graphic->str_y)
        jbw_graphic_draw_text (graphic->str_y, -1.f, sb + k, jbw_blue);
      if (graphic->str_z)
        jbw_graphic_draw_text (graphic->str_z,
                               1.f - sx * strlen (graphic->str_z), sb + k,
                               jbw_red);
    }
  if (graphic->str_yy || graphic->str_zz)
    {
      k -= sy;
      graphic->y2 -= graphic->char_height;
      if (graphic->str_yy)
        jbw_graphic_draw_text (graphic->str_yy, -1.f, sb + k, jbw_green);
      if (graphic->str_zz)
        jbw_graphic_draw_text (graphic->str_zz,
                               1.f - sx * strlen (graphic->str_zz), sb + k,
                               jbw_brown);
    }
  graphic->y1 = ceil (2.5f * graphic->char_height);
  graphic->y2 -= ceil (0.5f * graphic->char_height);
  if (graphic->str_y || graphic->str_yy)
    graphic->x1 = (JBW_GRAPHIC_N_CHARS + 1) * graphic->char_width;
  if (graphic->str_z || graphic->str_zz)
    graphic->x2 -= (JBW_GRAPHIC_N_CHARS + 1) * graphic->char_width;
  else
    graphic->x2 -= ceil (0.5f * JBW_GRAPHIC_N_CHARS * graphic->char_width);
  if (graphic->map)
    jbw_graphic_map_resize ();
  x1 = (2.f * graphic->x1) / graphic->width - 1.f;
  x2 = (2.f * graphic->x2) / graphic->width - 1.f;
  y1 = (2.f * graphic->y1) / graphic->height - 1.f;
  y2 = (2.f * graphic->y2) / graphic->height - 1.f;
  if (graphic->str_x)
    {
      jbw_draw_rangel (&graphic->xmin, &graphic->xmax);
      jbw_draw_ticsl (graphic->xmin, graphic->xmax,
                      graphic->nxmax, &graphic->nx, graphic->xtic);
      jbw_graphic_draw_text (graphic->str_x,
                             ((float) graphic->x1 + graphic->x2)
                             / graphic->width - 1.f
                             - 0.5f * sx * strlen (graphic->str_x),
                             sb - 1.f, jbw_black);
      for (i = 0; i < graphic->nx; ++i)
        {
          sprintf (buffer, FGL, graphic->xtic[i]);
          xtic[i] =
            jbm_extrapolatel (graphic->xtic[i], graphic->xmin, graphic->xmax,
                              (JBDOUBLE) x1, (JBDOUBLE) x2);
          k = (GLfloat) xtic[i];
          jbw_graphic_draw_text (buffer,
                                 k - 0.5f * sx * strlen (buffer),
                                 sb - 1.f + sy, jbw_black);
        }
    }
  else
    graphic->nx = 0;
  if (graphic->str_y || graphic->str_yy)
    {
      jbw_draw_rangel (&graphic->ymin, &graphic->ymax);
      jbw_draw_ticsl (graphic->ymin, graphic->ymax,
                      graphic->nymax, &graphic->ny, graphic->ytic);
      for (i = 0; i < graphic->ny; ++i)
        {
          sprintf (buffer, FGL, graphic->ytic[i]);
          ytic[i] =
            jbm_extrapolatel (graphic->ytic[i], graphic->ymin, graphic->ymax,
                              (JBDOUBLE) y1, (JBDOUBLE) y2);
          k = (GLfloat) ytic[i];
          jbw_graphic_draw_text (buffer,
                                 x1 - sx * strlen (buffer) - sa,
                                 sb + k - 0.5f * sy, jbw_blue);
        }
    }
  else
    graphic->ny = 0;
  if (graphic->str_z || graphic->str_zz)
    {
      jbw_draw_rangel (&graphic->zmin, &graphic->zmax);
      jbw_draw_ticsl (graphic->zmin, graphic->zmax,
                      graphic->nzmax, &graphic->nz, graphic->ztic);
      for (i = 0; i < graphic->nz; ++i)
        {
          sprintf (buffer, FGL, graphic->ztic[i]);
          ztic[i] =
            jbm_extrapolatel (graphic->ztic[i], graphic->zmin, graphic->zmax,
                              (JBDOUBLE) y1, (JBDOUBLE) y2);
          k = (GLfloat) ztic[i];
          jbw_graphic_draw_text (buffer, x2 + sa, sb + k - 0.5f * sy, jbw_red);
        }
    }
  else
    graphic->nz = 0;
  glUseProgram (graphic->program_2D);
  glUniformMatrix4fv (graphic->uniform_2D_matrix, 1, GL_FALSE, jbw_identity);
  if (graphic->grid)
    {
      kx = y2;
      ky = x2;
      kz = x1;
      color_x = jbw_stargray;
      color_y = jbw_starblue;
      color_z = jbw_starred;

    }
  else
    {
      kx = y1 + 0.5 * sy;
      ky = x1 + 0.5 * sx;
      kz = x2 - 0.5 * sx;
      color_x = color_y = color_z = jbw_black;
    }
  if (graphic->nx)
    {
      for (i = 0; i < graphic->nx; ++i)
        {
          x[2 * i + 1] = x[2 * i] = (JBFLOAT) xtic[i];
          y[2 * i] = y1;
          y[2 * i + 1] = kx;
        }
      jbw_graphic_draw_farray (x, y, 2 * i - 1, color_x, GL_LINES);
    }
  if (graphic->nz)
    {
      for (i = 0; i < graphic->nz; ++i)
        {
          y[2 * i + 1] = y[2 * i] = (JBFLOAT) ztic[i];
          x[2 * i] = kz;
          x[2 * i + 1] = x2;
        }
      jbw_graphic_draw_farray (x, y, 2 * i - 1, color_z, GL_LINES);
    }
  if (graphic->ny)
    {
      for (i = 0; i < graphic->ny; ++i)
        {
          y[2 * i + 1] = y[2 * i] = (JBFLOAT) ytic[i];
          x[2 * i] = x1;
          x[2 * i + 1] = ky;
        }
      jbw_graphic_draw_farray (x, y, 2 * i - 1, color_y, GL_LINES);
    }
  jbw_graphic_draw_rectangle ((JBFLOAT) x1, (JBFLOAT) y1,
                              (JBFLOAT) x2, (JBFLOAT) y2, jbw_black);
  glViewport (graphic->x1, graphic->y1,
              graphic->x2 - graphic->x1, graphic->y2 - graphic->y1);
}

/**
 * Function to render the logo in the current JBWGraphic widget.
 */
void
jbw_graphic_draw_logo (void)
{
  JBWGraphic *graphic = jbw_graphic_pointer;
  JBWImage *logo = graphic->logo;
  if (logo)
    jbw_image_draw (logo, 0, 0, graphic->width, graphic->height);
}

/**
 * Function to draw lines defined by float arrays in the current JBWGraphic
 * widget (JBFLOAT).
 */
void
jbw_graphic_draw_lines (JBFLOAT *x,     ///< x-coordinates array.
                        JBFLOAT *y1,    ///< 1st y-coordinates array.
                        JBFLOAT *y2,    ///< 2nd y-coordinates array.
                        JBFLOAT *z1,    ///< 1st z-coordinates array.
                        JBFLOAT *z2,    ///< 2nd z-coordinates array.
                        int n)  ///< last arrays element number.
{
  JBWGraphic *graphic = jbw_graphic_pointer;
  if (!x)
    {
      jbw_graphic_draw_labels ();
      return;
    }
  if (graphic->resize)
    jbw_graphic_draw_resize (x, y1, y2, z1, z2, n);
  jbw_graphic_draw_labels ();
  if (y1 || y2)
    {
      jbw_draw_orthogonal_matrixl (graphic->uniform_2D_matrix,
                                   (GLdouble) graphic->xmin,
                                   (GLdouble) graphic->ymin,
                                   (GLdouble) graphic->xmax - graphic->xmin,
                                   (GLdouble) graphic->ymax - graphic->ymin);
      if (y1)
        jbw_graphic_draw_farray (x, y1, n, jbw_blue, GL_LINE_STRIP);
      if (y2)
        jbw_graphic_draw_farray (x, y2, n, jbw_brown, GL_LINE_STRIP);
    }
  if (z1 || z2)
    {
      jbw_draw_orthogonal_matrixl (graphic->uniform_2D_matrix,
                                   (GLdouble) graphic->xmin,
                                   (GLdouble) graphic->zmin,
                                   (GLdouble) graphic->xmax - graphic->xmin,
                                   (GLdouble) graphic->zmax - graphic->zmin);
      if (z1)
        jbw_graphic_draw_farray (x, z1, n, jbw_red, GL_LINE_STRIP);
      if (z2)
        jbw_graphic_draw_farray (x, z2, n, jbw_green, GL_LINE_STRIP);
    }
}

/**
 * Function to draw lines defined by float arrays in the current JBWGraphic 
 * widget (JBDOUBLE).
 */
void
jbw_graphic_draw_linesl (JBDOUBLE *x,   ///< x-coordinates array.
                         JBDOUBLE *y1,  ///< 1st y-coordinates array.
                         JBDOUBLE *y2,  ///< 2nd y-coordinates array.
                         JBDOUBLE *z1,  ///< 1st z-coordinates array.
                         JBDOUBLE *z2,  ///< 2nd z-coordinates array.
                         int n) ///< last arrays element number.
{
  JBWGraphic *graphic = jbw_graphic_pointer;
  if (!x)
    {
      jbw_graphic_draw_labels ();
      return;
    }
  if (graphic->resize)
    jbw_graphic_draw_resizel (x, y1, y2, z1, z2, n);
  jbw_graphic_draw_labels ();
  if (y1 || y2)
    {
      jbw_draw_orthogonal_matrixl (graphic->uniform_2D_matrix,
                                   (GLdouble) graphic->xmin,
                                   (GLdouble) graphic->ymin,
                                   (GLdouble) graphic->xmax - graphic->xmin,
                                   (GLdouble) graphic->ymax - graphic->ymin);
      if (y1)
        jbw_graphic_draw_darray (x, y1, n, jbw_blue, GL_LINE_STRIP);
      if (y2)
        jbw_graphic_draw_darray (x, y2, n, jbw_brown, GL_LINE_STRIP);
    }
  if (z1 || z2)
    {
      jbw_draw_orthogonal_matrixl (graphic->uniform_2D_matrix,
                                   (GLdouble) graphic->xmin,
                                   (GLdouble) graphic->ymin,
                                   (GLdouble) graphic->xmax - graphic->xmin,
                                   (GLdouble) graphic->ymax - graphic->ymin);
      if (z1)
        jbw_graphic_draw_darray (x, z1, n, jbw_red, GL_LINE_STRIP);
      if (z2)
        jbw_graphic_draw_darray (x, z2, n, jbw_green, GL_LINE_STRIP);
    }
}

/**
 * Function to draw lines defined by struct arrays in the current JBWGraphic
 * widget (JBFLOAT).
 */
void
jbw_graphic_draw_linesv (void *x,
                         ///< pointer to the first x-coordinate element.
                         void *y1,
                         ///< pointer to the first 1st y-coordinate element.
                         void *y2,
                         ///< pointer to the first 2nd y-coordinate element.
                         void *z1,
                         ///< pointer to the first 1st z-coordinate element.
                         void *z2,
                         ///< pointer to the first 2nd z-coordinate element.
                         unsigned int size,     ///< struct size.
                         int n) ///< last arrays element number.
{
  JBWGraphic *graphic = jbw_graphic_pointer;
  if (!x)
    {
      jbw_graphic_draw_labels ();
      return;
    }
  if (graphic->resize)
    jbw_graphic_draw_resizev (x, y1, y2, z1, z2, size, n);
  jbw_graphic_draw_labels ();
  if (y1 || y2)
    {
      jbw_draw_orthogonal_matrixl (graphic->uniform_2D_matrix,
                                   (GLdouble) graphic->xmin,
                                   (GLdouble) graphic->ymin,
                                   (GLdouble) graphic->xmax - graphic->xmin,
                                   (GLdouble) graphic->ymax - graphic->ymin);
      if (y1)
        jbw_graphic_draw_varray (x, y1, size, n, jbw_blue, GL_LINE_STRIP);
      if (y2)
        jbw_graphic_draw_varray (x, y2, size, n, jbw_brown, GL_LINE_STRIP);
    }
  if (z1 || z2)
    {
      jbw_draw_orthogonal_matrixl (graphic->uniform_2D_matrix,
                                   (GLdouble) graphic->xmin,
                                   (GLdouble) graphic->zmin,
                                   (GLdouble) graphic->xmax - graphic->xmin,
                                   (GLdouble) graphic->zmax - graphic->zmin);
      if (z1)
        jbw_graphic_draw_varray (x, z1, size, n, jbw_red, GL_LINE_STRIP);
      if (z2)
        jbw_graphic_draw_varray (x, z2, size, n, jbw_green, GL_LINE_STRIP);
    }
}

/**
 * Function to draw lines defined by struct arrays in the current JBWGraphic 
 * widget (JBDOUBLE).
 */
void
jbw_graphic_draw_linesvl (void *x,
                          ///< pointer to the first x-coordinate element.
                          void *y1,
                          ///< pointer to the first 1st y-coordinate element.
                          void *y2,
                          ///< pointer to the first 2nd y-coordinate element.
                          void *z1,
                          ///< pointer to the first 1st z-coordinate element.
                          void *z2,
                          ///< pointer to the first 2nd z-coordinate element.
                          unsigned int size,    ///< struct size.
                          int n)        ///< last arrays element number.
{
  JBWGraphic *graphic = jbw_graphic_pointer;
  if (!x)
    {
      jbw_graphic_draw_labels ();
      return;
    }
  if (graphic->resize)
    jbw_graphic_draw_resizevl (x, y1, y2, z1, z2, size, n);
  jbw_graphic_draw_labels ();
  if (y1 || y2)
    {
      jbw_draw_orthogonal_matrixl (graphic->uniform_2D_matrix,
                                   (GLdouble) graphic->xmin,
                                   (GLdouble) graphic->ymin,
                                   (GLdouble) graphic->xmax - graphic->xmin,
                                   (GLdouble) graphic->ymax - graphic->ymin);
      if (y1)
        jbw_graphic_draw_varrayl (x, y1, size, n, jbw_blue, GL_LINE_STRIP);
      if (y2)
        jbw_graphic_draw_varrayl (x, y2, size, n, jbw_brown, GL_LINE_STRIP);
    }
  if (z1 || z2)
    {
      jbw_draw_orthogonal_matrixl (graphic->uniform_2D_matrix,
                                   (GLdouble) graphic->xmin,
                                   (GLdouble) graphic->zmin,
                                   (GLdouble) graphic->xmax - graphic->xmin,
                                   (GLdouble) graphic->zmax - graphic->zmin);
      if (z1)
        jbw_graphic_draw_varrayl (x, z1, size, n, jbw_red, GL_LINE_STRIP);
      if (z2)
        jbw_graphic_draw_varrayl (x, z2, size, n, jbw_green, GL_LINE_STRIP);
    }
}

/**
 * Function to save the current JBWGraphic widget on a file.
 */
void
jbw_graphic_save (char *file_name)      ///< file name.
{
  JBWGraphic *graphic;
  png_struct *png;
  png_info *info;
  png_byte **row_pointers;
  GLubyte *pixels;
  FILE *file;
  unsigned int row_bytes, pointers_bytes, pixels_bytes, i, x2, y2;
  graphic = jbw_graphic_pointer;
  jbw_graphic_get_display_size ();
  x2 = graphic->width;
  y2 = graphic->height;
  png = png_create_write_struct (PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
  if (!png)
    return;
  info = png_create_info_struct (png);
  if (!info)
    return;
  file = fopen (file_name, "wb");
  if (!file)
    return;
  if (setjmp (png_jmpbuf (png)))
    {
      printf ("Error png_init_io\n");
      exit (0);
    }
  png_init_io (png, file);
  if (setjmp (png_jmpbuf (png)))
    {
      printf ("Error png_set_IHDR\n");
      exit (0);
    }
  png_set_IHDR (png,
                info,
                x2,
                y2,
                8,
                PNG_COLOR_TYPE_RGBA,
                PNG_INTERLACE_NONE,
                PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);
  if (setjmp (png_jmpbuf (png)))
    {
      printf ("Error png_write_info\n");
      exit (0);
    }
  png_write_info (png, info);
  glViewport (0, 0, x2, y2);
  row_bytes = 4 * x2;
  pixels_bytes = row_bytes * y2;
  pixels = (GLubyte *) g_slice_alloc (pixels_bytes);
  glReadPixels (0, 0, x2, y2, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
  pointers_bytes = y2 * sizeof (png_byte *);
  row_pointers = (png_byte **) g_slice_alloc (pointers_bytes);
  for (i = 0; i < y2; ++i)
    {
      row_pointers[i] = (png_byte *) g_slice_alloc (row_bytes);
      memcpy (row_pointers[i], pixels + (y2 - 1 - i) * row_bytes, row_bytes);
    }
  if (setjmp (png_jmpbuf (png)))
    {
      printf ("Error png_write_image\n");
      exit (0);
    }
  png_write_image (png, row_pointers);
  for (i = 0; i < y2; ++i)
    g_slice_free1 (row_bytes, row_pointers[i]);
  g_slice_free1 (pointers_bytes, row_pointers);
  g_slice_free1 (pixels_bytes, pixels);
  if (setjmp (png_jmpbuf (png)))
    {
      printf ("Error png_write_end\n");
      exit (0);
    }
  png_write_end (png, NULL);
  fclose (file);
  png_destroy_write_struct (&png, &info);
}

/**
 * function to save the view of the current JBWGraphic widget on a file.
 */
static void
jbw_graphic_dialog_response (GtkFileChooserDialog *dlg,
                             ///< GtkFileChooserDialog struct.
                             int id)    ///< response identifier.
{
  JBWGraphic *graphic;
  GMainContext *context;
  GFile *file;
  char *buffer;
  if (id == GTK_RESPONSE_OK)
    {
      file = gtk_file_chooser_get_file (GTK_FILE_CHOOSER (dlg));
      buffer = g_file_get_path (file);
      g_object_unref (file);
      if (buffer)
        {
          graphic = jbw_graphic_pointer;
          context = g_main_context_default ();
          graphic->draw (graphic);
          while (g_main_context_pending (context))
            g_main_context_iteration (context, 0);
          jbw_graphic_save (buffer);
          g_free (buffer);
        }
    }
  gtk_window_destroy (GTK_WINDOW (dlg));
}

/**
 * Function to show a dialog to save the JBWGraphic widget on a graphic file.
 */
void
jbw_graphic_dialog_save (void)
{
#if JBW_GRAPHIC_OUTPUT == JBW_GRAPHIC_OUTPUT_GDKPIXBUF
  const char *filter_name[JBW_GRAPHIC_N_TYPES] = {
    _("PNG file"),
    _("JPEG file"),
    _("XPM file"),
    _("TIFF file"),
    _("BMP file"),
    _("GIF file"),
    _("ICO file")
  };
  const char *pattern[JBW_GRAPHIC_N_PATTERNS][JBW_GRAPHIC_N_TYPES] = {
    {"png", "jpg", "xpm", "tif", "bmp", "gif", "ico"},
    {"PNG", "JPG", "XPM", "TIF", "BMP", "GIF", "ICO"},
    {NULL, "jpeg", NULL, "tiff", NULL, NULL, NULL},
    {NULL, "JPEG", NULL, "TIFF", NULL, NULL, NULL}
  };
#else
  const char *filter_name[JBW_GRAPHIC_N_TYPES] = { _("PNG file") };
  const char *pattern[JBW_GRAPHIC_N_PATTERNS][JBW_GRAPHIC_N_TYPES] = {
    {"png"}, {"PNG"}
  };
#endif
  GtkFileChooserDialog *dlg;
  GtkFileFilter *filter;
  GMainLoop *loop;
  unsigned int i, j;
  dlg =
    (GtkFileChooserDialog *)
    gtk_file_chooser_dialog_new (_("Save graph"),
                                 window_parent,
                                 GTK_FILE_CHOOSER_ACTION_SAVE,
                                 _("_OK"), GTK_RESPONSE_OK,
                                 _("_Cancel"), GTK_RESPONSE_CANCEL, NULL);
  for (i = 0; i < JBW_GRAPHIC_N_TYPES; ++i)
    {
      filter = gtk_file_filter_new ();
      gtk_file_filter_set_name (filter, filter_name[i]);
      for (j = 0; j < JBW_GRAPHIC_N_PATTERNS; ++j)
        if (pattern[j][i])
          gtk_file_filter_add_pattern (filter, pattern[j][i]);
      gtk_file_chooser_add_filter (GTK_FILE_CHOOSER (dlg), filter);
    }
  g_signal_connect (dlg, "response", G_CALLBACK (jbw_graphic_dialog_response),
                    NULL);
#if GTK_MAJOR_VERSION > 3
  gtk_window_present (GTK_WINDOW (dlg));
#else
  gtk_file_chooser_set_do_overwrite_confirmation (GTK_FILE_CHOOSER (dlg), 1);
  gtk_widget_show_all (GTK_WIDGET (dlg));
#endif
  loop = g_main_loop_new (NULL, 0);
  g_signal_connect_swapped (dlg, "destroy", G_CALLBACK (g_main_loop_quit),
                            loop);
  g_main_loop_run (loop);
  g_main_loop_unref (loop);
}

#if GTK_MAJOR_VERSION < 4
/**
 * Function to check the type of a column on a JBWArrayEditor widget.
 */
void
jbw_array_editor_check_column (JBWArrayEditor *editor,
                               ///< JBWArrayEditor widget.
                               int column,      ///< column number.
                               int type)        ///< column type.
{
  const char *error_msg;
  if (editor->type[column] != type)
    {
      switch (type)
        {
        case JBW_EDITOR_WIDGET_TYPE_TEXT:
          error_msg = _("no a text editor type");
          break;
        case JBW_EDITOR_WIDGET_TYPE_INT:
          error_msg = _("no an integer numbers editor type");
          break;
        case JBW_EDITOR_WIDGET_TYPE_FLOAT:
          error_msg = _("no a float numbers editor type");
          break;
        default:
          error_msg = _("no a date editor type");
        }
      jb_error_add (error_msg);
      jb_error_show ();
      jb_error_destroy ();
      exit (0);
    }
}

/**
 * Function to set the string of an element of a JBWArrayEditor widget.
 */
void
jbw_array_editor_set_element (JBWArrayEditor *editor,
                              ///< JBWArrayEditor widget.
                              int row,  ///< element row number.
                              int column,       ///< element column number.
                              const char *str)  ///< string.
{
  GtkWidget *element;
  jbw_array_editor_check_column (editor, column, JBW_EDITOR_WIDGET_TYPE_TEXT);
  element = editor->matrix_entry[column][row];
  gtk_entry_set_text (GTK_ENTRY (element), str);
}

/**
 * Function to get the string of an element of a JBWArrayEditor widget.
 *
 * \return string. It has to be freed with g_free.
 */
char *
jbw_array_editor_get_element (JBWArrayEditor *editor,
                              ///< JBWArrayEditor widget.
                              int row,  ///< element row number.
                              int column)       ///< element column number.
{
  GtkWidget *element;
  jbw_array_editor_check_column (editor, column, JBW_EDITOR_WIDGET_TYPE_TEXT);
  element = editor->matrix_entry[column][row];
  return g_strdup (gtk_entry_get_text (GTK_ENTRY (element)));
}

/**
 * Function to set an integer number in an element of a JBWArrayEditor widget.
 */
void
jbw_array_editor_set_element_int (JBWArrayEditor *editor,
                                  ///< JBWArrayEditor widget.
                                  int row,      ///< element row number.
                                  int column,   ///< element column number.
                                  long int x)   ///< integer number.
{
  GtkWidget *element;
  jbw_array_editor_check_column (editor, column, JBW_EDITOR_WIDGET_TYPE_INT);
  element = editor->matrix_entry[column][row];
  gtk_spin_button_set_value (GTK_SPIN_BUTTON (element), (gdouble) x);
}

/**
 * Function to get an integer number in an element of a JBWArrayEditor widget.
 *
 * \return integer number.
 */
long int
jbw_array_editor_get_element_int (JBWArrayEditor *editor,
                                  ///< JBWArrayEditor widget.
                                  int row,      ///< element row number.
                                  int column)   ///< element column number.
{
  GtkWidget *element;
  jbw_array_editor_check_column (editor, column, JBW_EDITOR_WIDGET_TYPE_INT);
  element = editor->matrix_entry[column][row];
  return (long int) gtk_spin_button_get_value (GTK_SPIN_BUTTON (element));
}

/**
 * Function to set a float number in an element of a JBWArrayEditor widget.
 */
void
jbw_array_editor_set_element_float (JBWArrayEditor *editor,
                                    ///< JBWArrayEditor widget.
                                    int row,    ///< element row number.
                                    int column, ///< element column number.
                                    JBDOUBLE x) ///< integer number.
{
  GtkWidget *element;
  jbw_array_editor_check_column (editor, column, JBW_EDITOR_WIDGET_TYPE_FLOAT);
  element = editor->matrix_entry[column][row];
  jbw_float_entry_set_value ((JBWFloatEntry *) element, x);
}

/**
 * Function to get a float number in an element of a JBWArrayEditor widget.
 *
 * \return float number.
 */
JBDOUBLE
jbw_array_editor_get_element_float (JBWArrayEditor *editor,
                                    ///< JBWArrayEditor widget.
                                    int row,    ///< element row number.
                                    int column) ///< element column number.
{
  GtkWidget *element;
  jbw_array_editor_check_column (editor, column, JBW_EDITOR_WIDGET_TYPE_FLOAT);
  element = editor->matrix_entry[column][row];
  return jbw_float_entry_get_value ((JBWFloatEntry *) element);
}

/**
 * Function to set a date in an element of a JBWArrayEditor widget.
 */
void
jbw_array_editor_set_element_time (JBWArrayEditor *editor,
                                   ///< JBWArrayEditor widget.
                                   int row,     ///< element row number.
                                   int column,  ///< element column number.
                                   JBDOUBLE t)  ///< date.
{
  GtkWidget *element;
  char *buffer;
  jbw_array_editor_check_column (editor, column, JBW_EDITOR_WIDGET_TYPE_TIME);
  element = editor->matrix_entry[column][row];
  buffer = jbm_set_time (t);
  gtk_entry_set_text (GTK_ENTRY (element), buffer);
  g_free (buffer);
}

/**
 * Function to get a date in an element of a JBWArrayEditor widget.
 *
 * \return date.
 */
JBDOUBLE
jbw_array_editor_get_element_time (JBWArrayEditor *editor,
                                   ///< JBWArrayEditor widget.
                                   int row,     ///< element row number.
                                   int column)  ///< element column number.
{
  GtkWidget *element;
  JBDOUBLE t;
  int e;
  jbw_array_editor_check_column (editor, column, JBW_EDITOR_WIDGET_TYPE_TIME);
  element = editor->matrix_entry[column][row];
  t = jbm_get_time (gtk_entry_get_text (GTK_ENTRY (element)), &e);
  if (!e)
    t = 0.L;
  return t;
}

/**
 * Function to set the strings of a column in a JBWArrayEditor widget.
 */
void
jbw_array_editor_set_column (JBWArrayEditor *editor,
                             ///< JBWArrayEditor widget.
                             int column,        ///< column number.
                             char **c)  ///< array of strings.
{
  int i, j;
  j = editor->nrows;
  if (column >= editor->nfull)
    --j;
  for (i = 0; i < j; ++i)
    jbw_array_editor_set_element (editor, i, column, c[i]);
}

/**
 * Function to get the strings of a column in a JBWArrayEditor widget.
 */
void
jbw_array_editor_get_column (JBWArrayEditor *editor,
                             ///< JBWArrayEditor widget.
                             int column,        ///< column number.
                             char **c)  ///< array of strings.
{
  int i, j;
  j = editor->nrows;
  if (column >= editor->nfull)
    --j;
  for (i = 0; i < j; ++i)
    c[i] = jbw_array_editor_get_element (editor, i, column);
}

/**
 * Function to set the integer numbers of a column in a JBWArrayEditor widget.
 */
void
jbw_array_editor_set_column_int (JBWArrayEditor *editor,
                                 ///< JBWArrayEditor widget.
                                 int column,    ///< column number.
                                 long int *x)   ///< array of integer numbers.
{
  int i, j;
  j = editor->nrows;
  if (column >= editor->nfull)
    --j;
  for (i = 0; i < j; ++i)
    jbw_array_editor_set_element_int (editor, i, column, x[i]);
}

/**
 * Function to get the integer numbers of a column in a JBWArrayEditor widget.
 */
void
jbw_array_editor_get_column_int (JBWArrayEditor *editor,
                                 ///< JBWArrayEditor widget.
                                 int column,    ///< column number.
                                 long int *x)   ///< array of integer numbers.
{
  int i, j;
  j = editor->nrows;
  if (column >= editor->nfull)
    --j;
  for (i = 0; i < j; ++i)
    x[i] = jbw_array_editor_get_element_int (editor, i, column);
}

/**
 * Function to set the float numbers of a column in a JBWArrayEditor widget
 * (JBFLOAT).
 */
void
jbw_array_editor_set_column_float (JBWArrayEditor *editor,
                                   ///< JBWArrayEditor widget.
                                   int column,  ///< column number.
                                   JBFLOAT *x)  ///< array of float numbers.
{
  int i, j;
  j = editor->nrows;
  if (column >= editor->nfull)
    --j;
  for (i = 0; i < j; ++i)
    jbw_array_editor_set_element_float (editor, i, column, (JBDOUBLE) x[i]);
}

/**
 * Function to set the float numbers of a column in a JBWArrayEditor widget
 * (JBDOUBLE).
 */
void
jbw_array_editor_set_column_floatl (JBWArrayEditor *editor,
                                    ///< JBWArrayEditor widget.
                                    int column, ///< column number.
                                    JBDOUBLE *x)
                                    ///< array of float numbers.
{
  int i, j;
  j = editor->nrows;
  if (column >= editor->nfull)
    --j;
  for (i = 0; i < j; ++i)
    jbw_array_editor_set_element_float (editor, i, column, x[i]);
}

/**
 * Function to get the float numbers of a column in a JBWArrayEditor widget
 * (JBFLOAT).
 */
void
jbw_array_editor_get_column_float (JBWArrayEditor *editor,
                                   ///< JBWArrayEditor widget.
                                   int column,  ///< column number.
                                   JBFLOAT *x)  ///< array of float numbers.
{
  int i, j;
  j = editor->nrows;
  if (column >= editor->nfull)
    --j;
  for (i = 0; i < j; ++i)
    x[i] = (JBFLOAT) jbw_array_editor_get_element_float (editor, i, column);
}

/**
 * Function to get the float numbers of a column in a JBWArrayEditor widget
 * (JBDOUBLE).
 */
void
jbw_array_editor_get_column_floatl (JBWArrayEditor *editor,
                                    ///< JBWArrayEditor widget.
                                    int column, ///< column number.
                                    JBDOUBLE *x)        ///< array of float numbers.
{
  int i, j;
  j = editor->nrows;
  if (column >= editor->nfull)
    --j;
  for (i = 0; i < j; ++i)
    x[i] = jbw_array_editor_get_element_float (editor, i, column);
}

/**
 * Function to set the dates of a column in a JBWArrayEditor widget.
 */
void
jbw_array_editor_set_column_time (JBWArrayEditor *editor,
                                  ///< JBWArrayEditor widget.
                                  int column,   ///< column number.
                                  JBDOUBLE *t)  ///< array of dates.
{
  int i, j;
  j = editor->nrows;
  if (column >= editor->nfull)
    --j;
  for (i = 0; i < j; ++i)
    jbw_array_editor_set_element_time (editor, i, column, t[i]);
}

/**
 * Function to get the dates of a column in a JBWArrayEditor widget.
 */
void
jbw_array_editor_get_column_time (JBWArrayEditor *editor,
                                  ///< JBWArrayEditor widget.
                                  int column,   ///< column number.
                                  JBDOUBLE *t)  ///< array of dates.
{
  int i, j;
  j = editor->nrows;
  if (column >= editor->nfull)
    --j;
  for (i = 0; i < j; ++i)
    t[i] = jbw_array_editor_get_element_time (editor, i, column);
}

/**
 * Function to do a column keyboard sensitive/insensitive in a JBWGraphic
 * widget.
 */
void
jbw_array_editor_set_column_sensitive (JBWArrayEditor *editor,
                                       ///< JBWArrayEditor widget.
                                       int column,      ///< column number.
                                       int sensitive)
                                       ///< 1 on sensitive, 0 otherwise.
{
  GtkWidget **array;
  int i, j;
  array = editor->matrix_entry[column];
  j = editor->nrows;
  if (column >= editor->nfull)
    --j;
  for (i = 0; i < j; ++i)
    gtk_widget_set_sensitive (array[i], sensitive);
}

/**
 * Function to show a column in a JBWArrayEditor widget.
 */
void
jbw_array_editor_show_column (JBWArrayEditor *editor,
                              ///< JBWArrayEditor widget.
                              int column)       ///< column number.
{
  GtkWidget **array;
  int i, j;
  gtk_widget_show (GTK_WIDGET (editor->button_title[column]));
  array = editor->matrix_entry[column];
  j = editor->nrows;
  if (column >= editor->nfull)
    --j;
  for (i = 0; i < j; ++i)
    gtk_widget_show (array[i]);
}

/**
 * Function to hide a column in a JBWArrayEditor widget.
 */
void
jbw_array_editor_hide_column (JBWArrayEditor *editor,
                              ///< JBWArrayEditor widget.
                              int column)       ///< column number.
{
  GtkWidget **array;
  int i, j;
  gtk_widget_hide (GTK_WIDGET (editor->button_title[column]));
  array = editor->matrix_entry[column];
  j = editor->nrows;
  if (column >= editor->nfull)
    --j;
  for (i = 0; i < j; ++i)
    gtk_widget_hide (array[i]);
}

/**
 * Function to insert a row position GtkButton at the end of a JBWArrayEditor
 * widget.
 */
static void
jbw_array_editor_insert_button_end (JBWArrayEditor *editor,
                                    ///< JBWArrayEditor widget.
                                    int row)    ///< last row number.
{
  char buffer[32];
  int k;
  k = row + 1;
  sprintf (buffer, "%d", k);
  editor->button_numeric =
    (GtkButton **) jb_realloc (editor->button_numeric,
                               k * sizeof (GtkButton *));
  editor->button_numeric[row] =
    (GtkButton *) gtk_button_new_with_label (buffer);
  gtk_widget_set_sensitive (GTK_WIDGET (editor->button_numeric[row]), 0);
  k = row + row;
  gtk_grid_attach (editor->grid, GTK_WIDGET (editor->button_numeric[row]),
                   0, k + 1, 1, 2);
}

/**
 * Function to insert an entry widget at the end of a column in a JBWArrayEditor
 * widget.
 */
static void
jbw_array_editor_insert_entry_end (JBWArrayEditor *editor,
                                   ///< JBWArrayEditor widget.
                                   int column,  ///< column number.
                                   int row,     ///< last row number.
                                   int position)        ///< vertical position.
{
  GtkWidget *widget;
  editor->matrix_entry[row] = (GtkWidget **)
    jb_realloc (editor->matrix_entry[column], (row + 1) * sizeof (GtkWidget *));
  switch (editor->type[column])
    {
    case JBW_EDITOR_WIDGET_TYPE_TEXT:
    case JBW_EDITOR_WIDGET_TYPE_TIME:
      widget = gtk_entry_new ();
      break;
    case JBW_EDITOR_WIDGET_TYPE_INT:
      widget = gtk_spin_button_new_with_range (-INFINITY, INFINITY, 1.);
      gtk_spin_button_set_digits (GTK_SPIN_BUTTON (widget), 0);
      break;
    default:
      widget
        = gtk_spin_button_new_with_range (-INFINITY, INFINITY, JBM_EPSILONL);
    }
  gtk_entry_set_text (GTK_ENTRY (widget), "0");
  gtk_grid_attach (editor->grid, widget, row + 1, position, 1, 2);
  editor->matrix_entry[row][position] = widget;
}

/**
 * Function to insert the last row of a JBWArrayEditor widget.
 */
static void
jbw_array_editor_insert_last (JBWArrayEditor *editor)
{
  int i, j, k;
  j = editor->nrows++;
  jbw_array_editor_insert_button_end (editor, j);
  k = j + j;
  for (i = 0; i < editor->nfull; ++i)
    jbw_array_editor_insert_entry_end (editor, i, j, k + 1);
  if (j > 0)
    for (; i < editor->ncolumns; ++i)
      jbw_array_editor_insert_entry_end (editor, i, j - 1, k);
#if GTK_MAJOR_VERSION > 3
  gtk_widget_show (GTK_WIDGET (editor->grid));
#else
  gtk_widget_show_all (GTK_WIDGET (editor->grid));
#endif
}

/**
 * Function to up the information on a column of a JBWArrayEditor widget.
 */
static void
jbw_array_editor_up_rows (JBWArrayEditor *editor,
                          ///< JBWArrayEditor widget.
                          int column,   ///< column number.
                          int row,      ///< initial row to down.
                          int n)        ///< total number of rows.
{
  GtkWidget **entry1, **entry2;
  entry1 = editor->matrix_entry[column] + (--n);
  for (; --n >= row;)
    {
      entry2 = entry1--;
      gtk_entry_set_text (GTK_ENTRY (*entry2),
                          gtk_entry_get_text (GTK_ENTRY (*entry1)));
    }
  gtk_entry_set_text (GTK_ENTRY (*entry1), "0");
}

/**
 * Function to insert a row in a JBWArrayEditor widget.
 */
void
jbw_array_editor_insert_row (JBWArrayEditor *editor,
                             ///< JBWArrayEditor widget.
                             int row)   ///< row number.
{
  int i;
  jbw_array_editor_insert_last (editor);
  for (i = 0; i < editor->nfull; ++i)
    jbw_array_editor_up_rows (editor, i, row, editor->nrows);
  for (; i < editor->ncolumns; ++i)
    jbw_array_editor_up_rows (editor, i, row, editor->nrows - 1);
}

/**
 * Function to remove an entry widget at the end of a column in a JBWArrayEditor
 * widget.
 */
static void
jbw_array_editor_remove_entry_end (JBWArrayEditor *editor,
                                   ///< JBWArrayEditor widget.
                                   int column,  ///< column number.
                                   int row)     ///< last row number.
{
#if GTK_MAJOR_VERSION > 3
  gtk_grid_remove (editor->grid, editor->matrix_entry[column][row]);
#else
  gtk_widget_destroy (editor->matrix_entry[column][row]);
#endif
  editor->matrix_entry[column] =
    (GtkWidget **) jb_realloc (editor->matrix_entry[column],
                               row * sizeof (GtkWidget *));
}

/**
 * Function to remove the last row in a JBWArrayEditor widget.
 */
static void
jbw_array_editor_remove_last (JBWArrayEditor *editor)
                                    ///< JBWArrayEditor widget.
{
  int i, j;
  if (editor->nrows <= 0)
    return;
  j = --editor->nrows;
#if GTK_MAJOR_VERSION > 3
  gtk_grid_remove (editor->grid, GTK_WIDGET (editor->button_numeric[j]));
#else
  gtk_widget_destroy (GTK_WIDGET (editor->button_numeric[j]));
#endif
  for (i = 0; i < editor->nfull; ++i)
    jbw_array_editor_remove_entry_end (editor, i, j);
  if (--j >= 0)
    for (; i < editor->ncolumns; ++i)
      jbw_array_editor_remove_entry_end (editor, i, j);
}

/**
 * Function to down the information on a column of a JBWArrayEditor widget.
 */
static void
jbw_array_editor_down_rows (JBWArrayEditor *editor,
                            ///< JBWArrayEditor widget.
                            int column, ///< column number.
                            int row,    ///< initial row to down.
                            int n)      ///< total number of rows.
{
  GtkWidget **entry1, **entry2;
  entry1 = editor->matrix_entry[column] + row;
  for (; ++row < n;)
    {
      entry2 = entry1++;
      gtk_entry_set_text (GTK_ENTRY (*entry2),
                          gtk_entry_get_text (GTK_ENTRY (*entry1)));
    }
}

/**
 * Function to remove a row in a JBWArrayEditor widget.
 */
void
jbw_array_editor_remove_row (JBWArrayEditor *editor,
                             ///< JBWArrayEditor widget.
                             int row)   ///< row number.
{
  int i;
  for (i = 0; i < editor->nfull; ++i)
    jbw_array_editor_down_rows (editor, i, row, editor->nrows);
  for (; i < editor->ncolumns; ++i)
    jbw_array_editor_down_rows (editor, i, row, editor->nrows - 1);
  jbw_array_editor_remove_last (editor);
}

/**
 * Function to set the number of rows in a JBWArrayEditor widget.
 */
void
jbw_array_editor_set_rows (JBWArrayEditor *editor,
                           ///< JBWArrayEditor widget.
                           int n)       ///< number of rows.
{
  int i;
  for (i = editor->nrows; i > n; --i)
    jbw_array_editor_remove_last (editor);
  for (; i < n; ++i)
    jbw_array_editor_insert_last (editor);
#if GTK_MAJOR_VERSION > 3
  gtk_widget_show (GTK_WIDGET (editor->grid));
#else
  gtk_widget_show_all (GTK_WIDGET (editor->grid));
#endif
}

/**
 * Function to set the title of a column in a JBWArrayEditor widget.
 */
void
jbw_array_editor_set_title (JBWArrayEditor *editor,
                            ///< JBWArrayEditor widget.
                            int column, ///< column number.
                            char *title)        ///< column title string.
{
  gtk_button_set_label (editor->button_title[column], title);
}

/**
 * Function to close and free the memory used by a JBWArrayEditor widget.
 */
void
jbw_array_editor_destroy (JBWArrayEditor *editor)
                                ///< JBWArrayEditor widget.
{
  int i;
  for (i = editor->ncolumns; --i >= 0;)
    jb_free_null ((void **) &editor->matrix_entry[i]);
  jb_free_null ((void **) &editor->button_numeric);
  g_free (editor->button_title);
  g_free (editor->matrix_entry);
  g_free (editor);
}

/**
 * Function to create a new JBWArrayEditor widget.
 */
JBWArrayEditor *
jbw_array_editor_new (int ncolumns,     ///< number of columns.
                      int nfull,        ///< number of full columns.
                      int nrows,        ///< initial number of rows.
                      const int *type,  ///< array of entry types.
                      const char **label)       ///< array of labels.
{
  JBWArrayEditor *editor;
  const char *error_msg;
  int i;
  for (i = 0; i < ncolumns; ++i)
    if (type[i] < JBW_EDITOR_WIDGET_TYPE_TEXT
        || type[i] > JBW_EDITOR_WIDGET_TYPE_TIME)
      {
        error_msg = _("bad array editor widget type");
        goto error1;
      }
  editor = g_try_malloc (sizeof (JBWArrayEditor));
  if (!editor)
    {
      error_msg = _("not enough memory to open the array editor");
      goto error1;
    }
#if GTK_MAJOR_VERSION > 3
  editor->scrolled = (GtkScrolledWindow *) gtk_scrolled_window_new ();
#else
  editor->scrolled = (GtkScrolledWindow *) gtk_scrolled_window_new (0, 0);
#endif
  gtk_widget_set_hexpand (GTK_WIDGET (editor->scrolled), TRUE);
  gtk_widget_set_vexpand (GTK_WIDGET (editor->scrolled), TRUE);
  editor->grid = (GtkGrid *) gtk_grid_new ();
  editor->matrix_entry =
    (GtkWidget ***) g_malloc (ncolumns * sizeof (GtkWidget **));
  editor->button_title =
    (GtkButton **) g_malloc (ncolumns * sizeof (GtkButton *));
  for (i = 0; i < ncolumns; ++i)
    {
      editor->matrix_entry[i] = NULL;
      editor->button_title[i]
        = (GtkButton *) gtk_button_new_with_label (label[i]);
      gtk_widget_set_sensitive (GTK_WIDGET (editor->button_title[i]), 0);
      gtk_grid_attach (editor->grid,
                       GTK_WIDGET (editor->button_title[i]), i + 1, 0, 1, 1);
    }
  editor->button_numeric = NULL;
  editor->ncolumns = ncolumns;
  editor->nfull = nfull;
  editor->nrows = 0;
  editor->type = (int *) g_try_malloc (ncolumns * sizeof (int));
  memcpy (editor->type, type, ncolumns * sizeof (int));
  jbw_array_editor_set_rows (editor, nrows);
  gtk_scrolled_window_set_child (editor->scrolled, GTK_WIDGET (editor->grid));
  gtk_scrolled_window_set_policy (editor->scrolled,
                                  GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
  return editor;

error1:
  jb_error_add (error_msg, NULL);
  jb_error_show ();
  jb_error_destroy ();
  return NULL;
}
#endif

#if GTK_MAJOR_VERSION > 3

/**
 * function to set a text on a GtkEntry struct as in GTK3.
 */
void
gtk_entry_set_text (GtkEntry *entry,    ///< GtkEntry struct.
                    const char *text)   ///< text.
{
  GtkEntryBuffer *buffer;
  buffer = gtk_entry_get_buffer (entry);
  gtk_entry_buffer_set_text (buffer, text, -1);
}

/**
 * function to get the text of a GtkEntry widget as in GTK3.
 *
 * \return text.
 */
const char *
gtk_entry_get_text (GtkEntry *entry)    ///< GtkEntry struct.
{
  GtkEntryBuffer *buffer;
  buffer = gtk_entry_get_buffer (entry);
  return gtk_entry_buffer_get_text (buffer);
}

#endif

#endif
