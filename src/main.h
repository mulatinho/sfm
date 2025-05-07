/*
 * main.h
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
 *	Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 *	MA 02110-1301, USA.
 */

#ifndef _SFM_CORE_H_
#define _SFM_CORE_H_

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>
#include <pthread.h>
#include <linux/limits.h>
#include <gtk/gtk.h>
#include <dirent.h>
#include <ncurses.h>
#include <menu.h>

#include "memory.h"
#include "util.h"
#include "views.h"
#include "gui.h"
#include "console.h"
#include "options.h"

#define ICON_SZ_L 64
#define ICON_SZ_M 32
#define ICON_SZ_S 16
#define PROGAUTHOR "Alexandre Mulatinho <alex at mulatinho dot net>"
#define PROGDESC "A Lightweight Simple File Manager"
#define PROGNAME "SFM"
#define PROGVERSION "0.01"
#define SFM_CACHE "./sfm/cache"
#define SFM_CONF "./sfm/sfm.conf"
#define SFM_IMAGES "./picz"
#define SFM_VERSION PROGNAME " v" PROGVERSION "\nWritten by " PROGAUTHOR "\n"
#define SFM_VSN PROGNAME " v" PROGVERSION

#define BUFFER_ZERO(buffer) memset(buffer, '\0', sizeof(buffer))

static char sfm_current_path[FILENAME_MAX];

void sfm_gui(void);
void sfm_ncurses(void);

#endif
