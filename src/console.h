
#include "main.h"

#ifndef _SFM_CONSOLE_H_
#define _SFM_CONSOLE_H_

#define SFM_KEY_TAB   9 
#define SFM_KEY_ENTER 10 

#define ARRAY_SIZE(array_list) (sizeof(array_list) / sizeof(array_list[0]));

typedef struct
{
	WINDOW *sfm_win_menu;
	WINDOW *sfm_win_root;
	WINDOW *sfm_win_status;

	ITEM **sfm_menu_items;
	MENU *sfm_menu;

	int lines, cols;
} sfm_ncurses_win;

static char *menu_choices[] = {
	"< Execute >",
	"<   Edit  >",
	"<   New   >",
	"<   Copy  >",
	"<  Paste  >",
	"<   Move  >",
	"< Options >",
	"<   Exit  >",
	(char *)NULL,
};

void sfm_left_tree(void);
void sfm_right_tree(void);
void sfm_bottom_menu(void);

#endif
