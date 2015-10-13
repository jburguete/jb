#include "jb_win.h"

JBWGraphic *graphic1, *graphic2;

void
draw1 ()
{
  JBFLOAT x[] = { 0., 1. };
  JBFLOAT y[] = { 0., 1. };
  JBWGraphic *graphic;
  printf ("draw1: start\n");
  graphic = (JBWGraphic *) jbw_graphic_queue.head->data;
  printf ("Graphic is %lu\n", (size_t) graphic);
  printf ("drawing lines\n");
  jbw_graphic_draw_lines (graphic, x, y, NULL, NULL, NULL, 2);
  printf ("draw1: end\n");
}

void
draw2 ()
{
  JBFLOAT x[] = { 0., 1. };
  JBFLOAT y[] = { 1., 0. };
  JBWGraphic *graphic;
  printf ("draw2: start\n");
  graphic = (JBWGraphic *) jbw_graphic_queue.head->data;
  printf ("Graphic is %lu\n", (size_t) graphic);
  printf ("drawing lines\n");
  jbw_graphic_draw_lines (graphic, x, y, NULL, NULL, NULL, 2);
  printf ("draw2: end\n");
}

void
cb_open1 ()
{
  JBWGraphic *graphic;
  GList *list;
  list = jbw_graphic_queue.head;
  if (list)
    printf ("Head was %lu %lu\n", (size_t) list, (size_t) list->data);
  else
    printf ("Head was %lu\n", (size_t) list);
  graphic = jbw_graphic_new (NULL, 5, 5, 5, draw1);
  glutPostRedisplay ();
  list = jbw_graphic_queue.head;
  printf ("Head is %lu %lu\n", (size_t) list, (size_t) graphic);
}

void
cb_open2 ()
{
  JBWGraphic *graphic;
  GList *list;
  list = jbw_graphic_queue.head;
  if (list)
    printf ("Head was %lu %lu\n", (size_t) list, (size_t) list->data);
  else
    printf ("Head was %lu\n", (size_t) list);
  graphic = jbw_graphic_new (NULL, 5, 5, 5, draw2);
  glutPostRedisplay ();
  list = jbw_graphic_queue.head;
  printf ("Head is %lu %lu\n", (size_t) list, (size_t) graphic);
}

void
cb_close ()
{
  GList *list;
  list = jbw_graphic_queue.head;
  if (list)
    jbw_graphic_destroy ((JBWGraphic *) list->data);
  list = jbw_graphic_queue.head;
  if (list)
    glutPostRedisplay ();
}

int
main (int argn, char **argc)
{
  GList *list;
  GtkButton *button_open1, *button_open2, *button_close;
  GtkBox *box;
  GtkWindow *window;
  JBWGraphic *graphic;

  jbw_graphic_init (&argn, &argc);

  button_open1 = (GtkButton *) gtk_button_new_with_label ("Draw 1");
  button_open2 = (GtkButton *) gtk_button_new_with_label ("Draw 2");
  button_close = (GtkButton *) gtk_button_new_with_label ("Close");

  g_signal_connect (button_open1, "clicked", cb_open1, NULL);
  g_signal_connect (button_open2, "clicked", cb_open2, NULL);
  g_signal_connect (button_close, "clicked", cb_close, NULL);

  box = (GtkBox *) gtk_hbox_new (0, 0);
  gtk_container_add (GTK_CONTAINER (box), GTK_WIDGET (button_open1));
  gtk_container_add (GTK_CONTAINER (box), GTK_WIDGET (button_open2));
  gtk_container_add (GTK_CONTAINER (box), GTK_WIDGET (button_close));

  window = (GtkWindow *) gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_container_add (GTK_CONTAINER (window), GTK_WIDGET (box));
  gtk_widget_show_all (GTK_WIDGET (window));
  g_signal_connect (window, "destroy", glutLeaveMainLoop, NULL);

  graphic = jbw_graphic_new (NULL, 5, 5, 5, draw1);
  printf ("Graphic is %lu\n", (size_t) graphic);
  list = jbw_graphic_queue.head;
  printf ("Head is %lu %lu\n", (size_t) list, (size_t) list->data);

  glutIdleFunc ((void (*)) gtk_main_iteration);
  printf ("glutMainLoop\n");
  glutMainLoop ();
  printf ("end\n");

  return 0;
}
