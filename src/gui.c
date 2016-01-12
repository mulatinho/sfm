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

struct sfm_ncurses {
	WINDOW *sfmncmenu;
	WINDOW *sfmnroot;
	WINDOW *sfmnstatus;
	int lines, cols;
};

void sfm_handle_menubar(GtkWidget *menubar)
{
}

void sfm_handle_localdir(GtkWidget *localdir)
{
}

void sfm_handle_statusbar(GtkWidget *menubar)
{
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

	label_two = gtk_label_new("<b><a href=\"Samba\">Samba</a> | <a href=\"SSH\">SSH</a> | <a href=\"FTP\">FTP</a></b>");
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

void sfm_gui(void)
{
	gchar buf[FILENAME_MAX];
	gchar **text = NULL;

	gtk_init(NULL, NULL);

	BUFFER_ZERO(sfm_current_path);
	snprintf(sfm_current_path, FILENAME_MAX-1, "%s", getenv("HOME"));

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

	sfm.clist = gtk_clist_new(1);
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
	
	free(text);

	snprintf(buf, FILENAME_MAX-1, "%s/sfm.png", SFM_IMAGES);
	sfm.logo = gtk_image_new_from_file(buf);
	gtk_box_pack_start(GTK_BOX(sfm.level3), sfm.logo, FALSE, TRUE, 1);

	sfm.level4 = gtk_vbox_new(2, TRUE);
	sfm.statusbar = gtk_statusbar_new();
	gtk_box_pack_start(GTK_BOX(sfm.level4), sfm.statusbar, FALSE, TRUE, 1);
	gtk_box_pack_start(GTK_BOX(sfm.level2), sfm.level4, FALSE, TRUE, 1);

	sfm_scan_directory(1);
	gtk_entry_set_text(GTK_ENTRY(sfm.path_entry), sfm_current_path);

	g_signal_connect(GTK_OBJECT(sfm.clist), "select_iface->lines", GTK_SIGNAL_FUNC(sfm_select_menu), NULL);
	g_signal_connect(GTK_OBJECT(sfm.path_entry), "key-press-event", GTK_SIGNAL_FUNC(sfm_path_new), NULL);
	g_signal_connect(G_OBJECT(sfm.firstwin), "delete_event", gtk_main_quit, NULL);

	gtk_widget_show_all(sfm.firstwin);
	gtk_main();
}

void sfm_list_directory(void);

void sfm_ncurses(void)
{
	int x;
	struct sfm_ncurses *iface = malloc(sizeof(struct sfm_ncurses));
	char root_items[FILENAME_MAX];
	int user_input;
	ITEM **ncmenu_items, *current_item;
	MENU *sfm_menu;

	initscr();
	start_color();	
	noecho();
	cbreak();

	getmaxyx(stdscr, iface->lines, iface->cols);
	keypad(stdscr, TRUE);
	refresh();

	iface->sfmnroot = newwin(iface->lines-6, iface->cols-4, 0, 1);
	snprintf(root_items, sizeof(root_items)-1, "%-40s . %-6s . %-4s . %-3s . %-10s", 
		"FILENAME", "SIZE", "TYPE", "UID", "PERMISSIONS");
	wattron(iface->sfmnroot, A_REVERSE|A_BOLD);
	wprintw(iface->sfmnroot, root_items);
	wattroff(iface->sfmnroot, A_REVERSE|A_BOLD);

	for (x = 2; x < (iface->lines - 6); x++) {
		snprintf(root_items, sizeof(root_items)-1, "Item line %2d                             . 55Kb   . .PDF . 100 . -rw-r--r--", x);
		mvwprintw(iface->sfmnroot, x, 0, root_items);
	}

	wrefresh(iface->sfmnroot);

	iface->sfmncmenu = newwin(3, iface->cols-1, iface->lines-5, 0);
	ncmenu_items = calloc(menu_choices_n + 1, sizeof(ITEM *));
	for (x = 0; x < menu_choices_n; ++x)
		ncmenu_items[x] = new_item(menu_choices[x], menu_choices[x]);
	ncmenu_items[menu_choices_n] = (ITEM *)NULL;

	sfm_menu = new_menu((ITEM **)ncmenu_items);

	keypad(iface->sfmncmenu, TRUE);
	set_menu_win(ncmenu_items, iface->sfmncmenu);
	menu_opts_off(sfm_menu, O_SHOWDESC);
	set_menu_format(sfm_menu, 1, menu_choices_n);
	post_menu(sfm_menu);
	
	box(iface->sfmncmenu, 0, 0);
	wrefresh(iface->sfmncmenu);

	iface->sfmnstatus = newwin(1, iface->cols-1, iface->lines-2, 1);
	wprintw(iface->sfmnstatus, ":. Hello! Welcome to .: %s :. lines:%d, cols:%d", 
		SFM_VSN, iface->lines, iface->cols);
	wrefresh(iface->sfmnstatus); 

	while (1) {
		keypad(stdscr, TRUE);
		user_input = getch();

		switch (user_input) {
		case KEY_LEFT:
			menu_driver(sfm_menu, REQ_LEFT_ITEM);
			break;
		case KEY_RIGHT:
			menu_driver(sfm_menu, REQ_RIGHT_ITEM);
			break;
		case KEY_UP:
			break;
		case KEY_DOWN:
			break;
		case 'Q':
		case 'q':
			wclear(iface->sfmnstatus);
			wprintw(iface->sfmnstatus, ":. Are you sure you want to quit!? [Y/N] ");
			wrefresh(iface->sfmnstatus);
			user_input = wgetch(iface->sfmnstatus);
			switch (user_input) {
			case 'y': case 'Y':
			case 's': case 'S':
				wclear(iface->sfmnstatus);
				wprintw(iface->sfmnstatus, ":. Thanks for using SFM! :) Quitting...");
				wrefresh(iface->sfmnstatus);
				sleep(1);
				delwin(iface->sfmnroot);
				goto sfm_ncurses_exit;
			default:
				break;
			}
		}

		wclear(iface->sfmnstatus);
		wprintw(iface->sfmnstatus, ":. status: %d", user_input);
		wrefresh(iface->sfmnstatus);
	} 

	sfm_ncurses_exit:
	unpost_menu(sfm_menu);
	free_menu(sfm_menu);
	for(x = 0; x < menu_choices_n; ++x)
		free_item(ncmenu_items[x]);
	free(iface);
	endwin();
}
