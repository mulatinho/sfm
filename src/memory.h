#include "main.h"

#ifndef _SFM_MEMORY_H_
#define _SFM_MEMORY_H_

enum
{
	FILES_ALL,
	FILES_HIDDEN
};

enum
{
	SORT_FILE,
	SORT_TYPE,
	SORT_SIZE,
	SORT_TIME
};

typedef struct
{
	int id;
	char fname[FILENAME_MAX];
	struct stat fstat;
	struct mfile *next;
} mfile;

static mfile *list; // = NULL;

void sfm_mfile_free(void);
void sfm_mfile_insert(int *, char *, struct stat *);
#endif
