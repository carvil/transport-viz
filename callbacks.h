#include <gtk/gtk.h>


void
on_window1_destroy                     (GtkObject       *object,
                                        gpointer         user_data);

void
on_abrir_clicked                       (GtkButton       *button,
                                        gpointer         user_data);

void
on_gravar_activate                     (GtkButton       *button,
                                        gpointer         user_data);

void
on_full_toggled                        (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_sair_clicked                        (GtkButton       *button,
                                        gpointer         user_data);

void
on_a_cancelar_clicked                  (GtkButton       *button,
                                        gpointer         user_data);

void
on_a_abrir_clicked                     (GtkButton       *button,
                                        gpointer         user_data);

void
on_g_cancelar_clicked                  (GtkButton       *button,
                                        gpointer         user_data);

void
on_g_gravar_clicked                    (GtkButton       *button,
                                        gpointer         user_data);
void
on_e_ok_clicked                        (GtkButton       *button,
                                        gpointer         user_data);
