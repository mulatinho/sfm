
#include "main.h"

#ifndef _SFM_CONSOLE_H_
#define _SFM_CONSOLE_H_

struct sfm_ncurses {
	WINDOW *sfmncmenu;
	WINDOW *sfmnroot;
	WINDOW *sfmnstatus;
	int lines, cols;
};

static char *menu_choices[] = {
	"Execute", "Edit", "New", "Copy", "Paste",
	"Move", "Help", "Exit", (char*)NULL,
};
static int menu_choices_n = sizeof(menu_choices) / sizeof(menu_choices[0]);

#endif
