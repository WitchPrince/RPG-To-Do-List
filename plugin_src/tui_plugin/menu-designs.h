#include "../../settings.h"
#include "../../plugin.h"
#include <ncurses.h>

int n_choices;
char **choices;

//Function headers
void print_menu(WINDOW *menu_win, int highlight);
void load_menu(char **menu);
void destroy_win(WINDOW *local_win);
WINDOW *create_newwin(int height, int width, int starty, int startx);

int userMenuTui(int height, int width);

WINDOW *taskMenuTui(int height, int width);
WINDOW *inventoryTui(int height, int width);
WINDOW *marketMenuTui(int height, int width);
WINDOW *profileTui(int height, int width);
WINDOW *cheatMenuTui(int height, int width);
WINDOW *settingsTui(int height, int width);


//Menu lists
char *user_menu_choices[] = {
				"Login",
				"Sign Up",
				NULL,
};


//Some functions that I didn't want to add to the main file
void load_menu(char **menu){
	choices = menu;
	n_choices = 0;

	while(choices[n_choices] != NULL) 
		n_choices++;
}

void print_menu(WINDOW *menu_win, int highlight){
	int x, y;

	x = 2;
	y = 2;

	box(menu_win, 0, 0);

	for(int i = 0; i < n_choices; i++){
		if(highlight == i + 1){
			wattron(menu_win, A_REVERSE);
			mvwprintw(menu_win, y, x, "%s", choices[i]);	
		}

		else{
			mvwprintw(menu_win, y, x, "%s", choices[i]);
		}
		++y;
	}
	wrefresh(menu_win);
}

WINDOW *create_newwin(int height, int width, int starty, int startx){
	WINDOW *local_win;

	local_win = newwin(height, width, starty, startx);
	box(local_win, 0, 0);

	wrefresh(local_win);

	return local_win;
}

void destroy_win(WINDOW *local_win){
	wborder(local_win, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
	wrefresh(local_win);
	delwin(local_win);
}
