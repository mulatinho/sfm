#include "main.h"

void sfm_view_list(GtkWidget *wid, gpointer p)
{
}

void sfm_view_compact(GtkWidget *wid, gpointer p)
{
}

void sfm_view_icons(GtkWidget *wid, gpointer p)
{
}

void sfm_preferences(GtkWidget *wid, gpointer p)
{
}

void sfm_warn_message(gchar *title, gchar *message, gint width, gint height)
{
	GtkWidget *dialog, *label; 
	 
	dialog = gtk_dialog_new_with_buttons(title, GTK_WINDOW(sfm.firstwin), 
	GTK_DIALOG_DESTROY_WITH_PARENT, GTK_STOCK_OK, GTK_RESPONSE_NONE, NULL);
	gtk_widget_set_usize(dialog, width, height);
	 
	label = gtk_label_new(message);
		 
	g_signal_connect_swapped(dialog, "response", 
		G_CALLBACK(gtk_widget_destroy), dialog);

	gtk_container_add(GTK_CONTAINER(GTK_DIALOG(dialog)->vbox), label); 
	gtk_widget_show_all(dialog);
}

void sfm_about(void)
{
	GtkWidget *about;
	GdkPixbuf *sfm_pic;
	GError *err_pix = NULL;
	const gchar *license = {
		"This program is free software; you can redistribute it and/or modify\n" \
		"it under the terms of the GNU General Public License as published by\n" \
		"the Free Software Foundation; either version 2 of the License.\n" \
		"\n" \
		"This program is distributed in the hope that it will be useful,\n" \
		"but WITHOUT ANY WARRANTY; without even the implied warranty of\n" \
		"MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	See the\n" \
		"GNU General Public License for more details.\n" \
		"\n" \
		"You should have received a copy of the GNU General Public License\n" \
		"along with this program; if not, write to the Free Software\n" \
		"Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,\n" \
		"MA 02110-1301, USA."
	};
	
	const gchar *sfm_authors[] = {
		"Alexandre Mulatinho <alex@mulatinho.net>",
		"Alexandre Alux <alexandre@aluxnet.com.br>",
		NULL
	};
	
	about = gtk_about_dialog_new();
	
	sfm_pic = gdk_pixbuf_new_from_file(SFM_IMAGES "/sfm.png", &err_pix);
	if (err_pix == NULL)
		gtk_about_dialog_set_logo(GTK_ABOUT_DIALOG(about), sfm_pic);
	else {
		fprintf(stderr, "err: %s\n", err_pix->message);
		g_error_free(err_pix);
	}

	gtk_about_dialog_set_name(GTK_ABOUT_DIALOG(about), PROGNAME);
	gtk_about_dialog_set_version(GTK_ABOUT_DIALOG(about), PROGVERSION);
	gtk_about_dialog_set_copyright(GTK_ABOUT_DIALOG(about), "(C) 2010 Alexandre Mulatinho");
	gtk_about_dialog_set_comments(GTK_ABOUT_DIALOG(about), "A simple file manager to lightweight window managers.");
	gtk_about_dialog_set_license(GTK_ABOUT_DIALOG(about), license);
	gtk_about_dialog_set_website(GTK_ABOUT_DIALOG(about), "http//github.com/mulatinho/sfm");
	
	gtk_about_dialog_set_authors(GTK_ABOUT_DIALOG(about), sfm_authors);
	
	gtk_dialog_run(GTK_DIALOG(about));
	gtk_widget_destroy(about);
}
