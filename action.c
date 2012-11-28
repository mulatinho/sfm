//      action.c
//      
//      Copyright 2010 Alexandre Mulatinho <alex@mulatinho.net>
//      
//      This program is free software; you can redistribute it and/or modify
//      it under the terms of the GNU General Public License as published by
//      the Free Software Foundation; either version 2 of the License, or
//      (at your option) any later version.
//      
//      This program is distributed in the hope that it will be useful,
//      but WITHOUT ANY WARRANTY; without even the implied warranty of
//      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//      GNU General Public License for more details.
//      
//      You should have received a copy of the GNU General Public License
//      along with this program; if not, write to the Free Software
//      Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
//      MA 02110-1301, USA.

#include "main.h"

void sfm_select_menu(GtkWidget *wid, gint x, gint y) 
{
	gchar *text=NULL;
	char *homeDir;

	gtk_clist_get_text(GTK_CLIST(wid), x, y, &text);
// DEBUG
	fprintf(stderr, "linha: %d. celula: %s\n", x, g_locale_to_utf8(text,-1,NULL,NULL,NULL));

	memset(sfm_current_path, 0, strlen(sfm_current_path));
	if (!x) {
		strcpy(sfm_current_path, "/");
		sfm_scan_directory(hbox, sfm_current_path, 1);
	} else if (x==1) {
		homeDir = getenv("HOME");
		fprintf(stdout, "home: %s\n", homeDir);
		fprintf(stdout, "debug-> &p = %x | &p = %s | p = %s | *p = %s\n", &homeDir, &homeDir, homeDir, *homeDir);

		sfm_scan_directory(hbox, sfm_current_path, 1);
	} else if (x==2) {
		// SAMBA IS HERE
	}

	gtk_entry_set_text(GTK_ENTRY(entry1), sfm_current_path);
}
void do_select(GtkWidget *wid, gint x, gint y) 
{
	gchar *text=NULL;
	gchar filen[256], filep[strlen(sfm_current_path)];
	int i;

	gtk_clist_get_text(GTK_CLIST(wid), x, y, &text);
	fprintf(stderr, "line: %d. cell: %s/%s -> %s\n", x, sfm_current_path, text, g_locale_to_utf8(text,-1,NULL,NULL,NULL));

	if (!strncmp(text,"..",2)) {
		strcpy(filep, sfm_current_path);
		fprintf(stderr, "DEBUG: %s -> %s\n", sfm_current_path, filep);
		
		for (i=strlen(filep); filep[i]!='/'; i--)
			filep[i] = '\0';
		
		if (i)
			filep[i] = '\0';
		
		snprintf(filen, 255, "%s\0", filep);
		sfm_current_path = filen;
		
		fprintf(stderr, "DEBUG: %s -> %s\n", sfm_current_path, filen);
	} else {
		fprintf(stderr, "DEBUG: %s -> %s\n", sfm_current_path, text);
		snprintf(filen, 255, "%s/%s\0", sfm_current_path, text);
		sfm_current_path = filen;
		fprintf(stderr, "DEBUG: %s -> %s\n", sfm_current_path, filen);
	}
	
	gtk_clist_clear(GTK_CLIST(wid)); usleep(5);
	
	if (wid == clist)
		list_scanfile(GTK_CLIST(clist_two), sfm_current_path);
	else
		fprintf(stdout, "clikei.\n");

	text=NULL;
	gtk_widget_show_all(sfm_win);
}

void sfm_execute(GtkWidget *wid, GdkEvent *event, gpointer p)
{
	gchar filen[256], testf[256];
	struct stat obj;
	int i;

	fprintf(stderr, "==> %d\n", event->type);

	if (event->type==5) {
		if (!strcmp(p, "..")) {
			for (i=strlen(sfm_current_path);i!=0;i--) {
				if (sfm_current_path[i] == '/') {
					sfm_current_path[i] = '\0';
					break;
				}
				sfm_current_path[i] = '\0';
			}
			snprintf(filen, 255, "%s\0", sfm_current_path);
			lstat(filen, &obj);
		} else {
			snprintf(testf, 255, "%s/%s\0", sfm_current_path, p);
			lstat(testf, &obj);

			if (S_ISDIR(obj.st_mode))
				snprintf(filen, 255, "%s/%s\0", sfm_current_path, p);
			else
				snprintf(filen, 255, "%s\0", sfm_current_path);

			snprintf(testf, 255, "%s/%s\0", sfm_current_path, p);
			lstat(testf, &obj);
		}

		strcpy(sfm_current_path,filen);
		gtk_entry_set_text(GTK_ENTRY(entry1), filen);

		if (S_ISDIR(obj.st_mode))
			sfm_scan_directory(hbox, sfm_current_path, 1);
		else 
			on_executefile(testf);
		
		// DEBUG
		fprintf(stderr, "sfm_current_path: %s -> %s\n", sfm_current_path, p);

	}
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
		"MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n" \
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

void sfm_cut_file(void)
{
	fprintf(stderr, ".");
}

void sfm_copy_file(void)
{
	fprintf(stderr, ".");
}
