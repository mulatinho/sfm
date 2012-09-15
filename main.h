//      main.h
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

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <pthread.h>

#include <gtk/gtk.h>
#include <dirent.h>

#define PROGNAME "SFM - Simple File Manager, v1.0.0"
#define SFM_IMAGES "./picz"
#define SFM_CONF   "/etc/sfm.conf" 
#define FILESIZ 128

void do_copyfile(void);
void do_cutfile(void);
void do_author(void);
void do_execute(GtkWidget *, GdkEvent *, gpointer);
void do_select(GtkWidget *, gint, gint); 
void select_menu(GtkWidget *, gint, gint); 
void icon_scanfile(GtkWidget *, char *, int);
	
static GtkItemFactoryEntry menu_items[] = {
	{ "/_Arquivo",			NULL,         NULL,				0, "<Branch>" , 0 },
	{ "/Arquivo/_Abrir",	"<control>A", NULL,				0, "<StockItem>", GTK_STOCK_OPEN },
	{ "/Arquivo/sep1",		NULL,         NULL,				0, "<Separator>" , 0 },
	{ "/Arquivo/_Sair",		"<control>S", gtk_main_quit,	0, "<StockItem>", GTK_STOCK_QUIT },
	{ "/_Editar",			NULL, 		   NULL,			0, "<Branch>" , 0 },
	{ "/Editar/_Executar",	"<control>E", do_execute,		0, "<StockItem>", GTK_STOCK_EXECUTE },
	{ "/Editar/sep1",		NULL,         NULL,				0, "<Separator>" , 0 },
	{ "/Editar/Copiar",	"<control>C", do_copyfile,		0, "<StockItem>", GTK_STOCK_COPY },
	{ "/Editar/Colar",		"<control>V", do_cutfile,		0, "<StockItem>", GTK_STOCK_CUT },
	{ "/Editar/sep1",		NULL,         NULL,				0, "<Separator>", 0 },
	{ "/Editar/_Preferencias",	NULL, do_execute,		0, "<StockItem>", GTK_STOCK_PROPERTIES },
	{ "/_Visao",			NULL, 		   NULL,			0, "<Branch>", 0 },
	{ "/Visao/_Lista",	"<control>E", do_execute,		0, "<StockItem>", GTK_STOCK_EXECUTE },
	{ "/Visao/_Icones Pequenos",	"<control>E", do_execute,	0, "<StockItem>", GTK_STOCK_EXECUTE },
	{ "/Visao/Icones _Grandes",	"<control>E", do_execute,	0, "<StockItem>", GTK_STOCK_ZOOM_100 },
	{ "/_Sobre",            NULL,         NULL,			0, "<LastBranch>", 0 },
	{ "/Sobre/_SFM", 	"<control>S", do_author,		0, "<StockItem>", GTK_STOCK_DIALOG_INFO },
};

static int nmenu = sizeof(menu_items) / sizeof(menu_items[0]);
extern int alphasort();
char *path;

GtkWidget *win, *hbox;
GtkWidget *clist, *clist_two;
GtkWidget *scrolled, *viewport, *entry1, *fixedright;
void warnm(gchar *, gchar *, gint, gint); 
// void on_executefile(gchar *);
