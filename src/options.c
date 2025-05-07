#include "main.h"

#define SFM_CONFIG ".config/sfm/config"

int sfm_config_init(void)
{
	int i, fd;
	char *ENV_HOME = getenv("HOME");
	char realfile[FILENAME_MAX];

	for (i = 0; i < 2; i++)
	{
		BUFFER_ZERO(realfile);

		if (!i)
			snprintf(realfile, FILENAME_MAX - 1,
					 "%s/%s", ENV_HOME, ".config");
		else
			snprintf(realfile, FILENAME_MAX - 1,
					 "%s/%s", ENV_HOME, ".config/sfm");

		if (mkdir(realfile, S_IRWXU) == -1)
		{
			if (errno != EEXIST)
			{
				fprintf(stderr, ".: error creating '%s' - %d - %s\n",
						realfile, errno, strerror(errno));
				return -1;
			}
		}
	}

	BUFFER_ZERO(realfile);
	snprintf(realfile, FILENAME_MAX - 1, "%s/%s", ENV_HOME, SFM_CONFIG);

	if ((fd = open(realfile, O_RDONLY)) == -1)
	{
		if ((fd = open(realfile, O_CREAT, S_IWUSR | S_IRUSR)) == -1)
		{
			fprintf(stderr, ".: error creating '%s' - %d - %s\n",
					realfile, errno, strerror(errno));
			return -1;
		}
		else
		{
			close(fd);
		}
	}
	else
	{
		close(fd);
	}

	return 0;
}

int sfm_config_set(char *key, char *value)
{
	return 0;
}

int sfm_config_load(void)
{
	FILE *fp;
	int bytes;
	char *ENV_HOME = getenv("HOME");
	char realfile[FILENAME_MAX];
	char line[FILENAME_MAX];

	BUFFER_ZERO(realfile);
	snprintf(realfile, FILENAME_MAX - 1, "%s/%s", ENV_HOME, SFM_CONFIG);

	if ((fp = fopen(realfile, "r")) != NULL)
	{
		while (fgets(line, sizeof(line) - 1, fp))
		{
			fprintf(stdout, "%s", line);
		}
		fclose(fp);
	}

	return 0;
}
