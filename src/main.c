//		main.c
//		
//		Copyright 2010 Alexandre Mulatinho <alex@mulatinho.net>
//		
//		This program is free software; you can redistribute it and/or modify
//		it under the terms of the GNU General Public License as published by
//		the Free Software Foundation; either version 2 of the License, or
//		(at your option) any later version.
//		
//		This program is distributed in the hope that it will be useful,
//		but WITHOUT ANY WARRANTY; without even the implied warranty of
//		MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	See the
//		GNU General Public License for more details.
//		
//		You should have received a copy of the GNU General Public License
//		along with this program; if not, write to the Free Software
//		Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
//		MA 02110-1301, USA.

#include "main.h"

#ifdef DEBUG
int main(int argc, char **argv)
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
#else
int main(int argc, char **argv)
{
	int opt = 0;
	int user = 0;
	char *env_pwd = getenv("PWD");

	sfm_set_path(env_pwd);

	while ((opt = getopt(argc, argv, "gnv")) != -1) {
		switch (opt) {
		case 'g':
			sfm_gui();
			break;
		case 'n':
			sfm_ncurses();
			break;
		case 'v':
			fprintf(stdout, SFM_VERSION);
			exit(0);
			break;
		}
		user++;
	}
	
	if (!user)
		fprintf(stdout, "usage: %s [-n ncurses|-g graphical|-v version]\n", argv[0]);

	return 0;
}
#endif
