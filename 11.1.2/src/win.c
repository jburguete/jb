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
jbw_show_error_terminal (const char *message)
{
  jbw_show_message (_("Error!"), message);
}

void
jbw_show_warning_terminal (const char *message)
{
  jbw_show_message (_("Warning!"), message);
}

#elif JBW == JBW_GTK

///> Frame vertices.
const JBWVertex jbw_vertices_frame[5] = {
  {{-1.f, -1.f}}, {{1.f, -1.f}}, {{1.f, 1.f}}, {{-1.f, 1.f}}, {{-1.f, -1.f}}
};

///> Image vertices.
const JBWVertexImage jbw_vertices_image[4] = {
  {{-1.f, -1.f}, {0.f, 0.f}},
  {{1.f, -1.f}, {1.f, 0.f}},
  {{-1.f, 1.f}, {0.f, 1.f}},
  {{1.f, 1.f}, {1.f, 1.f}}
};

GdkGLContext *jbw_gdk_gl_context;
///< GdkGLContext OpenGL context used in GTK widgets.
JBWGraphic *jbw_graphic_pointer;
///< pointer to the JBWGraphic current widget.

#if HAVE_VULKAN

#if JBW_VK_N_VALIDATION_LAYERS
const char *jbw_vk_validation_layer[JBW_VK_N_VALIDATION_LAYERS]
  = { "VK_LAYER_KHRONOS_validation" };
///< Vulkan validation layers.
#endif

const char *jbw_vk_device_extension[JBW_VK_N_DEVICE_EXTENSIONS]
  = { VK_KHR_SWAPCHAIN_EXTENSION_NAME };
///< Required Vulkan device extensions.

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

#if HAVE_GTKWIDGET
int (*jbw_graphic_loop_idle) (void) = NULL;
GMainLoop *jbw_graphic_loop_pointer = NULL;
///< pointer to the idle function on a main loop.
#elif HAVE_FREEGLUT
void (*jbw_graphic_loop_idle) (void) = NULL;
///< pointer to the idle function on a main loop.
void (*jbw_graphic_loop_resize) (int width, int height) = NULL;
///< pointer to the resize function on a main loop.
void (*jbw_graphic_loop_render) (void) = NULL;
///< pointer to the render function on a main loop.
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
#if HAVE_FREEGLUT
  glutInit (argn, *argc);
  glutInitDisplayMode (GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
#elif HAVE_SDL
  if (SDL_Init (SDL_INIT_VIDEO | SDL_INIT_EVENTS))
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
jbw_process_pending ()
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
jbw_show_error_gtk (const char *message)        ///< error message.
{
  jbw_show_message_gtk (_("Error!"), message, GTK_MESSAGE_ERROR);
}

/**
 * Function to display a warning message.
 */
void
jbw_show_warning_gtk (const char *message)      ///< warning message.
{
  jbw_show_message_gtk (_("Warning!"), message, GTK_MESSAGE_WARNING);
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

#if HAVE_VULKAN

#if JBW_VK_N_VALIDATION_LAYERS

/**
 * Callback function to print the Vulkan validation messages.
 *
 * \return VK_FALSE.
 */
static VKAPI_ATTR VkBool32 VKAPI_CALL
jbw_debug_callback (VkDebugUtilsMessageSeverityFlagBitsEXT message_severity,
                    ///< Vulkan debug utils message severity flag bits.
                    VkDebugUtilsMessageTypeFlagsEXT message_type,
                    ///< Vulkan debug utils message type flags.
                    const VkDebugUtilsMessengerCallbackDataEXT *p_callback_data,
                    ///< Vulkan debug utils messenger callback data.
                    void *p_user_data __attribute__((unused)))  ///< user data.
{
  fprintf (stderr, "validation layer severity=");
  switch (message_severity)
    {
    case VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT:
      fprintf (stderr, "verbose");
      break;
    case VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT:
      fprintf (stderr, "info");
      break;
    case VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT:
      fprintf (stderr, "warning");
      break;
    case VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT:
      fprintf (stderr, "error");
      break;
    default:
      fprintf (stderr, "unknown");
    }
  fprintf (stderr, " type=");
  switch (message_type)
    {
    case VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT:
      fprintf (stderr, "general");
      break;
    case VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT:
      fprintf (stderr, "validation");
      break;
    case VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT:
      fprintf (stderr, "performance");
      break;
    default:
      fprintf (stderr, "unknown");
    }
  fprintf (stderr, ":\n%s\n", p_callback_data->pMessage);
  return VK_FALSE;
}

/**
 * Function to free the memory used by a debug utils messenger.
 */
static inline void
jbw_debug_messenger_destroy (VkInstance instance,       ///< Vulkan instance.
                             VkDebugUtilsMessengerEXT debug_messenger,
                             ///< debug utils messenger.
                             const VkAllocationCallbacks *p_allocator)
///< Vulkan allocation callbacks.
{
  PFN_vkDestroyDebugUtilsMessengerEXT func;
  func = (PFN_vkDestroyDebugUtilsMessengerEXT)
    vkGetInstanceProcAddr (instance, "vkDestroyDebugUtilsMessengerEXT");
  if (func != NULL)
    func (instance, debug_messenger, p_allocator);
}

/**
 * Function to create a debug utils messenger.
 *
 * \return VK_SUCCESS on success, error code on error.
 */
static inline VkResult
jbw_debug_messenger_create (VkInstance instance,        ///< Vulkan instance.
                            const VkDebugUtilsMessengerCreateInfoEXT
                            *p_create_info,
                            ///< struct with create data.
                            const VkAllocationCallbacks *p_allocator,
                            ///< Vulkan allocation callbacks.
                            VkDebugUtilsMessengerEXT *p_debug_messenger)
///< pointer to the Vulkan debug utils messenger.
{
  PFN_vkCreateDebugUtilsMessengerEXT func;
  func = (PFN_vkCreateDebugUtilsMessengerEXT)
    vkGetInstanceProcAddr (instance, "vkCreateDebugUtilsMessengerEXT");
  if (func != NULL)
    return func (instance, p_create_info, p_allocator, p_debug_messenger);
  return VK_ERROR_EXTENSION_NOT_PRESENT;
}

/**
 * Function to populate the Vulkan debug utils messenger create data struct.
 */
void
jbw_debug_messenger_create_info_populate (VkDebugUtilsMessengerCreateInfoEXT
                                          *p_create_info)
///< pointer to the Vulkan debug utils messenger create info data struct.
{
  p_create_info->sType
    = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
  p_create_info->messageSeverity
    = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT
    | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT
    | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
  p_create_info->messageType
    = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT
    | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT
    | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
  p_create_info->pfnUserCallback = jbw_debug_callback;
  p_create_info->pUserData = NULL;
}

/**
 * Function to set up the Vulkan debug utils messenger.
 *
 * \return pointer to the Vulkan debug utils messenger on succes, NULL on
 * error.
 */
static inline VkDebugUtilsMessengerEXT *
jbw_debug_messenger_setup (VkInstance instance)     ///< Vulkan instance.
{
  VkDebugUtilsMessengerCreateInfoEXT create_info = { };
  VkDebugUtilsMessengerEXT *p_debug_messenger;
  p_debug_messenger = (VkDebugUtilsMessengerEXT *)
    g_try_malloc (sizeof (VkDebugUtilsMessengerEXT));
  jbw_debug_messenger_create_info_populate (&create_info);
  if (jbw_debug_messenger_create
      (instance, &create_info, NULL, p_debug_messenger) != VK_SUCCESS)
    {
      jb_error_add (_("failed to set up debug messenger"));
      return NULL;
    }
  return p_debug_messenger;
}

#endif

/**
 * Function to free the memory used by the Vulkan swap chain.
 */
static inline void
jbw_vk_cleanup_swap_chain (JBWVK *vk)     ///< JBWVK struct.
{
  unsigned int i;
  if (vk->swap_chain_framebuffers)
    {
      for (i = 0; i < vk->n_image_views; ++i)
        if (vk->swap_chain_framebuffers[i])
          vkDestroyFramebuffer (vk->device, vk->swap_chain_framebuffers[i],
                                NULL);
      g_free (vk->swap_chain_framebuffers);
    }
  if (vk->swap_chain_image_views)
    {
      for (i = 0; i < vk->n_image_views; ++i)
        if (vk->swap_chain_image_views[i])
          vkDestroyImageView (vk->device, vk->swap_chain_image_views[i], NULL);
      g_free (vk->swap_chain_image_views);
    }
  if (vk->swap_chain)
    vkDestroySwapchainKHR (vk->device, vk->swap_chain, NULL);
  g_free (vk->swap_chain_images);
}

/**
 * Function to free the memory used by the Vulkan resources.
 */
static inline void
jbw_vk_destroy (JBWVK *vk)        ///< JBWVK struct.
{
  uint32_t i;
  jbw_vk_cleanup_swap_chain (vk);
  if (vk->texture_sampler)
    vkDestroySampler (vk->device, vk->texture_sampler, NULL);
  for (i = 0; i < JBW_MAX_FRAMES_IN_FLIGHT; ++i)
    {
      if (vk->uniform_buffers[i])
        vkDestroyBuffer (vk->device, vk->uniform_buffers[i], NULL);
      if (vk->uniform_buffers_memory[i])
        vkFreeMemory (vk->device, vk->uniform_buffers_memory[i], NULL);
    }
  for (i = 0; i < JBW_MAX_FRAMES_IN_FLIGHT; ++i)
    {
      if (vk->in_flight_fences[i])
        vkDestroyFence (vk->device, vk->in_flight_fences[i], NULL);
      if (vk->render_finished_semaphores[i])
        vkDestroySemaphore (vk->device, vk->render_finished_semaphores[i],
                            NULL);
      if (vk->image_available_semaphores[i])
        vkDestroySemaphore (vk->device, vk->image_available_semaphores[i],
                            NULL);
    }
  if (vk->descriptor_pool_images)
    vkDestroyDescriptorPool (vk->device, vk->descriptor_pool_images, NULL);
  if (vk->descriptor_pool_lines)
    vkDestroyDescriptorPool (vk->device, vk->descriptor_pool_lines, NULL);
  if (vk->image_descriptor_set_layout)
    vkDestroyDescriptorSetLayout (vk->device, vk->image_descriptor_set_layout,
                                  NULL);
  if (vk->descriptor_set_layout)
    vkDestroyDescriptorSetLayout (vk->device, vk->descriptor_set_layout, NULL);
  if (vk->vertex_buffer_image)
    vkDestroyBuffer (vk->device, vk->vertex_buffer_image, NULL);
  if (vk->vertex_buffer_frame)
    vkDestroyBuffer (vk->device, vk->vertex_buffer_frame, NULL);
  if (vk->vertex_buffer_memory_image)
    vkFreeMemory (vk->device, vk->vertex_buffer_memory_image, NULL);
  if (vk->vertex_buffer_memory_frame)
    vkFreeMemory (vk->device, vk->vertex_buffer_memory_frame, NULL);
  if (vk->image_pipeline)
    vkDestroyPipeline (vk->device, vk->image_pipeline, NULL);
  if (vk->pipeline)
    vkDestroyPipeline (vk->device, vk->pipeline, NULL);
  if (vk->image_pipeline_layout)
    vkDestroyPipelineLayout (vk->device, vk->image_pipeline_layout, NULL);
  if (vk->pipeline_layout)
    vkDestroyPipelineLayout (vk->device, vk->pipeline_layout, NULL);
  if (vk->command_pool)
    vkDestroyCommandPool (vk->device, vk->command_pool, NULL);
  if (vk->render_pass)
    vkDestroyRenderPass (vk->device, vk->render_pass, NULL);
  if (vk->device)
    vkDestroyDevice (vk->device, NULL);
  if (vk->surface)
    vkDestroySurfaceKHR (vk->instance, vk->surface, NULL);
#if JBW_VK_N_VALIDATION_LAYERS
  if (vk->debug_messenger)
    jbw_debug_messenger_destroy (vk->instance, *vk->debug_messenger, NULL);
  g_free (vk->debug_messenger);
#endif
  if (vk->instance)
    vkDestroyInstance (vk->instance, NULL);
}

/**
 * Function to create the Vulkan instance.
 *
 * \return JBW_VK_ERROR_CODE_SUCCESS on success, error code on error.
 */
static inline unsigned int
jbw_graphic_vk_create_instance (JBWGraphic *graphic)    ///< JBWGraphic struct.
{
  JBWVK *vk;
  VkApplicationInfo app_info = { };
  VkInstanceCreateInfo create_info = { };
#if HAVE_GLFW
  const char **glfw_extension;
#endif
  const char **window_extension;
  uint32_t i, count;
  unsigned int exit_code = JBW_VK_ERROR_CODE_SUCCESS;
#if JBW_VK_N_VALIDATION_LAYERS
  VkDebugUtilsMessengerCreateInfoEXT debug_create_info = { };
  VkLayerProperties *available_layers;
  uint32_t j, n_vk_validation_layers;
#endif

  // Checking Vulkan extensions support
  vk = graphic->vk;
  vkEnumerateInstanceExtensionProperties (NULL, &count, NULL);
  if (!count)
    {
      jb_error_add (_("no Vulkan instance extensions supported"));
      return JBW_VK_ERROR_CODE_NO_INSTANCE_EXTENSIONS;
    }

  // Check validation layers
#if JBW_VK_N_VALIDATION_LAYERS
  vkEnumerateInstanceLayerProperties (&count, NULL);
  available_layers
    = (VkLayerProperties *) g_try_malloc (count * sizeof (VkLayerProperties));
  vkEnumerateInstanceLayerProperties (&count, available_layers);
  for (j = 0; j < JBW_VK_N_VALIDATION_LAYERS; ++j)
    {
      for (i = 0; i < count; ++i)
        if (!strcmp (available_layers[i].layerName, jbw_vk_validation_layer[j]))
          break;
      if (i == count)
        {
          n_vk_validation_layers = 0;
          break;
        }
      n_vk_validation_layers = j + 1;
    }
  g_free (available_layers);
#endif

  // Creating Vulkan instance
  app_info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
  app_info.pApplicationName = "Vulkan tutorial";
  app_info.applicationVersion = VK_MAKE_VERSION (1, 0, 0);
  app_info.pEngineName = "No Engine";
  app_info.engineVersion = VK_MAKE_VERSION (1, 0, 0);
  app_info.apiVersion = VK_API_VERSION_1_0;
  create_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
  create_info.pApplicationInfo = &app_info;
#if HAVE_GLFW
  glfw_extension = glfwGetRequiredInstanceExtensions (&count);
  window_extension =
    (const char **) g_try_malloc (count * sizeof (const char *));
  memcpy (window_extension, glfw_extension, count * sizeof (const char *));
#elif HAVE_SDL
  SDL_Vulkan_GetInstanceExtensions (graphic->window, &count, NULL);
  window_extension =
    (const char **) g_try_malloc (count * sizeof (const char *));
  SDL_Vulkan_GetInstanceExtensions (graphic->window, &count, window_extension);
#elif HAVE_GTK
  count = 2;
  window_extension =
    (const char **) g_try_malloc (count * sizeof (const char *));
  window_extension[0] = "VK_KHR_surface";
#ifdef GDK_WINDOWING_WAYLAND
  window_extension[1] = "VK_KHR_wayland_surface";
#elif defined(GDK_WINDOWING_X11)
  window_extension[1] = "VK_KHR_xlib_surface";
#elif defined(GDK_WINDOWING_WIN32)
  window_extension[1] = "VK_KHR_win32_surface";
#elif defined(GDK_WINDOWING_MACOS)
  window_extension[1] = "VK_EXT_metal_surface";
#endif
#endif
#if JBW_VK_N_VALIDATION_LAYERS
  if (n_vk_validation_layers)
    {
      create_info.enabledLayerCount = JBW_VK_N_VALIDATION_LAYERS;
      create_info.ppEnabledLayerNames = jbw_vk_validation_layer;
      ++count;
      window_extension = (const char **)
        g_try_realloc (window_extension, count * sizeof (const char *));
      window_extension[count - 1] = VK_EXT_DEBUG_UTILS_EXTENSION_NAME;
      jbw_debug_messenger_create_info_populate (&debug_create_info);
      create_info.pNext = &debug_create_info;
    }
#endif

  // Encountered VK_ERROR_INCOMPATIBLE_DRIVER
  ++count;
  window_extension = (const char **)
    g_try_realloc (window_extension, count * sizeof (const char *));
  window_extension[count - 1] = VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME;
  create_info.flags |= VK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR;
  create_info.enabledExtensionCount = count;
  create_info.ppEnabledExtensionNames = window_extension;
  if (vkCreateInstance (&create_info, NULL, &vk->instance) != VK_SUCCESS)
    {
      jb_error_add (_("failed to create Vulkan instance"));
      exit_code = JBW_VK_ERROR_CODE_FAILED_TO_CREATE_INSTANCE;
    }
  g_free (window_extension);
#if JBW_VK_N_VALIDATION_LAYERS
  if (exit_code == JBW_VK_ERROR_CODE_SUCCESS && n_vk_validation_layers)
    vk->debug_messenger = jbw_debug_messenger_setup (vk->instance);
#endif

  return exit_code;
}

/**
 * Function to create a Vulkan surface.
 *
 * \return JBW_VK_ERROR_CODE_SUCCESS on success, error code on error.
 */
static inline unsigned int
jbw_graphic_vk_create_surface (JBWGraphic *graphic)     ///< JBWGraphic struct.
{
  JBWVK *vk;
  vk = graphic->vk;
#if HAVE_GLFW
  if (glfwCreateWindowSurface (vk->instance, graphic->window, NULL, &vk->surface)
      == VK_SUCCESS)
    return JBW_VK_ERROR_CODE_SUCCESS;
#elif HAVE_SDL
  if (SDL_Vulkan_CreateSurface (graphic->window,
                                (SDL_vulkanInstance) vk->instance,
                                (SDL_vulkanSurface *) & vk->surface) ==
      SDL_TRUE)
    return JBW_VK_ERROR_CODE_SUCCESS;
#elif HAVE_GTK
  GdkSurface *gdk_surface;
  gdk_surface = gtk_native_get_surface (GTK_NATIVE (graphic->window));
#ifdef GDK_WINDOWING_WAYLAND
  GdkDisplay *gdk_display;
  VkWaylandSurfaceCreateInfoKHR surface_info = { };
  gdk_display = gdk_surface_get_display (gdk_surface);
  surface_info.sType = VK_STRUCTURE_TYPE_WAYLAND_SURFACE_CREATE_INFO_KHR;
  surface_info.display = gdk_wayland_display_get_wl_display (gdk_display);
  surface_info.surface = gdk_wayland_surface_get_wl_surface (gdk_surface);
  if (vkCreateWaylandSurfaceKHR (vk->instance, &surface_info, NULL,
                                 &vk->surface) == VK_SUCCESS)
    return JBW_VK_ERROR_CODE_SUCCESS;
#elif defined(GDK_WINDOWING_X11)
  GdkDisplay *gdk_display;
  VkXlibSurfaceCreateInfoKHR surface_info = { };
  gdk_display = gdk_surface_get_display (gdk_surface);
  surface_info.sType = VK_STRUCTURE_TYPE_XLIB_SURFACE_CREATE_INFO_KHR;
  surface_info.dpy = gdk_x11_display_get_xdisplay (gdk_display);
  surface_info.window = gdk_x11_surface_get_xid (gdk_surface);
  if (vkCreateXlibSurfaceKHR (vk->instance, &surface_info, NULL, &vk->surface)
      == VK_SUCCESS)
    return JBW_VK_ERROR_CODE_SUCCESS;
#elif defined(GDK_WINDOWING_WIN32)
  VkWin32SurfaceCreateInfoKHR surface_info = { };
  surface_info.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
  surface_info.hinstance = GetModuleHandle (NULL);
  surface_info.hwnd = gdk_win32_surface_get_handle (gdk_surface);
  if (vkCreateWin32SurfaceKHR (vk->instance, &surface_info, NULL, &vk->surface)
      == VK_SUCCESS)
    return JBW_VK_ERROR_CODE_SUCCESS;
#elif defined(GDK_WINDOWING_MACOS)
  VkMetalSurfaceCreateInfoEXT surface_info = { };
  Class metal_layer_class;
  id nsview, metal_layer;
  typedef id (*Func1) (id, SEL);
  typedef void (*Func2) (id, SEL, id);
  typedef void (*Func3) (id, SEL, BOOL);
  Func1 func1 = (Func1) objc_msgSend;
  Func2 func2 = (Func2) objc_msgSend;
  Func3 func3 = (Func3) objc_msgSend;
  nsview = (id) g_object_get_data (G_OBJECT (gdk_surface), "nsview");
  metal_layer_class = objc_getClass ("CAMetalLayer");
  metal_layer = func1 ((id) metal_layer_class, sel_getUid ("alloc"));
  metal_layer = func1 (metal_layer, sel_getUid ("init"));
  func2 (nsview, sel_getUid ("setLayer:"), metal_layer);
  func3 (nsview, sel_getUid ("setWantsLayer:"), YES);
  surface_info.sType = VK_STRUCTURE_TYPE_METAL_SURFACE_CREATE_INFO_EXT;
  surface_info.pLayer = (CAMetalLayer *) metal_layer;
  if (vkCreateMetalSurfaceEXT (vk->instance, &surface_info, NULL, &vk->surface)
      == VK_SUCCESS)
    return JBW_VK_ERROR_CODE_SUCCESS;
#endif
#endif
  jb_error_add (_("failed to create a Vulkan surface"));
  return JBW_VK_ERROR_CODE_NO_SURFACE;
}

/**
 * Function to select a graphic card.
 *
 * \return JBW_VK_ERROR_CODE_SUCCESS on success, error code on error.
 */
static inline unsigned int
jbw_vk_select_physical_device (JBWVK *vk)       ///< JBWVK data struct.
{
  VkPhysicalDevice device;
  VkPhysicalDeviceProperties device_properties;
  VkPhysicalDeviceFeatures device_features;
  VkPhysicalDevice *devices;
  VkQueueFamilyProperties *queue_families;
  VkExtensionProperties *available_extensions;
  const char *buffer;
  VkResult result;
  VkBool32 present_support;
  uint32_t i, j, count, k;

  // Select physical device
  vkEnumeratePhysicalDevices (vk->instance, &count, NULL);
  if (!count)
    {
      jb_error_add (_("failed to find a GPU with Vulkan support"));
      return JBW_VK_ERROR_CODE_NO_PHYSICAL_DEVICES;
    }
  devices =
    (VkPhysicalDevice *) g_try_malloc (count * sizeof (VkPhysicalDevice));
  result = vkEnumeratePhysicalDevices (vk->instance, &count, devices);
  if (result != VK_SUCCESS)
    {
      g_free (devices);
      jb_error_add (_("error reading Vulkan physical devices"));
      return JBW_VK_ERROR_CODE_BAD_PHYSICAL_DEVICES;
    }
  for (i = 0; i < count; ++i)
    if (devices[i])
      {
        vkGetPhysicalDeviceProperties (devices[i], &device_properties);
      }
  for (k = i = 0; i < count; ++i)
    {
      device = devices[i];
      if (!device)
        continue;
      vkGetPhysicalDeviceProperties (device, &device_properties);
      vkGetPhysicalDeviceFeatures (device, &device_features);
      switch (device_properties.deviceType)
        {
        case VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU:
          j = 4000;
          break;
        case VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU:
          j = 3000;
          break;
        case VK_PHYSICAL_DEVICE_TYPE_VIRTUAL_GPU:
          j = 2000;
          break;
        case VK_PHYSICAL_DEVICE_TYPE_CPU:
          j = 1000;
          break;
        default:
          j = 0;
        }
      if (!j)
        continue;
      if (!device_features.geometryShader)
        continue;
      if (!device_features.samplerAnisotropy)
        continue;
      j += device_properties.limits.maxImageDimension2D;
      if (j > k)
        {
          vk->physical_device = device;
          k = j;
        }
    }
  g_free (devices);
  if (!k)
    {
      jb_error_add (_("no suitable physical devices"));
      return JBW_VK_ERROR_CODE_NO_SUITABLE_PHYSICAL_DEVICES;
    }

  // Queue families
  vkGetPhysicalDeviceQueueFamilyProperties (vk->physical_device, &count, NULL);
  queue_families = (VkQueueFamilyProperties *)
    g_try_malloc (count * sizeof (VkQueueFamilyProperties));
  vkGetPhysicalDeviceQueueFamilyProperties (vk->physical_device, &count,
                                            queue_families);
  for (i = 0; i < count; ++i)
    if (queue_families[i].queueFlags & VK_QUEUE_GRAPHICS_BIT)
      break;
  g_free (queue_families);
  if (i == count)
    {
      jb_error_add (_("no suitable Vulkan physical device queue family"));
      return JBW_VK_ERROR_CODE_NO_SUITABLE_QUEUE_FAMILY;
    }
  vk->queue_family_index_graphics = i;

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
      jb_error_add (_("Vulkan device does not support surfaces"));
      return JBW_VK_ERROR_CODE_NO_SURFACE_SUPPORT;
    }
  vk->queue_family_index_present = i;

  // Checking Vulkan extensions
  vkEnumerateDeviceExtensionProperties (vk->physical_device, NULL, &count,
                                        NULL);
  if (!count)
    {
      jb_error_add (_("no Vulkan instance extensions supported"));
      return JBW_VK_ERROR_CODE_NO_INSTANCE_EXTENSIONS;
    }
  available_extensions = (VkExtensionProperties *)
    g_try_malloc (count * sizeof (VkExtensionProperties));
  vkEnumerateDeviceExtensionProperties (vk->physical_device, NULL, &count,
                                        available_extensions);
  for (j = 0; j < JBW_VK_N_DEVICE_EXTENSIONS; ++j)
    {
      k = 0;
      buffer = jbw_vk_device_extension[j];
      for (i = 0; i < count; ++i)
        if (!strcmp (available_extensions[i].extensionName, buffer))
          k = 1;
      if (!k)
        {
          g_free (available_extensions);
          jb_error_add3 (_("no available Vulkan extension"), ": ",
                          jbw_vk_device_extension[j]);
          return JBW_VK_ERROR_CODE_NO_AVAILABLE_EXTENSION;
        }
    }
  g_free (available_extensions);

  // Exit on success
  return JBW_VK_ERROR_CODE_SUCCESS;
}

/**
 * Function to create the logical device and queues.
 *
 * \return JBW_VK_ERROR_CODE_SUCCESS on succes, error code on error.
 */
static inline unsigned int
jbw_vk_create_logical_device (JBWVK *vk)        ///< JBWVK data struct.
{
  VkDeviceCreateInfo create_info = { };
  VkDeviceQueueCreateInfo queue_create_infos[2] = { };
  VkPhysicalDeviceFeatures device_features = { };
  float queue_priority = 1.0f;

  // Anisotropy device feature
  device_features.samplerAnisotropy = VK_TRUE;

  // Specifying the queues to be created
  queue_create_infos[0].sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
  queue_create_infos[0].queueFamilyIndex = vk->queue_family_index_graphics;
  queue_create_infos[0].queueCount = 1;
  queue_create_infos[0].pQueuePriorities = &queue_priority;

  // Enabling device extensions
  create_info.enabledExtensionCount = JBW_VK_N_DEVICE_EXTENSIONS;
  create_info.ppEnabledExtensionNames = jbw_vk_device_extension;

  // Creating the logical device
  create_info.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
  create_info.pQueueCreateInfos = queue_create_infos;
  if (vk->queue_family_index_graphics != vk->queue_family_index_present)
    {
      // Creating the presentation queue
      queue_create_infos[1].sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
      queue_create_infos[1].queueFamilyIndex = vk->queue_family_index_present;
      queue_create_infos[1].queueCount = 1;
      queue_create_infos[1].pQueuePriorities = &queue_priority;
      create_info.queueCreateInfoCount = 2;
    }
  else
    create_info.queueCreateInfoCount = 1;
  device_features.fillModeNonSolid = VK_TRUE;
  create_info.pEnabledFeatures = &device_features;
#if JBW_VK_N_VALIDATION_LAYERS
#if VULKAN_API_VERSION_MAJOR == 1 && VULKAN_API_VERSION_MINOR < 1
  create_info.enabledLayerCount = JBW_VK_N_VALIDATION_LAYERS;
  create_info.ppEnabledLayerNames = jbw_vk_validation_layer;
#endif
#endif
  if (vkCreateDevice (vk->physical_device, &create_info, NULL, &vk->device)
      != VK_SUCCESS)
    {
      jb_error_add (_("failed to create the Vulkan device"));
      return JBW_VK_ERROR_CODE_NO_DEVICE;
    }

  // Retrieving queue handles
  vkGetDeviceQueue (vk->device, vk->queue_family_index_graphics, 0,
                    &vk->graphics_queue);
  vkGetDeviceQueue (vk->device, vk->queue_family_index_present, 0,
                    &vk->present_queue);

  // Exit on success
  return JBW_VK_ERROR_CODE_SUCCESS;
}

/**
 * Function to create the swap chain.
 *
 * \return JBW_VK_ERROR_CODE_SUCCESS on succes, error code on error.
 */
static inline unsigned int
jbw_graphic_vk_create_swap_chain (JBWGraphic *graphic)
///< JBWGraphic data struct.
{
  JBWVK *vk;
  VkSurfaceCapabilitiesKHR capabilities;
  VkSurfaceFormatKHR *formats = NULL;
  VkPresentModeKHR *present_modes = NULL;
  VkPresentModeKHR present_mode;
  VkSwapchainCreateInfoKHR create_info = { };
  uint32_t queue_family_indices[2];
  int width, height;
  uint32_t count, i;

  // Querying details of swap chain support
  vk = graphic->vk;
  vkGetPhysicalDeviceSurfaceCapabilitiesKHR (vk->physical_device, vk->surface,
                                             &capabilities);
  vkGetPhysicalDeviceSurfaceFormatsKHR (vk->physical_device, vk->surface,
                                        &count, NULL);
  if (count)
    {
      formats = (VkSurfaceFormatKHR *)
        g_try_malloc (count * sizeof (VkSurfaceFormatKHR));
      vkGetPhysicalDeviceSurfaceFormatsKHR (vk->physical_device, vk->surface,
                                            &count, formats);
    }
  else
    {
      jb_error_add (_("No surface formats"));
      return JBW_VK_ERROR_CODE_NO_SURFACE_FORMATS;
    }

  // Surface format
  for (i = 0; i < count; ++i)
    {
      vk->surface_format = formats[i];
      if (vk->surface_format.format == VK_FORMAT_B8G8R8A8_SRGB
          && vk->surface_format.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR)
        break;
    }
  if (i == count)
    {
      g_free (formats);
      jb_error_add (_("failed to find a suitable surface format"));
      return JBW_VK_ERROR_CODE_FAILED_TO_FIND_SUITABLE_SURFACE_FORMAT;
    }

  // Presentation mode
  vkGetPhysicalDeviceSurfacePresentModesKHR (vk->physical_device, vk->surface,
                                             &count, NULL);
  if (count)
    {
      present_modes = (VkPresentModeKHR *)
        g_try_malloc (count * sizeof (VkPresentModeKHR));
      vkGetPhysicalDeviceSurfacePresentModesKHR (vk->physical_device,
                                                 vk->surface, &count,
                                                 present_modes);
    }
  present_mode = VK_PRESENT_MODE_FIFO_KHR;
  for (i = 0; i < count; ++i)
    {
      if (present_modes[i] == VK_PRESENT_MODE_MAILBOX_KHR)
        {
          present_mode = VK_PRESENT_MODE_MAILBOX_KHR;
          break;
        }
    }

  // Swap extent
#if HAVE_GLFW
  glfwGetFramebufferSize (graphic->window, &width, &height);
#elif HAVE_SDL
  SDL_Vulkan_GetDrawableSize (graphic->window, &width, &height);
#elif HAVE_GTK
  width = gtk_widget_get_content_width (graphic->widget);
  height = gtk_widget_get_content_height (graphic->widget);
#endif
  vk->extent.width = width;
  vk->extent.height = height;
  i = capabilities.minImageExtent.width;
  if (i > vk->extent.width)
    vk->extent.width = i;
  i = capabilities.maxImageExtent.width;
  if (i < vk->extent.width)
    vk->extent.width = i;
  i = capabilities.minImageExtent.height;
  if (i > vk->extent.height)
    vk->extent.height = i;
  i = capabilities.maxImageExtent.height;
  if (i < vk->extent.height)
    vk->extent.height = i;

  // Creating the swap chain
  count = capabilities.minImageCount + 1;
  if (capabilities.maxImageCount > 0 && capabilities.maxImageCount < count)
    count = capabilities.maxImageCount;
  create_info.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
  create_info.surface = vk->surface;
  create_info.minImageCount = count;
  create_info.imageFormat = vk->surface_format.format;
  create_info.imageColorSpace = vk->surface_format.colorSpace;
  create_info.imageExtent = vk->extent;
  create_info.imageArrayLayers = 1;
  create_info.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT
    | VK_IMAGE_USAGE_TRANSFER_SRC_BIT;
  if (vk->queue_family_index_graphics != vk->queue_family_index_present)
    {
      create_info.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
      create_info.queueFamilyIndexCount = 2;
      queue_family_indices[0] = vk->queue_family_index_graphics;
      queue_family_indices[1] = vk->queue_family_index_present;
      create_info.pQueueFamilyIndices = queue_family_indices;
    }
  else
    create_info.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
  create_info.preTransform = capabilities.currentTransform;
  if (capabilities.supportedCompositeAlpha & VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR)
    create_info.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
  else if (capabilities.supportedCompositeAlpha
           & VK_COMPOSITE_ALPHA_PRE_MULTIPLIED_BIT_KHR)
    create_info.compositeAlpha = VK_COMPOSITE_ALPHA_PRE_MULTIPLIED_BIT_KHR;
  create_info.presentMode = present_mode;
  create_info.clipped = VK_TRUE;
  create_info.oldSwapchain = VK_NULL_HANDLE;
  if (vkCreateSwapchainKHR (vk->device, &create_info, NULL,
                            &vk->swap_chain) != VK_SUCCESS)
    {
      g_free (present_modes);
      g_free (formats);
      jb_error_add (_("failed to create the Vulkan swap chain"));
      return JBW_VK_ERROR_CODE_NO_SWAPCHAIN;
    }
  g_free (present_modes);
  g_free (formats);

  // Retrieving the swap chain images
  vkGetSwapchainImagesKHR (vk->device, vk->swap_chain, &count, NULL);
  vk->swap_chain_images = (VkImage *) g_try_malloc (count * sizeof (VkImage));
  vkGetSwapchainImagesKHR (vk->device, vk->swap_chain, &count,
                           vk->swap_chain_images);
  vk->n_image_views = count;

  return JBW_VK_ERROR_CODE_SUCCESS;
}

/**
 * Function to create a Vulkan image view.
 *
 * \return JBW_VK_ERROR_CODE_SUCCESS on success, error code on error.
 */
static unsigned int
jbw_vk_create_image_view (JBWVK *vk,    ///< JBWVK data struct.
                          VkImage image,        ///< Vulkan image struct.
                          VkFormat format,      ///< Vulkan image format.
                          VkImageView *image_view)
                            ///< Vulkan image view pointer.
{
  VkImageViewCreateInfo create_info = { };
  create_info.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
  create_info.image = image;
  create_info.viewType = VK_IMAGE_VIEW_TYPE_2D;
  create_info.format = format;
  create_info.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
  create_info.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
  create_info.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
  create_info.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
  create_info.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
  create_info.subresourceRange.baseMipLevel = 0;
  create_info.subresourceRange.levelCount = 1;
  create_info.subresourceRange.baseArrayLayer = 0;
  create_info.subresourceRange.layerCount = 1;
  if (vkCreateImageView (vk->device, &create_info, NULL, image_view)
      != VK_SUCCESS)
    {
      jb_error_add (_("failed to create the image view"));
      return JBW_VK_ERROR_CODE_FAILED_TO_CREATE_IMAGE_VIEW;
    }
  return JBW_VK_ERROR_CODE_SUCCESS;
}

/**
 * Function to create the Vulkan image views.
 *
 * \return JBW_VK_ERROR_CODE_SUCCESS on success, error code on error.
 */
static inline unsigned int
jbw_vk_create_image_views (JBWVK *vk)   ///< JBWVK data struct.
{
  uint32_t i;
  unsigned int j;

  // Image views
  vk->swap_chain_image_views
    = (VkImageView *) g_try_malloc0 (vk->n_image_views * sizeof (VkImageView));
  for (i = 0; i < vk->n_image_views; ++i)
    {
      j = jbw_vk_create_image_view (vk,
                                    vk->swap_chain_images[i],
                                    vk->surface_format.format,
                                    vk->swap_chain_image_views + i);
      if (j != JBW_VK_ERROR_CODE_SUCCESS)
        return j;
    }

  return JBW_VK_ERROR_CODE_SUCCESS;
}

/**
 * Function to create the Vulkan render pass.
 *
 * \return JBW_VK_ERROR_CODE_SUCCESS on success, error code on error.
 */
static inline unsigned int
jbw_vk_create_render_pass (JBWVK *vk)   ///< JBWVK data struct.
{
  VkAttachmentDescription color_attachment = { };
  VkAttachmentReference color_attachment_ref = { };
  VkSubpassDescription subpass = { };
  VkRenderPassCreateInfo render_pass_info = { };
  VkSubpassDependency dependency = { };

  // Attachment description
  color_attachment.format = vk->surface_format.format;
  color_attachment.samples = VK_SAMPLE_COUNT_1_BIT;
  color_attachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
  color_attachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
  color_attachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
  color_attachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
  color_attachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
  color_attachment.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

  // Subpasses and attachment references
  color_attachment_ref.attachment = 0;
  color_attachment_ref.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
  subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
  subpass.colorAttachmentCount = 1;
  subpass.pColorAttachments = &color_attachment_ref;

  // Render pass
  render_pass_info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
  render_pass_info.attachmentCount = 1;
  render_pass_info.pAttachments = &color_attachment;
  render_pass_info.subpassCount = 1;
  render_pass_info.pSubpasses = &subpass;

  // Subpass dependencies
  dependency.srcSubpass = VK_SUBPASS_EXTERNAL;
  dependency.dstSubpass = 0;
  dependency.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
  dependency.srcAccessMask = 0;
  dependency.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
  dependency.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
  render_pass_info.dependencyCount = 1;
  render_pass_info.pDependencies = &dependency;

  // Create render pass
  if (vkCreateRenderPass (vk->device, &render_pass_info, NULL, &vk->render_pass)
      != VK_SUCCESS)
    {
      jb_error_add (_("failed to create render pass"));
      return JBW_VK_ERROR_CODE_FAILED_TO_CREATE_RENDER_PASS;
    }

  return JBW_VK_ERROR_CODE_SUCCESS;
}

/**
 * Function to create a Vulkan shader module.
 *
 * \return Vulkan shader module on success, 0 on error.
 */
VkShaderModule
jbw_vk_create_shader_module (VkDevice device,   ///< Vulkan logical device.
                             const char *file_name)     ///< file name.
{
  VkShaderModule shader_module;
  VkShaderModuleCreateInfo create_info = { };
  char *shader_code;
  size_t size;
  shader_code = jb_read_file (file_name, &size);
  if (!shader_code)
    return 0;
  create_info.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
  create_info.codeSize = size;
  create_info.pCode = (const uint32_t *) shader_code;
  if (vkCreateShaderModule (device, &create_info, NULL, &shader_module)
      != VK_SUCCESS)
    {
      g_free (shader_code);
      return 0;
    }
  g_free (shader_code);
  return shader_module;
}

/**
 * Function to create the Vulkan vertex input binding description.
 *
 * \return Vulkan vertex input binding description.
 */
static inline VkVertexInputBindingDescription
jbw_vk_vertex_get_binding_description ()
{
  VkVertexInputBindingDescription binding_description = { };
  binding_description.stride = sizeof (JBWVertex);
  binding_description.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
  return binding_description;
}

/**
 * Function to create the Vulkan vertex image input binding description.
 *
 * \return Vulkan vertex image input binding description.
 */
static inline VkVertexInputBindingDescription
jbw_vk_vertex_get_image_binding_description ()
{
  VkVertexInputBindingDescription binding_description = { };
  binding_description.stride = sizeof (JBWVertexImage);
  binding_description.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
  return binding_description;
}

/**
 * Function to create the Vulkan vertex input attribute descriptions.
 *
 * \return array of Vulkan vertex input attribute descriptions.
 */
static inline VkVertexInputAttributeDescription *
jbw_vk_vertex_get_attribute_descriptions ()
{
  VkVertexInputAttributeDescription *attribute_descriptions;
  attribute_descriptions = (VkVertexInputAttributeDescription *)
    g_try_malloc0 (sizeof (VkVertexInputAttributeDescription));
  attribute_descriptions[0].location = 0;
  attribute_descriptions[0].format = VK_FORMAT_R32G32_SFLOAT;
  attribute_descriptions[0].offset = offsetof (JBWVertex, position);
  return attribute_descriptions;
}

/**
 * Function to create the Vulkan vertex image input attribute descriptions.
 *
 * \return array of Vulkan vertex image input attribute descriptions.
 */
static inline VkVertexInputAttributeDescription *
jbw_vk_vertex_get_image_attribute_descriptions ()
{
  VkVertexInputAttributeDescription *attribute_descriptions;
  attribute_descriptions = (VkVertexInputAttributeDescription *)
    g_try_malloc0 (2 * sizeof (VkVertexInputAttributeDescription));
  attribute_descriptions[0].location = 0;
  attribute_descriptions[0].format = VK_FORMAT_R32G32_SFLOAT;
  attribute_descriptions[0].offset = offsetof (JBWVertexImage, position);
  attribute_descriptions[1].location = 1;
  attribute_descriptions[1].format = VK_FORMAT_R32G32_SFLOAT;
  attribute_descriptions[1].offset = offsetof (JBWVertexImage, texture);
  return attribute_descriptions;
}

/**
 * Function to create the Vulkan descriptor set layout.
 *
 * \return JBW_VK_ERROR_CODE_SUCCESS on success, error code on error.
 */
static inline unsigned int
jbw_vk_create_descriptor_set_layout (JBWVK *vk) ///< JBWVK struct.
{
  VkDescriptorSetLayoutBinding uc_layout_binding = { };
  VkDescriptorSetLayoutCreateInfo layout_info = { };

  // Descriptor set layout
  uc_layout_binding.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
  uc_layout_binding.descriptorCount = 1;
  uc_layout_binding.stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT;
  layout_info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
  layout_info.bindingCount = 1;
  layout_info.pBindings = &uc_layout_binding;
  if (vkCreateDescriptorSetLayout (vk->device, &layout_info, NULL,
                                   &vk->descriptor_set_layout) != VK_SUCCESS)
    {
      jb_error_add (_("failed to create descriptor set layout"));
      return JBW_VK_ERROR_CODE_FAILED_TO_CREATE_DESCRIPTOR_SET_LAYOUT;
    }

  return JBW_VK_ERROR_CODE_SUCCESS;
}

/**
 * Function to create the Vulkan image descriptor set layout.
 *
 * \return JBW_VK_ERROR_CODE_SUCCESS on success, error code on error.
 */
static inline unsigned int
jbw_vk_create_image_descriptor_set_layout (JBWVK *vk)
///< JBWVK struct.
{
  VkDescriptorSetLayoutCreateInfo layout_info = { };
  VkDescriptorSetLayoutBinding sampler_layout_binding = { };

  // Updating the descriptors
  sampler_layout_binding.binding = 0;
  sampler_layout_binding.descriptorCount = 1;
  sampler_layout_binding.descriptorType
    = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
  sampler_layout_binding.pImmutableSamplers = NULL;
  sampler_layout_binding.stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT;

  layout_info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
  layout_info.bindingCount = 1;
  layout_info.pBindings = &sampler_layout_binding;
  if (vkCreateDescriptorSetLayout (vk->device, &layout_info, NULL,
                                   &vk->image_descriptor_set_layout)
      != VK_SUCCESS)
    {
      jb_error_add (_("failed to create image descriptor set layout"));
      return JBW_VK_ERROR_CODE_FAILED_TO_CREATE_IMAGE_DESCRIPTOR_SET_LAYOUT;
    }

  return JBW_VK_ERROR_CODE_SUCCESS;
}

/**
 * Function to create the Vulkan graphics pipeline.
 *
 * \return JBW_VK_ERROR_CODE_SUCCESS on success, error code on error.
 */
static inline unsigned int
jbw_vk_create_pipeline (JBWVK *vk)      ///< JBWVK data struct.
{
  VkShaderModule vert_shader_module, frag_shader_module;
  VkPipelineShaderStageCreateInfo shader_stages[2] = { };
  const VkDynamicState dynamic_states[2]
    = { VK_DYNAMIC_STATE_VIEWPORT, VK_DYNAMIC_STATE_SCISSOR };
  VkPipelineDynamicStateCreateInfo dynamic_state = { };
  VkPipelineVertexInputStateCreateInfo vertex_input_info = { };
  VkPipelineInputAssemblyStateCreateInfo input_assembly = { };
  VkPipelineViewportStateCreateInfo viewport_state = { };
  VkPipelineRasterizationStateCreateInfo rasterizer = { };
  VkPipelineMultisampleStateCreateInfo multisampling = { };
  VkPipelineColorBlendAttachmentState color_blend_attachment = { };
  VkPipelineColorBlendStateCreateInfo color_blending = { };
  VkPipelineLayoutCreateInfo pipeline_layout_info = { };
  VkGraphicsPipelineCreateInfo pipeline_info = { };
  VkVertexInputBindingDescription binding_description;
  VkVertexInputAttributeDescription *attribute_descriptions;
  unsigned int exit_code = JBW_VK_ERROR_CODE_SUCCESS;

  // Creating shader modules
  vert_shader_module =
    jbw_vk_create_shader_module (vk->device, "shaders/vert1.spv");
  if (!vert_shader_module)
    return JBW_VK_ERROR_CODE_FAILED_TO_CREATE_VERTEX_SHADER;
  frag_shader_module =
    jbw_vk_create_shader_module (vk->device, "shaders/frag1.spv");
  if (!frag_shader_module)
    {
      vkDestroyShaderModule (vk->device, vert_shader_module, NULL);
      return JBW_VK_ERROR_CODE_FAILED_TO_CREATE_FRAGMENT_SHADER;
    }

  // Shader stage creation
  shader_stages[0].sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
  shader_stages[0].stage = VK_SHADER_STAGE_VERTEX_BIT;
  shader_stages[0].module = vert_shader_module;
  shader_stages[0].pName = "main";
  shader_stages[1].sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
  shader_stages[1].stage = VK_SHADER_STAGE_FRAGMENT_BIT;
  shader_stages[1].module = frag_shader_module;
  shader_stages[1].pName = "main";

  // Dynamic state
  dynamic_state.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
  dynamic_state.dynamicStateCount = 2;
  dynamic_state.pDynamicStates = dynamic_states;

  // Vertex input
  vertex_input_info.sType
    = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;

  // Pipeline vertex input
  binding_description = jbw_vk_vertex_get_binding_description ();
  vertex_input_info.vertexBindingDescriptionCount = 1;
  vertex_input_info.pVertexBindingDescriptions = &binding_description;
  attribute_descriptions = jbw_vk_vertex_get_attribute_descriptions ();
  vertex_input_info.vertexAttributeDescriptionCount = 1;
  vertex_input_info.pVertexAttributeDescriptions = attribute_descriptions;

  // Input assembly
  input_assembly.sType
    = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
  input_assembly.topology = VK_PRIMITIVE_TOPOLOGY_LINE_STRIP;
  input_assembly.primitiveRestartEnable = VK_FALSE;

  // Viewports and scissors
  viewport_state.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
  viewport_state.viewportCount = 1;
  viewport_state.scissorCount = 1;

  // Rasterizer
  rasterizer.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
  rasterizer.depthClampEnable = VK_FALSE;
  rasterizer.rasterizerDiscardEnable = VK_FALSE;
  rasterizer.polygonMode = VK_POLYGON_MODE_LINE;
  rasterizer.lineWidth = 1.0f;
  rasterizer.cullMode = VK_CULL_MODE_BACK_BIT;
  rasterizer.frontFace = VK_FRONT_FACE_CLOCKWISE;
  rasterizer.depthBiasEnable = VK_FALSE;
  rasterizer.depthBiasConstantFactor = 0.0f;
  rasterizer.depthBiasClamp = 0.0f;
  rasterizer.depthBiasSlopeFactor = 0.0f;

  // Multisampling
  multisampling.sType
    = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
  multisampling.sampleShadingEnable = VK_FALSE;
  multisampling.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;
  multisampling.minSampleShading = 1.0f;
  multisampling.pSampleMask = NULL;
  multisampling.alphaToCoverageEnable = VK_FALSE;
  multisampling.alphaToOneEnable = VK_FALSE;

  // Depth and stencil testing

  // Color blending
  color_blend_attachment.colorWriteMask = VK_COLOR_COMPONENT_R_BIT
    | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT
    | VK_COLOR_COMPONENT_A_BIT;
  color_blend_attachment.blendEnable = VK_FALSE;
  color_blend_attachment.srcColorBlendFactor = VK_BLEND_FACTOR_ONE;
  color_blend_attachment.dstColorBlendFactor = VK_BLEND_FACTOR_ZERO;
  color_blend_attachment.colorBlendOp = VK_BLEND_OP_ADD;
  color_blend_attachment.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE;
  color_blend_attachment.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;
  color_blend_attachment.alphaBlendOp = VK_BLEND_OP_ADD;
  color_blending.sType
    = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
  color_blending.logicOpEnable = VK_FALSE;
  color_blending.logicOp = VK_LOGIC_OP_COPY;
  color_blending.attachmentCount = 1;
  color_blending.pAttachments = &color_blend_attachment;
  color_blending.blendConstants[0] = 0.0f;
  color_blending.blendConstants[1] = 0.0f;
  color_blending.blendConstants[2] = 0.0f;
  color_blending.blendConstants[3] = 0.0f;

  // Pipeline layout
  pipeline_layout_info.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
  pipeline_layout_info.setLayoutCount = 1;
  pipeline_layout_info.pSetLayouts = &vk->descriptor_set_layout;
  if (vkCreatePipelineLayout (vk->device, &pipeline_layout_info, NULL,
                              &vk->pipeline_layout) != VK_SUCCESS)
    {
      jb_error_add (_("failed to create the pipeline layout"));
      exit_code = JBW_VK_ERROR_CODE_FAILED_TO_CREATE_PIPELINE_LAYOUT;
      goto exit_on_error;
    }

  // Conclusion
  pipeline_info.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
  pipeline_info.stageCount = 2;
  pipeline_info.pStages = shader_stages;
  pipeline_info.pVertexInputState = &vertex_input_info;
  pipeline_info.pInputAssemblyState = &input_assembly;
  pipeline_info.pViewportState = &viewport_state;
  pipeline_info.pRasterizationState = &rasterizer;
  pipeline_info.pMultisampleState = &multisampling;
  pipeline_info.pColorBlendState = &color_blending;
  pipeline_info.pDynamicState = &dynamic_state;
  pipeline_info.layout = vk->pipeline_layout;
  pipeline_info.renderPass = vk->render_pass;
  pipeline_info.basePipelineHandle = VK_NULL_HANDLE;    // Optional
  pipeline_info.basePipelineIndex = -1; // Optional
  if (vkCreateGraphicsPipelines (vk->device, VK_NULL_HANDLE, 1, &pipeline_info,
                              NULL, &vk->pipeline) != VK_SUCCESS)
    {
      jb_error_add (_("failed to create graphics pipeline"));
      exit_code = JBW_VK_ERROR_CODE_FAILED_TO_CREATE_PIPELINE;
    }

  // Cleanup shader modules
exit_on_error:
  g_free (attribute_descriptions);
  vkDestroyShaderModule (vk->device, frag_shader_module, NULL);
  vkDestroyShaderModule (vk->device, vert_shader_module, NULL);

  // Exit
  return exit_code;
}

/**
 * Function to create the Vulkan image pipeline.
 *
 * \return JBW_VK_ERROR_CODE_SUCCESS on success, error code on error.
 */
static inline unsigned int
jbw_vk_create_image_pipeline (JBWVK *vk)        ///< JBWVK data struct.
{
  VkShaderModule vert_shader_module, frag_shader_module;
  VkPipelineShaderStageCreateInfo shader_stages[2] = { };
  const VkDynamicState dynamic_states[2]
    = { VK_DYNAMIC_STATE_VIEWPORT, VK_DYNAMIC_STATE_SCISSOR };
  VkPipelineDynamicStateCreateInfo dynamic_state = { };
  VkPipelineVertexInputStateCreateInfo vertex_input_info = { };
  VkPipelineInputAssemblyStateCreateInfo input_assembly = { };
  VkPipelineViewportStateCreateInfo viewport_state = { };
  VkPipelineRasterizationStateCreateInfo rasterizer = { };
  VkPipelineMultisampleStateCreateInfo multisampling = { };
  VkPipelineColorBlendAttachmentState color_blend_attachment = { };
  VkPipelineColorBlendStateCreateInfo color_blending = { };
  VkPipelineLayoutCreateInfo pipeline_layout_info = { };
  VkGraphicsPipelineCreateInfo pipeline_info = { };
  VkVertexInputBindingDescription binding_description;
  VkVertexInputAttributeDescription *attribute_descriptions;
  unsigned int exit_code = JBW_VK_ERROR_CODE_SUCCESS;

  // Creating shader modules
  vert_shader_module =
    jbw_vk_create_shader_module (vk->device, "shaders/vert2.spv");
  if (!vert_shader_module)
    return JBW_VK_ERROR_CODE_FAILED_TO_CREATE_IMAGE_VERTEX_SHADER;
  frag_shader_module =
    jbw_vk_create_shader_module (vk->device, "shaders/frag2.spv");
  if (!frag_shader_module)
    {
      vkDestroyShaderModule (vk->device, vert_shader_module, NULL);
      return JBW_VK_ERROR_CODE_FAILED_TO_CREATE_IMAGE_FRAGMENT_SHADER;
    }

  // Shader stage creation
  shader_stages[0].sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
  shader_stages[0].stage = VK_SHADER_STAGE_VERTEX_BIT;
  shader_stages[0].module = vert_shader_module;
  shader_stages[0].pName = "main";
  shader_stages[1].sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
  shader_stages[1].stage = VK_SHADER_STAGE_FRAGMENT_BIT;
  shader_stages[1].module = frag_shader_module;
  shader_stages[1].pName = "main";

  // Dynamic state
  dynamic_state.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
  dynamic_state.dynamicStateCount = 2;
  dynamic_state.pDynamicStates = dynamic_states;

  // Vertex input
  vertex_input_info.sType
    = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;

  // Pipeline vertex input
  binding_description = jbw_vk_vertex_get_image_binding_description ();
  vertex_input_info.vertexBindingDescriptionCount = 1;
  vertex_input_info.pVertexBindingDescriptions = &binding_description;
  attribute_descriptions = jbw_vk_vertex_get_image_attribute_descriptions ();
  vertex_input_info.vertexAttributeDescriptionCount = 2;
  vertex_input_info.pVertexAttributeDescriptions = attribute_descriptions;

  // Input assembly
  input_assembly.sType
    = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
  input_assembly.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_STRIP;
  input_assembly.primitiveRestartEnable = VK_FALSE;

  // Viewports and scissors
  viewport_state.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
  viewport_state.viewportCount = 1;
  viewport_state.scissorCount = 1;

  // Rasterizer
  rasterizer.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
  rasterizer.depthClampEnable = VK_FALSE;
  rasterizer.rasterizerDiscardEnable = VK_FALSE;
  rasterizer.polygonMode = VK_POLYGON_MODE_FILL;
  rasterizer.lineWidth = 1.0f;
  rasterizer.cullMode = VK_CULL_MODE_BACK_BIT;
  rasterizer.frontFace = VK_FRONT_FACE_CLOCKWISE;
  rasterizer.depthBiasEnable = VK_FALSE;
  rasterizer.depthBiasConstantFactor = 0.0f;
  rasterizer.depthBiasClamp = 0.0f;
  rasterizer.depthBiasSlopeFactor = 0.0f;

  // Multisampling
  multisampling.sType
    = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
  multisampling.sampleShadingEnable = VK_FALSE;
  multisampling.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;
  multisampling.minSampleShading = 1.0f;
  multisampling.pSampleMask = NULL;
  multisampling.alphaToCoverageEnable = VK_FALSE;
  multisampling.alphaToOneEnable = VK_FALSE;

  // Depth and stencil testing

  // Color blending
  color_blend_attachment.colorWriteMask = VK_COLOR_COMPONENT_R_BIT
    | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT
    | VK_COLOR_COMPONENT_A_BIT;
  color_blend_attachment.blendEnable = VK_TRUE;
  color_blend_attachment.srcColorBlendFactor = VK_BLEND_FACTOR_SRC_ALPHA;
  color_blend_attachment.dstColorBlendFactor
    = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
  color_blend_attachment.colorBlendOp = VK_BLEND_OP_ADD;
  color_blend_attachment.srcAlphaBlendFactor = VK_BLEND_FACTOR_SRC_ALPHA;
  color_blend_attachment.dstAlphaBlendFactor
    = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
  color_blend_attachment.alphaBlendOp = VK_BLEND_OP_ADD;
  color_blending.sType
    = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
  color_blending.logicOpEnable = VK_FALSE;
  color_blending.logicOp = VK_LOGIC_OP_COPY;
  color_blending.attachmentCount = 1;
  color_blending.pAttachments = &color_blend_attachment;
  color_blending.blendConstants[0] = 0.0f;
  color_blending.blendConstants[1] = 0.0f;
  color_blending.blendConstants[2] = 0.0f;
  color_blending.blendConstants[3] = 0.0f;

  // Pipeline layout
  pipeline_layout_info.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
  pipeline_layout_info.setLayoutCount = 1;
  pipeline_layout_info.pSetLayouts = &vk->image_descriptor_set_layout;
  if (vkCreatePipelineLayout (vk->device, &pipeline_layout_info, NULL,
                              &vk->image_pipeline_layout) != VK_SUCCESS)
    {
      jb_error_add (_("failed to create the image pipeline layout"));
      exit_code = JBW_VK_ERROR_CODE_FAILED_TO_CREATE_IMAGE_PIPELINE_LAYOUT;
      goto exit_on_error;
    }

  // Conclusion
  pipeline_info.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
  pipeline_info.stageCount = 2;
  pipeline_info.pStages = shader_stages;
  pipeline_info.pVertexInputState = &vertex_input_info;
  pipeline_info.pInputAssemblyState = &input_assembly;
  pipeline_info.pViewportState = &viewport_state;
  pipeline_info.pRasterizationState = &rasterizer;
  pipeline_info.pMultisampleState = &multisampling;
  pipeline_info.pColorBlendState = &color_blending;
  pipeline_info.pDynamicState = &dynamic_state;
  pipeline_info.layout = vk->image_pipeline_layout;
  pipeline_info.renderPass = vk->render_pass;
  pipeline_info.basePipelineHandle = VK_NULL_HANDLE;    // Optional
  pipeline_info.basePipelineIndex = -1; // Optional
  if (vkCreateGraphicsPipelines (vk->device, VK_NULL_HANDLE, 1, &pipeline_info,
                              NULL, &vk->image_pipeline) != VK_SUCCESS)
    {
      jb_error_add (_("failed to create image pipeline"));
      exit_code = JBW_VK_ERROR_CODE_FAILED_TO_CREATE_IMAGE_PIPELINE;
    }

  // Cleanup shader modules
exit_on_error:
  g_free (attribute_descriptions);
  vkDestroyShaderModule (vk->device, frag_shader_module, NULL);
  vkDestroyShaderModule (vk->device, vert_shader_module, NULL);

  // Exit
  return exit_code;
}

/**
 * Function to create the swap chain framebuffers.
 *
 * \return JBW_VK_ERROR_CODE_SUCCESS on success, error code on error.
 */
static inline unsigned int
jbw_vk_create_framebuffers (JBWVK *vk)  ///< JBWVK struct.
{
  VkFramebufferCreateInfo framebuffer_info = { };
  uint32_t i;

  framebuffer_info.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
  framebuffer_info.renderPass = vk->render_pass;
  framebuffer_info.attachmentCount = 1;
  framebuffer_info.width = vk->extent.width;
  framebuffer_info.height = vk->extent.height;
  framebuffer_info.layers = 1;
  vk->swap_chain_framebuffers = (VkFramebuffer *)
    g_try_malloc0 (vk->n_image_views * sizeof (VkFramebuffer));
  for (i = 0; i < vk->n_image_views; ++i)
    {
      framebuffer_info.pAttachments = vk->swap_chain_image_views + i;
      if (vkCreateFramebuffer (vk->device, &framebuffer_info, NULL,
                               vk->swap_chain_framebuffers + i) != VK_SUCCESS)
        {
          jb_error_add (_("failed to create framebuffer"));
          return JBW_VK_ERROR_CODE_FAILED_TO_CREATE_FRAMEBUFFER;
        }
    }

  return JBW_VK_ERROR_CODE_SUCCESS;
}

/**
 * Function to create a Vulkan command pool.
 *
 * \return JBW_VK_ERROR_CODE_SUCCESS on success, error code on error.
 */
static inline unsigned int
jbw_vk_create_command_pool (JBWVK *vk)  ///< JBWVK struct.
{
  VkCommandPoolCreateInfo pool_info = { };

  // Command pools
  pool_info.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
  pool_info.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
  pool_info.queueFamilyIndex = vk->queue_family_index_graphics;
  if (vkCreateCommandPool (vk->device, &pool_info, NULL, &vk->command_pool)
      != VK_SUCCESS)
    {
      jb_error_add (_("failed to create command pool"));
      return JBW_VK_ERROR_CODE_FAILED_TO_CREATE_COMMAND_POOL;
    }

  return JBW_VK_ERROR_CODE_SUCCESS;
}

/**
 * Function to find the right type of memory to use.
 * 
 * \return type of memory index on success, -1 on error.
 */
static inline int32_t
jbw_vk_find_memory_type (JBWVK *vk,     ///< JBWVK struct.
                         uint32_t type_filter,  ///< filter type.
                         VkMemoryPropertyFlags properties)
///< memory property flags.
{
  VkPhysicalDeviceMemoryProperties mem_properties;
  uint32_t i;
  vkGetPhysicalDeviceMemoryProperties (vk->physical_device, &mem_properties);
  for (i = 0; i < mem_properties.memoryTypeCount; ++i)
    {
      if ((type_filter & (1 << i))
          && (mem_properties.memoryTypes[i].propertyFlags & properties)
          == properties)
        return i;
    }
  return -1;
}

/**
 * Function to create a buffer.
 *
 * \return JBW_VK_ERROR_CODE_SUCCESS on success, error code on error.
 */
static inline unsigned int
jbw_vk_create_buffer (JBWVK *vk,        ///< JBWVK struct.
                      VkDeviceSize size,        ///< buffer size.
                      VkBufferUsageFlags usage, ///< buffer usage.
                      VkMemoryPropertyFlags properties,
                      ///< memory property flags.
                      VkBuffer *buffer, ///< buffer.
                      VkDeviceMemory *buffer_memory)    ///< buffer memory.
{
  VkBufferCreateInfo buffer_info = { };
  VkMemoryRequirements mem_requirements;
  VkMemoryAllocateInfo alloc_info = { };
  int32_t i;

  // Buffer creation
  buffer_info.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
  buffer_info.size = size;
  buffer_info.usage = usage;
  buffer_info.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
  if (vkCreateBuffer (vk->device, &buffer_info, NULL, buffer) != VK_SUCCESS)
    {
      jb_error_add (_("failed to create buffer"));
      return JBW_VK_ERROR_CODE_FAILED_TO_CREATE_BUFFER;
    }

  // Memory requirements
  vkGetBufferMemoryRequirements (vk->device, *buffer, &mem_requirements);

  // Memory allocation
  i = jbw_vk_find_memory_type (vk, mem_requirements.memoryTypeBits, properties);
  if (i < 0)
    {
      vkDestroyBuffer (vk->device, *buffer, NULL);
      jb_error_add (_("failed to find suitable memory type"));
      return JBW_VK_ERROR_CODE_FAILED_TO_FIND_SUITABLE_MEMORY_TYPE;
    }

  alloc_info.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
  alloc_info.allocationSize = mem_requirements.size;
  alloc_info.memoryTypeIndex = i;
  if (vkAllocateMemory (vk->device, &alloc_info, NULL, buffer_memory)
      != VK_SUCCESS)
    {
      vkDestroyBuffer (vk->device, *buffer, NULL);
      jb_error_add (_("failed to allocate buffer memory"));
      return JBW_VK_ERROR_CODE_FAILED_TO_ALLOCATE_BUFFER_MEMORY;
    }
  vkBindBufferMemory (vk->device, *buffer, *buffer_memory, 0);

  return JBW_VK_ERROR_CODE_SUCCESS;
}

/**
 * Function to begin a Vulkan command buffer.
 *
 * \return Vulkan command buffer.
 */
static VkCommandBuffer
jbw_vk_begin_single_time_commands (JBWVK *vk)   ///< JBWVK struct.
{
  VkCommandBufferAllocateInfo alloc_info = { };
  VkCommandBuffer command_buffer;
  VkCommandBufferBeginInfo begin_info = { };

  // Layout transitions
  alloc_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
  alloc_info.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
  alloc_info.commandPool = vk->command_pool;
  alloc_info.commandBufferCount = 1;
  vkAllocateCommandBuffers (vk->device, &alloc_info, &command_buffer);
  begin_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
  begin_info.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
  vkBeginCommandBuffer (command_buffer, &begin_info);
  return command_buffer;
}

/**
 * Function to end a Vulkan command buffer.
 */
static void
jbw_vk_end_single_time_commands (JBWVK *vk,     ///< JBWVK struct.
                                 VkCommandBuffer command_buffer)
///< command buffer.
{
  VkSubmitInfo submit_info = { };

  // Layout transitions
  vkEndCommandBuffer (command_buffer);
  submit_info.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
  submit_info.commandBufferCount = 1;
  submit_info.pCommandBuffers = &command_buffer;
  vkQueueSubmit (vk->graphics_queue, 1, &submit_info, VK_NULL_HANDLE);
  vkQueueWaitIdle (vk->graphics_queue);
  vkFreeCommandBuffers (vk->device, vk->command_pool, 1, &command_buffer);
}

/**
 * Function to copy two Vulkan buffers.
 */
static void
jbw_vk_buffer_copy (JBWVK *vk,  ///< JBWVK struct.
                    VkBuffer src_buffer,        ///< source Vulkan buffer.
                    VkBuffer dst_buffer,        ///< destination Vulkan buffer.
                    VkDeviceSize size)  ///< Vulkan buffers size.
{
  VkCommandBuffer command_buffer;
  VkBufferCopy copy_region = { };

  // Layout transitions
  command_buffer = jbw_vk_begin_single_time_commands (vk);
  copy_region.size = size;
  vkCmdCopyBuffer (command_buffer, src_buffer, dst_buffer, 1, &copy_region);
  jbw_vk_end_single_time_commands (vk, command_buffer);
}

/**
 * Function to create an image.
 *
 * \return JBW_VK_ERROR_CODE_SUCCESS on success, error code on error.
 */
static inline unsigned int
jbw_vk_create_image (JBWVK *vk, ///< JBWVK struct.
                     uint32_t width,    ///< width.
                     uint32_t height,   ///< height.
                     VkFormat format,   ///< format.
                     VkImageTiling tiling,      ///< tiling.
                     VkImageUsageFlags usage,   ///< usage flags.
                     VkMemoryPropertyFlags properties,
                     ///< memory property flags.
                     VkImage *image,    ///< image.
                     VkDeviceMemory *image_memory)      ///< image memory.
{
  VkImageCreateInfo image_info = { };
  VkMemoryRequirements mem_requirements;
  VkMemoryAllocateInfo alloc_info = { };

  // Texture image
  image_info.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
  image_info.imageType = VK_IMAGE_TYPE_2D;
  image_info.extent.width = width;
  image_info.extent.height = height;
  image_info.extent.depth = 1;
  image_info.mipLevels = 1;
  image_info.arrayLayers = 1;
  image_info.format = format;
  image_info.tiling = tiling;
  image_info.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
  image_info.usage = usage;
  image_info.samples = VK_SAMPLE_COUNT_1_BIT;
  image_info.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
  if (vkCreateImage (vk->device, &image_info, NULL, image) != VK_SUCCESS)
    {
      jb_error_add (_("failed to create image"));
      return JBW_VK_ERROR_CODE_FAILED_TO_CREATE_IMAGE;
    }
  vkGetImageMemoryRequirements (vk->device, *image, &mem_requirements);
  alloc_info.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
  alloc_info.allocationSize = mem_requirements.size;
  alloc_info.memoryTypeIndex
    = jbw_vk_find_memory_type (vk, mem_requirements.memoryTypeBits, properties);
  if (vkAllocateMemory (vk->device, &alloc_info, NULL, image_memory)
      != VK_SUCCESS)
    {
      jb_error_add (_("failed to allocate image memory"));
      return JBW_VK_ERROR_CODE_FAILED_TO_ALLOCATE_IMAGE_MEMORY;
    }
  vkBindImageMemory (vk->device, *image, *image_memory, 0);

  return JBW_VK_ERROR_CODE_SUCCESS;
}

/**
 * Function to handle layout transitions.
 */
static unsigned int
jbw_vk_transition_image_layout (JBWVK *vk,      ///< JBWVK struct.
                                VkImage image,  ///< image.
                                VkFormat format __attribute__((unused)),
///< format.
                                VkImageLayout old_layout,
///< old image layout.
                                VkImageLayout new_layout)
///< new image layout.
{
  VkCommandBuffer command_buffer;
  VkImageMemoryBarrier barrier = { };
  VkPipelineStageFlags source_stage, destination_stage;

  // Layout transitions
  command_buffer = jbw_vk_begin_single_time_commands (vk);
  barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
  barrier.oldLayout = old_layout;
  barrier.newLayout = new_layout;
  barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
  barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
  barrier.image = image;
  barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
  barrier.subresourceRange.baseMipLevel = 0;
  barrier.subresourceRange.levelCount = 1;
  barrier.subresourceRange.baseArrayLayer = 0;
  barrier.subresourceRange.layerCount = 1;

  // Transition barrier masks
  if (old_layout == VK_IMAGE_LAYOUT_UNDEFINED
      && new_layout == VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL)
    {
      barrier.srcAccessMask = 0;
      barrier.dstAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
      source_stage = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;
      destination_stage = VK_PIPELINE_STAGE_TRANSFER_BIT;
    }
  else if (old_layout == VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL
           && new_layout == VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL)
    {
      barrier.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
      barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;
      source_stage = VK_PIPELINE_STAGE_TRANSFER_BIT;
      destination_stage = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
    }
  else
    {
      jb_error_add (_("Unsupported layout transition"));
      return JBW_VK_ERROR_CODE_UNSUPPORTED_LAYOUT_TRANSITION;
    }
  vkCmdPipelineBarrier (command_buffer, source_stage, destination_stage, 0,
                        0, NULL, 0, NULL, 1, &barrier);
  jbw_vk_end_single_time_commands (vk, command_buffer);

  return JBW_VK_ERROR_CODE_SUCCESS;
}

/**
 * Function to copy a buffer to an image.
 */
static inline void
jbw_vk_copy_buffer_to_image (JBWVK *vk, ///< JBWVK struct.
                             VkBuffer buffer,   ///< buffer.
                             VkImage image,     ///< image.
                             uint32_t width,    ///< image width.
                             uint32_t height)   ///< image height.
{
  VkCommandBuffer command_buffer;
  VkBufferImageCopy region = { };
  VkOffset3D offset = { 0, 0, 0 };
  VkExtent3D extent = { width, height, 1 };

  // Copying buffer to image
  command_buffer = jbw_vk_begin_single_time_commands (vk);
  region.bufferOffset = 0;
  region.bufferRowLength = 0;
  region.bufferImageHeight = 0;
  region.imageSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
  region.imageSubresource.mipLevel = 0;
  region.imageSubresource.baseArrayLayer = 0;
  region.imageSubresource.layerCount = 1;
  region.imageOffset = offset;
  region.imageExtent = extent;
  vkCmdCopyBufferToImage (command_buffer, buffer, image,
                          VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 1, &region);
  jbw_vk_end_single_time_commands (vk, command_buffer);
}

/**
 * Function to create the texture image.
 *
 * \return JBW_VK_ERROR_CODE_SUCCESS on success, error code on error.
 */
static inline unsigned int
jbw_vk_create_texture_image (JBWVK *vk, ///< JBWVK struct.
                             guchar *pixels,    ///< pixels bitmap.
                             uint32_t tex_width,        ///< texture width.
                             uint32_t tex_height,       ///< texture height.
                             uint32_t tex_rowstride,    ///< texture row stride.
                             VkImage *tex_image,        ///< texture image.
                             VkDeviceMemory *tex_image_memory,
///< texture image memory.
                             VkImageView *tex_image_view,
///< texture imabe view.
                             uint32_t use)
///< 0 for 1st image, >0 otherwise.
{
  VkDeviceSize image_size;
  VkBuffer staging_buffer;
  VkDeviceMemory staging_buffer_memory;
  void *data;
  unsigned int i;

  image_size = tex_rowstride * tex_height;

  // Staging buffer
  i =
    jbw_vk_create_buffer (vk, image_size,
                          VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
                          VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT |
                          VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
                          &staging_buffer, &staging_buffer_memory);
  if (i != JBW_VK_ERROR_CODE_SUCCESS)
    return i;
  vkMapMemory (vk->device, staging_buffer_memory, 0, image_size, 0, &data);
  memcpy (data, pixels, (size_t) image_size);
  vkUnmapMemory (vk->device, staging_buffer_memory);

  // Texture image
  i =
    jbw_vk_create_image (vk, tex_width, tex_height,
                         VK_FORMAT_R8G8B8A8_SRGB, VK_IMAGE_TILING_OPTIMAL,
                         VK_IMAGE_USAGE_TRANSFER_DST_BIT |
                         VK_IMAGE_USAGE_SAMPLED_BIT,
                         VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, tex_image,
                         tex_image_memory);
  if (i != JBW_VK_ERROR_CODE_SUCCESS)
    {
      jb_error_add2 (":\n", _("failed to create texture image"));
      i = JBW_VK_ERROR_CODE_FAILED_TO_CREATE_TEXTURE_IMAGE;
      goto end;
    }

  // Preparing the texture image
  if (!use)
    {
      i = jbw_vk_transition_image_layout
        (vk, *tex_image, VK_FORMAT_R8G8B8A8_SRGB, VK_IMAGE_LAYOUT_UNDEFINED,
         VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL);
      if (i != JBW_VK_ERROR_CODE_SUCCESS)
        goto end;
    }
  jbw_vk_copy_buffer_to_image (vk, staging_buffer, *tex_image,
                               tex_width, tex_height);
  i = jbw_vk_transition_image_layout
    (vk, *tex_image, VK_FORMAT_R8G8B8A8_SRGB,
     VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
     VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);

  // Texture image view
  i = jbw_vk_create_image_view (vk, *tex_image, VK_FORMAT_R8G8B8A8_SRGB,
                                tex_image_view);
  if (i != JBW_VK_ERROR_CODE_SUCCESS)
    {
      jb_error_add2 (":\n", _("failed to create texture image view"));
      return JBW_VK_ERROR_CODE_FAILED_TO_CREATE_TEXTURE_IMAGE_VIEW;
    }

end:
  vkDestroyBuffer (vk->device, staging_buffer, NULL);
  vkFreeMemory (vk->device, staging_buffer_memory, NULL);
  return i;
}

/**
 * Function to create the texture sampler.
 *
 * \return JBW_VK_ERROR_CODE_SUCCESS on success, error code on error.
 */
static inline unsigned int
jbw_vk_create_texture_sampler (JBWVK *vk)       ///< JBWVK struct.
{
  VkSamplerCreateInfo sampler_info = { };
  VkPhysicalDeviceProperties properties = { };

  // Samplers
  sampler_info.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
  sampler_info.magFilter = VK_FILTER_LINEAR;
  sampler_info.minFilter = VK_FILTER_LINEAR;
  sampler_info.addressModeU = VK_SAMPLER_ADDRESS_MODE_REPEAT;
  sampler_info.addressModeV = VK_SAMPLER_ADDRESS_MODE_REPEAT;
  sampler_info.addressModeW = VK_SAMPLER_ADDRESS_MODE_REPEAT;
  sampler_info.anisotropyEnable = VK_TRUE;
  vkGetPhysicalDeviceProperties (vk->physical_device, &properties);
  sampler_info.maxAnisotropy = properties.limits.maxSamplerAnisotropy;
  sampler_info.borderColor = VK_BORDER_COLOR_INT_OPAQUE_BLACK;
  sampler_info.unnormalizedCoordinates = VK_FALSE;
  sampler_info.compareEnable = VK_FALSE;
  sampler_info.compareOp = VK_COMPARE_OP_ALWAYS;
  sampler_info.mipmapMode = VK_SAMPLER_MIPMAP_MODE_LINEAR;
  sampler_info.mipLodBias = 0.f;
  sampler_info.minLod = 0.f;
  sampler_info.maxLod = 0.f;
  if (vkCreateSampler (vk->device, &sampler_info, NULL, &vk->texture_sampler)
      != VK_SUCCESS)
    {
      jb_error_add (_("failed to create texture sampler"));
      return JBW_VK_ERROR_CODE_FAILED_TO_CREATE_TEXTURE_SAMPLER;
    }

  return JBW_VK_ERROR_CODE_SUCCESS;
}

/**
 * Function to create the vertex buffer.
 *
 * \return JBW_VK_ERROR_CODE_SUCCESS on success, error code on error.
 */
static inline unsigned int
jbw_vk_create_vertex_buffer_frame (JBWVK *vk) ///< JBWVK struct.
{
  VkDeviceSize buffer_size;
  VkBuffer staging_buffer;
  VkDeviceMemory staging_buffer_memory;
  void *data;
  unsigned int i;

  // Using a staging buffer
  buffer_size = sizeof (jbw_vertices_frame);
  if (jbw_vk_create_buffer
      (vk, buffer_size, VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
       VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT |
       VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, &staging_buffer,
       &staging_buffer_memory) != JBW_VK_ERROR_CODE_SUCCESS)
    {
      jb_error_add2 (":\n", _("failed to create the staging buffer"));
      return JBW_VK_ERROR_CODE_FAILED_TO_CREATE_STAGING_BUFFER;
    }
  vkMapMemory (vk->device, staging_buffer_memory, 0, buffer_size, 0, &data);
  memcpy (data, jbw_vertices_frame, buffer_size);
  vkUnmapMemory (vk->device, staging_buffer_memory);
  i = jbw_vk_create_buffer (vk, buffer_size,
                            VK_BUFFER_USAGE_TRANSFER_DST_BIT
                            | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT,
                            VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
                            &vk->vertex_buffer_frame,
                            &vk->vertex_buffer_memory_frame);
  if (i != JBW_VK_ERROR_CODE_SUCCESS)
    {
      jb_error_add2 (":\n", _("failed to create the vertex buffer"));
      i = JBW_VK_ERROR_CODE_FAILED_TO_CREATE_VERTEX_BUFFER;
    }
  else
    jbw_vk_buffer_copy (vk, staging_buffer, vk->vertex_buffer_frame,
                        buffer_size);
  vkDestroyBuffer (vk->device, staging_buffer, NULL);
  vkFreeMemory (vk->device, staging_buffer_memory, NULL);

  return i;
}

/**
 * Function to create the image vertex buffer.
 *
 * \return JBW_VK_ERROR_CODE_SUCCESS on success, error code on error.
 */
static inline unsigned int
jbw_vk_create_vertex_buffer_image (JBWVK *vk)   ///< JBWVK struct.
{
  VkDeviceSize buffer_size;
  VkBuffer staging_buffer;
  VkDeviceMemory staging_buffer_memory;
  void *data;
  unsigned int i;

  // Using a staging buffer
  buffer_size = sizeof (jbw_vertices_image);
  if (jbw_vk_create_buffer
      (vk, buffer_size, VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
       VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT |
       VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, &staging_buffer,
       &staging_buffer_memory) != JBW_VK_ERROR_CODE_SUCCESS)
    {
      jb_error_add2 (":\n", _("failed to create the staging buffer"));
      return JBW_VK_ERROR_CODE_FAILED_TO_CREATE_STAGING_BUFFER;
    }
  vkMapMemory (vk->device, staging_buffer_memory, 0, buffer_size, 0, &data);
  memcpy (data, jbw_vertices_image, buffer_size);
  vkUnmapMemory (vk->device, staging_buffer_memory);
  i = jbw_vk_create_buffer (vk, buffer_size,
                            VK_BUFFER_USAGE_TRANSFER_DST_BIT
                            | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT,
                            VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
                            &vk->vertex_buffer_image,
                            &vk->vertex_buffer_memory_image);
  if (i != JBW_VK_ERROR_CODE_SUCCESS)
    {
      jb_error_add2 (":\n", _("failed to create the image vertex buffer"));
      i = JBW_VK_ERROR_CODE_FAILED_TO_CREATE_IMAGE_VERTEX_BUFFER;
    }
  else
    jbw_vk_buffer_copy (vk, staging_buffer, vk->vertex_buffer_image,
                        buffer_size);
  vkDestroyBuffer (vk->device, staging_buffer, NULL);
  vkFreeMemory (vk->device, staging_buffer_memory, NULL);

  return i;
}

/**
 * Function to create the descriptor pool for lines.
 *
 * \return JBW_VK_ERROR_CODE_SUCCESS on success, error code on error.
 */
static inline unsigned int
jbw_vk_create_descriptor_pool_lines (JBWVK *vk, ///< JBWVK struct.
                                     unsigned int n)
///< maximum number of lines.
{
  VkDescriptorPoolSize pool_size = { };
  VkDescriptorPoolCreateInfo pool_info = { };

  // Descriptor pool
  pool_size.type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
  pool_size.descriptorCount = n * JBW_MAX_FRAMES_IN_FLIGHT;
  pool_info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
  pool_info.poolSizeCount = 1;
  pool_info.pPoolSizes = &pool_size;
  pool_info.maxSets = n * JBW_MAX_FRAMES_IN_FLIGHT;
  if (vkCreateDescriptorPool (vk->device, &pool_info, NULL,
                              &vk->descriptor_pool_lines) != VK_SUCCESS)
    {
      jb_error_add (_("failed to create descriptor pool for lines"));
      return JBW_VK_ERROR_CODE_FAILED_TO_CREATE_DESCRIPTOR_POOL_LINES;
    }

  return JBW_VK_ERROR_CODE_SUCCESS;
}

/**
 * Function to create the descriptor pool for images.
 *
 * \return JBW_VK_ERROR_CODE_SUCCESS on success, error code on error.
 */
static inline unsigned int
jbw_vk_create_descriptor_pool_images (JBWVK *vk,        ///< JBWVK struct.
                                     unsigned int n)
///< maximum number of images.
{
  VkDescriptorPoolSize pool_size = { };
  VkDescriptorPoolCreateInfo pool_info = { };

  // Descriptor pool
  pool_size.type = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
  pool_size.descriptorCount = n * JBW_MAX_FRAMES_IN_FLIGHT;
  pool_info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
  pool_info.poolSizeCount = 1;
  pool_info.pPoolSizes = &pool_size;
  pool_info.maxSets = n * JBW_MAX_FRAMES_IN_FLIGHT;
  if (vkCreateDescriptorPool (vk->device, &pool_info, NULL,
                              &vk->descriptor_pool_images) != VK_SUCCESS)
    {
      jb_error_add (_("failed to create descriptor pool for images"));
      return JBW_VK_ERROR_CODE_FAILED_TO_CREATE_DESCRIPTOR_POOL_IMAGES;
    }

  return JBW_VK_ERROR_CODE_SUCCESS;
}

/**
 * Function to create the descriptor sets for a line.
 *
 * \return JBW_VK_ERROR_CODE_SUCCESS on success, error code on error.
 */
static inline unsigned int
jbw_vk_create_descriptor_sets_line (JBWVK *vk,  ///< JBWVK struct.
                                    VkDescriptorSet
				    descriptor_set[JBW_MAX_FRAMES_IN_FLIGHT])
///< array of descriptor sets for a line.
{
  VkDescriptorSetLayout layouts[JBW_MAX_FRAMES_IN_FLIGHT];
  VkDescriptorSetAllocateInfo alloc_info = { };
  VkDescriptorBufferInfo buffer_info = { };
  VkWriteDescriptorSet descriptor_write = { };
  unsigned int i;

  // Descriptor set
  for (i = 0; i < JBW_MAX_FRAMES_IN_FLIGHT; ++i)
    memcpy (layouts + i, &vk->descriptor_set_layout,
            sizeof (VkDescriptorSetLayout));
  alloc_info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
  alloc_info.descriptorPool = vk->descriptor_pool_lines;
  alloc_info.descriptorSetCount = JBW_MAX_FRAMES_IN_FLIGHT;
  alloc_info.pSetLayouts = layouts;
  if (vkAllocateDescriptorSets (vk->device, &alloc_info, descriptor_set)
      != VK_SUCCESS)
    {
      jb_error_add (_("failed to allocate descriptor sets for a line"));
      return JBW_VK_ERROR_CODE_FAILED_TO_ALLOCATE_DESCRIPTOR_SETS_LINE;
    }
  buffer_info.offset = 0;
  buffer_info.range = sizeof (JBWUniformColor);
  descriptor_write.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
  descriptor_write.dstBinding = 0;
  descriptor_write.dstArrayElement = 0;
  descriptor_write.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
  descriptor_write.descriptorCount = 1;
  descriptor_write.pBufferInfo = &buffer_info;
  for (i = 0; i < JBW_MAX_FRAMES_IN_FLIGHT; ++i)
    {
      buffer_info.buffer = vk->uniform_buffers[i];
      descriptor_write.dstSet = descriptor_set[i];
      vkUpdateDescriptorSets (vk->device, 1, &descriptor_write, 0, NULL);
    }

  return JBW_VK_ERROR_CODE_SUCCESS;
}

/**
 * Function to create the descriptor sets for lines.
 *
 * \return JBW_VK_ERROR_CODE_SUCCESS on success, error code on error.
 */
static inline unsigned int
jbw_vk_create_descriptor_sets_lines (JBWVK *vk) ///< JBWVK struct.
{
  unsigned int i, j;
  vk->descriptor_sets_lines
    = g_try_malloc (vk->n_lines
                    * sizeof (VkDescriptorSet[JBW_MAX_FRAMES_IN_FLIGHT]));
  if (!vk->descriptor_sets_lines)
    {
      jb_error_add (_("failed to allocate descriptor sets for lines"));
      return JBW_VK_ERROR_CODE_FAILED_TO_ALLOCATE_DESCRIPTOR_SETS_LINES;
    }
  for (i = 0; i < vk->n_lines; ++i)
    {
      j = jbw_vk_create_descriptor_sets_line (vk, vk->descriptor_sets_lines[i]);
      if (j != JBW_VK_ERROR_CODE_SUCCESS)
        return j;
    }
  return JBW_VK_ERROR_CODE_SUCCESS;
}

/**
 * Function to create the descriptor sets for a image.
 *
 * \return JBW_VK_ERROR_CODE_SUCCESS on success, error code on error.
 */
static inline unsigned int
jbw_vk_create_descriptor_sets_image (JBWVK *vk, ///< JBWVK struct.
                                     VkDescriptorSet
				     descriptor_set[JBW_MAX_FRAMES_IN_FLIGHT],
///< array of descriptor sets for a image.
                                     VkImageView image_view)
///< image view.
{
  VkDescriptorSetLayout layouts[JBW_MAX_FRAMES_IN_FLIGHT];
  VkDescriptorSetAllocateInfo alloc_info = { };
  VkWriteDescriptorSet descriptor_write = { };
  VkDescriptorImageInfo image_info = { };
  unsigned int i;

  // Descriptor set
  for (i = 0; i < JBW_MAX_FRAMES_IN_FLIGHT; ++i)
    memcpy (layouts + i, &vk->image_descriptor_set_layout,
            sizeof (VkDescriptorSetLayout));
  alloc_info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
  alloc_info.descriptorPool = vk->descriptor_pool_images;
  alloc_info.descriptorSetCount = JBW_MAX_FRAMES_IN_FLIGHT;
  alloc_info.pSetLayouts = layouts;
  if (vkAllocateDescriptorSets (vk->device, &alloc_info, descriptor_set)
      != VK_SUCCESS)
    {
      jb_error_add (_("failed to allocate descriptor sets for a image"));
      return JBW_VK_ERROR_CODE_FAILED_TO_ALLOCATE_DESCRIPTOR_SETS_IMAGE;
    }

  // Updating the descriptors
  image_info.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
  image_info.imageView = image_view;
  image_info.sampler = vk->texture_sampler;
  descriptor_write.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
  descriptor_write.dstBinding = 0;
  descriptor_write.dstArrayElement = 0;
  descriptor_write.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
  descriptor_write.descriptorCount = 1;
  descriptor_write.pImageInfo = &image_info;
  for (i = 0; i < JBW_MAX_FRAMES_IN_FLIGHT; ++i)
    {
      descriptor_write.dstSet = descriptor_set[i];
      vkUpdateDescriptorSets (vk->device, 1, &descriptor_write, 0, NULL);
    }

  return JBW_VK_ERROR_CODE_SUCCESS;
}

/**
 * Function to create the uniform buffers.
 *
 * \return JBW_VK_ERROR_CODE_SUCCESS on success, error code on error.
 */
static inline unsigned int
jbw_vk_create_uniform_buffers (JBWVK *vk)       ///< JBWVK struct.
{
  VkDeviceSize buffer_size;
  JBWUniformColor uc = { {0.f, 0.f, 0.f} };
  unsigned int i, j;

  // Uniform buffer
  buffer_size = sizeof (JBWUniformColor);
  for (i = 0; i < JBW_MAX_FRAMES_IN_FLIGHT; ++i)
    {
      j = jbw_vk_create_buffer (vk, buffer_size,
                                VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT,
                                VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT
                                | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
                                vk->uniform_buffers + i,
                                vk->uniform_buffers_memory + i);
      if (j != JBW_VK_ERROR_CODE_SUCCESS)
        return j;
      vkMapMemory (vk->device, vk->uniform_buffers_memory[i], 0, buffer_size, 0,
                   vk->uniform_buffers_mapped + i);
      memcpy (vk->uniform_buffers_mapped[i], &uc, sizeof (JBWUniformColor));
    }

  return JBW_VK_ERROR_CODE_SUCCESS;
}

/**
 * Function to create a Vulkan command buffer.
 *
 * \return JBW_VK_ERROR_CODE_SUCCESS on success, error code on error.
 */
static inline unsigned int
jbw_vk_create_command_buffers (JBWVK *vk)       ///< JBWVK struct.
{
  VkCommandBufferAllocateInfo alloc_info = { };
  unsigned int i;

  // Command buffer allocation
  alloc_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
  alloc_info.commandPool = vk->command_pool;
  alloc_info.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
  alloc_info.commandBufferCount = 1;
  for (i = 0; i < JBW_MAX_FRAMES_IN_FLIGHT; ++i)
    {
      if (vkAllocateCommandBuffers (vk->device, &alloc_info,
                                    vk->command_buffers + i) != VK_SUCCESS)
        {
          jb_error_add (_("failed to allocate command buffers"));
          return JBW_VK_ERROR_CODE_FAILED_TO_ALLOCATE_COMMAND_BUFFERS;
        }
    }

  return JBW_VK_ERROR_CODE_SUCCESS;
}

/**
 * Function to create the Vulkan semaphores.
 *
 * \return JBW_VK_ERROR_CODE_SUCCESS on success, error code on error.
 */
static inline unsigned int
jbw_vk_create_sync_objects (JBWVK *vk)  ///< JBWVK struct.
{
  VkSemaphoreCreateInfo semaphore_info = { };
  VkFenceCreateInfo fence_info = { };
  unsigned int i;

  // Creating the synchronization objects
  semaphore_info.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
  fence_info.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
  fence_info.flags = VK_FENCE_CREATE_SIGNALED_BIT;
  for (i = 0; i < JBW_MAX_FRAMES_IN_FLIGHT; ++i)
    {
      if (vkCreateSemaphore (vk->device, &semaphore_info, NULL,
                             vk->image_available_semaphores + i) != VK_SUCCESS
          || vkCreateSemaphore (vk->device, &semaphore_info, NULL,
                                vk->render_finished_semaphores + i) !=
          VK_SUCCESS
          || vkCreateFence (vk->device, &fence_info, NULL,
                            vk->in_flight_fences + i) != VK_SUCCESS)
        {
          jb_error_add (_("failed to create semaphores"));
          return JBW_VK_ERROR_CODE_FAILED_TO_CREATE_SEMAPHORES;
        }
    }

  return JBW_VK_ERROR_CODE_SUCCESS;
}

/**
 * Function to recreate the Vulkan swap chain.
 *
 * \return EXIT_CODE_SUCCESS on success, error code on error.
 */
static inline unsigned int
jbw_graphic_vk_recreate_swap_chain (JBWGraphic *graphic)
///< JBWGraphic struct.
{
  JBWVK *vk;
#if HAVE_SDL
  SDL_Event event;
#endif
  int width = 0, height = 0;
  unsigned int i;

  // Handling minimization
  vk = graphic->vk;
#if HAVE_GLFW
  glfwGetFramebufferSize (graphic->window, &width, &height);
  while (width == 0 || height == 0)
    {
      glfwGetFramebufferSize (graphic->window, &width, &height);
      glfwWaitEvents ();
    }
#elif HAVE_SDL
  SDL_Vulkan_GetDrawableSize (graphic->window, &width, &height);
  while (width == 0 || height == 0)
    {
      SDL_Vulkan_GetDrawableSize (graphic->window, &width, &height);
      SDL_PollEvent (&event);
    }
#elif HAVE_GTK
  width = gtk_widget_get_content_width (graphic->widget);
  height = gtk_widget_get_content_height (graphic->widget);
  while (width == 0 || height == 0)
    {
      width = gtk_widget_get_content_width (graphic->widget);
      height = gtk_widget_get_content_height (graphic->widget);
      g_main_context_iteration (NULL, TRUE);
    }
#endif

  // Recreating the swap chain
  vkDeviceWaitIdle (vk->device);
  jbw_vk_cleanup_swap_chain (vk);
  i = jbw_graphic_vk_create_swap_chain (graphic);
  if (i != JBW_VK_ERROR_CODE_SUCCESS)
    return i;
  i = jbw_vk_create_image_views (vk);
  if (i != JBW_VK_ERROR_CODE_SUCCESS)
    return i;
  return jbw_vk_create_framebuffers (vk);
}

#endif

/**
 * Function to show an error opening the JBWImage widget.
 */
static void
jbw_image_error (const char *msg)
{
  jb_error_add3 ("JBWImage", ":\n", msg);
}

/**
 * Function to free the memory used by a JBWImage widget.
 */
static void
jbw_image_delete (JBWImage *image)      ///< JBWImage widget.
{
#if HAVE_VULKAN
  JBWVK *vk;
  vk = image->vk;
  if (image->vk_view)
    vkDestroyImageView (vk->device, image->vk_view, NULL);
  if (image->vk_image)
    vkDestroyImage (vk->device, image->vk_image, NULL);
  if (image->vk_memory)
    vkFreeMemory (vk->device, image->vk_memory, NULL);
#endif
  glDeleteProgram (image->program_texture);
  if (image->vbo_texture)
    glDeleteBuffers (1, &image->vbo_texture);
  if (image->ibo)
    glDeleteBuffers (1, &image->ibo);
  if (image->vbo)
    glDeleteBuffers (1, &image->vbo);
  if (image->id_texture)
    glDeleteTextures (1, &image->id_texture);
  g_free (image->pixel);
  g_free (image);
}

/**
 * Function to init the OpenGL functions on a JBWImage widget.
 */
static void
jbw_image_init_gl (JBWImage *image,     ///< JBWImage widget.
                   const char *gl_version)      ///< OpenGL GLSL version string.
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
  const char *error_msg;
  guchar *pixel;
  GLint error_code;
  GLuint fs, vs;
  unsigned int i, h, h1, s;

  // copying pixels in the OpenGL order
  pixel = g_malloc (image->nbytes);
  h = image->height;
  h1 = h - 1;
  s = image->row_stride;
  for (i = 0; i < h; ++i)
    memcpy (pixel + i * s, image->pixel + (h1 - i) * s, s);
  g_free (image->pixel);
  image->pixel = pixel;

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
      error_msg = _("unable to compile the texture fragment shader");
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
      error_msg = _("unable to compile the texture vertex shader");
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
                image->pixel);  // image data

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
      jbw_image_error (error_msg);
      jb_show_error (jb_error_message);
      exit (0);
    }
}

#if HAVE_VULKAN

/**
 * Function to init the Vulkan resources of a JBWImage.
 *
 * \return JBW_VK_ERROR_CODE_SUCCESS on success, error code on error.
 */
static inline unsigned int
jbw_image_init_vk (JBWImage *image,     ///< JBWImage struct.
                   JBWVK *vk)   ///< JBWVK struct.
{
  unsigned int i;
  image->vk = vk;
  i = jbw_vk_create_texture_image (vk, image->pixel,
		                   image->width, image->height,
				   image->row_stride,
                                   &image->vk_image, &image->vk_memory,
                                   &image->vk_view, 0);
  if (i != JBW_VK_ERROR_CODE_SUCCESS)
    {
      jb_error_add2 (":\n", _("failed to init the image"));
      return JBW_VK_ERROR_CODE_FAILED_TO_INIT_IMAGE;
    }
  return i;
}

#endif

/**
 * Function to create a new JBWImage widget from a file.
 * 
 * \return JBWImage struct on success, NULL on error.
 */
JBWImage *
jbw_image_new_from_file (const char *name)      ///< file name.
{
  JBWImage *image = NULL;
  GdkPixbuf *pixbuf, *pixbuf2;
  guchar *pixel;
  const char *err_msg;

  pixbuf = gdk_pixbuf_new_from_file (name, NULL);
  if (!pixbuf)
    {
      err_msg = _("failed to load logo image");
      goto error1;
    }
  if (!gdk_pixbuf_get_has_alpha (pixbuf))
    {
      pixbuf2 = gdk_pixbuf_add_alpha (pixbuf, FALSE, 0, 0, 0);
      g_object_unref (G_OBJECT (pixbuf));
      pixbuf = pixbuf2;
      if (!pixbuf)
        {
          err_msg = _("failed to add alpha channel");
          goto error1;
        }
    }

  // creating the image struct data
  image = (JBWImage *) g_try_malloc0 (sizeof (JBWImage));
  if (!image)
    {
      err_msg = _("not enough memory to open the widget");
      goto error1;
    }

  // copying the data from the GdkPixbuf
  image->width = gdk_pixbuf_get_width (pixbuf);
  image->height = gdk_pixbuf_get_height (pixbuf);
  image->row_stride = gdk_pixbuf_get_rowstride (pixbuf);
  image->nbytes = image->row_stride * image->height;
  pixel = gdk_pixbuf_get_pixels (pixbuf);
  image->pixel = g_try_malloc (image->nbytes);
  if (!image->pixel)
    {
      err_msg = _("not enough memory to open the image");
      goto error2;
    }
  memcpy (image->pixel, pixel, image->nbytes);
  g_object_unref (pixbuf);
  return image;

error2:
  g_object_unref (pixbuf);
  g_free (image);

error1:
  jbw_image_error (err_msg);
  return NULL;
}

/**
 * Function to draw a text string.
 *
 * \return JBWImage struct on success, NULL on error.
 */
JBWImage *
jbw_image_new_from_text (JBWGraphic *graphic,   /// JBWGraphic struct.
                         const char *text,      /// text string.
                         const unsigned char red,       /// red color.
                         const unsigned char green,     /// green color.
                         const unsigned char blue)      /// blue color.
{
  JBWImage *image;
  FT_Face face;
  FT_GlyphSlot glyph;
  FT_Bitmap *bitmap;
  FT_Vector *advance;
  unsigned char *buffer, *pixmap;
  const char *err_msg;
  FT_UInt index;
  uint32_t i, j, c, d, l, x, y, xx;

  // Creating the image pixmap
  l = g_utf8_strlen (text, -1) * graphic->char_width * 4;
  pixmap = g_try_malloc0 (l * graphic->char_height);
  if (!pixmap)
    {
      err_msg = _("failed to allocate text");
      goto error1;
    }
  face = graphic->face;
  for (xx = 0; *text; text = g_utf8_next_char (text))
    {
      c = g_utf8_get_char (text);
      index = FT_Get_Char_Index (face, c);
      if (FT_Load_Glyph (face, index, FT_LOAD_RENDER | FT_LOAD_MONOCHROME))
        continue;
      glyph = face->glyph;
      bitmap = &glyph->bitmap;
      advance = &glyph->advance;
      buffer = bitmap->buffer;
      for (j = 0; j < bitmap->rows; ++j)
        for (i = 0; i < bitmap->width; ++i)
          {
            c = i / 8;
            d = 7 - i % 8;
            x = xx + glyph->bitmap_left + i;
            y = graphic->char_height - glyph->bitmap_top + j
                + graphic->char_descender;
            x = y * l + x * 4;
            if ((buffer[j * bitmap->pitch + c] >> d) & 1)
              {
                pixmap[x] = red;
                pixmap[x + 1] = green;
                pixmap[x + 2] = blue;
                pixmap[x + 3] = 255;
              }
          }
      xx += advance->x >> 6;
    }

  // creating the image struct data
  image = (JBWImage *) g_try_malloc0 (sizeof (JBWImage));
  if (!image)
    {
      err_msg = _("not enough memory to open the widget");
      goto error2;
    }
  image->width = xx;
  image->height = graphic->char_height;
  image->row_stride = 4 * xx;
  image->nbytes = image->row_stride * image->height;
  image->pixel = pixmap;
  return image;

error2:
  g_free (pixmap);

error1:
  jbw_image_error (err_msg);
  return NULL;
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

/**
 * Function to free the memory used by the current JBWGraphic widget.
 */
static inline void
jbw_graphic_delete (JBWGraphic *graphic)        ///< current JBWGraphic widget.
{
  if (graphic->vbo_text)
    glDeleteBuffers (1, &graphic->vbo_text);
  if (graphic->face)
    FT_Done_Face (graphic->face);
  if (graphic->ft)
    FT_Done_FreeType (graphic->ft);
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
#if HAVE_GTKWIDGET
      gtk_window_destroy (graphic->window);
#elif HAVE_FREEGLUT
      glutDestroyWindow (graphic->window);
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
    jbw_image_init_gl (graphic->logo, gl_version);

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

  glGenBuffers (1, &graphic->vbo_text);

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
  jb_show_error2 ("JBWGraphic", error_msg);
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
#if HAVE_FREEGLUT
  glutReshapeWindow (width, height);
#endif
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
#if HAVE_GTKWIDGET
  gtk_widget_queue_draw (graphic->widget);
#elif HAVE_FREEGLUT
  glutSwapBuffers ();
#elif HAVE_SDL
  SDL_GL_SwapWindow (graphic->window);
#elif HAVE_GLFW
  glfwSwapBuffers (graphic->window);
#endif
}

#if HAVE_GTKWIDGET

static void
jbw_graphic_init_gtk (JBWGraphic *graphic)
{
#if HAVE_VULKAN
  graphic->is_window_realized = 1;
#endif
  gtk_gl_area_make_current ((GtkGLArea *) graphic->widget);
  jbw_graphic_init ();
}

static void
jbw_graphic_resize_gtk (JBWGraphic *graphic, int width, int height)
{
#if HAVE_VULKAN
  graphic->vk->framebuffer_resized = 1;
#endif
  jbw_graphic_resize (width, height);
  gtk_widget_queue_draw (graphic->widget);
}

/**
 * Function to close the GTK window.
 */
static void
jbw_graphic_window_close (JBWGraphic *graphic)  ///< JBWGraphic struct.
{
  graphic->has_to_close = 1;
  gtk_window_close (graphic->window);
}

#elif HAVE_GLFW

static void
jbw_graphic_resize_glfw (GLFWwindow *window __attribute__((unused)),
                         int width, int height)
{
#if HAVE_VULKAN
  JBWVK *vk;
  vk = (JBWVK *) glfwGetWindowUserPointer (window);
  vk->framebuffer_resized = 1;
#endif
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
#if HAVE_GTKWIDGET

  if (jbw_graphic_loop_idle)
    g_idle_add ((GSourceFunc) jbw_graphic_loop_idle, NULL);
  g_main_loop_run (jbw_graphic_loop_pointer);
  g_main_loop_unref (jbw_graphic_loop_pointer);

#elif HAVE_FREEGLUT

  // Passing the GTK signals to the FreeGLUT main loop
  glutIdleFunc (jbw_graphic_loop_idle);
  // Setting our draw resize function as the FreeGLUT reshape function
  glutReshapeFunc (jbw_graphic_loop_resize);
  // Setting our draw function as the FreeGLUT display function
  glutDisplayFunc (jbw_graphic_loop_render);
  // FreeGLUT main loop
  glutMainLoop ();

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
#if HAVE_GTKWIDGET
  gtk_window_set_title (graphic->window, title);
#elif HAVE_FREEGLUT
  glutSetWindowTitle (title);
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
  graphic->logo = jbw_image_new_from_file (name);
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
  JBWGraphic *graphic;
#if HAVE_GTKWIDGET
#if GTK_MAJOR_VERSION > 3
  GListModel *list_monitors;
  GdkMonitor *monitor;
#else
  GdkScreen *screen;
#endif
  GdkRectangle geometry;
#elif HAVE_SDL
  SDL_DisplayMode mode;
#elif HAVE_GLFW
  GLFWmonitor *monitor;
  const GLFWvidmode *mode;
#endif
  FT_Face face;
  FT_Size_Metrics *metrics;
  FT_UInt height;

  // Checking tic numbers
  if (nx > JBW_GRAPHIC_N_TICS || ny > JBW_GRAPHIC_N_TICS
      || nz > JBW_GRAPHIC_N_TICS)
    {
      jb_error_add (_("bad tics number"));
      goto error1;
    }

  // Allocating memory
  graphic = (JBWGraphic *) g_try_malloc0 (sizeof (JBWGraphic));
  if (!graphic)
    {
      jb_error_add (_("not enough memory to open the graphic area"));
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
  graphic->init = 0;
  jbw_graphic_set_draw (graphic, draw);

  // Setting up the new window
#if HAVE_GTKWIDGET

#if GTK_MAJOR_VERSION > 3
  list_monitors = gdk_display_get_monitors (gdk_display_get_default ());
  monitor = (GdkMonitor *) g_list_model_get_object (list_monitors, 0);
  gdk_monitor_get_geometry (monitor, &geometry);
#else
  screen = gdk_screen_get_default ();
  gdk_screen_get_monitor_geometry (screen, 0, &geometry);
#endif
  graphic->screen_width = geometry.width;
  graphic->screen_height = geometry.height;
#if HAVE_VULKAN
  graphic->is_vulkan_supported = 1;
#endif
  graphic->widget = gtk_gl_area_new ();
  if (!graphic->widget)
    {
      jb_error_add (_("unable to open the graphic area widget"));
      goto error2;
    }
  g_signal_connect_swapped (graphic->widget, "realize",
                            (GCallback) jbw_graphic_init_gtk, graphic);
  g_signal_connect_swapped (graphic->widget, "resize",
                            (GCallback) jbw_graphic_resize_gtk, graphic);
  g_signal_connect (graphic->widget, "render",
                    (GCallback) jbw_graphic_render, NULL);
#if GTK_MAJOR_VERSION > 3
  graphic->window = (GtkWindow *) gtk_window_new ();
#else
  graphic->window = (GtkWindow *) gtk_window_new (GTK_WINDOW_TOPLEVEL);
#endif
  gtk_window_set_child (graphic->window, graphic->widget);
  gtk_window_set_title (graphic->window, title);
  g_signal_connect_swapped (graphic->window, "close_request",
                            (GCallback) jbw_graphic_window_close, graphic);
  g_signal_connect_swapped (graphic->window, "destroy",
                            (GCallback) jbw_graphic_destroy, graphic);
#if GTK_MAJOR_VERSION > 3
  gtk_window_present (graphic->window);
#else
  gtk_widget_show_all (GTK_WIDGET (graphic->window));
#endif
  while (!graphic->is_window_realized)
    g_main_context_iteration (NULL, FALSE);

#elif HAVE_FREEGLUT

  graphic->screen_width = glutGet (GLUT_SCREEN_WIDTH);
  graphic->screen_height = glutGet (GLUT_SCREEN_HEIGHT);
  glutInitWindowSize (JBW_WINDOW_WIDTH, JBW_WINDOW_HEIGHT);
  graphic->window = glutCreateWindow (title);

#elif HAVE_SDL

  SDL_GetCurrentDisplayMode (0, &mode);
  graphic->screen_width = mode.w;
  graphic->screen_height = mode.h;
#if HAVE_VULKAN
/*
  graphic->window
    = SDL_CreateWindow (title,
                        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                        JBW_WINDOW_WIDTH, JBW_WINDOW_HEIGHT,
                        SDL_WINDOW_RESIZABLE | SDL_WINDOW_VULKAN);
*/
  if (!graphic->window)
    {
      graphic->window
        = SDL_CreateWindow (title,
                            SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                            JBW_WINDOW_WIDTH, JBW_WINDOW_HEIGHT,
                            SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);
      graphic->is_vulkan_supported = 0;
    }
  else
    graphic->is_vulkan_supported = 1;
#else
  graphic->window
    = SDL_CreateWindow (title,
                        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                        JBW_WINDOW_WIDTH, JBW_WINDOW_HEIGHT,
                        SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);
#endif
  if (!graphic->window)
    {
      jb_error_add (SDL_GetError ());
      goto error2;
    }
  SDL_GL_SetAttribute (SDL_GL_CONTEXT_MAJOR_VERSION, 2);
  graphic->sdl_context = SDL_GL_CreateContext (graphic->window);
  if (!graphic->sdl_context)
    {
      jb_error_add (SDL_GetError ());
      goto error2;
    }

#elif HAVE_GLFW

  monitor = glfwGetPrimaryMonitor ();
  mode = glfwGetVideoMode (monitor);
  graphic->screen_width = mode->width;
  graphic->screen_height = mode->height;
  glfwWindowHint (GLFW_CLIENT_API, GLFW_NO_API);
  graphic->window
    = glfwCreateWindow (JBW_WINDOW_WIDTH, JBW_WINDOW_HEIGHT, title, NULL, NULL);
  if (!graphic->window)
    {
      jb_error_add (_("unable to open the window"));
      glfwTerminate ();
      goto error2;
    }
  glfwMakeContextCurrent (graphic->window);
#if HAVE_VULKAN
  glfwSetWindowUserPointer (graphic->window, graphic->vk);
#endif
  glfwSetFramebufferSizeCallback (graphic->window, jbw_graphic_resize_glfw);
  glfwSetWindowRefreshCallback (graphic->window, jbw_graphic_render_glfw);

#endif

  // Initing FreeType
  if (FT_Init_FreeType (&graphic->ft))
    {
      jb_error_add (_("could not init the FreeType library"));
      goto error2;
    }
  if (FT_New_Face (graphic->ft, FONT, 0, &graphic->face))
    {
      jb_error_add (_("could not open font"));
      goto error2;
    }
  face = graphic->face;
  FT_Select_Charmap (face, ft_encoding_unicode);

  // Setting char and window sizes
  if (graphic->screen_height < 720)
    height = 14;
  else if (graphic->screen_height < 800)
    height = 15;
  else if (graphic->screen_height < 900)
    height = 16;
  else if (graphic->screen_height < 1080)
    height = 17;
  else
    height = 18;
  FT_Set_Pixel_Sizes (face, 0, height);
  metrics = &face->size->metrics;
  graphic->char_width = (unsigned int) metrics->max_advance >> 6;
  graphic->char_ascender = (int) metrics->ascender >> 6;
  graphic->char_descender = (int) metrics->descender >> 6;
  graphic->char_height
    = (unsigned int) (graphic->char_ascender - graphic->char_descender);
  jbw_graphic_set_size_request (graphic,
                                ((1 + graphic->nxmax) * JBW_GRAPHIC_N_CHARS +
                                 1) * graphic->char_width,
                                (5 + graphic->nymax) * graphic->char_height);

  // Return the widget pointer
  jbw_graphic_pointer = graphic;
  return graphic;

  // Exit and show an error message on error
#if !HAVE_FREEGLUT
error2:
#endif
  jbw_graphic_destroy ();
error1:
  jb_show_error (jb_error_message);
  jb_free_null ((void **) &jb_error_message);
  return NULL;
}

/**
 * Function to get the graphical size of the current JBWGraphic widget.
 */
void
jbw_graphic_get_display_size (void)
{
  JBWGraphic *graphic = jbw_graphic_pointer;
#if HAVE_GTKWIDGET
  graphic->width = gtk_widget_get_allocated_width (graphic->widget);
  graphic->height = gtk_widget_get_allocated_height (graphic->widget);
#elif HAVE_FREEGLUT
  graphic->width = glutGet (GLUT_WINDOW_WIDTH);
  graphic->height = glutGet (GLUT_WINDOW_HEIGHT);
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
  FT_Face face;
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
      glyph = FT_Get_Char_Index (face, c);
      if (FT_Load_Glyph (face, glyph, FT_LOAD_RENDER))
        continue;
      glTexImage2D (GL_TEXTURE_2D,
                    0,
                    GL_ALPHA,
                    face->glyph->bitmap.width,
                    face->glyph->bitmap.rows,
                    0,
                    GL_ALPHA, GL_UNSIGNED_BYTE, face->glyph->bitmap.buffer);
      x2 = x + face->glyph->bitmap_left * sx;
      y2 = -y - face->glyph->bitmap_top * sy;
      w = face->glyph->bitmap.width * sx;
      h = face->glyph->bitmap.rows * sy;
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
      x += (face->glyph->advance.x >> 6) * sx;
      y += (face->glyph->advance.y >> 6) * sy;
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
      jb_show_error (error_msg);
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
  jb_show_error (error_msg);
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
