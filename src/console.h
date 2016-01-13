
#include "main.h"

#ifndef _SFM_CONSOLE_H_
#define _SFM_CONSOLE_H_

struct sfm_ncurses {
	WINDOW *sfmncmenu;
	WINDOW *sfmnroot;
	WINDOW *sfmnstatus;
	int lines, cols;
};

#endif
