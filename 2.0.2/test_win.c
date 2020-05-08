#include "jb_win.h"

void
draw1 (JBWGraphic * graphic)
{
  const JBFLOAT x[3] = { 0., 1., 3. };
  const JBFLOAT y[3] = { 0., 1., 3. };
  const JBFLOAT yy[3] = { 0., 0.5, 1.5 };
  const JBFLOAT z[3] = { 3., 1., 0. };
  const JBFLOAT zz[3] = { 2., 0.5, 0. };
  jbw_draw_clear (1.f, 1.f, 1.f, 0.f);
  jbw_graphic_draw_lines (graphic, (JBFLOAT *) x, (JBFLOAT *) y, (JBFLOAT *) yy,
                          (JBFLOAT *) z, (JBFLOAT *) zz, 2);
  jbw_graphic_draw_logo (graphic);
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
  jbw_graphic_draw_text (graphic, str1, x1, -y, jbw_yellow);
  jbw_graphic_draw_text (graphic, str2, x2, y, jbw_pink);
}

void
cb_open1 (JBWGraphic * graphic)
{
  jbw_graphic_set_draw (graphic, draw1);
  gtk_widget_queue_draw (GTK_WIDGET (graphic->widget));
}

void
cb_open2 (JBWGraphic * graphic)
{
  jbw_graphic_set_draw (graphic, draw2);
  gtk_widget_queue_draw (GTK_WIDGET (graphic->widget));
}

int
main (int argn, char **argc)
{
  GtkButton *button_open1, *button_open2, *button_close;
  GtkGrid *grid;
  GtkWindow *window;
  JBWGraphic *graphic;

  jbw_init (&argn, &argc);

  graphic = jbw_graphic_new (5, 5, 5, draw1, 1);
  jbw_graphic_set_title (graphic, "Test");
  jbw_graphic_set_xlabel (graphic, "g");
  jbw_graphic_set_ylabel (graphic, "y");
  jbw_graphic_set_yylabel (graphic, "yy");
  jbw_graphic_set_zlabel (graphic, "z");
  jbw_graphic_set_zzlabel (graphic, "zz");
  jbw_graphic_set_grid (graphic, 1);
  jbw_graphic_set_resize (graphic, 0);
  jbw_graphic_set_logo (graphic, "check_error.png");
  jbw_graphic_set_logo (graphic, "test.png");
  graphic->xmin = 0.;
  graphic->xmax = 3.;
  graphic->ymin = 0.3;
  graphic->ymax = 2.99;
  graphic->zmin = 0.003;
  graphic->zmax = 2.9999;
  jbw_graphic_show (graphic);
  g_signal_connect (graphic->window, "delete-event", (GCallback) gtk_main_quit,
                    NULL);

  button_open1 = (GtkButton *) gtk_button_new_with_label ("Draw 1");
  g_signal_connect_swapped (button_open1, "clicked", (GCallback) cb_open1,
                            graphic);
  button_open2 = (GtkButton *) gtk_button_new_with_label ("Draw 2");
  g_signal_connect_swapped (button_open2, "clicked", (GCallback) cb_open2,
                            graphic);
  button_close = (GtkButton *) gtk_button_new_with_label ("Close");
  g_signal_connect (button_close, "clicked", (GCallback) gtk_main_quit, NULL);

  grid = (GtkGrid *) gtk_grid_new ();
  gtk_grid_attach (grid, GTK_WIDGET (button_open1), 0, 0, 1, 1);
  gtk_grid_attach (grid, GTK_WIDGET (button_open2), 1, 0, 1, 1);
  gtk_grid_attach (grid, GTK_WIDGET (button_close), 2, 0, 1, 1);

  window = (GtkWindow *) gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_container_add (GTK_CONTAINER (window), GTK_WIDGET (grid));
  gtk_widget_show_all (GTK_WIDGET (window));
  g_signal_connect (window, "delete-event", (GCallback) gtk_main_quit, NULL);

  gtk_main ();

  jbw_graphic_destroy (graphic);
  gtk_widget_destroy (GTK_WIDGET (window));

  return 0;
}
