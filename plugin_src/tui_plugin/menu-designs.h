#include "../../settings.h"
#include "../../plugin.h"
#include <ncurses.h>

//Variables
int n_choices;
char **choices;
#define SIGN_UP_H (getmaxy()) 
#define SIGN_UP_W 30
#define LOGIN_W 30
#define LOGIN_H 10


//Macros
#define X_MEDIUM_SEQ(win, text) (getmaxx(win) - strlen(text)) / 2
#define X_MEDIUM(win) getmaxx(win) / 2 		//This is a requirement while creating a window. I didn't want to calculate it everytime
#define Y_MEDIUM(win) (getmaxy(win) - n_choices) / 2

#define MENU_H height = n_choices + 4
#define MENU_W int biggest = choices[0];\
		      for(int i = 1; i < n_choices; i++){\
				if(strlen(choices[i]) > biggest) biggest = strlen(choices[i])\
		      }\
		      width = biggest + 6
			

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
	int x, y;
	y = getmaxy(menu_win);
	y = (y - n_choices) / 2;
	int startx = getmaxx(menu_win);

	for(int i = 0; i < n_choices; i++){
		if(highlight == i + 1){
			x = (startx - strlen(choices[i])) / 2;
			wattron(menu_win, A_REVERSE);
			mvwprintw(menu_win, y, x, "%s", choices[i]);	
			wattroff(menu_win, A_REVERSE);
		}

		else{
			x = (startx - strlen(choices[i])) / 2;
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
	/* ncurses manual was showing wborder solution to delete windows but since I want to delete 
	 * whole window with its context, I learned werase() is much more useful. But maybe I can change this
	 *  another time idk */
	//wborder(local_win, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
	werase(local_win);
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
