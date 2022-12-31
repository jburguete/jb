#include "jb_win.h"

#define WITH_GTK 1

#if HAVE_FREEGLUT

JBWGraphic *graphic;

static void
jbw_freeglut_idle (void)
{
  GMainContext *context = g_main_context_default ();
  if (jbw_gdk_gl_context)
    gdk_gl_context_make_current (jbw_gdk_gl_context);
  while (g_main_context_pending (context))
    g_main_context_iteration (context, 0);
  glutSetWindow (graphic->window);
}

static void
jbw_freeglut_draw_resize (int width, int height)
{
  jbw_graphic_resize (width, height);
  jbw_graphic_render ();
}

static void
jbw_freeglut_draw_render (void)
{
  jbw_graphic_render ();
}

#elif HAVE_SDL

JBWGraphic *graphic;

static void
jbw_sdl_draw_resize (int width, int height)
{
  jbw_graphic_resize (width, height);
  jbw_graphic_render ();
}

static void
jbw_sdl_draw_render (void)
{
  jbw_graphic_render ();
}

#elif HAVE_GLFW

JBWGraphic *graphic;

static void
jbw_glfw_window_close (JBWGraphic * graphic)
{
  jbw_graphic_loop_quit ();
  glfwSetWindowShouldClose (graphic->window, 1);
}

#endif

void
draw1 (JBWGraphic * graphic __attribute__((unused)))
{
  const JBFLOAT x[3] = { 0., 1., 3. };
  const JBFLOAT y[3] = { 0., 1., 3. };
  const JBFLOAT yy[3] = { 0., 0.5, 1.5 };
  const JBFLOAT z[3] = { 3., 1., 0. };
  const JBFLOAT zz[3] = { 2., 0.5, 0. };
  jbw_draw_clear (1.f, 1.f, 1.f, 0.f);
  jbw_graphic_draw_lines ((JBFLOAT *) x, (JBFLOAT *) y,
                          (JBFLOAT *) yy, (JBFLOAT *) z, (JBFLOAT *) zz, 2);
  jbw_graphic_draw_logo ();
}

void
draw2 (JBWGraphic * graphic)
{
  const char *str1 = "draw2";
  const char *str2 = "graphic draw 2";
  GLfloat x1, x2, y;
  jbw_draw_clear (0.f, 0.f, 0.f, 0.f);
  x1 = (-1.f * graphic->char_width * strlen (str1)) / graphic->width;
  x2 = (-1.f * graphic->char_width * strlen (str2)) / graphic->width;
  y = (-1.f * graphic->char_height) / graphic->height;
  jbw_graphic_draw_text (str1, x1, -y, jbw_yellow);
  jbw_graphic_draw_text (str2, x2, y, jbw_pink);
}

void
cb_open1 (JBWGraphic * graphic)
{
  jbw_graphic_set_draw (graphic, draw1);
  jbw_graphic_render ();
}

void
cb_open2 (JBWGraphic * graphic)
{
  jbw_graphic_set_draw (graphic, draw2);
  jbw_graphic_render ();
}

int
main (int argn, char **argc)
{
#if HAVE_GTKGLAREA
  JBWGraphic *graphic;
#endif
#if HAVE_SDL
  SDL_Event exit_event[1];
#endif
#if WITH_GTK
#if GTK_MAJOR_VERSION > 3
  const char *close = "close-request";
#else
  const char *close = "delete-event";
#endif
  GtkWindow *window;
  GtkGrid *grid;
  GtkButton *button_open1, *button_open2, *button_close;
#endif
  const char *title;
  const char *version;

  if (!jbw_init (&argn, &argc))
    return 1;

#if HAVE_GTKGLAREA
  title = "GtkGLArea";
#elif HAVE_FREEGLUT
  title = "FreeGLUT";
#elif HAVE_SDL
  title = "SDL";
#elif HAVE_GLFW
  title = "GLFW";
#endif
  graphic = jbw_graphic_new (5, 5, 5, draw1, title);
  jbw_graphic_set_xlabel (graphic, "g");
  jbw_graphic_set_ylabel (graphic, "y");
  jbw_graphic_set_yylabel (graphic, "yy");
  jbw_graphic_set_zlabel (graphic, "z");
  jbw_graphic_set_zzlabel (graphic, "zz");
  jbw_graphic_set_grid (graphic, 1);
  jbw_graphic_set_resize (graphic, 0);
  if (!jbw_graphic_set_logo (LOGO_FILE))
    return 2;
  graphic->xmin = 0.;
  graphic->xmax = 3.;
  graphic->ymin = 0.3;
  graphic->ymax = 2.99;
  graphic->zmin = 0.003;
  graphic->zmax = 2.9999;
#if HAVE_GTKGLAREA
  jbw_graphic_show (graphic);
#elif HAVE_FREEGLUT
  jbw_graphic_init ();
  jbw_graphic_loop_idle = jbw_freeglut_idle;
  jbw_graphic_loop_resize = jbw_freeglut_draw_resize;
  jbw_graphic_loop_render = jbw_freeglut_draw_render;
#elif HAVE_SDL
  exit_event->type = SDL_QUIT;
  jbw_graphic_init ();
  jbw_graphic_loop_resize = jbw_sdl_draw_resize;
  jbw_graphic_loop_render = jbw_sdl_draw_render;
#elif HAVE_GLFW
  jbw_graphic_init ();
  jbw_graphic_loop_render = jbw_graphic_render;
#endif
  if (glewIsSupported ("GL_VERSION_4_0"))
    version = "OpenGL supported version 4.0";
  else if (glewIsSupported ("GL_VERSION_3_0"))
    version = "OpenGL supported version 3.0";
  else if (glewIsSupported ("GL_VERSION_2_1"))
    version = "OpenGL supported version 2.1";
  else if (glewIsSupported ("GL_VERSION_2_0"))
    version = "OpenGL supported version 2.0";
  else if (glewIsSupported ("GL_VERSION_1_3"))
    version = "OpenGL supported version 1.3";
  else
    version = "OpenGL unsupported";
  jbw_show_message ("Info", version, GTK_MESSAGE_INFO);
  printf ("OpenGL version %s\n", glGetString (GL_VERSION));
  printf ("GLSL version %s\n", glGetString (GL_SHADING_LANGUAGE_VERSION));
  if (!graphic->init)
    return 3;

#if WITH_GTK
  button_open1 = (GtkButton *) gtk_button_new_with_label ("Draw 1");
  button_open2 = (GtkButton *) gtk_button_new_with_label ("Draw 2");
  button_close = (GtkButton *) gtk_button_new_with_label ("Close");
  grid = (GtkGrid *) gtk_grid_new ();
  gtk_grid_attach (grid, GTK_WIDGET (button_open1), 0, 0, 1, 1);
  gtk_grid_attach (grid, GTK_WIDGET (button_open2), 1, 0, 1, 1);
  gtk_grid_attach (grid, GTK_WIDGET (button_close), 2, 0, 1, 1);

#if GTK_MAJOR_VERSION > 3
  window = (GtkWindow *) gtk_window_new ();
#else
  window = (GtkWindow *) gtk_window_new (GTK_WINDOW_TOPLEVEL);
#endif
  gtk_window_set_title (window, "test_win");
  gtk_window_set_child (window, GTK_WIDGET (grid));
#if HAVE_GTKGLAREA
  jbw_graphic_loop_pointer = g_main_loop_new (NULL, 0);
  g_signal_connect_swapped (graphic->window, close,
                            (GCallback) g_main_loop_quit,
                            jbw_graphic_loop_pointer);
  g_signal_connect_swapped (button_close, "clicked",
                            (GCallback) g_main_loop_quit,
                            jbw_graphic_loop_pointer);
  g_signal_connect_swapped (window, close, (GCallback) g_main_loop_quit,
                            jbw_graphic_loop_pointer);
#elif HAVE_FREEGLUT
  g_signal_connect (button_close, "clicked", (GCallback) glutLeaveMainLoop,
                    NULL);
  g_signal_connect (window, close, (GCallback) glutLeaveMainLoop, NULL);
#elif HAVE_SDL
  g_signal_connect_swapped (button_close, "clicked",
                            (GCallback) SDL_PushEvent, exit_event);
  g_signal_connect_swapped (window, close, (GCallback) SDL_PushEvent,
                            exit_event);
#elif HAVE_GLFW
  g_signal_connect_swapped (button_close, "clicked",
                            (GCallback) jbw_glfw_window_close, graphic);
  g_signal_connect_swapped (window, close,
                            (GCallback) jbw_glfw_window_close, graphic);
#endif
  g_signal_connect_swapped (button_open1, "clicked", (GCallback) cb_open1,
                            graphic);
  g_signal_connect_swapped (button_open2, "clicked", (GCallback) cb_open2,
                            graphic);
#if GTK_MAJOR_VERSION > 3
  gtk_widget_show (GTK_WIDGET (window));
#else
  gtk_widget_show_all (GTK_WIDGET (window));
#endif
#endif
  jbw_gdk_gl_context = gdk_gl_context_get_current ();

  jbw_graphic_loop ();

  jbw_graphic_destroy ();
#if WITH_GTK
  if (window)
    gtk_window_destroy (window);
#endif

  return 0;
}
