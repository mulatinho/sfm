#include "main.h"
#include "memory.h"

mfile *list;

void sfm_mfile_insert(int *id, char *name, struct stat *stat)
{
	mfile *new = malloc(sizeof(mfile));

	if (!new)
		return;

	new->id = *id;
	strcpy(new->fname, name);
	new->fstat = *stat;
	new->next = NULL;

	if (!list)
		list = new;
	else
	{
		mfile *item = list;

		while (item->next != NULL)
			item = (mfile *)item->next;

		item->next = (struct mfile *)new;
	}
}

void sfm_mfile_list(int type)
{
	mfile *next_file = list;

	while (next_file != NULL)
	{
		fprintf(stdout, "%4d %6lu %s\n", next_file->id, next_file->fstat.st_size, next_file->fname);
		next_file = (mfile *)next_file->next;
	}
}

mfile *sfm_mfile_search(char *name)
{
	mfile *next_file = NULL, *tmp = NULL;

	next_file = list;
	while (next_file != NULL)
	{
		if (!strncmp(next_file->fname, name, strlen(name)))
			return next_file;
	}

	return NULL;
}

void sfm_mfile_free(void)
{
	mfile *next_file = NULL, *tmp = NULL;

	next_file = list;
	while (next_file != NULL)
	{
		tmp = next_file;
		next_file = (mfile *)next_file->next;
		if (tmp)
			free(tmp);
	}

	list = NULL;
	next_file = NULL;
}
