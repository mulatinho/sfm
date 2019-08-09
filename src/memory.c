#include "main.h"

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
	else {
		mfile *item = list;

		while (item->next != NULL)
			item = (mfile*)item->next;

		item->next = (struct mfile *)new;
	}
}

void sfm_mfile_list(int type)
{
	mfile *n = list;

	while (n != NULL) {
		fprintf(stdout, "%4d %6lu %s\n", n->id, n->fstat.st_size, n->fname);
		n = (mfile*)n->next;
	}
}

struct mfile *sfm_mfile_search(char *name)
{
	mfile *n = NULL, *tmp = NULL;

	n = list;
	while (n != NULL) {
	        if (!strncmp(n->fname, name, strlen(name)))
                        return n;
        }

        return NULL;
}

void sfm_mfile_free(void)
{
	mfile *n = NULL, *tmp = NULL;

	n = list;
	while (n != NULL) {
		tmp = n;
		n = (mfile*)n->next;
		if (tmp)
			free(tmp);
	}

	list = NULL;
}
