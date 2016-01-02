#include "main.h"

#define SFM_CONFIG ".config/sfm/config"

int sfm_config_init(void)
{
	int i, fd;
	char *env_home = getenv("HOME");
	char realfile[FILENAME_MAX];

	for (i=0; i<2; i++) {
		BUFFER_ZERO(realfile);

		if (!i) 
			snprintf(realfile, FILENAME_MAX-1, 
				"%s/%s", env_home, ".config");
		else 
			snprintf(realfile, FILENAME_MAX-1, 
				"%s/%s", env_home, ".config/sfm");

		if (mkdir(realfile, S_IRWXU) == -1) {
			if (errno != EEXIST) {
				fprintf(stderr, ".: error creating '%s' - %d - %s\n", 
					realfile, errno, strerror(errno));
				return -1;
			}
		}
	}

	BUFFER_ZERO(realfile);
	snprintf(realfile, FILENAME_MAX-1, "%s/%s", env_home, ".config/sfm/config");

	if ((fd = open(realfile, O_RDONLY)) == -1) {
		if ((fd = open(realfile, O_CREAT, S_IWUSR|S_IRUSR)) == -1) {
			fprintf(stderr, ".: error creating '%s' - %d - %s\n", 
				realfile, errno, strerror(errno));
			return -1;
		} else {
			close(fd);
		}
	} else {
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
	int fd, bytes;
	char *env_home = getenv("HOME");
	char realfile[FILENAME_MAX];
	char line[FILENAME_MAX];

	if ((fd = open(realfile, O_RDONLY)) != -1) {
		while ((bytes = read(fd, line, sizeof(line)-1)) != -1) {
			fprintf(stdout, "%s", line);
		}
		close(fd);
	}

	return 0;
}

int main(void)
{
	int ret = 0;

	ret = sfm_config_init();
	fprintf(stdout, "sfm_config_init: %d\n", ret);

	ret = sfm_config_load();
	fprintf(stdout, "sfm_config_load: %d\n", ret);

	ret = sfm_config_set("ui", "ncurses");
	fprintf(stdout, "sfm_config_set : %d\n", ret);

	return 0;
}
