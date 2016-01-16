#include "main.h"

#ifndef _SFM_UTIL_H_
#define _SFM_UTIL_H_

char *sfm_bash_exec(char*);
int sfm_has_shortcuts(void);
void sfm_set_current_path(const char*);
void sfm_exec_file(gchar*);
extern int alphasort();
void sfm_scan_directory(int);
void sfm_warn_message(gchar*, gchar*, gint, gint);

#endif
