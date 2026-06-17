#include "menu-designs.h"

void main_menu(){
	WINDOW *main_menu;
	int c, highlight = 1, choice = 0;

	height = get_menu_h(20);
	width = get_menu_w(60);
	y = Y_MEDIUM(stdscr);
	x = X_MEDIUM(stdscr);

	main_menu = create_newwin(height, width, y, x);
	keypad(main_menu, TRUE);
	noecho();
	cbreak();
	curs_set(0);

	char *info = "Use up and down arrow keys to move and return to choose";

	x = X_MEDIUM_SEQ(main_menu, strlen(info));
	y = Y_MEDIUM(main_menu);
	
	mvwprintw(stdscr, LINES - 5, x, "%s", info);
	refresh();

	print_menu(main_menu, highlight);

	while(1){
		c = wgetch(main_menu);

		switch(c){
			case KEY_UP:
				if(highlight == 1)
					highlight = n_choices;
				else
					--highlight;
				break;

			case KEY_DOWN:
				if(highlight == n_choices)
					highlight = 1;
				else
					++highlight;
				break;
			
			case KEY_F(1):
				endwin();
				exit(1);

			case 10:
				choice = highlight;
				break;
		}
		
		print_menu(main_menu, highlight);
		
		switch(choice){

			case 0: 
				break;

			case 1:
				marketMenuTui();
				break;
			
			case 2:
				taskMenuTui();
				break;

			case 3:
				inventoryMenuTui();
				break;

			case 4:
				cheatMenuTui(userName);
				break;

			case 5:
				profileTui();
				break;

			case 6:
				settingsTui();
				break;

			case 7:
				destroy_win(main_menu);
				char *message = "See you!";
				mvprintw(Y_MEDIUM(stdscr), X_MEDIUM_SEQ(stdscr, strlen(message)), message);
				getch();
				endwin();
				exit(1);
		}
		choice = 0;
	}
}
