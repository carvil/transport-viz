#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtk/gtk.h>

#include "callbacks.h"
#include "interface.h"
#include "support.h"
#include <string.h>
#include <stdlib.h>

#include "y.tab.h"


void imprime_erro(GtkWidget * principal, gchar * msm)
{
	GtkWidget * erro = lookup_widget(principal,"fs_erro");
	
        GtkWidget * label_erro = lookup_widget(erro,"e_label");
      
        gtk_label_set_text(GTK_LABEL(label_erro),msm);
      
        char * res = strtok(msm,"\n");
        int len = 0;
        
        while(res != NULL)
        {
        	if(strlen(res) > len) len = strlen(res);
        	res = strtok(NULL,"\n");
        }
        
        gtk_window_set_resizable (GTK_WINDOW (erro), TRUE);
        gtk_window_resize(GTK_WINDOW(erro),len*8 + 60 ,50);
           

        free(msm);

        gtk_widget_show(erro);
}

int actualizaImage(GtkWidget * principal,char * path)
{	
	GtkWidget * imagem = lookup_widget(principal,"image1");
	
	gtk_image_set_from_file(GTK_IMAGE(imagem),path);

	return EXIT_SUCCESS;
}


void
on_window1_destroy                     (GtkObject       *object,
                                        gpointer         user_data)
{
	gtk_main_quit();
}


void
on_abrir_clicked                       (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget * fs_abrir = lookup_widget(user_data,"fs_abrir");
	GtkWidget * gravar = lookup_widget(user_data,"gravar");
	GtkWidget * abrir = lookup_widget(user_data,"abrir");
	
	gtk_widget_set_sensitive(gravar,FALSE);
	//gtk_widget_set_sensitive(abrir,FALSE);
	gtk_widget_show(fs_abrir);
}


void
on_gravar_activate                     (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget * fs_gravar = lookup_widget(user_data,"fs_gravar");
	GtkWidget * gravar = lookup_widget(user_data,"gravar");
	GtkWidget * abrir = lookup_widget(user_data,"abrir");
	
	gtk_widget_set_sensitive(gravar,FALSE);
	gtk_widget_set_sensitive(abrir,FALSE);
	gtk_widget_show(fs_gravar);
}


void
on_full_toggled                        (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(togglebutton)) )
		 gtk_window_fullscreen(GTK_WINDOW(user_data));
		 
	else
		gtk_window_unfullscreen(GTK_WINDOW(user_data));
}


void
on_sair_clicked                        (GtkButton       *button,
                                        gpointer         user_data)
{
	gtk_main_quit();
}


void
on_a_cancelar_clicked                  (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget * fs_abrir = lookup_widget(user_data,"fs_abrir");
	GtkWidget * gravar = lookup_widget(user_data,"gravar");
	GtkWidget * abrir = lookup_widget(user_data,"abrir");
	
	gtk_widget_set_sensitive(gravar,TRUE);
	gtk_widget_set_sensitive(abrir,TRUE);
	gtk_widget_hide(fs_abrir);
}


void
on_a_abrir_clicked                     (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget * fs_abrir = lookup_widget(user_data,"fs_abrir");
	GtkWidget * gravar = lookup_widget(user_data,"gravar");
	//GtkWidget * abrir = lookup_widget(user_data,"abrir");
	GtkWidget * imagem = lookup_widget(user_data,"image1");

	char *destino = strdup("/tmp/pl_temp.gif"), ** args, *erro;

	char * origem = strdup(gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(fs_abrir)));
	
	int i = 0;
	
	if(origem == NULL)
		gtk_file_chooser_get_current_folder(GTK_FILE_CHOOSER(fs_abrir));
	
	
	//gtk_widget_set_sensitive(abrir,TRUE);
	
	if(origem != NULL) 
	{
		gtk_widget_set_sensitive(gravar,TRUE);
	
		args = (char **)malloc(sizeof(char *)*5);
		
		args[0] = strdup("exec");
		args[1] = strdup("-i");
		args[2] = strdup(origem);
		args[3] = strdup("-o");
		args[4] = destino;
		
		erro = (char *)funcao(5,args);
		
		if(erro == NULL)
		{
			gtk_widget_set_sensitive(gravar,TRUE);

			gtk_image_set_pixel_size(GTK_IMAGE(imagem),100);
			
			gtk_image_set_from_file(GTK_IMAGE(imagem),destino);
		
		}
		else
		{
			imprime_erro(user_data,erro);
			gtk_widget_set_sensitive(gravar,FALSE);
		}
		
		free(args[0]);
		free(args[1]);
		free(args[2]);
		free(args[3]);
		free(args[4]);
		
		free(args);
		

		gtk_widget_hide(fs_abrir);
	}
	
}


void
on_g_cancelar_clicked                  (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget * fs_gravar = lookup_widget(user_data,"fs_gravar");
	GtkWidget * gravar = lookup_widget(user_data,"gravar");
	GtkWidget * abrir = lookup_widget(user_data,"abrir");
	
	gtk_widget_set_sensitive(gravar,TRUE);
	gtk_widget_set_sensitive(abrir,TRUE);
	gtk_widget_hide(fs_gravar);}


void
on_g_gravar_clicked                    (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget * fs_gravar = lookup_widget(user_data,"fs_gravar");
	GtkWidget * gravar = lookup_widget(user_data,"gravar");
	GtkWidget * abrir = lookup_widget(user_data,"abrir");

	char * comando, *comando_aux;

	comando_aux = strdup("cp /tmp/pl_temp.gif ");
	
	char * file = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(fs_gravar));
	
	if(file == NULL)
		gtk_file_chooser_get_current_folder(GTK_FILE_CHOOSER(fs_gravar));
	
	gtk_widget_set_sensitive(gravar,TRUE);
	gtk_widget_set_sensitive(abrir,TRUE);
	
	if(file != NULL) 
	{
		comando = (char *) malloc(strlen(comando_aux) + strlen(file) + 1);

		sprintf(comando,"%s%s",comando_aux, file);

		system(comando);

		if(comando_aux != NULL)
			free(comando_aux);

		if(comando_aux != NULL)
			free(comando);		

		gtk_widget_hide(fs_gravar);
	}
}

void
on_e_ok_clicked                        (GtkButton       *button,
                                        gpointer         user_data)
{
        GtkWidget *label = lookup_widget(user_data,"e_label");
        
        gtk_label_set_text(GTK_LABEL(label),"");
        gtk_widget_hide(user_data);
}
