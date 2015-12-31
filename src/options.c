#include "main.h"

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

int sfm_config_load(void)
{
	int fd;
	char line[
	
	if ((fd = open(realfile, O_RDONLY)) != -1) {
		close(fd);
	}

	return 0;
}

int main(void)
{
	int ret = 0;

	ret = sfm_config_init();
	fprintf(stdout, "ret: %d\n", ret);

	ret = sfm_config_load();
	fprintf(stdout, "ret: %d\n", ret);

	return 0;
}
