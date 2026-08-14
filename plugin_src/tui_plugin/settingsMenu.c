#include "settingsTui.h"

void settingsMenuTui(){
	load_menu(settings_menu_choices);

	highlight = 1, choice = 0;
	while(1){
		werase(stdscr);
	
		height = get_menu_h(0);
		width = get_menu_w(0);
		WINDOW *settingsMenu = create_newwin(height, width, Y_MEDIUM(stdscr), X_MEDIUM(stdscr));
		
		choice = choose_keys(settingsMenu);

		destroy_win(settingsMenu);

		switch(choice){
			//These features are on development right now. Changing username or password means lots of file process and I'm too lazy for that rn.
			
			case 1:
				FILE *auto_login = fopen(AUTO, "r");
				if(auto_login != NULL){
					remove(AUTO);
					char *mesg = "Auto login has been disabled! Press any key to exit.";
					mvwprintw(stdscr, Y_MEDIUM(stdscr), X_MEDIUM_SEQ(stdscr, strlen(mesg)), "%s", mesg);
					refresh();
					getch();
					werase(stdscr);
					refresh();
					fclose(auto_login);
					return;
				}

				else{
					char *mesg = "Auto login has already been disabled! Press any key to exit.";
					mvwprintw(stdscr, Y_MEDIUM(stdscr), X_MEDIUM_SEQ(stdscr, strlen(mesg)), "%s", mesg);
					refresh();
					getch();
					werase(stdscr);
					refresh();
				}
				break;
			/*
			case 2:
				char *newUserName[MAX_USER_NAME], char *u = "New username: ";
				height = 3;
				width = sizeof(u) + MAX_USER_NAME + 1;
				WINDOW changeName = create_newwin(height, width, Y_MEDIUM(stdscr), X_MEDIUM(stdscr));

				mvwprintw(changeName, Y_MEDIUM(changeName), 1, "%d", u);
				newUserName = wgetstr(changeName);

				FILE *userFile = fopen();
			
			case 3:
				//change password
				break;*/
			
			case 4:
				return;
		}
	}
}

