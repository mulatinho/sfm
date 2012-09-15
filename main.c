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
	GtkWidget *frame, *but;
	GtkWidget *menu, *iconwin, *nbox, *fixed, *vbox;
	GtkWidget *image, *label1, *button;
	GtkItemFactory *item_factory;
	GtkBox *box;
	GtkAccelGroup *accel_group;
	gchar buf[FILESIZ], **text;

	gtk_init(&argc, &argv);
	path = (char*)malloc(256);

	win = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(win), PROGNAME);
	gtk_window_set_default_size(GTK_WINDOW(win), 700, 480);

	vbox = gtk_vbox_new(FALSE, 1);
	gtk_container_set_border_width(GTK_CONTAINER(vbox), 4);
	gtk_container_add(GTK_CONTAINER(win), vbox);

	accel_group = gtk_accel_group_new();
	item_factory = gtk_item_factory_new(GTK_TYPE_MENU_BAR, "<main>", accel_group);
	gtk_item_factory_create_items(item_factory, nmenu, menu_items, NULL);
	gtk_window_add_accel_group(GTK_WINDOW(win), accel_group);
	menu = gtk_item_factory_get_widget(item_factory, "<main>");
	gtk_box_pack_start(GTK_BOX(vbox), menu, FALSE, TRUE, 0);

	hbox = gtk_hbox_new(FALSE, 4);
	gtk_container_add(GTK_CONTAINER(vbox), hbox);

	fixed = gtk_fixed_new();
	gtk_box_pack_start(GTK_BOX(hbox), fixed, FALSE, TRUE, 1);
	
	label1 = gtk_label_new("Caminho: ");
	gtk_fixed_put(GTK_FIXED(fixed), label1, 5, 10);

	entry1 = gtk_entry_new();
	gtk_widget_set_usize(GTK_WIDGET(entry1), 200, 20);
	gtk_fixed_put(GTK_FIXED(fixed), entry1, 5, 30);

	clist = gtk_clist_new(1);
	gtk_clist_set_shadow_type(GTK_CLIST(clist), GTK_SHADOW_OUT);

	text = malloc(128 * 4); // 128 chars, 4 lines
	snprintf(buf, FILESIZ-1, "$+ Raiz: /\0");
	text[0] = (char*)buf;
	gtk_clist_append(GTK_CLIST(clist), (char**)&text[0]);
	path = getenv("HOME");
	snprintf(buf, FILESIZ-1, "$+ Home: %s\0", path);
	text[1] = (char*)buf;
	gtk_clist_append(GTK_CLIST(clist), (char**)&text[1]);
	snprintf(buf, FILESIZ-1, "$+ Rede Interna (SAMBA)\0");
	text[2] = (char*)buf;
	gtk_clist_append(GTK_CLIST(clist), (char**)&text[2]);
	snprintf(buf, FILESIZ-1, "$+ Painel de Controle\0");
	text[3] = (char*)buf;
	gtk_clist_append(GTK_CLIST(clist), (char**)&text[3]);
	free(text);

	gtk_widget_set_usize(GTK_WIDGET(clist), 200, 70);
	gtk_fixed_put(GTK_FIXED(fixed), clist, 5, 60);

	snprintf(buf, FILESIZ-1, "%s/sfm.png\0", SFM_IMAGES);
	image = gtk_image_new_from_file(buf);
	gtk_fixed_put(GTK_FIXED(fixed), image, 5, 160);

	scrolled = gtk_scrolled_window_new(NULL, NULL);
	viewport = gtk_viewport_new(NULL,NULL);
	fixedright = gtk_fixed_new();

	icon_scanfile(hbox, path, 1);
	gtk_entry_set_text(GTK_ENTRY(entry1), path);

	g_signal_connect(GTK_OBJECT(clist), "select_row", GTK_SIGNAL_FUNC(select_menu), NULL);
	g_signal_connect(G_OBJECT(win), "delete_event", gtk_main_quit, NULL);

	gtk_widget_show_all(win);
	gtk_main();
	
	return 0;
}
