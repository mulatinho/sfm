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
#include <ncurses.h>

#define PROGNAME "SFM - (A Lightweight) Simple File Manager"
#define PROGVERSION "0.01"
#define PROGAUTHOR "Alexandre Mulatinho <alex at mulatinho dot net>"
#define SFM_VERSION PROGNAME " v" PROGVERSION "\nWritten by " PROGAUTHOR "\n"

/* This three definitions will be deprecated, the idea is to user sqlite */
#define SFM_IMAGES "./picz"
#define SFM_CONF "./sfm/sfm.conf" 
#define SFM_CACHE "./sfm/cache" 

#define ICON_SZ_S 16
#define ICON_SZ_M 32
#define ICON_SZ_L 64 

#define NFILEMAXSZ 512

#define BUFFER_ZERO(buffer) memset(buffer, '\0', sizeof(buffer))

typedef struct {
	GtkWidget *firstwin;

	GtkWidget *level1, *level2, *level3, *level4;
	
	GtkWidget *content, *leftview, *fileview;
	
	GtkWidget *menu, *logo, *statusbar;

	GtkWidget *leftview_vbox;

	GtkWidget *path_fixed, *path_entry, *path_label;

	GtkWidget *shlabel, *clist, *clist_two;
	
	GtkWidget *scroll, *viewport, *fixedright;

	GtkItemFactory *item_factory;

	GtkAccelGroup *accel_group;
} sfm_t;

enum {
	S_FILENMTR,
	S_FILESIZE,
	S_FILETYPE,
	S_FILEMODF,
	S_FILEPERM,
	S_TRITEMS,
} sfm_tree_items;

enum {
	S_FILENMIC,
	S_FILENAME,
	S_FILEPICT,
	S_FILEDIRT,
	S_ICITEMS
} sfm_icon_items;

/* Global Variables */
sfm_t sfm;
char sfm_current_path[FILENAME_MAX];

/* Some important functions */
void sfm_init(void);
void sfm_about(void);

void sfm_handle_leftview(GtkWidget *leftview);

void sfm_execute(GtkWidget *, GdkEventButton *, gpointer);
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

void sfm_link_event(GtkWidget *label, const gchar *uri, gpointer data);
void sfm_link_home(GtkWidget *, const gchar *, gpointer);
void sfm_link_network(GtkWidget *, const gchar *, gpointer);

void sfm_handle_leftview(GtkWidget *);
void sfm_warn_message(gchar *, gchar *, gint, gint); 

static GtkItemFactoryEntry menu_items[] = {
	{ "/_File", NULL, NULL, 0, "<Branch>", 0 },
	{ "/File/_Open", "<control>A", sfm_open, 0, "<StockItem>", GTK_STOCK_OPEN },
	{ "/File/sep1", NULL, NULL, 0, "<Separator>", 0 },
	{ "/File/_Exit", "<control>S", gtk_main_quit, 0, "<StockItem>", GTK_STOCK_QUIT },
	{ "/_Edit", NULL, NULL, 0, "<Branch>", 0 },
	{ "/Edit/_Execute", "<control>E", sfm_run, 0, "<StockItem>", GTK_STOCK_EXECUTE },
	{ "/Edit/sep1", NULL, NULL, 0, "<Separator>", 0 },
	{ "/Edit/Copy", "<control>C", sfm_copy_file, 0, "<StockItem>", GTK_STOCK_COPY },
	{ "/Edit/Cut", "<control>V", sfm_paste_file, 0, "<StockItem>", GTK_STOCK_CUT },
	{ "/Edit/sep1", NULL, NULL, 0, "<Separator>", 0 },
	{ "/Edit/_Preferences", NULL, sfm_preferences, 0, "<StockItem>", GTK_STOCK_PROPERTIES },
	{ "/_View", NULL, NULL, 0, "<Branch>", 0 },
	{ "/View/_List", "<control>E", sfm_view_list, 0, "<StockItem>", GTK_STOCK_EXECUTE },
	{ "/View/_Compact", "<control>E", sfm_view_compact, 0, "<StockItem>", GTK_STOCK_EXECUTE },
	{ "/View/Big _Icons", "<control>E", sfm_view_icons, 0, "<StockItem>", GTK_STOCK_ZOOM_100 },
	{ "/_About", NULL, NULL, 0, "<LastBranch>", 0 },
	{ "/About/_SFM", "<control>S", sfm_about, 0, "<StockItem>", GTK_STOCK_DIALOG_INFO },
};
static int menu_items_n = sizeof(menu_items) / sizeof(menu_items[0]);

#endif _SFM_CORE_H_
