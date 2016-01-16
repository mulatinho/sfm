//	util.c
//		
//	Copyright 2010 Alexandre Mulatinho <alex@mulatinho.net>
//		
//	This program is free software; you can redistribute it and/or modify
//	it under the terms of the GNU General Public License as published by
//	the Free Software Foundation; either version 2 of the License, or
//	(at your option) any later version.
//		
//	This program is distributed in the hope that it will be useful,
//	but WITHOUT ANY WARRANTY; without even the implied warranty of
//	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	See the
//	GNU General Public License for more details.
//	
//	You should have received a copy of the GNU General Public License
//	along with this program; if not, write to the Free Software
//	Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
//	MA 02110-1301, USA.

#include "main.h"

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

int sfm_has_shortcuts(void)
{
	// FIXME: Do the things here.
	return 0;
}

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

	BUFFER_ZERO(rbuf);
	BUFFER_ZERO(inbuf);
	BUFFER_ZERO(outbuf);

	g_snprintf(inbuf, sizeof(inbuf)-1, "xdg-open \"%s\"", current_file);

	tid = fork();
	if (!tid) {
		if ((fp = popen(inbuf, "r"))) {
			while (fgets(rbuf, sizeof(rbuf-1), fp)) {
				totalbytez+=strlen(rbuf);
				strncat(outbuf, rbuf, strlen(rbuf)-1);
				BUFFER_ZERO(rbuf);
			}
			fclose(fp);
		}

		waitpid(tid, &status, 0);
		exit(0);
	}
}

GtkWidget *sfm_create_icon(GtkWidget *box, gchar *label, gchar *file, int x, int y)
{
	GtkWidget *vbox, *image, *label1, *eventbox;
	gchar buf[FILENAME_MAX], filen[FILENAME_MAX];
	struct stat obj;

	eventbox = gtk_event_box_new();

	snprintf(filen, FILENAME_MAX-1, "%s/%s", sfm_current_path, file);
	lstat(filen, &obj);

	if (S_ISDIR(obj.st_mode)) 
		image = gtk_image_new_from_stock(GTK_STOCK_DIRECTORY, 
			GTK_ICON_SIZE_DIALOG);
		/* snprintf(buf, FILENAME_MAX-1, "%s/sfmfolder.png", SFM_IMAGES); */
	else 
		image = gtk_image_new_from_stock(GTK_STOCK_FILE,
			GTK_ICON_SIZE_DIALOG);
		/* snprintf(buf, FILENAME_MAX-1, "%s/sfmfile.png", SFM_IMAGES); */
	
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
	int count, n;
	char filename[FILENAME_MAX];

	count = scandir(sfm_current_path, &files, 0, alphasort);
	
	for (n = 0; n < count; n++) {
		BUFFER_ZERO(filename);
		snprintf(filename, FILENAME_MAX, "%s/%s", sfm_current_path, files[n]->d_name);
		stat(filename, &obj);

		sfm_mfile_insert(&n, files[n]->d_name, &obj);
		free(files[n]);
	}
	free(files);
}

void sfm_set_path(char *name)
{
	struct stat fstat;

	BUFFER_ZERO(sfm_current_path);
	
	stat(name, &fstat);
	if (S_ISDIR(fstat))	
		snprintf(sfm_current_path, FILENAME_MAX-1, "%s", name);
	else {
		gtk_statusbar_pop(sfm.statusbar, 1);
		gtk_statusbar_push(sfm.statusbar, 1, "Diretorio nao existe");
	}
}
