#ifndef _SFM_UTIL_H_
#define _SFM_UTIL_H_

#include "main.h"

#define SFM_PREFIX_ROOT "/"
#define SFM_PREFIX_SMB "smb://"

#define BUFFER_ZERO(buffer) memset(buffer, '\0', sizeof(buffer))

#ifdef DEBUG
	#define SFM_DEBUG(format, debug_message...) \
	fprintf(stderr, ":.\n:. debug: %s:%d\n", __FILE__, __LINE__); \
	fprintf(stderr, ":. sfm_current_path: %s\n:. message: ", ctx->sfm_current_path); \
	fprintf(stderr, format, ## debug_message);
#else
	#define SFM_DEBUG(format, debug_message..)
#endif

char *sfm_bash_exec(char *);
extern int alphasort();
int sfm_has_shortcuts(void);
void sfm_debug(const char *);
void sfm_exec_file(gchar *);
void sfm_scan_directory(int);
void sfm_set_current_path(char *);
char *sfm_get_current_path();
void sfm_warn_message(gchar *, gchar *, gint, gint);

#endif