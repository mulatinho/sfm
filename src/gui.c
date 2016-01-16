//		main.c
//		
//		Copyright 2010 Alexandre Mulatinho <alex@mulatinho.net>
//		
//		This program is free software; you can redistribute it and/or modify
//		it under the terms of the GNU General Public License as published by
//		the Free Software Foundation; either version 2 of the License, or
//		(at your option) any later version.
//		
//		This program is distributed in the hope that it will be useful,
//		but WITHOUT ANY WARRANTY; without even the implied warranty of
//		MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	See the
//		GNU General Public License for more details.
//		
//		You should have received a copy of the GNU General Public License
//		along with this program; if not, write to the Free Software
//		Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
//		MA 02110-1301, USA.

#include "main.h"

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
	gchar buf[NAME_MAX];

	memset(buf, '\0', sizeof(buf));
	memset(sfm_current_path, '\0', sizeof(sfm_current_path));
	
	fprintf(stdout, "label: '%s'\nuri: '%s'\nsfm_linkbutton\n", label, uri);

	if (!strncmp(uri, "Home", strlen(uri))) {
		char *env_home = getenv("HOME");
		sfm_set_current_path(env_home);
	} else if (!strncmp(uri, "Samba", strlen(uri))) {
		fprintf(stdout, "sfm_linkbutton -> samba\n");
	} else if (!strncmp(uri, "SSH", strlen(uri))) {
		fprintf(stdout, "sfm_linkbutton -> ssh\n");
	} else if (!strncmp(uri, "FTP", strlen(uri))) {
		fprintf(stdout, "sfm_linkbutton -> ftp\n");
	}
	
	gtk_entry_set_text(GTK_ENTRY(sfm.path_entry), sfm_current_path);
}

void sfm_link_network(GtkWidget *label, const gchar *uri, gpointer data)
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
		//sfm_scan_directory(1);
	} else if (x == 1) {
		snprintf(sfm_current_path, NAME_MAX-1, "%s", text);
		//sfm_scan_directory(1);
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
	
	fprintf(stdout, "clikei.\n");

	text=NULL;
	gtk_widget_show_all(sfm.firstwin);
}

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
		//fixme: open file
		g_free(filename);
	}
	 
	gtk_widget_destroy(dialog); 
}

void sfm_handle_leftview(GtkWidget *leftview)
{
	GtkWidget *label, *label_two, *label_sc;

	label = gtk_label_new("<b></b>");
	gtk_label_set_use_markup (GTK_LABEL (label), TRUE);
	gtk_box_pack_start(GTK_BOX(leftview), label, FALSE, TRUE, 1);

	label = gtk_label_new("<b><a href=\"Home\">Home Directory</a></b>");
	gtk_label_set_use_markup (GTK_LABEL (label), TRUE);
	gtk_box_pack_start(GTK_BOX(leftview), label, FALSE, TRUE, 1);

	g_signal_connect(GTK_OBJECT(label), "activate-link", G_CALLBACK(sfm_link_event), NULL);

	// FIXME add personal menus here.

	label_two = gtk_label_new("<b><a href=\"Samba\">Samba</a> | <a href=\"SSH\">SSH</a> | <a href=\"FTP\">FTP</a> | <a href=\"LDAP\">LDAP</a></b>");
	gtk_label_set_use_markup (GTK_LABEL (label_two), TRUE);
	gtk_box_pack_start(GTK_BOX(leftview), label_two, FALSE, TRUE, 1);

	g_signal_connect(GTK_OBJECT(label_two), "activate-link", G_CALLBACK(sfm_link_event), NULL);

	if (sfm_has_shortcuts()) {
		label_sc = gtk_label_new("<b>Shortcuts</b>");
		gtk_label_set_use_markup (GTK_LABEL (label_sc), TRUE);
		gtk_box_pack_start(GTK_BOX(leftview), label_sc, FALSE, TRUE, 1);
	}
}

void sfm_handle_rightview(GtkWidget *rightview)
{
}

void sfm_gui_list_directory(int hidden)
{
	GtkListStore *store = NULL;
	GdkPixbuf *pixbuf = NULL;
	GtkTreeIter iter;
	mfile *n = NULL;

	if (sfm.scroll)
		gtk_widget_destroy(sfm.scroll);

	if (sfm.icon_view)
		gtk_widget_destroy(sfm.icon_view);

	if (sfm.fileview)
		gtk_widget_destroy(sfm.fileview);
		
	sfm.fileview = gtk_hbox_new(FALSE, 4);
	gtk_widget_reparent(sfm.fileview, sfm.leftview);
	gtk_container_add(GTK_CONTAINER(sfm.leftview), sfm.fileview);

	sfm.scroll = gtk_scrolled_window_new(NULL, NULL);
	gtk_scrolled_window_set_shadow_type(GTK_SCROLLED_WINDOW(sfm.scroll), 
		GTK_SHADOW_ETCHED_IN);
	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(sfm.scroll),
		GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);

	gtk_box_pack_start(GTK_BOX(sfm.fileview), sfm.scroll, TRUE, TRUE, 2);

	store = gtk_list_store_new(ITEM_TOTAL, G_TYPE_STRING, G_TYPE_STRING, 
		GDK_TYPE_PIXBUF, G_TYPE_STRING, G_TYPE_INT);
	gtk_list_store_clear(store);

	sfm_mfile_free();
	sfm_scan_directory(hidden);

	n = list; GError *gerror;
	while (n != NULL) {
		if (S_ISDIR(n->fstat.st_mode))
			pixbuf = gdk_pixbuf_new_from_file("picz/sfmfolder.png", &gerror);
		else
			pixbuf = gdk_pixbuf_new_from_file("picz/sfmfile.png", &gerror);

		gtk_list_store_append(store, &iter);
		gtk_list_store_set(store, &iter, ITEM_PATH, sfm_current_path, 
			ITEM_NAME, n->fname, ITEM_IMAGE, pixbuf, 
			ITEM_TYPE, n->fname+(strlen(n->fname)-3), 
			ITEM_SIZE, n->fstat.st_size, -1);

		fprintf(stdout, ".:- %s\n", n->fname);
		n = (mfile*)n->next;
		g_object_unref(pixbuf);
		pixbuf = NULL;
	}

	sfm.icon_view = gtk_icon_view_new_with_model(GTK_TREE_MODEL(store));
	gtk_icon_view_set_selection_mode(GTK_ICON_VIEW(sfm.icon_view), 
		GTK_SELECTION_MULTIPLE);

	gtk_icon_view_set_text_column(GTK_ICON_VIEW(sfm.icon_view), ITEM_NAME);
	gtk_icon_view_set_pixbuf_column(GTK_ICON_VIEW(sfm.icon_view), ITEM_IMAGE);
	gtk_icon_view_set_item_width(GTK_ICON_VIEW(sfm.icon_view), 96);

	gtk_container_add(GTK_CONTAINER(sfm.scroll), sfm.icon_view);

	g_signal_connect(G_OBJECT(sfm.icon_view), "item-activated", G_CALLBACK(sfm_callback_execute), store);

	gtk_widget_show_all(sfm.fileview);

	gtk_widget_show_all(sfm.firstwin);

	return;
}

void sfm_callback_execute(GtkIconView *iconview, 
	GtkTreePath *treepath, 	gpointer user_data)
{
	GtkListStore *store;
	GtkTreeModel *model;
	GtkTreeIter iter;
	gchar *item;

	store = GTK_LIST_STORE(user_data);

	gtk_tree_model_get_iter(GTK_TREE_MODEL(store), &iter, treepath);
	gtk_tree_model_get(GTK_TREE_MODEL(store), &iter, ITEM_NAME, &item, -1);

	fprintf(stdout, "-=> %s\n", item);
}

void sfm_callback_change_dir(GtkWidget *widget, GtkWidget *entry)
{
	const gchar *directory = gtk_entry_get_text(GTK_ENTRY(entry));
	sfm_set_current_path(directory);
	sfm_gui_list_directory(FILES_HIDDEN);
}

gboolean sfm_callback_exit(GtkWidget *widget, GdkEvent *event)
{
	sfm_mfile_free();
	gtk_widget_destroy(sfm.firstwin);
	sfm.firstwin = NULL;
	gtk_main_quit();
}

void sfm_gui(void)
{
	gchar buf[FILENAME_MAX];
	gchar **text = NULL;

	gtk_init(NULL, NULL);

	/* principal window */
	sfm.firstwin = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(sfm.firstwin), PROGNAME);
	gtk_window_set_default_size(GTK_WINDOW(sfm.firstwin), 800, 600);

	sfm.level1 = gtk_vbox_new(FALSE, 2);
	gtk_container_set_border_width(GTK_CONTAINER(sfm.level1), 4);
	gtk_container_add(GTK_CONTAINER(sfm.firstwin), sfm.level1);

	/* Menu */
	sfm.accel_group	= gtk_accel_group_new();
	gtk_window_add_accel_group(GTK_WINDOW(sfm.firstwin), sfm.accel_group);

	sfm.item_factory = gtk_item_factory_new(GTK_TYPE_MENU_BAR, "<main>", sfm.accel_group);
	gtk_item_factory_create_items(sfm.item_factory, guimenu_items_n, guimenu_items, NULL);

	sfm.menu = gtk_item_factory_get_widget(sfm.item_factory, "<main>");
	gtk_box_pack_start(GTK_BOX(sfm.level1), sfm.menu, FALSE, TRUE, 0);

	/* path entry, user input */
	sfm.path_fixed = gtk_hbox_new(FALSE, 2);
	
	sfm.path_label = gtk_label_new("Path: ");
	gtk_box_pack_start(GTK_BOX(sfm.path_fixed), sfm.path_label, FALSE, TRUE, 1);

	sfm.path_entry = gtk_entry_new();
	gtk_box_pack_start(GTK_BOX(sfm.path_fixed), sfm.path_entry, TRUE, TRUE, 1);

	gtk_box_pack_start(GTK_BOX(sfm.level1), sfm.path_fixed, FALSE, TRUE, 1);

	sfm.level2 = gtk_vbox_new(FALSE, 4);
	gtk_container_add(GTK_CONTAINER(sfm.level1), sfm.level2);

	sfm.leftview = gtk_hbox_new(FALSE, 4);
	gtk_container_add(GTK_CONTAINER(sfm.level2), sfm.leftview);

	sfm.level3 = gtk_vbox_new(FALSE, 4);
	gtk_box_pack_start(GTK_BOX(sfm.leftview), sfm.level3, FALSE, TRUE, 1);
	
	sfm_handle_leftview(sfm.level3);
	
	sfm.shlabel = gtk_label_new("<b></b>");
	gtk_label_set_use_markup (GTK_LABEL (sfm.shlabel), TRUE);
	gtk_box_pack_start(GTK_BOX(sfm.level3), sfm.shlabel, FALSE, FALSE, 1);

	sfm.shlabel = gtk_label_new("<b>Network List</b>");
	gtk_label_set_use_markup (GTK_LABEL (sfm.shlabel), TRUE);
	gtk_box_pack_start(GTK_BOX(sfm.level3), sfm.shlabel, FALSE, FALSE, 1);

/*	sfm.clist = gtk_clist_new(1);
	gtk_clist_set_shadow_type(GTK_CLIST(sfm.clist), GTK_SHADOW_OUT);

	text = malloc(FILENAME_MAX * 5); // FILENAME_MAX chars, 5 iface->lines
	
	snprintf(buf, FILENAME_MAX-1, "raiz: /");
	text[0] = (char*)buf;
	gtk_clist_append(GTK_CLIST(sfm.clist), (char**)&text[0]);
	
	text[1] = getenv("HOME");
	snprintf(buf, FILENAME_MAX-1, "home: %s", text[1]);
	gtk_clist_append(GTK_CLIST(sfm.clist), (char**)&text[1]);
	
	snprintf(buf, FILENAME_MAX-1, "smb://host/dir");
	text[2] = (char*)buf;
	gtk_clist_append(GTK_CLIST(sfm.clist), (char**)&text[2]);
	
	snprintf(buf, FILENAME_MAX-1, "ssh://user@host");
	text[3] = (char*)buf;
	gtk_clist_append(GTK_CLIST(sfm.clist), (char**)&text[3]);
	
	gtk_widget_set_usize(GTK_WIDGET(sfm.clist), 200, 70);
	gtk_box_pack_start(GTK_BOX(sfm.level3), sfm.clist, FALSE, TRUE, 1);
	
	free(text); */

	snprintf(buf, FILENAME_MAX-1, "%s/sfm.png", SFM_IMAGES);
	sfm.logo = gtk_image_new_from_file(buf);
	gtk_box_pack_start(GTK_BOX(sfm.level3), sfm.logo, FALSE, TRUE, 1);

	sfm.level4 = gtk_vbox_new(2, TRUE);
	sfm.statusbar = gtk_statusbar_new();
	gtk_box_pack_start(GTK_BOX(sfm.level4), sfm.statusbar, FALSE, TRUE, 1);
	gtk_box_pack_start(GTK_BOX(sfm.level2), sfm.level4, FALSE, TRUE, 1);

	sfm_gui_list_directory(FILES_HIDDEN);
	gtk_entry_set_text(GTK_ENTRY(sfm.path_entry), sfm_current_path);

//	g_signal_connect(GTK_OBJECT(sfm.clist), "select", GTK_SIGNAL_FUNC(sfm_callback_select_menu), NULL);
	g_signal_connect(G_OBJECT(sfm.firstwin), "delete_event", G_CALLBACK(sfm_callback_exit), NULL);
	g_signal_connect(G_OBJECT(sfm.path_entry), "activate", G_CALLBACK(sfm_callback_change_dir), sfm.path_entry);

	gtk_widget_show_all(sfm.firstwin);

	gtk_main();
}
