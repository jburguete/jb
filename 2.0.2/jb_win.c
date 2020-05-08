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
 * \file jb_win.c
 * \brief Source file with useful display functions.
 * \author Javier Burguete Tolosa.
 * \copyright Copyright 2005-2020, Javier Burguete Tolosa.
 */
#include "jb_win.h"

#if JBW == JBW_GTK

GtkWindow *window_parent;       ///< pointer to the parent GtkWindow struct.

const GLfloat jbw_black[4] = { 0.f, 0.f, 0.f, 1.f };

///< black color intensities array.
const GLfloat jbw_darkred[4] = { 0.5f, 0.f, 0.f, 1.f };

///< dark red color intensities array.
const GLfloat jbw_darkgreen[4] = { 0.f, 0.5f, 0.f, 1.f };

///< dark green color intensities array.
const GLfloat jbw_darkblue[4] = { 0.f, 0.f, 0.5f, 1.f };

///< dark blue color intensities array.
const GLfloat jbw_red[4] = { 1.f, 0.f, 0.f, 1.f };

///< red color intensities array.
const GLfloat jbw_brown[4] = { 0.5f, 0.5f, 0.f, 1.f };

///< brown color intensities array.
const GLfloat jbw_green[4] = { 0.f, 1.f, 0.f, 1.f };

///< green color intensities array.
const GLfloat jbw_greenblue[4] = { 0.f, 1.f, 0.f, 1.f };

///< green-blue color intensities array.
const GLfloat jbw_blue[4] = { 0.f, 0.f, 1.f, 1.f };

///< blue color intensities array.
const GLfloat jbw_violet[4] = { 0.5f, 0.f, 0.5f, 1.f };

///< violet color intensities array.
const GLfloat jbw_yellow[4] = { 1.f, 1.f, 0.f, 1.f };

///< yellow color intensities array.
const GLfloat jbw_pink[4] = { 1.f, 0.f, 1.f, 1.f };

///< pink color intensities array.
const GLfloat jbw_lightblue[4] = { 0.f, 1.f, 1.f, 1.f };

///< light blue color intensities array.
const GLfloat jbw_starred[4] = { 1.f, 0.85f, 0.85f, 1.f };

///< very light red
const GLfloat jbw_stargreen[4] = { 0.85f, 1.f, 0.85f, 1.f };

///< very light green
const GLfloat jbw_starblue[4] = { 0.85f, 0.85f, 1.f, 1.f };

///< very light blue
const GLfloat jbw_stargray[4] = { 0.9f, 0.9f, 0.9f, 1.f };

///< very light gray
const GLfloat jbw_white[4] = { 1.f, 1.f, 1.f, 1.f };

///< white color intensities array.

const GLfloat jbw_identity[16] = {
  1.f, 0.f, 0.f, 0.f,
  0.f, 1.f, 0.f, 0.f,
  0.f, 0.f, 1.f, 0.f,
  0.f, 0.f, 0.f, 1.f
};                              ///< identity matrix.

/**
 * Function to init locales in the JB library with GTK interface.
 */
void
jbw_init (int *argn,
          ///< pointer to the number of command line arguments.
          char ***argc)         ///< pointer to the command line arguments.
{
  jb_init ();
  gtk_disable_setlocale ();
  gtk_init (argn, argc);
}

/**
 * Function to display a message.
 */
void
jbw_show_message (const char *title,    ///< message title.
                  const char *message,  ///< message.
                  GtkMessageType type)  ///< message type.
{
  GtkMessageDialog *dlg;
  dlg = (GtkMessageDialog *) gtk_message_dialog_new
    (window_parent, GTK_DIALOG_MODAL, type, GTK_BUTTONS_OK, "%s", message);
  gtk_window_set_title (GTK_WINDOW (dlg), title);
  gtk_dialog_run (GTK_DIALOG (dlg));
  gtk_widget_destroy (GTK_WIDGET (dlg));
}

/**
 * Function to display an error message.
 */
void
jbw_show_error (const char *message)    ///< error message.
{
  jbw_show_message (_("Error!"), message, GTK_MESSAGE_ERROR);
}

/**
 * Function to display two error messages.
 */
void
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
void
jbw_show_error3 (const char *message1,  ///< 1st error message.
                 const char *message2,  ///< 2nd error message.
                 const char *message3)  ///< 3rd error message.
{
  char buffer[1024];
  snprintf (buffer, 1024, "%s: %s\n%s", message1, message2, message3);
  jbw_show_error (buffer);
}

/**
 * Function to display a warning message.
 */
void
jbw_show_warning (const char *message)  ///< warning message.
{
  jbw_show_message (_("Warning!"), message, GTK_MESSAGE_WARNING);
}

/**
 * Function to set the strings of a GtkComboBoxText from an array of strings.
 */
void
jbw_combo_box_set_strings (GtkComboBoxText * combo,
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
 * Function to set active a GtkRadioButton of an array.
 */
void
jbw_array_radio_buttons_set_active (GtkRadioButton ** array,
///< array of GtkRadioButton structs.
                                    int n,
///< number of the GtkRadioButton struct to set active.
                                    int is_active)
///< 1 on active, 0 on deactive.
{
  gtk_toggle_button_set_active ((GtkToggleButton *) array[n], is_active);
}

/**
 * Function to get the active GtkRadioButton of an array.
 *
 * \return element number of the active GtkRadioButton struct.
 */
int
jbw_array_radio_buttons_get_active (GtkRadioButton ** array)
///< array of GtkRadioButton structs.
{
  int i = 0;
  while (!gtk_toggle_button_get_active ((GtkToggleButton *) array[i]))
    ++i;
  return i;
}

/**
 * Function to set a JBWFloatEntry struct with a formated floating point value.
 */
void
jbw_float_entry_set_value_with_format (JBWFloatEntry * entry,
///< JBWFloatEntry struct.
                                       char *format,    ///< c-format string.
                                       JBDOUBLE value)
///< floating point value.
{
  char buffer[64];
  snprintf (buffer, 64, format, value);
  gtk_entry_set_text (GTK_ENTRY (entry), buffer);
}

#if HIGH_PRECISION > 2

/**
 * Function to set a JBWFloatEntry struct with a floating point value.
 */
void
jbw_float_entry_set_value (JBWFloatEntry * entry,
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
jbw_float_entry_get_value (JBWFloatEntry * entry)
///< JBWFloatEntry struct.
{
  JBDOUBLE value;
  sscanf (gtk_entry_get_text ((GtkEntry *) entry), FRL, &value);
  return value;
}

#endif

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
jbw_draw_range (JBFLOAT * xmin, ///< minimum graphical value.
                JBFLOAT * xmax) ///< maximum graphical value.
{
  register JBFLOAT m;
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
jbw_draw_rangel (JBDOUBLE * xmin,       ///< minimum graphical value.
                 JBDOUBLE * xmax)       ///< maximum graphical value.
{
  register JBDOUBLE m;
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
               JBFLOAT * tic)   ///< array of tic values.
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
                JBDOUBLE * tic) ///< array of tic values.
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
jbw_image_error (const char *msg)
{
  jbw_show_error2 ("JBWImage", msg);
}

/**
 * Function to free the memory used by a JBWImage widget.
 */
static void
jbw_image_delete (JBWImage * image)     ///< JBWImage widget.
{
  glDeleteProgram (image->program_texture);
  g_free (image->image);
  g_free (image);
}

/**
 * Function to init the OpenGL functions on a JBWImage widget.
 */
void
jbw_image_init (JBWImage * image)
{
  const char *vs_texture_source =
    "attribute vec2 position;"
    "attribute vec2 texture_position;"
    "varying vec2 t_position;"
    "uniform mat4 matrix;"
    "void main()"
    "{"
    "gl_Position=matrix*vec4 (position, 0.f, 1.f);"
    "t_position=texture_position;" "}";
  const char *fs_texture_source =
    "varying vec2 t_position;"
    "uniform sampler2D texture_image;"
    "void main()" "{" "gl_FragColor=texture2D(texture_image,t_position);" "}";
  const char *vertex_name = "position";
  const char *texture_name = "texture_image";
  const char *texture_position_name = "texture_position";
  const char *matrix_name = "matrix";
  const char *gl_version = "#version 120\n";    // OpenGL 2.1
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
  const char *error_msg;
  GLint error_code;
  GLuint vs, fs;

  // setting up matrices and vertices
  memcpy (image->matrix, matrix, 16 * sizeof (GLfloat));
  memcpy (image->vertices, vertices, 8 * sizeof (GLfloat));
  memcpy (image->square_texture, square_texture, 8 * sizeof (GLfloat));
  memcpy (image->elements, elements, 6 * sizeof (GLushort));

  // compiling vertex shader
  vs = glCreateShader (GL_VERTEX_SHADER);
  glShaderSource (vs, 2, vs_texture_sources, NULL);
  glCompileShader (vs);
  glGetShaderiv (vs, GL_COMPILE_STATUS, &error_code);
  if (!error_code)
    {
      error_msg = _("unable to compile the texture vertex shader");
      goto end;
    }

  // compiling texture fragment shader
  fs = glCreateShader (GL_FRAGMENT_SHADER);
  glShaderSource (fs, 2, fs_texture_sources, NULL);
  glCompileShader (fs);
  glGetShaderiv (fs, GL_COMPILE_STATUS, &error_code);
  if (!error_code)
    {
      glDeleteShader (vs);
      error_msg = _("unable to compile the texture fragment shader");
      goto end;
    }

  // linking texture program
  image->program_texture = glCreateProgram ();
  glAttachShader (image->program_texture, vs);
  glAttachShader (image->program_texture, fs);
  glLinkProgram (image->program_texture);
  glDeleteShader (fs);
  glDeleteShader (vs);
  glGetProgramiv (image->program_texture, GL_LINK_STATUS, &error_code);
  if (!error_code)
    {
      error_msg = _("unable to link the texture program");
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
      error_msg = _("could not bind texture attribute");
      goto end;
    }
  image->attribute_texture_position
    = glGetAttribLocation (image->program_texture, texture_position_name);
  if (image->attribute_texture_position == -1)
    {
      error_msg = _("could not bind texture position attribute");
      goto end;
    }
  image->uniform_texture
    = glGetUniformLocation (image->program_texture, texture_name);
  if (image->uniform_texture == -1)
    {
      error_msg = _("could not bind texture uniform");
      goto end;
    }
  image->uniform_matrix
    = glGetUniformLocation (image->program_texture, matrix_name);
  if (image->uniform_matrix == -1)
    {
      error_msg = _("could not bind matrix uniform");
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
  if (error_msg)
    {
      jbw_show_error2 ("JBWImage", error_msg);
      exit (0);
    }
}

/**
 * Function to create a new JBWImage widget from a PNG file.
 */
JBWImage *
jbw_image_new (char *name)      ///< PNG file name.
{
  JBWImage *image = NULL;
  png_struct *png;
  png_info *info;
  png_byte **row_pointers;
  FILE *file;
  const char *error_msg;
  unsigned int i, row_bytes;

  // starting png structs
  png = png_create_read_struct (PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
  info = png_create_info_struct (png);

  // opening file
  file = fopen (name, "rb");
  if (!file)
    {
      error_msg = _("unable to open the file");
      goto error1;
    }

  // reading file and transforming to 8 bits RGBA format
  if (setjmp (png_jmpbuf (png)))
    {
      error_msg = _("unable to open the PNG file");
      goto error2;
    }
  png_init_io (png, file);
  if (setjmp (png_jmpbuf (png)))
    {
      error_msg = _("unable to open the PNG file");
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
      error_msg = _("not enough memory to open the widget");
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
      error_msg = _("not enough memory to open the image");
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
    jbw_image_error (error_msg);

  return image;
}

/**
 * Function to draw a JBWImage widget.
 */
void
jbw_image_draw (JBWImage * image,       ///< JBWImage struct.
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

/**
 * Function to free the memory used by a JBWGraphic widget.
 */
static void
jbw_graphic_delete (JBWGraphic * graphic)       ///< JBWGraphic widget.
{
  if (graphic->face)
    {
      FT_Done_Face (*graphic->face);
      g_free (graphic->face);
    }
  if (graphic->ft)
    {
      FT_Done_Library (*graphic->ft);
      g_free (graphic->ft);
    }
  if (graphic->program_text)
    glDeleteProgram (graphic->program_text);
  if (graphic->program_3D)
    glDeleteProgram (graphic->program_3D);
  if (graphic->program_2D)
    glDeleteProgram (graphic->program_2D);
  if (graphic->logo)
    jbw_image_delete (graphic->logo);
  g_free (graphic);
}

/**
 * Function to close and free the memory used by a JBWGraphic widget.
 */
void
jbw_graphic_destroy (JBWGraphic * graphic)      ///< JBWGraphic widget.
{
  if (graphic->window)
    gtk_widget_destroy (GTK_WIDGET (graphic->window));
  else
    gtk_widget_destroy (GTK_WIDGET (graphic->widget));
}

/**
 * Function to init the OpenGL functions on a JBWGraphic widget.
 */
void
jbw_graphic_init (JBWGraphic * graphic) ///< JBWGraphic widget.
{
  const char *gl_version = "#version 120\n";
  const char *fs_source =
    "varying vec3 fcolor;"
    "void main()" "{" "gl_FragColor=vec4(fcolor,1.f);" "}";
  const char *vs_2D_source =
    "attribute vec2 position;"
    "uniform vec3 color;"
    "uniform mat4 matrix;"
    "varying vec3 fcolor;"
    "void main()"
    "{" "gl_Position=matrix*vec4(position,0.f,1.f);" "fcolor=color;" "}";
  const char *vs_3D_source =
    "attribute vec3 position;"
    "uniform vec3 color;"
    "uniform mat4 matrix;"
    "varying vec3 fcolor;"
    "void main()"
    "{" "gl_Position=matrix*vec4(position,1.f);" "fcolor=color;" "}";
  const char *vs_2Dc_source =
    "attribute vec2 position;"
    "attribute vec3 color;"
    "uniform mat4 matrix;"
    "varying vec3 fcolor;"
    "void main()"
    "{" "gl_Position=matrix*vec4(position,0.f,1.f);" "fcolor=color;" "}";
  const char *vs_3Dc_source =
    "attribute vec3 position;"
    "attribute vec3 color;"
    "uniform mat4 matrix;"
    "varying vec3 fcolor;"
    "void main()"
    "{" "gl_Position=matrix*vec4(position,1.f);" "fcolor=color;" "}";
  const char *vs_text_source =
    "attribute vec4 position;"
    "varying vec2 textcoord;"
    "void main()"
    "{" "gl_Position=vec4(position.xy,0.f,1.f);" "textcoord=position.zw;" "}";
  const char *fs_text_source =
    "varying vec2 textcoord;"
    "uniform sampler2D text;"
    "uniform vec4 color;"
    "void main()"
    "{" "gl_FragColor=vec4(1.f,1.f,1.f,texture2D(text,textcoord).a)*color;" "}";
  const char *position_name = "position";
  const char *color_name = "color";
  const char *matrix_name = "matrix";
  const char *text_name = "text";
  const char *fs_sources[2] = { gl_version, fs_source };
  const char *vs_2D_sources[2] = { gl_version, vs_2D_source };
  const char *vs_3D_sources[2] = { gl_version, vs_3D_source };
  const char *vs_2Dc_sources[2] = { gl_version, vs_2Dc_source };
  const char *vs_3Dc_sources[2] = { gl_version, vs_3Dc_source };
  const char *fs_text_sources[2] = { gl_version, fs_text_source };
  const char *vs_text_sources[2] = { gl_version, vs_text_source };
  const char *error_msg;
  GLint error_code;
  GLuint fs, vs;
  GLenum glew_status;

  // Selecting current OpenGL area
  gtk_gl_area_make_current (graphic->widget);

  // Initing GLEW library
  glew_status = glewInit ();
  if (glew_status != GLEW_OK)
    {
      error_msg = (const char *) glewGetErrorString (glew_status);
      goto end;
    }

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
  glAttachShader (graphic->program_2D, vs);
  glAttachShader (graphic->program_2D, fs);
  glLinkProgram (graphic->program_2D);
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
  glAttachShader (graphic->program_3D, vs);
  glAttachShader (graphic->program_3D, fs);
  glLinkProgram (graphic->program_3D);
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
  glAttachShader (graphic->program_2Dc, vs);
  glAttachShader (graphic->program_2Dc, fs);
  glLinkProgram (graphic->program_2Dc);
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
  glAttachShader (graphic->program_3Dc, vs);
  glAttachShader (graphic->program_3Dc, fs);
  glLinkProgram (graphic->program_3Dc);
  glDeleteShader (vs);
  glDeleteShader (fs);
  glGetProgramiv (graphic->program_3D, GL_LINK_STATUS, &error_code);
  if (!error_code)
    {
      graphic->program_3Dc = 0;
      error_msg = _("unable to link the 3D with color program");
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

  // Linking the text program
  graphic->program_text = glCreateProgram ();
  glAttachShader (graphic->program_text, vs);
  glAttachShader (graphic->program_text, fs);
  glLinkProgram (graphic->program_text);
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
    jbw_image_init (graphic->logo);

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
  if (!graphic->ft)
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
  gtk_widget_set_size_request (GTK_WIDGET (graphic->widget),
                               ((1 + graphic->nxmax) * JBW_GRAPHIC_N_CHARS + 1)
                               * graphic->char_width,
                               (5 + graphic->nymax) * graphic->char_height);
  g_signal_connect_swapped (graphic->widget, "delete-event",
                            (GCallback) jbw_graphic_delete, graphic);

  // ending on success
  return;

  // ending on error
end:
  if (error_msg)
    {
      jbw_show_error2 ("JBWGraphic", error_msg);
      exit (0);
    }
}

/**
 * Function to resize a JBWGraphic widget.
 */
void
jbw_graphic_resize (JBWGraphic * graphic,       ///< JBWGraphic widget.
                    int width,  ///< new screen width.
                    int height) ///< new screen height.
{
  graphic->width = width;
  graphic->height = height;
  glViewport (0, 0, width, height);
}

/**
 * Function to render a JBWGraphic widget.
 */
void
jbw_graphic_render (JBWGraphic * graphic)       ///< JBWGraphic widget.
{
  graphic->draw (graphic);
}

/**
 * Function to create a new JBWGraphic widget.
 */
JBWGraphic *
jbw_graphic_new (unsigned int nx,       ///< maximum number of x-tics.
                 unsigned int ny,       ///< maximum number of x-tics.
                 unsigned int nz,       ///< maximum number of x-tics.
                 void (*draw) (JBWGraphic * graphic),
                 ///< pointer to the render function.
                 unsigned int window)   ///< 1 on new window, 0 otherwise.
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
  graphic->resize = graphic->grid = 1;
  graphic->map = 0;
  graphic->str_title = graphic->str_x = graphic->str_y =
    graphic->str_yy = graphic->str_z = graphic->str_zz = NULL;
  graphic->logo = NULL;
  graphic->nxmax = nx;
  graphic->nymax = ny;
  graphic->nzmax = nz;
  graphic->draw = draw;
  graphic->program_2D = graphic->program_3D = graphic->program_text = 0;
  graphic->ft = NULL;
  graphic->face = NULL;
  jbw_graphic_set_draw (graphic, draw);

  // Setting up the GtkGLArea widget
  graphic->widget = (GtkGLArea *) gtk_gl_area_new ();
  if (!graphic->widget)
    {
      error_msg = _("unable to open the graphic area widget");
      goto error2;
    }
  g_signal_connect_swapped (graphic->widget, "realize",
                            (GCallback) jbw_graphic_init, graphic);
  g_signal_connect_swapped (graphic->widget, "resize",
                            (GCallback) jbw_graphic_resize, graphic);
  g_signal_connect_swapped (graphic->widget, "render",
                            (GCallback) jbw_graphic_render, graphic);

  // Setting up the new window
  if (window)
    {
      graphic->window = (GtkWindow *) gtk_window_new (GTK_WINDOW_TOPLEVEL);
      gtk_container_add (GTK_CONTAINER (graphic->window),
                         GTK_WIDGET (graphic->widget));
    }
  else
    graphic->window = NULL;

  // Return the widget pointer
  return graphic;

  // Exit and show an error message on error
error2:
  jbw_graphic_destroy (graphic);
error1:
  jbw_show_error (error_msg);
  return NULL;
}

/**
 * Function to set the logo on a JBWGraphic widget.
 */
void
jbw_graphic_set_logo (JBWGraphic * graphic,     ///< JBWGraphic widget.
                      char *name)       ///< logo PNG file name.
{
  if (graphic->logo)
    jbw_image_delete (graphic->logo);
  graphic->logo = jbw_image_new (name);
}

/**
 * Function to get the graphical size of a JBWGraphic widget.
 */
void
jbw_graphic_get_display_size (JBWGraphic * graphic)
{
  graphic->width
    = gtk_widget_get_allocated_width (GTK_WIDGET (graphic->widget));
  graphic->height
    = gtk_widget_get_allocated_height (GTK_WIDGET (graphic->widget));
}

/**
 * Function to draw a string in a JBWGraphic widget.
 */
void
jbw_graphic_draw_text (JBWGraphic * graphic,    ///< JBWGraphic widget.
                       const char *string,      ///< string.
                       GLfloat x,       ///< x initial position.
                       GLfloat y,       ///< y initial position.
                       const GLfloat * color)   ///< color intensities array.
{
  GLfloat box[16];
  FT_Face *face;
  GLfloat x2, y2, w, h, sx, sy;
  GLuint id;
  FT_UInt glyph;
  gunichar c;

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

  // disabling OpenGL features
  glDisable (GL_BLEND);
}

/**
 * Function to resize the graphic limits if map on a JBWGraphic widget.
 */
void
jbw_graphic_map_resize (JBWGraphic * graphic)
{
  register JBDOUBLE vw, vh, cw, ch;
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
 * Function to get the limit coordinates on a JBWGraphic widget from 4 tabular
 * functions (JBFLOAT).
 */
void
jbw_graphic_draw_resize (JBWGraphic * graphic,  ///< JBWGraphic widget.
                         JBFLOAT * x,   ///< x-coordinates array.
                         JBFLOAT * y1,  ///< 1st y-coordinates array.
                         JBFLOAT * y2,  ///< 2nd y-coordinates array.
                         JBFLOAT * z1,  ///< 1st z-coordinates array.
                         JBFLOAT * z2,  ///< 2nd z-coordinates array.
                         int n) ///< number of array points.
{
  JBFLOAT k1, k2, kmin, kmax;
  jbm_farray_maxmin (x, n, &kmax, &kmin);
  graphic->xmax = (JBDOUBLE) kmax;
  graphic->xmin = (JBDOUBLE) kmin;
  if (y1)
    {
      jbm_farray_maxmin (y1, n, &kmax, &kmin);
      if (y2)
        {
          jbm_farray_maxmin (y2, n, &k2, &k1);
          kmax = FMAX (kmax, k2);
          kmin = FMIN (kmin, k1);
        }
      graphic->ymax = (JBDOUBLE) kmax;
      graphic->ymin = (JBDOUBLE) kmin;
    }
  if (z1)
    {
      jbm_farray_maxmin (z1, n, &kmax, &kmin);
      if (z2)
        {
          jbm_farray_maxmin (z2, n, &k2, &k1);
          kmax = FMAX (kmax, k2);
          kmin = FMIN (kmin, k1);
        }
      graphic->zmax = (JBDOUBLE) kmax;
      graphic->zmin = (JBDOUBLE) kmin;
    }
}

/**
 * Function to get the limit coordinates on a JBWGraphic widget from 4 tabular
 * functions (JBDOUBLE).
 */
void
jbw_graphic_draw_resizel (JBWGraphic * graphic, ///< JBWGraphic widget.
                          JBDOUBLE * x, ///< x-coordinates array.
                          JBDOUBLE * y1,        ///< 1st y-coordinates array.
                          JBDOUBLE * y2,        ///< 2nd y-coordinates array.
                          JBDOUBLE * z1,        ///< 1st z-coordinates array.
                          JBDOUBLE * z2,        ///< 2nd z-coordinates array.
                          int n)        ///< number of array points.
{
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
 * Function to get the limit coordinates on a JBWGraphic widget from 4 tabular
 * functions defined by a struct array (JBFLOAT).
 */
void
jbw_graphic_draw_resizev (JBWGraphic * graphic, ///< JBWGraphic widget.
                          void *x,
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
 * Function to get the limit coordinates on a JBWGraphic widget from 4 tabular
 * functions defined by a struct array (JBDOUBLE).
 */
void
jbw_graphic_draw_resizevl (JBWGraphic * graphic,        ///< JBWGraphic widget.
                           void *x,
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
 * Function to draw rectangles with color in a JBWGraphic widget.
 */
void
jbw_graphic_draw_rectangles_color (JBWGraphic * graphic,
                                   ///< JBWGraphic widget.
                                   GLfloat * vertex,    ///< vertex array.
                                   GLushort * index,    ///< index array.
                                   unsigned int n)      ///< rectanbles number.
{
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
 * Function to draw a tabuled function on a JBWGraphic widget (JBFLOAT).
 */
void
jbw_graphic_draw_farray (JBWGraphic * graphic,
                         JBFLOAT * x,
                         JBFLOAT * y,
                         unsigned int n, const GLfloat * color, GLenum type)
{
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
 * Function to draw a tabuled function on a JBWGraphic widget (JBDOUBLE).
 */
void
jbw_graphic_draw_darray (JBWGraphic * graphic,
                         JBDOUBLE * x,
                         JBDOUBLE * y,
                         unsigned int n, const GLfloat * color, GLenum type)
{
  GLdouble *vertex;
  GLuint v;
  unsigned int i;
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
 * Function to draw a tabuled function on a JBWGraphic widget (JBFLOAT).
 */
void
jbw_graphic_draw_varray (JBWGraphic * graphic,
                         void *x,
                         void *y,
                         unsigned int size,
                         unsigned int n, const GLfloat * color, GLenum type)
{
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
 * Function to draw a tabuled function on a JBWGraphic widget (JBFLOAT).
 */
void
jbw_graphic_draw_varrayl (JBWGraphic * graphic,
                          void *x,
                          void *y,
                          unsigned int size,
                          unsigned int n, const GLfloat * color, GLenum type)
{
  GLdouble *vertex;
  GLuint v;
  unsigned int i;
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
 * Function to draw a rectangle on a JBWGraphic widget (JBFLOAT).
 */
void
jbw_graphic_draw_rectangle (JBWGraphic * graphic,       ///< JBWGraphic widget.
                            JBFLOAT x1, ///< 1st corner x-coordinate.
                            JBFLOAT y1, ///< 1st corner y-coordinate.
                            JBFLOAT x2, ///< 2nd corner x-coordinate.
                            JBFLOAT y2, ///< 2nd corner y-coordinate.
                            const GLfloat * color)
                            ///< intensity color array.
{
  JBFLOAT x[4] = { x1, x2, x2, x1 };
  JBFLOAT y[4] = { y1, y1, y2, y2 };
  jbw_graphic_draw_farray (graphic, x, y, 3, color, GL_LINE_LOOP);
}

/**
 * Function to draw a rectangle on a JBWGraphic widget (JBDOUBLE).
 */
void
jbw_graphic_draw_rectanglel (JBWGraphic * graphic,      ///< JBWGraphic widget.
                             JBDOUBLE x1,       ///< 1st corner x-coordinate.
                             JBDOUBLE y1,       ///< 1st corner y-coordinate.
                             JBDOUBLE x2,       ///< 2nd corner x-coordinate.
                             JBDOUBLE y2,       ///< 2nd corner y-coordinate.
                             const GLfloat * color)
                             ///< intensity color array.
{
  JBDOUBLE x[4] = { x1, x2, x2, x1 };
  JBDOUBLE y[4] = { y1, y1, y2, y2 };
  jbw_graphic_draw_darray (graphic, x, y, 3, color, GL_LINE_LOOP);
}

/**
 * Function to set the viewport and to draw labels, tics and grid on a
 * JBWGraphic widget.
 */
void
jbw_graphic_draw_labels (JBWGraphic * graphic)  ///< JBWGraphic widget.
{
  JBDOUBLE xtic[JBW_GRAPHIC_N_TICS];
  JBDOUBLE ytic[JBW_GRAPHIC_N_TICS];
  JBDOUBLE ztic[JBW_GRAPHIC_N_TICS];
  JBFLOAT x[2 * JBW_GRAPHIC_N_TICS];
  JBFLOAT y[2 * JBW_GRAPHIC_N_TICS];
  const GLfloat *color_x, *color_y, *color_z;
  JBFLOAT kx, ky, kz;
  GLfloat k, x1, x2, y1, y2, sx, sy, sa, sb;
  char buffer[512];
  int i;
  jbw_graphic_get_display_size (graphic);
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
      jbw_graphic_draw_text (graphic, graphic->str_title,
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
        jbw_graphic_draw_text (graphic, graphic->str_y, -1.f, sb + k, jbw_blue);
      if (graphic->str_z)
        jbw_graphic_draw_text (graphic, graphic->str_z,
                               1.f - sx * strlen (graphic->str_z), sb + k,
                               jbw_red);
    }
  else
    graphic->ny = 0;
  if (graphic->str_yy || graphic->str_zz)
    {
      k -= sy;
      graphic->y2 -= graphic->char_height;
      if (graphic->str_yy)
        jbw_graphic_draw_text (graphic, graphic->str_yy, -1.f, sb + k,
                               jbw_green);
      if (graphic->str_zz)
        jbw_graphic_draw_text (graphic, graphic->str_zz,
                               1.f - sx * strlen (graphic->str_zz), sb + k,
                               jbw_brown);
    }
  else
    graphic->nz = 0;
  graphic->y1 = ceil (2.5f * graphic->char_height);
  graphic->y2 -= ceil (0.5f * graphic->char_height);
  if (graphic->str_y || graphic->str_yy)
    graphic->x1 = (JBW_GRAPHIC_N_CHARS + 1) * graphic->char_width;
  if (graphic->str_z || graphic->str_zz)
    graphic->x2 -= (JBW_GRAPHIC_N_CHARS + 1) * graphic->char_width;
  else
    graphic->x2 -= ceil (0.5f * JBW_GRAPHIC_N_CHARS * graphic->char_width);
  if (graphic->map)
    jbw_graphic_map_resize (graphic);
  jbw_draw_rangel (&graphic->xmin, &graphic->xmax);
  jbw_draw_ticsl (graphic->xmin, graphic->xmax,
                  graphic->nxmax, &graphic->nx, graphic->xtic);
  jbw_draw_rangel (&graphic->ymin, &graphic->ymax);
  jbw_draw_ticsl (graphic->ymin, graphic->ymax,
                  graphic->nymax, &graphic->ny, graphic->ytic);
  jbw_draw_rangel (&graphic->zmin, &graphic->zmax);
  jbw_draw_ticsl (graphic->zmin, graphic->zmax,
                  graphic->nzmax, &graphic->nz, graphic->ztic);
  x1 = (2.f * graphic->x1) / graphic->width - 1.f;
  x2 = (2.f * graphic->x2) / graphic->width - 1.f;
  y1 = (2.f * graphic->y1) / graphic->height - 1.f;
  y2 = (2.f * graphic->y2) / graphic->height - 1.f;
  if (graphic->str_x)
    {
      jbw_graphic_draw_text (graphic, graphic->str_x,
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
          jbw_graphic_draw_text (graphic, buffer,
                                 k - 0.5f * sx * strlen (buffer), sb - 1.f + sy,
                                 jbw_black);
        }
    }
  if (graphic->str_y || graphic->str_yy)
    {
      for (i = 0; i < graphic->ny; ++i)
        {
          sprintf (buffer, FGL, graphic->ytic[i]);
          ytic[i] =
            jbm_extrapolatel (graphic->ytic[i], graphic->ymin, graphic->ymax,
                              (JBDOUBLE) y1, (JBDOUBLE) y2);
          k = (GLfloat) ytic[i];
          jbw_graphic_draw_text (graphic, buffer,
                                 x1 - sx * strlen (buffer) - sa,
                                 sb + k - 0.5f * sy, jbw_blue);
        }
    }
  if (graphic->str_z || graphic->str_zz)
    {
      for (i = 0; i < graphic->nz; ++i)
        {
          sprintf (buffer, FGL, graphic->ztic[i]);
          ztic[i] =
            jbm_extrapolatel (graphic->ztic[i], graphic->zmin, graphic->zmax,
                              (JBDOUBLE) y1, (JBDOUBLE) y2);
          k = (GLfloat) ztic[i];
          jbw_graphic_draw_text (graphic, buffer, x2 + sa, sb + k - 0.5f * sy,
                                 jbw_red);
        }
    }
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
      jbw_graphic_draw_farray (graphic, x, y, 2 * i - 1, color_x, GL_LINES);
    }
  if (graphic->nz)
    {
      for (i = 0; i < graphic->nz; ++i)
        {
          y[2 * i + 1] = y[2 * i] = (JBFLOAT) ztic[i];
          x[2 * i] = kz;
          x[2 * i + 1] = x2;
        }
      jbw_graphic_draw_farray (graphic, x, y, 2 * i - 1, color_z, GL_LINES);
    }
  if (graphic->ny)
    {
      for (i = 0; i < graphic->ny; ++i)
        {
          y[2 * i + 1] = y[2 * i] = (JBFLOAT) ytic[i];
          x[2 * i] = x1;
          x[2 * i + 1] = ky;
        }
      jbw_graphic_draw_farray (graphic, x, y, 2 * i - 1, color_y, GL_LINES);
    }
  jbw_graphic_draw_rectangle (graphic, (JBFLOAT) x1, (JBFLOAT) y1,
                              (JBFLOAT) x2, (JBFLOAT) y2, jbw_black);
  glViewport (graphic->x1, graphic->y1,
              graphic->x2 - graphic->x1, graphic->y2 - graphic->y1);
}

/**
 * Function to render the logo in a JBWGraphic widget.
 */
void
jbw_graphic_draw_logo (JBWGraphic * graphic)    ///< JBWGraphic widget.
{
  JBWImage *logo = graphic->logo;
  if (logo)
    jbw_image_draw (logo, 0, 0, graphic->width, graphic->height);
}

/**
 * Function to draw lines defined by float arrays in a JBWGraphic widget
 * (JBFLOAT).
 */
void
jbw_graphic_draw_lines (JBWGraphic * graphic,   ///< JBWGraphic widget.
                        JBFLOAT * x,    ///< x-coordinates array.
                        JBFLOAT * y1,   ///< 1st y-coordinates array.
                        JBFLOAT * y2,   ///< 2nd y-coordinates array.
                        JBFLOAT * z1,   ///< 1st z-coordinates array.
                        JBFLOAT * z2,   ///< 2nd z-coordinates array.
                        int n)  ///< last arrays element number.
{
  if (!x)
    {
      jbw_graphic_draw_labels (graphic);
      return;
    }
  if (graphic->resize)
    jbw_graphic_draw_resize (graphic, x, y1, y2, z1, z2, n);
  jbw_graphic_draw_labels (graphic);
  jbw_draw_orthogonal_matrixl (graphic->uniform_2D_matrix,
                               (GLdouble) graphic->xmin,
                               (GLdouble) graphic->ymin,
                               (GLdouble) graphic->xmax - graphic->xmin,
                               (GLdouble) graphic->ymax - graphic->ymin);
  if (y1)
    jbw_graphic_draw_farray (graphic, x, y1, n, jbw_blue, GL_LINE_STRIP);
  if (y2)
    jbw_graphic_draw_farray (graphic, x, y2, n, jbw_brown, GL_LINE_STRIP);
  jbw_draw_orthogonal_matrixl (graphic->uniform_2D_matrix,
                               (GLdouble) graphic->xmin,
                               (GLdouble) graphic->zmin,
                               (GLdouble) graphic->xmax - graphic->xmin,
                               (GLdouble) graphic->zmax - graphic->zmin);
  if (z1)
    jbw_graphic_draw_farray (graphic, x, z1, n, jbw_red, GL_LINE_STRIP);
  if (z2)
    jbw_graphic_draw_farray (graphic, x, z2, n, jbw_green, GL_LINE_STRIP);
}

/**
 * Function to draw lines defined by float arrays in a JBWGraphic widget
 * (JBDOUBLE).
 */
void
jbw_graphic_draw_linesl (JBWGraphic * graphic,  ///< JBWGraphic widget.
                         JBDOUBLE * x,  ///< x-coordinates array.
                         JBDOUBLE * y1, ///< 1st y-coordinates array.
                         JBDOUBLE * y2, ///< 2nd y-coordinates array.
                         JBDOUBLE * z1, ///< 1st z-coordinates array.
                         JBDOUBLE * z2, ///< 2nd z-coordinates array.
                         int n) ///< last arrays element number.
{
  if (!x)
    {
      jbw_graphic_draw_labels (graphic);
      return;
    }
  if (graphic->resize)
    jbw_graphic_draw_resizel (graphic, x, y1, y2, z1, z2, n);
  jbw_graphic_draw_labels (graphic);
  jbw_draw_orthogonal_matrixl (graphic->uniform_2D_matrix,
                               (GLdouble) graphic->xmin,
                               (GLdouble) graphic->ymin,
                               (GLdouble) graphic->xmax - graphic->xmin,
                               (GLdouble) graphic->ymax - graphic->ymin);
  if (y1)
    jbw_graphic_draw_darray (graphic, x, y1, n, jbw_blue, GL_LINE_STRIP);
  if (y2)
    jbw_graphic_draw_darray (graphic, x, y2, n, jbw_brown, GL_LINE_STRIP);
  jbw_draw_orthogonal_matrixl (graphic->uniform_2D_matrix,
                               (GLdouble) graphic->xmin,
                               (GLdouble) graphic->ymin,
                               (GLdouble) graphic->xmax - graphic->xmin,
                               (GLdouble) graphic->ymax - graphic->ymin);
  if (z1)
    jbw_graphic_draw_darray (graphic, x, z1, n, jbw_red, GL_LINE_STRIP);
  if (z2)
    jbw_graphic_draw_darray (graphic, x, z2, n, jbw_green, GL_LINE_STRIP);
}

/**
 * Function to draw lines defined by struct arrays in a JBWGraphic widget
 * (JBFLOAT).
 */
void
jbw_graphic_draw_linesv (JBWGraphic * graphic,  ///< JBWGraphic widget.
                         void *x,
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
  if (!x)
    {
      jbw_graphic_draw_labels (graphic);
      return;
    }
  if (graphic->resize)
    jbw_graphic_draw_resizev (graphic, x, y1, y2, z1, z2, size, n);
  jbw_graphic_draw_labels (graphic);
  jbw_draw_orthogonal_matrixl (graphic->uniform_2D_matrix,
                               (GLdouble) graphic->xmin,
                               (GLdouble) graphic->ymin,
                               (GLdouble) graphic->xmax - graphic->xmin,
                               (GLdouble) graphic->ymax - graphic->ymin);
  if (y1)
    jbw_graphic_draw_varray (graphic, x, y1, size, n, jbw_blue, GL_LINE_STRIP);
  if (y2)
    jbw_graphic_draw_varray (graphic, x, y2, size, n, jbw_brown, GL_LINE_STRIP);
  jbw_draw_orthogonal_matrixl (graphic->uniform_2D_matrix,
                               (GLdouble) graphic->xmin,
                               (GLdouble) graphic->zmin,
                               (GLdouble) graphic->xmax - graphic->xmin,
                               (GLdouble) graphic->zmax - graphic->zmin);
  if (z1)
    jbw_graphic_draw_varray (graphic, x, z1, size, n, jbw_red, GL_LINE_STRIP);
  if (z2)
    jbw_graphic_draw_varray (graphic, x, z2, size, n, jbw_green, GL_LINE_STRIP);
}

/**
 * Function to draw lines defined by struct arrays in a JBWGraphic widget
 * (JBDOUBLE).
 */
void
jbw_graphic_draw_linesvl (JBWGraphic * graphic, ///< JBWGraphic widget.
                          void *x,
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
  if (!x)
    {
      jbw_graphic_draw_labels (graphic);
      return;
    }
  if (graphic->resize)
    jbw_graphic_draw_resizevl (graphic, x, y1, y2, z1, z2, size, n);
  jbw_graphic_draw_labels (graphic);
  jbw_draw_orthogonal_matrixl (graphic->uniform_2D_matrix,
                               (GLdouble) graphic->xmin,
                               (GLdouble) graphic->ymin,
                               (GLdouble) graphic->xmax - graphic->xmin,
                               (GLdouble) graphic->ymax - graphic->ymin);
  if (y1)
    jbw_graphic_draw_varrayl (graphic, x, y1, size, n, jbw_blue, GL_LINE_STRIP);
  if (y2)
    jbw_graphic_draw_varrayl (graphic, x, y2, size, n, jbw_brown,
                              GL_LINE_STRIP);
  jbw_draw_orthogonal_matrixl (graphic->uniform_2D_matrix,
                               (GLdouble) graphic->xmin,
                               (GLdouble) graphic->zmin,
                               (GLdouble) graphic->xmax - graphic->xmin,
                               (GLdouble) graphic->zmax - graphic->zmin);
  if (z1)
    jbw_graphic_draw_varrayl (graphic, x, z1, size, n, jbw_red, GL_LINE_STRIP);
  if (z2)
    jbw_graphic_draw_varrayl (graphic, x, z2, size, n, jbw_green,
                              GL_LINE_STRIP);
}

/**
 * Function to save the JBWGraphic widget on a file.
 */
void
jbw_graphic_save (JBWGraphic * graphic, ///< JBWGraphic struct.
                  char *file_name)      ///< file name.
{
  // function gdk_pixbuf_get_from_window is not working
#if JBW_GRAPHIC_OUTPUT == JBW_GRAPHIC_OUTPUT_GDKPIXBUF
  GdkWindow *window;
  GdkPixbuf *pixbuf;
  GError *error;
  const char *t;
  char *ext;
  jbw_graphic_get_display_size (graphic);
  gtk_window_present (graphic->window);
  window = gtk_widget_get_window (GTK_WIDGET (graphic->widget));
  pixbuf = gdk_pixbuf_get_from_window (window, 0, 0, graphic->width,
                                       graphic->height);
  if (!pixbuf)
    {
      jbw_show_error2 ("JBWGraphic", _("unable to get the GdkPixbuf widget"));
      return;
    }
  ext = strrchr (file_name, '.');
  t = "png";
  if (ext && ext != file_name)
    {
      if (!strcasecmp (ext, "jpg") || !strcasecmp (ext, "jpeg"))
        t = "jpeg";
      else if (!strcasecmp (ext, "xpm"))
        t = "xpm";
      else if (!strcasecmp (ext, "tif") || !strcasecmp (ext, "tiff"))
        t = "tiff";
      else if (!strcasecmp (ext, "bmp"))
        t = "bmp";
      else if (!strcasecmp (ext, "ico"))
        t = "ico";
    }
  gdk_pixbuf_save (pixbuf, file_name, t, &error, NULL);
#else
  png_struct *png;
  png_info *info;
  png_byte **row_pointers;
  GLubyte *pixels;
  FILE *file;
  unsigned int row_bytes, pointers_bytes, pixels_bytes, i, x2, y2;
  jbw_graphic_get_display_size (graphic);
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
#endif
}

/**
 * Function to show a dialog to save the JBWGraphic widget on a graphic file.
 */
void
jbw_graphic_dialog_save (JBWGraphic * graphic)  ///< JBWGraphic file.
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
  char *buffer = NULL;
  unsigned int i, j;
  dlg =
    (GtkFileChooserDialog *)
    gtk_file_chooser_dialog_new (_("Save graphical"),
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
  gtk_file_chooser_set_do_overwrite_confirmation (GTK_FILE_CHOOSER (dlg), 1);
  if (gtk_dialog_run ((GtkDialog *) dlg) == GTK_RESPONSE_OK)
    buffer = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (dlg));
  gtk_widget_destroy ((GtkWidget *) dlg);
  if (buffer)
    {
      graphic->draw (graphic);
      while (gtk_events_pending ())
        gtk_main_iteration ();
      jbw_graphic_save (graphic, buffer);
      g_free (buffer);
    }
}

/**
 * Function to check the type of a column on a JBWArrayEditor widget.
 */
void
jbw_array_editor_check_column (JBWArrayEditor * editor,
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
      jbw_show_error (error_msg);
      exit (0);
    }
}

/**
 * Function to set the string of an element of a JBWArrayEditor widget.
 */
void
jbw_array_editor_set_element (JBWArrayEditor * editor,
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
jbw_array_editor_get_element (JBWArrayEditor * editor,
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
jbw_array_editor_set_element_int (JBWArrayEditor * editor,
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
jbw_array_editor_get_element_int (JBWArrayEditor * editor,
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
jbw_array_editor_set_element_float (JBWArrayEditor * editor,
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
jbw_array_editor_get_element_float (JBWArrayEditor * editor,
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
jbw_array_editor_set_element_time (JBWArrayEditor * editor,
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
jbw_array_editor_get_element_time (JBWArrayEditor * editor,
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
jbw_array_editor_set_column (JBWArrayEditor * editor,
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
jbw_array_editor_get_column (JBWArrayEditor * editor,
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
jbw_array_editor_set_column_int (JBWArrayEditor * editor,
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
jbw_array_editor_get_column_int (JBWArrayEditor * editor,
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
jbw_array_editor_set_column_float (JBWArrayEditor * editor,
                                   ///< JBWArrayEditor widget.
                                   int column,  ///< column number.
                                   JBFLOAT * x) ///< array of float numbers.
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
jbw_array_editor_set_column_floatl (JBWArrayEditor * editor,
                                    ///< JBWArrayEditor widget.
                                    int column, ///< column number.
                                    JBDOUBLE * x)
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
jbw_array_editor_get_column_float (JBWArrayEditor * editor,
                                   ///< JBWArrayEditor widget.
                                   int column,  ///< column number.
                                   JBFLOAT * x) ///< array of float numbers.
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
jbw_array_editor_get_column_floatl (JBWArrayEditor * editor,
                                    ///< JBWArrayEditor widget.
                                    int column, ///< column number.
                                    JBDOUBLE * x)       ///< array of float numbers.
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
jbw_array_editor_set_column_time (JBWArrayEditor * editor,
                                  ///< JBWArrayEditor widget.
                                  int column,   ///< column number.
                                  JBDOUBLE * t) ///< array of dates.
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
jbw_array_editor_get_column_time (JBWArrayEditor * editor,
                                  ///< JBWArrayEditor widget.
                                  int column,   ///< column number.
                                  JBDOUBLE * t) ///< array of dates.
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
jbw_array_editor_set_column_sensitive (JBWArrayEditor * editor,
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
jbw_array_editor_show_column (JBWArrayEditor * editor,
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
jbw_array_editor_hide_column (JBWArrayEditor * editor,
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
jbw_array_editor_insert_button_end (JBWArrayEditor * editor,
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
  gtk_grid_attach (editor->table, GTK_WIDGET (editor->button_numeric[row]),
                   0, k + 1, 1, 2);
}

/**
 * Function to insert an entry widget at the end of a column in a JBWArrayEditor
 * widget.
 */
static void
jbw_array_editor_insert_entry_end (JBWArrayEditor * editor,
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
        = gtk_spin_button_new_with_range (-INFINITY, INFINITY, JB_EPSILONL);
    }
  gtk_entry_set_text (GTK_ENTRY (widget), "0");
  gtk_grid_attach (editor->table, widget, row + 1, position, 1, 2);
  editor->matrix_entry[row][position] = widget;
}

/**
 * Function to insert the last row of a JBWArrayEditor widget.
 */
static void
jbw_array_editor_insert_last (JBWArrayEditor * editor)
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
  gtk_widget_show_all (GTK_WIDGET (editor->table));
}

/**
 * Function to up the information on a column of a JBWArrayEditor widget.
 */
static void
jbw_array_editor_up_rows (JBWArrayEditor * editor,
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
jbw_array_editor_insert_row (JBWArrayEditor * editor,
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
jbw_array_editor_remove_entry_end (JBWArrayEditor * editor,
                                   ///< JBWArrayEditor widget.
                                   int column,  ///< column number.
                                   int row)     ///< last row number.
{
  gtk_widget_destroy (editor->matrix_entry[column][row]);
  editor->matrix_entry[column] =
    (GtkWidget **) jb_realloc (editor->matrix_entry[column],
                               row * sizeof (GtkWidget *));
}

/**
 * Function to remove the last row in a JBWArrayEditor widget.
 */
static void
jbw_array_editor_remove_last (JBWArrayEditor * editor)
                                    ///< JBWArrayEditor widget.
{
  int i, j;
  if (editor->nrows <= 0)
    return;
  j = --editor->nrows;
  gtk_widget_destroy (GTK_WIDGET (editor->button_numeric[j]));
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
jbw_array_editor_down_rows (JBWArrayEditor * editor,
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
jbw_array_editor_remove_row (JBWArrayEditor * editor,
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
jbw_array_editor_set_rows (JBWArrayEditor * editor,
                           ///< JBWArrayEditor widget.
                           int n)       ///< number of rows.
{
  int i;
  for (i = editor->nrows; i > n; --i)
    jbw_array_editor_remove_last (editor);
  for (; i < n; ++i)
    jbw_array_editor_insert_last (editor);
  gtk_widget_show_all (GTK_WIDGET (editor->table));
}

/**
 * Function to set the title of a column in a JBWArrayEditor widget.
 */
void
jbw_array_editor_set_title (JBWArrayEditor * editor,
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
jbw_array_editor_destroy (JBWArrayEditor * editor)
                                ///< JBWArrayEditor widget.
{
  register int i;
  gtk_widget_destroy (GTK_WIDGET (editor->scrolled));
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
  editor->scrolled = (GtkScrolledWindow *) gtk_scrolled_window_new (0, 0);
  gtk_widget_set_hexpand (GTK_WIDGET (editor->scrolled), TRUE);
  gtk_widget_set_vexpand (GTK_WIDGET (editor->scrolled), TRUE);
  editor->table = (GtkGrid *) gtk_grid_new ();
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
      gtk_grid_attach (editor->table,
                       GTK_WIDGET (editor->button_title[i]), i + 1, 0, 1, 1);
    }
  editor->button_numeric = NULL;
  editor->ncolumns = ncolumns;
  editor->nfull = nfull;
  editor->nrows = 0;
  editor->type = (int *) g_try_malloc (ncolumns * sizeof (int));
  memcpy (editor->type, type, ncolumns * sizeof (int));
  jbw_array_editor_set_rows (editor, nrows);
  gtk_container_add (GTK_CONTAINER (editor->scrolled),
                     GTK_WIDGET (editor->table));
  gtk_scrolled_window_set_policy (editor->scrolled,
                                  GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
  return editor;

error1:
  jbw_show_error (error_msg);
  return NULL;
}

#endif
