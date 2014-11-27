//	main.h
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

#ifndef _SFM_CORE_H_
#define _SFM_CORE_H_ 1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>
#include <pthread.h>
#include <linux/limits.h>
#include <gtk/gtk.h>
#include <dirent.h>

#define PROGNAME "SFM - Simple File Manager"
#define PROGVERSION "1.0.1"
#define SFM_IMAGES "./picz"
#define SFM_CONF "./sfm/sfm.conf" 
#define SFM_CACHE "./sfm/cache" 

#define ICON_SZ_S 16
#define ICON_SZ_M 32
#define ICON_SZ_L 130

typedef struct {
	GtkWidget *firstwin;

	GtkWidget *level1, *level2, *level3, *level4;
	
	GtkWidget *content, *leftview, *fileview;
	
	GtkWidget *menu, *logo, *statusbar;

	GtkWidget *leftview_vbox;

	GtkWidget *path_fixed, *path_entry, *path_label;

	GtkWidget *clist, *clist_two;
	
	GtkWidget *scroll, *viewport, *fixedright;

	GtkItemFactory *item_factory;

	GtkAccelGroup *accel_group;
} sfm_t;

sfm_t sfm;
char sfm_current_path[NAME_MAX];

void sfm_init(void);
void sfm_about(void);
void sfm_execute(GtkWidget *, GdkEvent *, gpointer);
void sfm_path_new(GtkWidget *, GdkEvent *, gpointer);
void sfm_select_item(GtkWidget *, gint, gint); 
void sfm_select_menu(GtkWidget *, gint, gint); 
void sfm_scan_directory(int);
	
void sfm_run(GtkWidget *, gpointer);
void sfm_open(GtkWidget *, gpointer);
void sfm_copy_file(GtkWidget *, gpointer);
void sfm_paste_file(GtkWidget *, gpointer);
void sfm_preferences(GtkWidget *, gpointer);
void sfm_view_list(GtkWidget *, gpointer);
void sfm_view_icons(GtkWidget *, gpointer);
void sfm_view_compact(GtkWidget *, gpointer);

void sfm_link_event(GtkWidget *, const gchar *, gpointer);
void sfm_link_home(GtkWidget *, const gchar *, gpointer);
void sfm_link_network(GtkWidget *, const gchar *, gpointer);

void sfm_handle_leftview(GtkWidget *);
void sfm_warn_message(gchar *, gchar *, gint, gint); 

static GtkItemFactoryEntry menu_items[] = {
	{ "/_Arquivo", NULL, NULL, 0, "<Branch>", 0 },
	{ "/Arquivo/_Abrir", "<control>A", sfm_open, 0, "<StockItem>", GTK_STOCK_OPEN },
	{ "/Arquivo/sep1", NULL, NULL, 0, "<Separator>", 0 },
	{ "/Arquivo/_Sair", "<control>S", gtk_main_quit, 0, "<StockItem>", GTK_STOCK_QUIT },
	{ "/_Editar", NULL, NULL, 0, "<Branch>", 0 },
	{ "/Editar/_Executar", "<control>E", sfm_run, 0, "<StockItem>", GTK_STOCK_EXECUTE },
	{ "/Editar/sep1", NULL, NULL, 0, "<Separator>", 0 },
	{ "/Editar/Copiar", "<control>C", sfm_copy_file, 0, "<StockItem>", GTK_STOCK_COPY },
	{ "/Editar/Colar", "<control>V", sfm_paste_file, 0, "<StockItem>", GTK_STOCK_CUT },
	{ "/Editar/sep1", NULL, NULL, 0, "<Separator>", 0 },
	{ "/Editar/_Preferencias", NULL, sfm_preferences, 0, "<StockItem>", GTK_STOCK_PROPERTIES },
	{ "/_Visao", NULL, NULL, 0, "<Branch>", 0 },
	{ "/Visao/_Lista", "<control>E", sfm_view_list, 0, "<StockItem>", GTK_STOCK_EXECUTE },
	{ "/Visao/_Compactados", "<control>E", sfm_view_compact, 0, "<StockItem>", GTK_STOCK_EXECUTE },
	{ "/Visao/Icones _Grandes", "<control>E", sfm_view_icons, 0, "<StockItem>", GTK_STOCK_ZOOM_100 },
	{ "/_Sobre", NULL, NULL, 0, "<LastBranch>", 0 },
	{ "/Sobre/_SFM", "<control>S", sfm_about, 0, "<StockItem>", GTK_STOCK_DIALOG_INFO },
};
static int menu_items_n = sizeof(menu_items) / sizeof(menu_items[0]);

#endif _SFM_CORE_H_
