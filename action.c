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

void select_menu(GtkWidget *wid, gint x, gint y) 
{
	gchar *text=NULL;
	char *p=NULL;

	gtk_clist_get_text(GTK_CLIST(wid), x, y, &text);
// DEBUG
	fprintf(stderr, "linha: %d. celula: %s\n", x, g_locale_to_utf8(text,-1,NULL,NULL,NULL));

	if (!x) {
		memset(path, 0, strlen(path));
		strcpy(path, "/");

		icon_scanfile(hbox, path, 1);
	} else if (x==1) {
		memset(path, 0, strlen(path));
		p = getenv("HOME");

		strcpy(path, "/home/alexandre");
		icon_scanfile(hbox, path, 1);
	} else if (x==2) {
	} else if (x==3) {
	}

	gtk_entry_set_text(GTK_ENTRY(entry1), path);
}
void do_select(GtkWidget *wid, gint x, gint y) 
{
	gchar *text=NULL;
	gchar filen[256], filep[strlen(path)];
	int i;

	gtk_clist_get_text(GTK_CLIST(wid), x, y, &text);
	fprintf(stderr, "linha: %d. celula: %s/%s -> %s\n", x, path, text, g_locale_to_utf8(text,-1,NULL,NULL,NULL));

	if (!strncmp(text,"..",2)) {
		strcpy(filep, path);
		fprintf(stderr, "DEBUG: %s -> %s\n", path, filep);
		
		for (i=strlen(filep); filep[i]!='/'; i--)
			filep[i] = '\0';
		
		if (i)
			filep[i] = '\0';
		
		snprintf(filen, 255, "%s\0", filep);
		path = filen;
		
		fprintf(stderr, "DEBUG: %s -> %s\n", path, filen);
	} else {
		fprintf(stderr, "DEBUG: %s -> %s\n", path, text);
		snprintf(filen, 255, "%s/%s\0", path, text);
		path = filen;
		fprintf(stderr, "DEBUG: %s -> %s\n", path, filen);
	}
	
	gtk_clist_clear(GTK_CLIST(wid)); usleep(5);
	
	if (wid == clist)
		list_scanfile(GTK_CLIST(clist_two), path);
	else
		fprintf(stdout, "clikei.\n");

	text=NULL;
	gtk_widget_show_all(win);
}

void do_execute(GtkWidget *wid, GdkEvent *event, gpointer p)
{
	gchar filen[256], testf[256];
	struct stat obj;
	int i;

	fprintf(stderr, "==> %d\n", event->button);

	if (event->type==5) {
		if (!strcmp(p, "..")) {
			for (i=strlen(path);i!=0;i--) {
				if (path[i] == '/') {
					path[i] = '\0';
					break;
				}
				path[i] = '\0';
			}
			snprintf(filen, 255, "%s\0", path);
			lstat(filen, &obj);
		} else {
			snprintf(testf, 255, "%s/%s\0", path, p);
			lstat(testf, &obj);

			if (S_ISDIR(obj.st_mode))
				snprintf(filen, 255, "%s/%s\0", path, p);
			else
				snprintf(filen, 255, "%s\0", path);

			snprintf(testf, 255, "%s/%s\0", path, p);
			lstat(testf, &obj);
		}

		strcpy(path,filen);
		gtk_entry_set_text(GTK_ENTRY(entry1), filen);

		if (S_ISDIR(obj.st_mode))
			icon_scanfile(hbox, path, 1);
		else 
			on_executefile(testf);
		
		// DEBUG
		// fprintf(stderr, "path: %s -> %s\n", path, p);

	}
}

void do_author(void)
{
	warnm("About",
	
	"Este gerenciador de arquivos foi desenvolvido em C embaixo da\n"
	"biblioteca GTK e com o objetivo de rodar em maquinas de baixo\n"
	"desempenho, implementado junto com o protocolo SMB/NFS/FTP/SSH.\n\n"
	
	"Alexandre Mulatinho <alex@mulatinho.net> 2010.\n\n"
	
	"Thanks to:\n"
	"Alexandre Alux pelos icones.\n"
	
	, 550, 120);
}

void do_cutfile(void)
{
	fprintf(stderr, ".");
}

void do_copyfile(void)
{
	fprintf(stderr, ".");
}
