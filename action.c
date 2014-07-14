//	action.c
//		
//	Copyright 2010 Alexandre Mulatinho <alex@mulatinho.net>
//	
//	This program is free software; you can redistribute it and/or modify
//	it under the terms of the GNU General Public License as published by
//	the Free Software Foundation; either version 2 of the License, or
//	(at your option) any later version.
//	
//	This program is distributed in the hope that it will be useful,
//	but WITHOUT ANY WARRANTY; without even the implied warranty of
//	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	See the
//	GNU General Public License for more details.
//		
//	You should have received a copy of the GNU General Public License
//	along with this program; if not, write to the Free Software
//	Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
//	MA 02110-1301, USA.

#include "main.h"

void sfm_linkbutton(GtkWidget *label, const gchar *uri, gpointer data)
{
	gchar buf[NAME_MAX];

	memset(buf, '\0', sizeof(buf));
	memset(sfm_current_path, '\0', sizeof(sfm_current_path));
	
	fprintf(stdout, "label: '%s'\nuri: '%s'\nsfm_linkbutton\n", label, uri);

	if (!strncmp(uri, "Home", strlen(uri))) {
		memset(sfm_current_path, '\0', sizeof(sfm_current_path)-1);
		snprintf(sfm_current_path, NAME_MAX-1, "%s", getenv("HOME"));
		sfm_scan_directory(1);
	} else if (!strncmp(uri, "Samba", strlen(uri))) {
		fprintf(stdout, "sfm_linkbutton -> samba\n");
	} else if (!strncmp(uri, "SSH", strlen(uri))) {
		fprintf(stdout, "sfm_linkbutton -> ssh\n");
	} else if (!strncmp(uri, "FTP", strlen(uri))) {
		fprintf(stdout, "sfm_linkbutton -> ftp\n");
	}
	
	gtk_entry_set_text(GTK_ENTRY(sfm.path_entry), sfm_current_path);
}

void sfm_linkbutton_network(GtkWidget *label, const gchar *uri, gpointer data)
{
	fprintf(stdout, "sfm_linkbutton_network\n");
}

void sfm_select_menu(GtkWidget *wid, gint x, gint y) 
{
	gchar *text=NULL;
	
	gtk_clist_get_text(GTK_CLIST(wid), x, y, &text);
	
	memset(sfm_current_path, '\0', NAME_MAX);
// DEBUG
	fprintf(stderr, "linha: %d. celula: %s\n", x, g_locale_to_utf8(text,-1,NULL,NULL,NULL));
	
	if (!x) {
		snprintf(sfm_current_path, NAME_MAX-1, "/");
		sfm_scan_directory(1);
	} else if (x == 1) {
		snprintf(sfm_current_path, NAME_MAX-1, "%s", text);
		sfm_scan_directory(1);
	} else if (x == 2) {
		snprintf(sfm_current_path, NAME_MAX-1, "smb://");
		sfm_smb_exec("list smb://");
	} else if (x == 3) {
		snprintf(sfm_current_path, NAME_MAX-1, "%s", text);
	}

	gtk_entry_set_text(GTK_ENTRY(sfm.path_entry), sfm_current_path);
}

void do_select(GtkWidget *wid, gint x, gint y) 
{
	gchar *text=NULL;
	gchar filen[NAME_MAX], filep[NAME_MAX];
	int i;

	memset(filen, '\0', sizeof(filen));
	memset(filep, '\0', sizeof(filep));

	gtk_clist_get_text(GTK_CLIST(wid), x, y, &text);
	fprintf(stderr, "line: %d. cell: %s/%s . %s\n", x, sfm_current_path, text, g_locale_to_utf8(text,-1,NULL,NULL,NULL));

	if (!strncmp(text,"..",2)) {
		strcpy(filep, sfm_current_path);
		
		for (i=strlen(filep); filep[i]!='/'; i--)
			filep[i] = '\0';
		
		if (i)
			filep[i] = '\0';
		
		snprintf(filen, NAME_MAX-1, "%s", filep);
		snprintf(sfm_current_path, NAME_MAX-1, "%s", filen);
		
		fprintf(stderr, "DEBUG: %s . %s\n", sfm_current_path, filen);
	} else {
		snprintf(filen, NAME_MAX, "%s/%s", sfm_current_path, text);
		snprintf(sfm_current_path, NAME_MAX-1, "%s", filen);
		fprintf(stderr, "DEBUG: %s . %s\n", sfm_current_path, filen);
	}
	
	gtk_clist_clear(GTK_CLIST(wid)); usleep(5);
	
	if (wid == sfm.clist)
		list_scanfile(GTK_CLIST(sfm.clist_two), sfm_current_path);
	else
		fprintf(stdout, "clikei.\n");

	text=NULL;
	gtk_widget_show_all(sfm.firstwin);
}

void sfm_run(GtkWidget *wid, gpointer p)
{
}

void sfm_paste_file(GtkWidget *wid, gpointer p)
{
}

void sfm_copy_file(GtkWidget *wid, gpointer p)
{
}

void sfm_open(GtkWidget *wid, gpointer p)
{
	GtkWidget *dialog;
	
	dialog = gtk_file_chooser_dialog_new ("Selecione arquivo.",		 
	wid, GTK_FILE_CHOOSER_ACTION_OPEN,
	GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
	GTK_STOCK_OPEN, GTK_RESPONSE_ACCEPT, NULL);
	 
	if (gtk_dialog_run (GTK_DIALOG (dialog)) == GTK_RESPONSE_ACCEPT)
	{
		char *filename;
	 
		filename = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (dialog));
		//fixme: open file
		g_free (filename);
	}
	 
	gtk_widget_destroy (dialog); 
}

void sfm_execute(GtkWidget *wid, GdkEvent *event, gpointer p)
{
	gchar filen[NAME_MAX], testf[NAME_MAX];
	struct stat obj;
	int i;

	memset(filen, '\0', sizeof(filen));
	memset(testf, '\0', sizeof(testf));
	
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
			snprintf(filen, NAME_MAX-1, "%s", sfm_current_path);
			lstat(filen, &obj);
		} else {
			snprintf(testf, NAME_MAX-1, "%s/%s", sfm_current_path, p);
			lstat(testf, &obj);

			if (S_ISDIR(obj.st_mode))
				snprintf(filen, NAME_MAX-1, "%s/%s", sfm_current_path, p);
			else
				snprintf(filen, NAME_MAX-1, "%s", sfm_current_path);

			snprintf(testf, NAME_MAX-1, "%s/%s", sfm_current_path, p);
			lstat(testf, &obj);
		}

		strcpy(sfm_current_path,filen);
		gtk_entry_set_text(GTK_ENTRY(sfm.path_entry), filen);

		if (S_ISDIR(obj.st_mode))
			sfm_scan_directory(1);
		else 
			sfm_exec_file(testf);
		
		// DEBUG
		fprintf(stderr, "sfm_current_path: %s . %s\n", sfm_current_path, p);

	}
}
