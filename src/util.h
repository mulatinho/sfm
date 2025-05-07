#include "main.h"

#ifndef _SFM_UTIL_H_
#define _SFM_UTIL_H_

char *sfm_bash_exec(char *);
extern int alphasort();
int sfm_has_shortcuts(void);
void sfm_debug(const char *);
void sfm_exec_file(gchar *);
void sfm_scan_directory(int);
void sfm_set_current_path(const char *);
void sfm_warn_message(gchar *, gchar *, gint, gint);

#endif
