
#include "main.h"

#ifndef _SFM_CONSOLE_H_
#define _SFM_CONSOLE_H_

typedef struct {
	WINDOW *sfmncmenu;
	WINDOW *sfmnroot;
	WINDOW *sfmnstatus;
	int lines, cols;
} sfm_ncurses_win;

static char *menu_choices[] = {
	"Execute", "Edit", "New", "Copy", "Paste",
	"Move", "Options", "Exit", (char*)NULL,
};
static int menu_choices_n = sizeof(menu_choices) / sizeof(menu_choices[0]);

#endif
