#include "main.h"

#ifndef _SFM_GUI_H_
#define _SFM_GUI_H_

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

#endif
