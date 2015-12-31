#include "main.h"

char *sfm_bash_exec(char*);
int sfm_has_shortcuts(void);
void sfm_path_new(GtkWidget*, GdkEvent*, gpointer);
void sfm_exec_file(gchar*);
extern int alphasort();
void sfm_scan_directory(int);
void sfm_warn_message(gchar*, gchar*, gint, gint);
