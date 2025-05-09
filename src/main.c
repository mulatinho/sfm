/*
 * main.c
 *
 * Copyright 2010 Alexandre Mulatinho <alex@mulatinho.net>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 *		MA 02110-1301, USA.
 */

#include "main.h"

struct context *ctx;

int main(int argc, char **argv)
{
	int ret, opt = 0;
	char *env_pwd = getenv("PWD");
	ctx = malloc(sizeof(struct context *));

	ctx->mode = SFM_MODE_GUI;
	sfm_set_current_path(env_pwd);

	while ((opt = getopt(argc, argv, "ghnuv")) != -1)
	{
		switch (opt)
		{
		case 'u':
		case 'h':
			fprintf(stdout,
					"usage: %s [-n ncurses|-g graphical|-v version]\n",
					argv[0]);
			break;
		case 'n':
			ctx->mode = SFM_MODE_NCURSES;
			sfm_ncurses(ctx);
			break;
		case 'v':
			fprintf(stdout, SFM_VERSION);
			break;
		case 'g':
		default:
			sfm_gui_start(ctx);
			break;
		}
	}

	return 0;
}