#include "main.h"

#ifndef _SFM_OPERATIONS_H_
#define _SFM_OPERATIONS_H_

void sfm_create_shortcut(GtkWidget*, gchar*);
void sfm_create_shortcut(GtkWidget*, gchar*);
void sfm_create_shortcut(GtkWidget*, gchar*);
void sfm_link_event(GtkWidget*, const gchar*, gpointer);
void sfm_link_network(GtkWidget*, const gchar*, gpointer);
void sfm_select_menu(GtkWidget*, gint, gint);
void do_select(GtkWidget*, gint, gint);
void sfm_run(GtkWidget*, gpointer);
void sfm_paste_file(GtkWidget*, gpointer);
void sfm_copy_file(GtkWidget*, gpointer);
void sfm_open(GtkWidget*, gpointer);
void sfm_execute(GtkWidget*, GdkEventButton*, gpointer);

#endif
