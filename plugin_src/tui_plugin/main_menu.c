#include "settingsTui.h"

void main_menu(){
	load_menu(menu_list_choices);
	WINDOW *main_menu;

	highlight = 1;
	choice = 0;
	char *good_bye_message = "See you!";

	noecho();
	cbreak();
	curs_set(0);

	char *info = "Use up and down arrow keys to move and return to choose";

	mvwprintw(stdscr, LINES - 1, X_MEDIUM_SEQ(stdscr, strlen(info)), "%s", info);


	//Menu for choosing marketplace, task, etc..
	while(1){
		info_panel();
		load_menu(menu_list_choices);
		height = get_menu_h(0);
		width = get_menu_w(0);
		
		main_menu = create_newwin(height, width, Y_MEDIUM(stdscr), X_MEDIUM(stdscr));
		print_menu(main_menu, highlight, 1);
		
		choice = choose_keys(main_menu);
		
		destroy_win(main_menu);
		switch(choice){
			case 0: 
				break;

			case 1:
				marketMenuTui();
				highlight = 1;
				break;
			
			case 2:
				taskMenuTui();
				highlight = 2;
				break;

			case 3:
				inventoryMenuTui();
				highlight = 3;
				break;

			case 4:
				cheatMenuTui(userName);
				highlight = 4;
				break;

			case 5:
				settingsMenuTui();
				highlight = 5;
				break;

			case 6:
				mvprintw(H_MEDIUM(stdscr), X_MEDIUM_SEQ(stdscr, strlen(good_bye_message)), good_bye_message);
				getch();
				endwin();
				exit(1);
				break;
		}

		choice = 0;

	}
}
