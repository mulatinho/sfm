#include "console.h"

void sfm_left_tree(void);
void sfm_right_tree(void);
void sfm_down_menu(void);

sfm_ncurses_win *iface = NULL;

sfm_ncurses_win *sfm_get_interface(void)
{
	return (sfm_ncurses_win *)iface;
}

WINDOW *sfm_create_window(int lines, int cols, int y, int x)
{
	// WINDOW *curr_window = newwin(lines, cols, y, x);
	WINDOW *curr_window = newwin(lines, cols, y, x);

	keypad(curr_window, TRUE);
	start_color();
	init_pair(1, COLOR_WHITE, COLOR_BLACK);
	noecho();

	//wattron(curr_window, COLOR_PAIR(1) | A_BOLD);
	//wattroff(curr_window, COLOR_PAIR(1) | A_BOLD);
	wrefresh(curr_window);
	refresh();

	return curr_window;
}

void sfm_refresh_window(WINDOW *curr_window)
{
	wrefresh(curr_window);
	refresh();
}

int sfm_update_window(WINDOW *curr_window)
{
	sfm_ncurses_win *curr_interface = sfm_get_interface();

	if (curr_interface->sfm_win_menu == curr_window)
		return 1;

	wclear(curr_window);
	sfm_refresh_window(curr_window);
}

int sfm_update_window_status(WINDOW *curr_window, char *message)
{
	time_t c_time;
	struct tm *time_now;
	sfm_ncurses_win *curr_interface = sfm_get_interface();

	c_time = time(NULL);
	time_now = localtime(&c_time);

	if (curr_interface->sfm_win_status != curr_window)
		return 1;
	
	wclear(curr_interface->sfm_win_status);
	mvwprintw(curr_window, 1, 1, "%.2dm%.2ds %s", 
		time_now->tm_min, time_now->tm_sec, message);

	sfm_refresh_window(curr_window);
}

void sfm_trigger_menu_action(ITEM *curr_item)
{
	int menu_choices_size = ARRAY_SIZE(menu_choices);
	const char *choosed_item_name = item_name(curr_item);

	if (!choosed_item_name)
		return;

	for (int choice = 0; choice < menu_choices_size; choice++) {
		if (!strncmp(menu_choices[choice], choosed_item_name, strlen(menu_choices[choice]))) {
			return;
		}
	}
}

void sfm_make_menu(void)
{
	int n_menu_choices;

	keypad(iface->sfm_win_menu, TRUE);
	start_color();
	init_pair(1, COLOR_WHITE, COLOR_BLACK);

	wattron(iface->sfm_win_menu, COLOR_PAIR(1) | A_BOLD);
	mvwprintw(iface->sfm_win_menu, iface->lines - 2, iface->cols - 2, "");

	n_menu_choices = ARRAY_SIZE(menu_choices);
	iface->sfm_menu_items = (ITEM **)calloc(n_menu_choices + 1, sizeof(ITEM *));

	for (int i = 0; i < n_menu_choices; ++i)
		iface->sfm_menu_items[i] = new_item(menu_choices[i], NULL);
	iface->sfm_menu_items[n_menu_choices] = (ITEM *)NULL;

	iface->sfm_menu = new_menu((ITEM **)iface->sfm_menu_items);

	menu_opts_off(iface->sfm_menu, O_SHOWDESC);
	set_menu_format(iface->sfm_menu, 1, n_menu_choices);
	set_menu_mark(iface->sfm_menu, "@");
	post_menu(iface->sfm_menu);

	sfm_refresh_window(iface->sfm_win_menu);
	// free(iface->sfm_menu);
	// for (int i = 0; i < n_menu_choices; i++)
	// 	free(iface->sfm_menu_items[i]);
}

void sfm_make_window_file_list(void)
{
	int n_menu_choices;

	start_color();
	init_pair(1, COLOR_WHITE, COLOR_BLACK);

	wattron(iface->sfm_win_root, COLOR_PAIR(1) | A_BOLD);
	mvwprintw(iface->sfm_win_root, iface->lines - 2, iface->cols - 2, "");

	n_menu_choices = ARRAY_SIZE(menu_choices);
	iface->sfm_menu_items = (ITEM **)calloc(n_menu_choices + 1, sizeof(ITEM *));

	for (int i = 0; i < n_menu_choices; ++i)
		iface->sfm_menu_items[i] = new_item(menu_choices[i], NULL);
	iface->sfm_menu_items[n_menu_choices] = (ITEM *)NULL;

	iface->sfm_menu = new_menu((ITEM **)iface->sfm_menu_items);

	menu_opts_off(iface->sfm_menu, O_SHOWDESC);
	set_menu_format(iface->sfm_menu, 1, n_menu_choices);
	set_menu_mark(iface->sfm_menu, "@");
	post_menu(iface->sfm_menu);

	sfm_refresh_window(iface->sfm_win_root);
	free(iface->sfm_menu);
	for (int i = 0; i < n_menu_choices; i++)
		free(iface->sfm_menu_items[i]);
}

void sfm_make_windows(struct context *ctx)
{
	int nloop, c;
	iface = malloc(sizeof(sfm_ncurses_win));

	initscr();
	cbreak();

	getmaxyx(stdscr, iface->lines, iface->cols);

	iface->sfm_win_menu = sfm_create_window(2, iface->cols - 1, 0, 0);
	sfm_make_menu();
	sfm_refresh_window(iface->sfm_win_menu);

	iface->sfm_win_root = sfm_create_window(iface->lines - 4, iface->cols - 1, 2, 0);
	sfm_refresh_window(iface->sfm_win_root);

	iface->sfm_win_status = sfm_create_window(2, iface->cols - 1, iface->lines - 2, 0);
	sfm_refresh_window(iface->sfm_win_status);


	nloop = 0; 
	WINDOW *window_list[] = {
		iface->sfm_win_menu,
		iface->sfm_win_root,
		iface->sfm_win_status,
	};
	int window_list_size = ARRAY_SIZE(window_list);

	keypad(stdscr, TRUE);
	while (true)
	{
		char message[NAME_MAX];
		time_t c_time;
		struct tm *time_now;

		c_time = time(NULL);
		time_now = localtime(&c_time);

		c = getch();
		switch (c) {
		// case KEY_UP:
		// 	nloop++;
		// 	if (nloop > window_list_size)
		// 		nloop = window_list_size; 
		// 	break;
		// case KEY_DOWN:
		// 	nloop--;
		// 	if (nloop < 0)
		// 		nloop = window_list_size;
		// 	break;
		case KEY_LEFT:
			menu_driver(iface->sfm_menu, REQ_LEFT_ITEM);
			break;

		case KEY_RIGHT:
			menu_driver(iface->sfm_menu, REQ_RIGHT_ITEM);
			break;

		case KEY_DOWN: // TAB
			nloop++;
			if (nloop > window_list_size) 
				nloop = 0;
			sprintf(message, "loop->%d time->%.2d%.2d KEYDOWN", nloop, time_now->tm_min, time_now->tm_sec);
			sfm_update_window_status(window_list[nloop], message);

			break;
		case KEY_UP: // TAB
			nloop--; 
			if (nloop < 0) 
				nloop = window_list_size;
			sprintf(message, "loop->%d time->%.2d%.2d KEYUP", nloop, time_now->tm_min, time_now->tm_sec);
			sfm_update_window_status(window_list[nloop], message);

			break;
		case SFM_KEY_ENTER:
			if (iface->sfm_win_menu == window_list[nloop]) {
				ITEM *curr_item = current_item(iface->sfm_menu);
				sfm_trigger_menu_action(curr_item);
			}

			sfm_update_window_status(window_list[nloop], "HELLO");
			break;
				
/*		default:
			nloop++;
			if (nloop > window_list_size) 
				nloop = 0;
			break; */
		}
	
		wrefresh(window_list[nloop]);
		keypad(window_list[nloop], TRUE);
		refresh();

		usleep(250);
	}

	endwin();
}

void sfm_free(void)
{
	free(iface);
}

void sfm_ncurses(struct context *ctx)
{
	sfm_make_windows(ctx);
}
