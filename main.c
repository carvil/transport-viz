/*
 * Initial main.c file generated by Glade. Edit as required.
 * Glade will not overwrite this file.
 */

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtk/gtk.h>

#include "interface.h"
#include "support.h"

int
main (int argc, char *argv[])
{
	if(argc == 1)
	{
		  GtkWidget *window1;

		/*#ifdef ENABLE_NLS
		  bindtextdomain (GETTEXT_PACKAGE, PACKAGE_LOCALE_DIR);
		  bind_textdomain_codeset (GETTEXT_PACKAGE, "UTF-8");
		  textdomain (GETTEXT_PACKAGE);
		#endif
		*/
		  gtk_set_locale ();
		  gtk_init (&argc, &argv);

		//  add_pixmap_directory (PACKAGE_DATA_DIR "/" PACKAGE "/pixmaps");
		  add_pixmap_directory ("/home/vilhena/MCC/PL/trabalhos/trabalho1/pixmaps");
  		  add_pixmap_directory ("/home/biosystem/Desktop/trabalho1/pixmaps");

		  /*
		   * The following code was added by Glade to create one of each component
		   * (except popup menus), just so that you see something after building
		   * the project. Delete any components that you don't want shown initially.
		   */
		  window1 = create_window1 ();
		  gtk_widget_show (window1);

		  gtk_main ();
	}
	else 
	{
		char * temp = (char *)funcao(argc,argv);
		
		if(temp != NULL)
			printf("%s\n",temp);
			
		free(temp);
	}
  return 0;
}

