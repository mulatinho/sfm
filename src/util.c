/*
* util.c
*
* Copyright 2010 Alexandre Mulatinho <alex@mulatinho.net>
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 2 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program; if not, write to the Free Software
* Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
* MA 02110-1301, USA.
*/

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

extern int alphasort();
void sfm_scan_directory(int hidden)
{
	struct dirent **files;
	struct stat obj;
	int count, n;
	char filename[FILENAME_MAX];

	sfm_mfile_free();

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

void sfm_set_current_path(const char *name)
{
	struct stat fstat;

	stat(name, &fstat);

	if (!S_ISDIR(fstat.st_mode)) {
		gtk_statusbar_pop(GTK_STATUSBAR(sfm.statusbar), 1);
		gtk_statusbar_push(GTK_STATUSBAR(sfm.statusbar), 1, "Error! Directory not found.");

		gtk_entry_set_text(GTK_ENTRY(sfm.path_entry), sfm_current_path);
	} else {
		BUFFER_ZERO(sfm_current_path);
		snprintf(sfm_current_path, FILENAME_MAX-1, "%s", name);

		gtk_statusbar_pop(GTK_STATUSBAR(sfm.statusbar), 1);
		gtk_statusbar_push(GTK_STATUSBAR(sfm.statusbar), 1, "Well done!");
	}
}
