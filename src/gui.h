#ifndef _SFM_GUI_H_
#define _SFM_GUI_H_

#include "main.h"
#include "views.h"

typedef struct
{
	GtkWidget *firstwin;

	GtkWidget *level1, *level2, *level3, *level4;

	GtkWidget *content, *leftview, *fileview;

	GtkWidget *menu, *logo;

	GtkWidget *leftview_vbox;

	GtkWidget *path_fixed, *path_entry, *path_label;

	GtkWidget *shlabel;

	GtkWidget *scroll, *icon_view;

	GtkWidget *statusbar;

	GtkCList *clist, clist_two;

	GtkItemFactory *item_factory;

	GtkAccelGroup *accel_group;
} sfm_t;

extern sfm_t sfm;

int sfm_smb_exec(char *);
void do_select(GtkWidget *, gint, gint);
void sfm_callback_execute(GtkIconView *, GtkTreePath *, gpointer);
void sfm_copy_file(GtkWidget *, gpointer);
void sfm_create_shortcut(GtkWidget *, gchar *);
void sfm_create_shortcut(GtkWidget *, gchar *);
void sfm_create_shortcut(GtkWidget *, gchar *);
void sfm_gui_list_directory(int);
void sfm_link_event(GtkWidget *, const gchar *, gpointer);
void sfm_link_network(GtkWidget *, const gchar *, gpointer);
void sfm_open(GtkWidget *, gpointer);
void sfm_paste_file(GtkWidget *, gpointer);
void sfm_run(GtkWidget *, gpointer);
void sfm_select_menu(GtkWidget *, gint, gint);

enum
{
	SFM_ITEM_PATH,
	SFM_ITEM_NAME,
	SFM_ITEM_IMAGE,
	SFM_ITEM_TYPE,
	SFM_ITEM_SIZE,
	SFM_ITEM_TOTAL
};

static GtkItemFactoryEntry guimenu_items[] = {
	{"/_File", NULL, NULL, 0, "<Branch>", 0},
	{"/File/_Open", "<control>A", sfm_open, 0, "<StockItem>", GTK_STOCK_OPEN},
	{"/File/sep1", NULL, NULL, 0, "<Separator>", 0},
	{"/File/_Exit", "<control>S", gtk_main_quit, 0, "<StockItem>", GTK_STOCK_QUIT},
	{"/_Edit", NULL, NULL, 0, "<Branch>", 0},
	{"/Edit/_Execute", "<control>E", sfm_run, 0, "<StockItem>", GTK_STOCK_EXECUTE},
	{"/Edit/sep1", NULL, NULL, 0, "<Separator>", 0},
	{"/Edit/Copy", "<control>C", sfm_copy_file, 0, "<StockItem>", GTK_STOCK_COPY},
	{"/Edit/Cut", "<control>V", sfm_paste_file, 0, "<StockItem>", GTK_STOCK_CUT},
	{"/Edit/sep1", NULL, NULL, 0, "<Separator>", 0},
	{"/Edit/_Preferences", NULL, sfm_preferences, 0, "<StockItem>", GTK_STOCK_PROPERTIES},
	{"/_View", NULL, NULL, 0, "<Branch>", 0},
	{"/View/_List", "<control>E", sfm_view_list, 0, "<StockItem>", GTK_STOCK_EXECUTE},
	{"/View/_Compact", "<control>E", sfm_view_compact, 0, "<StockItem>", GTK_STOCK_EXECUTE},
	{"/View/Big _Icons", "<control>E", sfm_view_icons, 0, "<StockItem>", GTK_STOCK_ZOOM_100},
	{"/_About", NULL, NULL, 0, "<LastBranch>", 0},
	{"/About/_SFM", "<control>S", sfm_about, 0, "<StockItem>", GTK_STOCK_DIALOG_INFO},
};
static int guimenu_items_n = sizeof(guimenu_items) / sizeof(guimenu_items[0]);

#endif
