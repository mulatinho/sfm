#include "main.h"

mfile *sfm_mfile_insert(int *id, char *name, struct stat *stat)
{
	mfile *new = malloc(sizeof(mfile));

	if (!new)
		return NULL;

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
	
	return new;
}

void sfm_mfile_list(int type)
{
	mfile *n = list;

	while (n != NULL) {

		fprintf(stdout, "%4d %6lu %s\n", n->id, n->fstat.st_size, n->fname);
		n = (mfile*)n->next;
	}
}

int sfm_mfile_remove(char *filename)
{
	mfile *n = NULL, *tmp = NULL;

	n = list;
	while (n != NULL) {
		if (!strncmp(n->fname, filename, strlen(n->fname))) {
			tmp = (mfile*)n->next;
			free(n);
			n = tmp;

			return 0;
		}
	}

	return 1;
}

void sfm_mfile_free(void)
{
	mfile *n = NULL, *tmp = NULL;

	n = list;
	while (n != NULL) {
		tmp = (mfile*)n->next;
		free(n);
		n = tmp;
	}
}
