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
	GtkWidget *frame, *vbox_submenu;
	GtkWidget *menu, *iconwin, *vbox, *fixed, *vbox_header, *vbox_content;
	GtkWidget *image, *label1, *button;
	GtkItemFactory *item_factory;
	GtkBox *box;
	GtkAccelGroup *accel_group;
	gchar buf[NAME_MAX], **text;

	gtk_init(&argc, &argv);
	memset(sfm_current_path, '\0', sizeof(sfm_current_path));
	snprintf(sfm_current_path, NAME_MAX-1, "%s", getenv("HOME"));

	/* Criação da Janela */
	sfm_win = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(sfm_win), PROGNAME);
	gtk_window_set_default_size(GTK_WINDOW(sfm_win), 800, 460);

	/* Adicionando um nível vertical */
	vbox_header = gtk_vbox_new(FALSE, 2);
	gtk_container_set_border_width(GTK_CONTAINER(vbox_header), 4);
	gtk_container_add(GTK_CONTAINER(sfm_win), vbox_header);

	/* Menu */
	accel_group = gtk_accel_group_new();
	item_factory = gtk_item_factory_new(GTK_TYPE_MENU_BAR, "<main>", accel_group);
	gtk_item_factory_create_items(item_factory, nmenu, menu_items, NULL);
	gtk_window_add_accel_group(GTK_WINDOW(sfm_win), accel_group);
	menu = gtk_item_factory_get_widget(item_factory, "<main>");
	gtk_box_pack_start(GTK_BOX(vbox_header), menu, FALSE, TRUE, 0);

	/* Localização */
	fixed = gtk_fixed_new();
//	gtk_box_pack_start(GTK_BOX(hbox), fixed, FALSE, TRUE, 1);
	gtk_box_pack_start(GTK_BOX(vbox_header), fixed, FALSE, TRUE, 1);
	
	label1 = gtk_label_new("Caminho: ");
	gtk_fixed_put(GTK_FIXED(fixed), label1, 5, 10);

	entry1 = gtk_entry_new();
	gtk_widget_set_usize(GTK_WIDGET(entry1), 700, 20);
	gtk_fixed_put(GTK_FIXED(fixed), entry1, 75, 8);

	/* Submenu & About */

	vbox_content = gtk_vbox_new(FALSE, 4);
	gtk_container_add(GTK_CONTAINER(vbox_header), vbox_content);
	hbox = gtk_hbox_new(FALSE, 4);
	gtk_container_add(GTK_CONTAINER(vbox_content), hbox);

	vbox_submenu = gtk_vbox_new(FALSE, 4);
	gtk_box_pack_start(GTK_BOX(hbox), vbox_submenu, FALSE, TRUE, 1);
	
	clist = gtk_clist_new(1);
	gtk_clist_set_shadow_type(GTK_CLIST(clist), GTK_SHADOW_OUT);

	text = malloc(NAME_MAX * 5); // NAME_MAX chars, 5 lines
	
	snprintf(buf, NAME_MAX-1, "raiz: /\0");
	text[0] = (char*)buf;
	gtk_clist_append(GTK_CLIST(clist), (char**)&text[0]);
	
	text[1] = getenv("HOME");
	snprintf(buf, NAME_MAX-1, "home: %s\0", text[1]);
	gtk_clist_append(GTK_CLIST(clist), (char**)&text[1]);
	
	snprintf(buf, NAME_MAX-1, "smb://host/dir\0");
	text[2] = (char*)buf;
	gtk_clist_append(GTK_CLIST(clist), (char**)&text[2]);
	
	snprintf(buf, NAME_MAX-1, "ssh://user@host\0");
	text[3] = (char*)buf;
	gtk_clist_append(GTK_CLIST(clist), (char**)&text[3]);
	
	gtk_widget_set_usize(GTK_WIDGET(clist), 200, 70);
	gtk_box_pack_start(GTK_BOX(vbox_submenu), clist, FALSE, TRUE, 1);
	
	free(text);

	snprintf(buf, NAME_MAX-1, "%s/sfm.png\0", SFM_IMAGES);
	image = gtk_image_new_from_file(buf);
	gtk_box_pack_start(GTK_BOX(vbox_submenu), image, FALSE, TRUE, 1);
//	gtk_fixed_put(GTK_FIXED(fixed), image, 5, 160);

	scrolled = gtk_scrolled_window_new(NULL, NULL);
	viewport = gtk_viewport_new(NULL, NULL);
	fixedright = gtk_fixed_new();

	fprintf(stdout, "%d\n", NAME_MAX);

	sfm_scan_directory(hbox, sfm_current_path, 1);
	gtk_entry_set_text(GTK_ENTRY(entry1), sfm_current_path);

	g_signal_connect(GTK_OBJECT(clist), "select_row", GTK_SIGNAL_FUNC(sfm_select_menu), NULL);
	g_signal_connect(G_OBJECT(sfm_win), "delete_event", gtk_main_quit, NULL);

	gtk_widget_show_all(sfm_win);
	gtk_main();
	
	return 0;
}
