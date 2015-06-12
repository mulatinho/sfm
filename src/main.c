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

int main(int argc, char **argv)
{
	gchar buf[NFILEMAXSZ];
	gchar **text = NULL;
	gint opt = 0;
	gint ncurses = 0;

	while ((opt = getopt(argc, argv, "nv")) != -1) {
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
		default:
			fprintf(stdout, "usage: %s [-n ncurses] [-v version]\n", argv[0]);
			return -1;
		}
	}

	sfm_ncurses();

	return 0;
}
