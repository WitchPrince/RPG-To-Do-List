#ifndef SETTINGSTUI_H
#define SETTINGSTUI_H

#include "../../settings.h"
#include "../../plugin.h"
#include <ncurses.h>

//Variables
extern int n_choices, height, width, x, y, c, choice, highlight, page, max_page, ratio;
extern char **choices, filePathP[100], filePathI[100], userName[MAX_USER_NAME];

//Menu lists
extern char *user_menu_choices[];
extern char *login_choices[];
extern char *yes_no_question[];
extern char *menu_list_choices[];
extern char *market_menu_choices[];
extern char *buy_menu_choices[100];
extern char *settings_menu_choices[];

//Macros
#define X_MEDIUM_SEQ(win, lenght) (getmaxx(win) - lenght) / 2
#define X_MEDIUM(win) (getmaxx(win) - width) / 2 		//This is a requirement while creating a middle window. I didn't want to calculate it everytime
#define Y_MEDIUM(win) (getmaxy(win) - height) / 2	//This is for creating a middle window too
#define H_MEDIUM(win) (getmaxy(win) / 2)			
#define Y_MEDIUM_LIST(win) (getmaxy(win) - n_choices) / 2


//Function headers
void print_menu(WINDOW *menu_win, int highlight, int page);
void load_menu(char **menu);
void destroy_win(WINDOW *local_win);
WINDOW *create_newwin(int height, int width, int starty, int startx);
int choose_keys(WINDOW *menu);

int get_menu_h(int padding);
int get_menu_w(int padding);

int userMenuTui();
void autoLoginTui(char user[MAX_USER_NAME]);
void logOut();
void main_menu();
int info_panel();
void taskMenuTui();
void inventoryMenuTui();
void marketMenuTui();
void buyMenuTui();
void profileTui();
void cheatMenuTui(char userName[MAX_USER_NAME]);
void settingsMenuTui();

unsigned long hashPassword(char *str);

#endif
