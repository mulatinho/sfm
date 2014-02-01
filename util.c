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

/*
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
}
*/

void sfm_path_new(GtkWidget *wid, GdkEvent *ev, gpointer p)
{
    fprintf(stdout, "sfm_path_new fixme\n");
}

void sfm_exec_file(gchar *current_file)
{
    FILE *fp;
	gchar inbuf[256], outbuf[256], rbuf[256];
    gint status = 0, totalbytez = 0;
	pid_t tid;

	memset(inbuf, '\0', sizeof(inbuf));
	memset(outbuf, '\0', sizeof(outbuf));
	memset(rbuf, '\0', sizeof(rbuf));

	g_snprintf(inbuf, sizeof(inbuf)-1, "xdg-open \"%s\"", current_file);

	tid = fork();
    if (!tid) {
        if ((fp = popen(inbuf, "r"))) {
            while (fgets(rbuf, sizeof(rbuf-1), fp)) {
                totalbytez+=strlen(rbuf);
                strncat(outbuf, rbuf, strlen(rbuf)-1);
	            memset(rbuf, '\0', sizeof(rbuf));
            }
            fclose(fp);
        }

    	waitpid(tid, &status, 0);
        exit(0);
    }
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

extern int alphasort();
void sfm_scan_directory(int hidden)
{
	struct dirent **files;
	struct stat obj;
	char *utf8;
	int loop, xstat, x, y, z, t, r;
	char iconname[256], filen[256];

	memset(filen, '\0', NAME_MAX);
	memset(iconname, '\0', NAME_MAX);

	if (sfm.viewport)
	    gtk_widget_destroy(sfm.viewport);

	if (sfm.scroll)
	    gtk_widget_destroy(sfm.scroll);

	if (sfm.fixedright)
	    gtk_widget_destroy(sfm.fixedright);

	if (sfm.fileview)
	    gtk_widget_destroy(sfm.fileview);

	sfm.fileview = gtk_hbox_new(FALSE, 4);
	gtk_container_add(GTK_CONTAINER(sfm.leftview), sfm.fileview);

	sfm.scroll = gtk_scrolled_window_new(NULL, NULL);
	gtk_scrolled_window_set_shadow_type((GtkScrolledWindow*)sfm.scroll, GTK_SHADOW_NONE);
	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(sfm.scroll),
		GTK_POLICY_AUTOMATIC, GTK_POLICY_ALWAYS);

	sfm.fixedright = gtk_fixed_new();

	sfm.viewport = gtk_viewport_new(NULL,NULL);
	gtk_viewport_set_shadow_type((GtkViewport*)sfm.viewport, GTK_SHADOW_NONE);

    gtk_box_pack_start(GTK_BOX(sfm.fileview), sfm.scroll, TRUE, TRUE, 2);
	gtk_container_add(GTK_CONTAINER(sfm.scroll), sfm.viewport);

	gtk_container_add(GTK_CONTAINER(sfm.viewport), sfm.fixedright);

	gtk_container_add(GTK_CONTAINER(sfm.leftview), sfm.fileview);

	xstat = scandir(sfm_current_path, &files, 0, alphasort);
	
	for (loop=0,z=1,y=10; loop<xstat; loop++) 
    {
		utf8 = g_locale_to_utf8(files[loop]->d_name, 
                strlen(files[loop]->d_name), NULL, NULL, NULL);
		snprintf(filen, NAME_MAX, "%s/%s",sfm_current_path,utf8);

		lstat(filen, &obj);
		
		/* Icon Y Axis */
		if (!(z % 4))
			y += 140;

		/* Icon X Axis */
		x = (z%4) * 120;

		for (r=0,t=0;t<=strlen(utf8);t++) {
			if (!(t%11) && t!=0) {
				iconname[r] = '\n';
				r++;
			}

			iconname[r] = utf8[t];
			r++;
		}
		
		if (!hidden)
			create_icone(sfm.fixedright, (char*)iconname, (char*)utf8, x, y);
		else {
			if ((utf8[0] == '.' && utf8[1] == '.') || utf8[0] != '.')
				create_icone(sfm.fixedright, (char*)iconname, (char*)utf8, x, y);
			else
				z--;
		}

		memset(filen, '\0', NAME_MAX); z++;
	}

	gtk_widget_show_all(sfm.firstwin);

	return;
}

void list_scanfile(GtkCList *clist, int hidden)
{
	struct dirent **files;
	struct stat obj;
	char **text, *utf8;
	int loop, xstat, x, z;
	char filen[NAME_MAX];

	xstat = scandir(sfm_current_path, &files, 0, alphasort);
	text = malloc(xstat*FILENSIZ);
	
	for (loop=0,x=0; loop<xstat; loop++) {
		utf8 = g_locale_to_utf8(files[loop]->d_name, 
                strlen(files[loop]->d_name), NULL, NULL, NULL);
		snprintf(filen, NAME_MAX-1, "%s/%s",sfm_current_path,utf8);

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

void sfm_warn_message(gchar *title, gchar *message, gint width, gint height)
{
       GtkWidget *dialog, *label; 
         
       dialog = gtk_dialog_new_with_buttons (title, GTK_WINDOW(sfm.firstwin), 
         GTK_DIALOG_DESTROY_WITH_PARENT, GTK_STOCK_OK, GTK_RESPONSE_NONE, NULL);
	   gtk_widget_set_usize(dialog, width, height);
         
       label = gtk_label_new (message);
       
       g_signal_connect_swapped (dialog, "response", 
         G_CALLBACK (gtk_widget_destroy), dialog);

       gtk_container_add (GTK_CONTAINER (GTK_DIALOG(dialog)->vbox), label); 
       gtk_widget_show_all (dialog);
}
