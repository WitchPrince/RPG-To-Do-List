#include "../../settings.h"
#include "../../plugin.h"
#include <ncurses.h>

//Variables
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

unsigned long hashPassword(char *str);


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
	box(menu_win, 0, 0);
	int *x, y;
	y = getmaxy(menu_win);
	y = (y - n_choices) / 2;
	int startx = getmaxx(menu_win);

	for(int i = 0; i < n_choices; i++){
		if(highlight == i + 1){
			x[i] = (startx - sizeof(choices[i])) / 2;
			wattron(menu_win, A_REVERSE);
			mvwprintw(menu_win, y, x[i], "%s", choices[i]);	
			wattroff(menu_win, A_REVERSE);
		}

		else{
			x[i] = (startx - sizeof(choices[i])) / 2;
			mvwprintw(menu_win, y, x[i], "%s", choices[i]);
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

unsigned long hashPassword(char *str){
	unsigned long hash = 5381;
	int c;
	while((c = *str++))
		hash = ((hash << 5) + hash) + c;
	return hash;
}
