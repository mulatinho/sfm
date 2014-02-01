//      main.c
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

int main(int argc, char **argv)
{
	gchar buf[NAME_MAX], **text;

	gtk_init(&argc, &argv);

	memset(sfm_current_path, '\0', sizeof(sfm_current_path));
	snprintf(sfm_current_path, NAME_MAX-1, "%s", getenv("HOME"));

    /* principal window */
	sfm.firstwin = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(sfm.firstwin), PROGNAME);
	gtk_window_set_default_size(GTK_WINDOW(sfm.firstwin), 700, 460);

	sfm.level1 = gtk_vbox_new(FALSE, 2);
	gtk_container_set_border_width(GTK_CONTAINER(sfm.level1), 4);
	gtk_container_add(GTK_CONTAINER(sfm.firstwin), sfm.level1);

	/* Menu */
	sfm.accel_group  = gtk_accel_group_new();
	gtk_window_add_accel_group(GTK_WINDOW(sfm.firstwin), sfm.accel_group);

	sfm.item_factory = gtk_item_factory_new(GTK_TYPE_MENU_BAR, "<main>", sfm.accel_group);
	gtk_item_factory_create_items(sfm.item_factory, menu_items_n, menu_items, NULL);

	sfm.menu = gtk_item_factory_get_widget(sfm.item_factory, "<main>");
	gtk_box_pack_start(GTK_BOX(sfm.level1), sfm.menu, FALSE, TRUE, 0);

    /* path entry, user input */
	sfm.path_fixed = gtk_fixed_new();
	
	sfm.path_label = gtk_label_new("Caminho: ");
	gtk_fixed_put(GTK_FIXED(sfm.path_fixed), sfm.path_label, 5, 10);

	sfm.path_entry = gtk_entry_new();
	gtk_widget_set_usize(GTK_WIDGET(sfm.path_entry), 605, 20);
	gtk_fixed_put(GTK_FIXED(sfm.path_fixed), sfm.path_entry, 75, 8);

	gtk_box_pack_start(GTK_BOX(sfm.level1), sfm.path_fixed, FALSE, TRUE, 1);



	sfm.level2 = gtk_vbox_new(FALSE, 4);
	gtk_container_add(GTK_CONTAINER(sfm.level1), sfm.level2);

	sfm.leftview = gtk_hbox_new(FALSE, 4);
	gtk_container_add(GTK_CONTAINER(sfm.level2), sfm.leftview);

	sfm.level3 = gtk_vbox_new(FALSE, 4);
	gtk_box_pack_start(GTK_BOX(sfm.leftview), sfm.level3, FALSE, TRUE, 1);
	
	sfm.clist = gtk_clist_new(1);
	gtk_clist_set_shadow_type(GTK_CLIST(sfm.clist), GTK_SHADOW_OUT);

	text = malloc(NAME_MAX * 5); // NAME_MAX chars, 5 lines
	
	snprintf(buf, NAME_MAX-1, "raiz: /\0");
	text[0] = (char*)buf;
	gtk_clist_append(GTK_CLIST(sfm.clist), (char**)&text[0]);
	
	text[1] = getenv("HOME");
	snprintf(buf, NAME_MAX-1, "home: %s\0", text[1]);
	gtk_clist_append(GTK_CLIST(sfm.clist), (char**)&text[1]);
	
	snprintf(buf, NAME_MAX-1, "smb://host/dir\0");
	text[2] = (char*)buf;
	gtk_clist_append(GTK_CLIST(sfm.clist), (char**)&text[2]);
	
	snprintf(buf, NAME_MAX-1, "ssh://user@host\0");
	text[3] = (char*)buf;
	gtk_clist_append(GTK_CLIST(sfm.clist), (char**)&text[3]);
	
	gtk_widget_set_usize(GTK_WIDGET(sfm.clist), 200, 70);
	gtk_box_pack_start(GTK_BOX(sfm.level3), sfm.clist, FALSE, TRUE, 1);
	
	free(text);

	snprintf(buf, NAME_MAX-1, "%s/sfm.png\0", SFM_IMAGES);
	sfm.logo = gtk_image_new_from_file(buf);
	gtk_box_pack_start(GTK_BOX(sfm.level3), sfm.logo, FALSE, TRUE, 1);

	sfm_scan_directory(1);
	gtk_entry_set_text(GTK_ENTRY(sfm.path_entry), sfm_current_path);

	g_signal_connect(GTK_OBJECT(sfm.clist), "select_row", GTK_SIGNAL_FUNC(sfm_select_menu), NULL);
	g_signal_connect(GTK_OBJECT(sfm.path_entry), "key-press-event", GTK_SIGNAL_FUNC(sfm_path_new), NULL);
	g_signal_connect(G_OBJECT(sfm.firstwin), "delete_event", gtk_main_quit, NULL);

	gtk_widget_show_all(sfm.firstwin);
	gtk_main();
	
	return 0;
}
