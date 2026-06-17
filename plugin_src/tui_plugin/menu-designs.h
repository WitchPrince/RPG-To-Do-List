#ifndef MENU_DESIGNS_H
#define MENU_DESIGNS_H

#include "../../settings.h"
#include "../../plugin.h"
#include <ncurses.h>

//Variables
extern int n_choices, height, width, x, y;
extern char **choices, filePathP[100], filePathI[100], userName[MAX_USER_NAME];

//Menu lists
extern char *user_menu_choices[];
extern char *menu_list_choices[];

//Macros
#define X_MEDIUM_SEQ(win, lenght) (getmaxx(win) - lenght) / 2
#define X_MEDIUM(win) (getmaxx(win) - width) / 2 		//This is a requirement while creating a window. I didn't want to calculate it everytime
#define Y_MEDIUM(win) (getmaxy(win) - n_choices - height) / 2	//This is for creating a window too
#define H_MEDIUM(win) getmaxy(win) / 2			
#define Y_MEDIUM_LIST(win) (getmaxy(win) - n_choices) / 2

//Function headers
void print_menu(WINDOW *menu_win, int highlight);
void load_menu(char **menu);
void destroy_win(WINDOW *local_win);
WINDOW *create_newwin(int height, int width, int starty, int startx);

int get_menu_h(int padding);
int get_menu_w(int padding);

int userMenuTui();
void main_menu();
void taskMenuTui();
void inventoryMenuTui();
void marketMenuTui();
void profileTui();
void cheatMenuTui(char userName[MAX_USER_NAME]);
void settingsTui();

unsigned long hashPassword(char *str);

#endif
