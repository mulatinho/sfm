#ifndef _SFM_MEMORY_H_
#define _SFM_MEMORY_H_

#include "main.h"

enum
{
	SFM_FILES_ALL,
	SFM_FILES_HIDDEN
};

enum
{
	SFM_SORT_FILE,
	SFM_SORT_TYPE,
	SFM_SORT_SIZE,
	SFM_SORT_TIME
};

typedef struct
{
	int id;
	char fname[FILENAME_MAX];
	struct stat fstat;
	struct mfile *next;
} mfile;

extern mfile *list;

void sfm_mfile_free(void);
void sfm_mfile_insert(int *, char *, struct stat *);
void sfm_mfile_list(int);
mfile *sfm_mfile_search(char *);

#endif