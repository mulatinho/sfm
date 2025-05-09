// main.c
//
// Copyright 2010 Alexandre Mulatinho <alex@mulatinho.net>
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
// MA 02110-1301, USA.

#include "gui.h"

sfm_t sfm_gui;

void sfm_handle_menubar(GtkWidget *menubar)
{
}

void sfm_handle_localdir(GtkWidget *localdir)
{
}

void sfm_handle_statusbar(GtkWidget *menubar)
{
}

void sfm_run(GtkWidget *wid, gpointer data)
{
}

void sfm_paste_file(GtkWidget *wid, gpointer data)
{
}

void sfm_copy_file(GtkWidget *wid, gpointer data)
{
}

void sfm_link_event(GtkWidget *label, const gchar *uri, gpointer data)
{
	fprintf(stdout, "%s:%d  -- uri: '%s'\nsfm_link_event\n", __FILE__, __LINE__, uri);

	if (!strncmp(uri, "Home", strlen(uri)))
	{
		char *env_home = getenv("HOME");
		sfm_set_current_path(env_home);
	}
	else if (!strncmp(uri, "Samba", strlen(uri)))
	{
		fprintf(stdout, "sfm_linkbutton -> samba\n");
	}
	else if (!strncmp(uri, "SSH", strlen(uri)))
	{
		fprintf(stdout, "sfm_linkbutton -> ssh\n");
	}
	else if (!strncmp(uri, "FTP", strlen(uri)))
	{
		fprintf(stdout, "sfm_linkbutton -> ftp\n");
	}

	gtk_entry_set_text(GTK_ENTRY(sfm_gui.path_entry), sfm_get_current_path());
}

void sfm_link_network(GtkWidget *label, const gchar *uri, gpointer data)
{
	fprintf(stdout, "sfm_linkbutton_network\n");
}

void sfm_select_menu(GtkWidget *wid, gint option, gint y)
{
	gchar *text = NULL;
	char current_path[FILENAME_MAX];

	gtk_clist_get_text(GTK_CLIST(wid), option, y, &text);

	BUFFER_ZERO(current_path);
	fprintf(stderr, "%s:%d -- line: %d. cell: %s\n", __FILE__, __LINE__, option, g_locale_to_utf8(text, -1, NULL, NULL, NULL));

	switch (option)
	{
	case 0:
		snprintf(current_path, strlen(SFM_PREFIX_ROOT), "%s", SFM_PREFIX_ROOT);
		break;
	case 1:
	case 3:
		snprintf(current_path, strlen(text), "%s", text);
		break;
	case 2:
		snprintf(current_path, strlen(SFM_PREFIX_SMB), "%s", SFM_PREFIX_SMB);
		sfm_smb_exec("list smb://");
		break;
	default:
		break;
	}

	if (option != 2) 
		sfm_set_current_path(current_path);
	gtk_entry_set_text(GTK_ENTRY(sfm_gui.path_entry), sfm_get_current_path());
}

/* void do_select(GtkWidget *wid, gint x, gint y)
{
	gchar *text = NULL;
	gchar filen[FILENAME_MAX], filep[FILENAME_MAX];
	int i;

	BUFFER_ZERO(filen);
	BUFFER_ZERO(filep);

	gtk_clist_get_text(GTK_CLIST(wid), x, y, &text);
	fprintf(stderr, "line: %d. cell: %s/%s . %s\n", x, sfm_get_current_path(), text, g_locale_to_utf8(text, -1, NULL, NULL, NULL));

	if (!strncmp(text, "..", 2))
	{
		strcpy(filep, sfm_get_current_path());

		snprintf(filen, strlen(filep), "%s", dirname(filep));
		fprintf(stdout, "%s\n", filen);
		sfm_set_current_path(filen);

		fprintf(stderr, "DEBUG: %s . %s\n", sfm_get_current_path(), filen);
	}

	gtk_clist_clear(GTK_CLIST(wid));
	usleep(5);

	fprintf(stdout, "clikei.\n");

	text = NULL;
	gtk_widget_show_all(sfm_gui.firstwin);
}
*/
void sfm_open(GtkWidget *wid, gpointer p)
{
	GtkWidget *dialog;

	dialog = gtk_file_chooser_dialog_new("Selecione arquivo.",
										 GTK_WINDOW(wid), GTK_FILE_CHOOSER_ACTION_OPEN, GTK_STOCK_CANCEL,
										 GTK_RESPONSE_CANCEL, GTK_STOCK_OPEN, GTK_RESPONSE_ACCEPT, NULL);

	if (gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_ACCEPT)
	{
		char *filename;

		filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));
		// fixme: open file
		g_free(filename);
	}

	gtk_widget_destroy(dialog);
}

void sfm_handle_leftview(GtkWidget *leftview)
{
	GtkWidget *label, *label_two, *label_sc;

	label = gtk_label_new("<b></b>");
	gtk_label_set_use_markup(GTK_LABEL(label), TRUE);
	gtk_box_pack_start(GTK_BOX(leftview), label, FALSE, TRUE, 1);

	label = gtk_label_new("<b><a href=\"Home\">Home Directory</a></b>");
	gtk_label_set_use_markup(GTK_LABEL(label), TRUE);
	gtk_box_pack_start(GTK_BOX(leftview), label, FALSE, TRUE, 1);

	g_signal_connect(GTK_OBJECT(label), "activate-link", G_CALLBACK(sfm_link_event), NULL);

	// FIXME add personal menus here.

	label_two = gtk_label_new("<b><a href=\"Samba\">Samba</a> | <a href=\"SSH\">SSH</a> | <a href=\"FTP\">FTP</a> | <a href=\"LDAP\">LDAP</a></b>");
	gtk_label_set_use_markup(GTK_LABEL(label_two), TRUE);
	gtk_box_pack_start(GTK_BOX(leftview), label_two, FALSE, TRUE, 1);

	g_signal_connect(GTK_OBJECT(label_two), "activate-link", G_CALLBACK(sfm_link_event), NULL);

	if (sfm_has_shortcuts())
	{
		label_sc = gtk_label_new("<b>Shortcuts</b>");
		gtk_label_set_use_markup(GTK_LABEL(label_sc), TRUE);
		gtk_box_pack_start(GTK_BOX(leftview), label_sc, FALSE, TRUE, 1);
	}
}

void sfm_handle_rightview(GtkWidget *rightview)
{
}

void sfm_gui_list_directory(int hidden)
{
	GtkListStore *store = NULL;
	GtkTreeIter iter;
	GError *gerror = NULL;
	mfile *file_list = NULL;

	GdkPixbuf *pixbuf_directory = gdk_pixbuf_new_from_file("picz/sfmfolder.png", &gerror);
	GdkPixbuf *pixbuf_file = gdk_pixbuf_new_from_file("picz/sfmfile.png", &gerror);

	if (sfm_gui.scroll)
		gtk_widget_destroy(sfm_gui.scroll);

	if (sfm_gui.icon_view)
		gtk_widget_destroy(sfm_gui.icon_view);

	if (sfm_gui.fileview)
		gtk_widget_destroy(sfm_gui.fileview);

	sfm_gui.fileview = gtk_hbox_new(FALSE, 4);
	gtk_widget_reparent(sfm_gui.fileview, sfm_gui.leftview);
	gtk_container_add(GTK_CONTAINER(sfm_gui.leftview), sfm_gui.fileview);

	sfm_gui.scroll = gtk_scrolled_window_new(NULL, NULL);
	gtk_scrolled_window_set_shadow_type(GTK_SCROLLED_WINDOW(sfm_gui.scroll),
										GTK_SHADOW_ETCHED_IN);
	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(sfm_gui.scroll),
								   GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);

	gtk_box_pack_start(GTK_BOX(sfm_gui.fileview), sfm_gui.scroll, TRUE, TRUE, 2);

	store = gtk_list_store_new(SFM_ITEM_TOTAL, G_TYPE_STRING, G_TYPE_STRING,
							   GDK_TYPE_PIXBUF, G_TYPE_STRING, G_TYPE_INT);
	gtk_list_store_clear(store);

	file_list = list;
	while (file_list != NULL)
	{
		GdkPixbuf *pixbuf = NULL;
		
		if (S_ISDIR(file_list->fstat.st_mode))
			pixbuf = pixbuf_directory;
		else
			pixbuf = pixbuf_file; 

		gtk_list_store_append(store, &iter);
		gtk_list_store_set(store, &iter, SFM_ITEM_PATH, sfm_get_current_path(),
						   SFM_ITEM_NAME, file_list->fname, SFM_ITEM_IMAGE, pixbuf,
						   SFM_ITEM_TYPE, file_list->fname + (strlen(file_list->fname) - 3),
						   SFM_ITEM_SIZE, file_list->fstat.st_size, -1);

		file_list = (mfile *)file_list->next;
		g_object_unref(pixbuf);
		pixbuf = NULL;
	}

	sfm_gui.icon_view = gtk_icon_view_new_with_model(GTK_TREE_MODEL(store));
	gtk_icon_view_set_selection_mode(GTK_ICON_VIEW(sfm_gui.icon_view),
									 GTK_SELECTION_MULTIPLE);

	gtk_icon_view_set_text_column(GTK_ICON_VIEW(sfm_gui.icon_view), SFM_ITEM_NAME);
	gtk_icon_view_set_pixbuf_column(GTK_ICON_VIEW(sfm_gui.icon_view), SFM_ITEM_IMAGE);
	gtk_icon_view_set_item_width(GTK_ICON_VIEW(sfm_gui.icon_view), 96);

	gtk_container_add(GTK_CONTAINER(sfm_gui.scroll), sfm_gui.icon_view);

	g_signal_connect(G_OBJECT(sfm_gui.icon_view), "item-activated", G_CALLBACK(sfm_callback_execute), store);

	gtk_widget_show_all(sfm_gui.fileview);

	gtk_widget_show_all(sfm_gui.firstwin);

	return;
}

void sfm_callback_execute(GtkIconView *iconview,
						  GtkTreePath *treepath, gpointer user_data)
{
	GtkListStore *store;
	GtkTreeModel *model;
	GtkTreeIter iter;
	gchar *item;
	struct stat obj;

	store = GTK_LIST_STORE(user_data);

	gtk_tree_model_get_iter(GTK_TREE_MODEL(store), &iter, treepath);
	gtk_tree_model_get(GTK_TREE_MODEL(store), &iter, SFM_ITEM_NAME, &item, -1);

	fprintf(stdout, "-=> %s\n", item);
	
	stat(item, &obj);
	if (S_ISDIR(obj.st_mode)) {
		char directory[FILENAME_MAX];
		BUFFER_ZERO(directory);
		if (!strncmp(item, "..", 2)) 
			snprintf(directory, FILENAME_MAX - 1, "%s", dirname(sfm_get_current_path()));
		else if (!strncmp(item, ".", 1)) {
			item[strlen(item)-1] = '\0';
			snprintf(directory, FILENAME_MAX - 1, "%s/%s", sfm_get_current_path(), item);
		} else
			snprintf(directory, FILENAME_MAX - 1, "%s/%s", sfm_get_current_path(), item);
		
		fprintf(stdout, "-=> %s:%d -> directory: %s\n", __FILE__, __LINE__, directory);
		sfm_set_current_path(directory);
	} else 
		sfm_exec_file(item);
}

void sfm_callback_change_dir(GtkWidget *widget, GtkWidget *entry)
{
	const gchar *directory = gtk_entry_get_text(GTK_ENTRY(entry));
	sfm_set_current_path(directory);
	sfm_gui_list_directory(SFM_FILES_HIDDEN);
	sfm_debug(directory);
}

gboolean sfm_callback_exit(GtkWidget *widget, GdkEvent *event)
{
	sfm_mfile_free();
	gtk_widget_destroy(sfm_gui.firstwin);
	sfm_gui.firstwin = NULL;
	gtk_main_quit();
}

void sfm_gui_start(struct context *ctx)
{
	gchar buf[FILENAME_MAX];
	gchar **text = NULL;

	gtk_init(NULL, NULL);

	/* principal window */
	sfm_gui.firstwin = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(sfm_gui.firstwin), PROGNAME);
	gtk_window_set_default_size(GTK_WINDOW(sfm_gui.firstwin), 800, 600);

	sfm_gui.level1 = gtk_vbox_new(FALSE, 2);
	gtk_container_set_border_width(GTK_CONTAINER(sfm_gui.level1), 4);
	gtk_container_add(GTK_CONTAINER(sfm_gui.firstwin), sfm_gui.level1);

	/* Menu */
	sfm_gui.accel_group = gtk_accel_group_new();
	gtk_window_add_accel_group(GTK_WINDOW(sfm_gui.firstwin), sfm_gui.accel_group);

	sfm_gui.item_factory = gtk_item_factory_new(GTK_TYPE_MENU_BAR, "<main>", sfm_gui.accel_group);
	gtk_item_factory_create_items(sfm_gui.item_factory, guimenu_items_n, guimenu_items, NULL);

	sfm_gui.menu = gtk_item_factory_get_widget(sfm_gui.item_factory, "<main>");
	gtk_box_pack_start(GTK_BOX(sfm_gui.level1), sfm_gui.menu, FALSE, TRUE, 0);

	/* path entry, user input */
	sfm_gui.path_fixed = gtk_hbox_new(FALSE, 2);

	sfm_gui.path_label = gtk_label_new("Path: ");
	gtk_box_pack_start(GTK_BOX(sfm_gui.path_fixed), sfm_gui.path_label, FALSE, TRUE, 1);

	sfm_gui.path_entry = gtk_entry_new();
	gtk_box_pack_start(GTK_BOX(sfm_gui.path_fixed), sfm_gui.path_entry, TRUE, TRUE, 1);

	gtk_box_pack_start(GTK_BOX(sfm_gui.level1), sfm_gui.path_fixed, FALSE, TRUE, 1);

	sfm_gui.level2 = gtk_vbox_new(FALSE, 4);
	gtk_container_add(GTK_CONTAINER(sfm_gui.level1), sfm_gui.level2);

	sfm_gui.leftview = gtk_hbox_new(FALSE, 4);
	gtk_container_add(GTK_CONTAINER(sfm_gui.level2), sfm_gui.leftview);

	sfm_gui.level3 = gtk_vbox_new(FALSE, 4);
	gtk_box_pack_start(GTK_BOX(sfm_gui.leftview), sfm_gui.level3, FALSE, TRUE, 1);

	sfm_handle_leftview(sfm_gui.level3);

	sfm_gui.shlabel = gtk_label_new("<b></b>");
	gtk_label_set_use_markup(GTK_LABEL(sfm_gui.shlabel), TRUE);
	gtk_box_pack_start(GTK_BOX(sfm_gui.level3), sfm_gui.shlabel, FALSE, FALSE, 1);

	sfm_gui.shlabel = gtk_label_new("<b>Network List</b>");
	gtk_label_set_use_markup(GTK_LABEL(sfm_gui.shlabel), TRUE);
	gtk_box_pack_start(GTK_BOX(sfm_gui.level3), sfm_gui.shlabel, FALSE, FALSE, 1);

	/*	sfm_gui.clist = gtk_clist_new(1);
 gtk_clist_set_shadow_type(GTK_CLIST(sfm_gui.clist), GTK_SHADOW_OUT);

 text = malloc(FILENAME_MAX * 5); // FILENAME_MAX chars, 5 iface->lines

 snprintf(buf, FILENAME_MAX-1, "raiz: /");
 text[0] = (char*)buf;
 gtk_clist_append(GTK_CLIST(sfm_gui.clist), (char**)&text[0]);

 text[1] = getenv("HOME");
 snprintf(buf, FILENAME_MAX-1, "home: %s", text[1]);
 gtk_clist_append(GTK_CLIST(sfm_gui.clist), (char**)&text[1]);

 snprintf(buf, FILENAME_MAX-1, "smb://host/dir");
 text[2] = (char*)buf;
 gtk_clist_append(GTK_CLIST(sfm_gui.clist), (char**)&text[2]);

 snprintf(buf, FILENAME_MAX-1, "ssh://user@host");
 text[3] = (char*)buf;
 gtk_clist_append(GTK_CLIST(sfm_gui.clist), (char**)&text[3]);

 gtk_widget_set_usize(GTK_WIDGET(sfm_gui.clist), 200, 70);
 gtk_box_pack_start(GTK_BOX(sfm_gui.level3), sfm_gui.clist, FALSE, TRUE, 1);

 free(text); */

	snprintf(buf, FILENAME_MAX - 1, "%s/sfm_gui.png", SFM_IMAGES);
	sfm_gui.logo = gtk_image_new_from_file(buf);
	gtk_box_pack_start(GTK_BOX(sfm_gui.level3), sfm_gui.logo, FALSE, TRUE, 1);

	sfm_gui.level4 = gtk_vbox_new(2, TRUE);
	sfm_gui.statusbar = gtk_statusbar_new();
	gtk_box_pack_start(GTK_BOX(sfm_gui.level4), sfm_gui.statusbar, FALSE, TRUE, 1);
	gtk_box_pack_start(GTK_BOX(sfm_gui.level2), sfm_gui.level4, FALSE, TRUE, 1);

	sfm_gui_list_directory(SFM_FILES_HIDDEN);
	gtk_entry_set_text(GTK_ENTRY(sfm_gui.path_entry), sfm_get_current_path());

	//	g_signal_connect(GTK_OBJECT(sfm_gui.clist), "select", GTK_SIGNAL_FUNC(sfm_callback_select_menu), NULL);
	g_signal_connect(G_OBJECT(sfm_gui.firstwin), "delete_event", G_CALLBACK(sfm_callback_exit), NULL);
	g_signal_connect(G_OBJECT(sfm_gui.path_entry), "activate", G_CALLBACK(sfm_callback_change_dir), sfm_gui.path_entry);

	gtk_widget_show_all(sfm_gui.firstwin);

	gtk_main();
}
