#include "main.h"

void sfm_left_tree(void);
void sfm_right_tree(void);
void sfm_down_menu(void);

void sfm_make_windows(void)
{
	sfm_ncurses_win *iface = malloc(sizeof(sfm_ncurses_win));

	initscr();
	start_color();
	noecho();
	cbreak();

	getmaxyx(stdscr, iface->lines, iface->cols);

	iface->sfmncmenu = newwin(3, iface->cols - 1, iface->lines - 5, 0);
	keypad(iface->sfmncmenu, TRUE);
	wmove(iface->sfmncmenu, 1, 1);
	box(iface->sfmncmenu, 0, 0);

	sleep(4);
	free(iface);

	refresh();
	endwin();
}

void sfm_ncurses(void)
{
	sfm_make_windows();
	/*
int x;
sfm_ncurses_win *iface = malloc(sizeof(sfm_ncurses_win));
char root_items[FILENAME_MAX];
int user_input;
WINDOW *current_window;
ITEM **ncmenu_items = NULL;
MENU *sfm_menu;

initscr();
start_color();
noecho();
cbreak();

getmaxyx(stdscr, iface->lines, iface->cols);
	fprintf(stdout, "lines: %d, columns: %d\n", iface->lines, iface->cols);
refresh();

iface->sfmncmenu = newwin(3, iface->cols-1, iface->lines-5, 0);
keypad(iface->sfmncmenu, TRUE);
wmove(iface->sfmncmenu, 1, 1);
box(iface->sfmncmenu, 0, 0);

ncmenu_items = malloc((menu_choices_n+1) * sizeof(ITEM *));
for (x = 0; x < menu_choices_n; x++)
	ncmenu_items[x] = new_item(menu_choices[x], menu_choices[x]);
//ncmenu_items[menu_choices_n] = (ITEM *)NULL;

sfm_menu = new_menu((ITEM **)ncmenu_items);
menu_opts_off(sfm_menu, O_SHOWDESC);
set_menu_format(sfm_menu, 1, menu_choices_n);
set_menu_mark(sfm_menu, " ");
set_menu_win(sfm_menu, iface->sfmncmenu);
set_menu_sub(sfm_menu, derwin(iface->sfmncmenu, 1, iface->cols-2, 1, 1));
post_menu(sfm_menu);

wrefresh(iface->sfmncmenu);

iface->sfmnroot = newwin(iface->lines-6, iface->cols-4, 0, 0);

snprintf(root_items, sizeof(root_items)-1, "%-40s . %-6s . %-4s . %-3s . %-10s",
	"FILENAME", "SIZE", "TYPE", "UID", "PERMISSIONS");
wattron(iface->sfmnroot, A_REVERSE|A_BOLD);
wprintw(iface->sfmnroot, root_items);
wattroff(iface->sfmnroot, A_REVERSE|A_BOLD);

for (x = 1; x < (iface->lines - 6); x++) {
	snprintf(root_items, sizeof(root_items)-1, "Item line %2d                             . 55Kb   . .PDF . 100 . -rw-r--r--", x);
	mvwprintw(iface->sfmnroot, x, 0, root_items);
}

wrefresh(iface->sfmnroot);

iface->sfmnstatus = newwin(1, iface->cols-1, iface->lines-2, 1);
wprintw(iface->sfmnstatus, ":. Hello! Welcome to .: %s :. lines:%d, cols:%d",
	SFM_VSN, iface->lines, iface->cols);
wrefresh(iface->sfmnstatus);

current_window = iface->sfmncmenu;
while (1) {
	user_input = wgetch(current_window);

	switch (user_input) {
	case KEY_LEFT:
		menu_driver(sfm_menu, REQ_LEFT_ITEM);
		break;
	case KEY_RIGHT:
		menu_driver(sfm_menu, REQ_RIGHT_ITEM);
		break;
	case KEY_UP:
		menu_driver(sfm_, REQ_UP_ITEM);
					break;
	case KEY_DOWN:
		menu_driver(sfm_menu, REQ_DOWN_ITEM);
		break;
	case 9:
		if (current_window == iface->sfmncmenu)
			current_window = iface->sfmnroot;
		else
			current_window = iface->sfmncmenu;

		keypad(current_window, TRUE);
		break;
	case 10:
		{
			//ITEM *cur;

			//cur = current_item(sfm_menu);

		}
		break;
	case 'Q':
	case 'q':
		wclear(iface->sfmnstatus);
		wprintw(iface->sfmnstatus, ":. Are you sure you want to quit!? [Y/N] ");
		wrefresh(iface->sfmnstatus);

		user_input = wgetch(iface->sfmnstatus);
		switch (user_input) {
		case 'y': case 'Y':
		case 's': case 'S':
			wclear(iface->sfmnstatus);
			wprintw(iface->sfmnstatus, ":. Thanks for using SFM! :) Quitting...");
			wrefresh(iface->sfmnstatus);
			sleep(1);

			goto sfm_ncurses_exit;
		default:
			break;
		}
	}

	wclear(iface->sfmnstatus);
	wprintw(iface->sfmnstatus, ":. status: %d", user_input);
	wrefresh(iface->sfmnstatus);
}

sfm_ncurses_exit:
delwin(iface->sfmnroot);
delwin(iface->sfmnstatus);
delwin(iface->sfmncmenu);

unpost_menu(sfm_menu);
free_menu(sfm_menu);

for (x = 0; x < menu_choices_n; x++)
	free_item(ncmenu_items[x]);

free(ncmenu_items);

free(iface);

refresh();
endwin();
	*/
}
