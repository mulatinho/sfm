//      util.c
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
#define MAXFILEZ 512
#define FILENSIZ NAME_MAX

char *sfm_bash_exec(char *cmd)
{
	FILE *fp;
	char buf[256];
	char *ret = (char*)malloc(sizeof(buf));
	int totalbytez = 0;

	memset(ret, 0, sizeof(buf));

	fp = popen(cmd, "r");
	while (fgets(buf, sizeof(buf)-1, fp)) {
		totalbytez+=strlen(buf);

		if (totalbytez > 12)
			ret = (char*)realloc(ret, totalbytez);

		strncat(ret, buf, strlen(buf)-1);
	}
	fclose(fp);

	if (!strlen(ret))
		return NULL;
	else
		return (char*)ret;
		
	pthread_exit(NULL);
}
void on_executefile(gchar *current_file)
{
	gchar buf[256];
	pthread_t tid;

	memset(buf, '\0', sizeof(buf));

	snprintf(buf, sizeof(buf)-1, "xdg-open %s", current_file);
	fprintf(stdout, "debug: %s\n", buf);

	pthread_create(&tid, NULL, (void*)sfm_bash_exec, buf);
	pthread_join(tid, NULL); 
}

GtkWidget *create_icone(GtkWidget *box, gchar *label, gchar *file, int x, int y)
{
	GtkWidget *vbox, *image, *label1, *eventbox;
	gchar buf[FILENSIZ], filen[FILENSIZ];
	struct stat obj;

	eventbox = gtk_event_box_new();

	snprintf(filen, FILENSIZ-1, "%s/%s", sfm_current_path, file);
	lstat(filen, &obj);

	if (S_ISDIR(obj.st_mode)) 
		snprintf(buf, FILENSIZ-1, "%s/sfmfolder.png", SFM_IMAGES);
	else 
		snprintf(buf, FILENSIZ-1, "%s/sfmfile.png", SFM_IMAGES);
	
	image = gtk_image_new_from_file(buf);

	label1 = gtk_label_new(label);
	gtk_widget_set_usize(GTK_WIDGET(label1), 125, 80);
	gtk_label_set_justify(GTK_LABEL(label1), GTK_JUSTIFY_CENTER);

	vbox = gtk_vbox_new(FALSE, 0);
	gtk_container_add(GTK_CONTAINER(eventbox), image);
	gtk_box_pack_start(GTK_BOX(vbox), GTK_WIDGET(eventbox), TRUE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(vbox), label1, TRUE, TRUE, 0);

	gtk_fixed_put(GTK_FIXED(box), vbox, x, y);

	g_signal_connect(GTK_OBJECT(eventbox), "button_press_event", G_CALLBACK(sfm_execute), file);
	return vbox;
}

void sfm_scan_directory(GtkWidget *wid, char *work_path, int hidden)
{
	struct dirent **files;
	struct stat obj;
	char *utf8;
	int loop, xstat, x, y, z, t, r;
	char iconname[256], filen[256];

	gtk_widget_destroy(fixedright);
	gtk_widget_destroy(viewport);
	gtk_widget_destroy(scrolled);

	scrolled = gtk_scrolled_window_new(NULL, NULL);
	gtk_scrolled_window_set_shadow_type((GtkScrolledWindow*)scrolled, GTK_SHADOW_NONE);
	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled),
		GTK_POLICY_AUTOMATIC, GTK_POLICY_ALWAYS);
	fixedright = gtk_fixed_new();
	viewport = gtk_viewport_new(NULL,NULL);
	gtk_viewport_set_shadow_type((GtkViewport*)viewport, GTK_SHADOW_NONE);
	gtk_box_pack_start(GTK_BOX(wid), scrolled, TRUE, TRUE, 2);
	gtk_container_add(GTK_CONTAINER(scrolled), viewport);
	gtk_container_add(GTK_CONTAINER(viewport), fixedright);

	xstat = scandir(work_path, &files, 0, alphasort);
	
	y = 10;
	for (loop=0,z=1; loop<xstat; loop++) {
		utf8 = g_locale_to_utf8(files[loop]->d_name, strlen(files[loop]->d_name), NULL, NULL, NULL);
		snprintf(filen, NAME_MAX, "%s/%s",work_path,utf8);

		lstat(filen, &obj);
		
		/* Numero de colunas */
		if (!(z % 4))
			y += 140;

		/* Tamanho de cada area/icone */
		x = (z%4) * 120;

		for (r=0,t=0;t<=strlen(utf8);t++) {
			if (!(t%12) && t!=0) {
				iconname[r] = '\n';
				r++;
			}

			iconname[r] = utf8[t];
			r++;
		}
		iconname[t] = '\0'; 

		if (!hidden)
			create_icone(fixedright, (char*)iconname, (char*)utf8, x, y);
		else {
			if ((utf8[0] == '.' && utf8[1] == '.') || utf8[0] != '.')
				create_icone(fixedright, (char*)iconname, (char*)utf8, x, y);
			else
				z--;
		}

		memset(filen, '\0', NAME_MAX); z++;
	}

	gtk_widget_show_all(hbox);
	return;
}

void list_scanfile(GtkCList *clist, char *worksfm_current_path, int hidden)
{
	struct dirent **files;
	struct stat obj;
	char **text, *utf8;
	int loop, xstat, x, z;
	char filen[NAME_MAX];

	xstat = scandir(worksfm_current_path, &files, 0, alphasort);
	text = malloc(xstat*FILENSIZ);
	
	for (loop=0,x=0; loop<xstat; loop++) {
		utf8 = g_locale_to_utf8(files[loop]->d_name, strlen(files[loop]->d_name), NULL, NULL, NULL);
		snprintf(filen, NAME_MAX, "%s/%s",worksfm_current_path,utf8);

		lstat(filen, &obj);
			
		if (!hidden)
			text[x] = utf8;
		else {
			if (utf8[0] != '.' && (utf8[1] != '\0' || utf8[1] != '.')) 
				text[x] = utf8;
			else
				x--;
		}

		memset(filen, '\0', NAME_MAX); x++;
	}

	for (loop=0; loop<x; loop++)
		gtk_clist_append(clist, (char**)&text[loop]);

	free(text);
	return;
}

void warnm(gchar *title, gchar *message, gint x, gint y)
{
       GtkWidget *dialog, *label; 
         
       dialog = gtk_dialog_new_with_buttons (title, GTK_WINDOW(sfm_win), GTK_DIALOG_DESTROY_WITH_PARENT,
               GTK_STOCK_OK, GTK_RESPONSE_NONE, NULL);
	   gtk_widget_set_usize(dialog, x, y);
         
       label = gtk_label_new (message);
       
       g_signal_connect_swapped (dialog, "response", G_CALLBACK (gtk_widget_destroy), dialog);

       gtk_container_add (GTK_CONTAINER (GTK_DIALOG(dialog)->vbox), label); 
       gtk_widget_show_all (dialog);
}
