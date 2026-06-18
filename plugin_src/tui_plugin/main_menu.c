#include "settingsTui.h"

void main_menu(){
	load_menu(menu_list_choices);
	WINDOW *main_menu;

	int highlight = 1, choice = 0;
	char *good_bye_message = "See you!";

	height = get_menu_h(0);
	width = get_menu_w(20);

	main_menu = create_newwin(height, width, Y_MEDIUM(stdscr), X_MEDIUM(stdscr));

	keypad(main_menu, TRUE);
	noecho();
	cbreak();
	curs_set(0);

	char *info = "Use up and down arrow keys to move and return to choose";

	mvwprintw(stdscr, LINES - 5, X_MEDIUM_SEQ(main_menu, strlen(info)), "%s", info);
	refresh();

	while(1){
		load_menu(menu_list_choices);
		print_menu(main_menu, highlight);
		
		choose_keys(main_menu);
		
		print_menu(main_menu, highlight);
		
		switch(choice){

			case 0: 
				break;

			case 1:
				destroy_win(main_menu);
				marketMenuTui();
				highlight = 1;
				break;
			
			case 2:
				destroy_win(main_menu);
				taskMenuTui();
				highlight = 2;
				break;

			case 3:
				destroy_win(main_menu);
				inventoryMenuTui();
				highlight = 3;
				break;

			case 4:
				destroy_win(main_menu);
				cheatMenuTui(userName);
				highlight = 4;
				break;

			case 5:
				destroy_win(main_menu);
				profileTui();
				highlight = 5;
				break;

			case 6:
				destroy_win(main_menu);
				settingsTui();
				highlight = 6;
				break;

			case 7:
				destroy_win(main_menu);
				mvprintw(H_MEDIUM(stdscr), X_MEDIUM_SEQ(stdscr, strlen(good_bye_message)), good_bye_message);
				getch();
				endwin();
				exit(1);
		}
		choice = 0;
	}
	endwin();
}
