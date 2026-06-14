#include "menu-designs.h"

static void *tui_handle = NULL;

static int init(){
	return 0;
}

static int run(int argc, char *argv[]){
	userMenuTui(5, 30);
	endwin();
	return 0;
}

static void cleanup(){
	if(tui_handle){
		dlclose(tui_handle);
	}
}

Plugin *get_plugin_info(){
	static Plugin p = {
		.moduleName = "TUI_Plugin",
		.init = init,
		.run = run,
		.cleanup = cleanup
	};
	return &p;
}

int userMenuTui(int height, int width){
	load_menu(user_menu_choices);
	
	WINDOW *user_menu;
	WINDOW *login_menu;
	WINDOW *sign_up_menu;

	FILE *nameList;
	FILE *profile;

	struct Profile p1;
	strcpy(p1.expBar, "[__________]");
	unsigned long hash, hashInFile;
	char userName[MAX_USER_NAME], filePath[100];
	int userNumber = 1, check = 1;
	int highlight = 1, choice = 0;
	int x, y;
	int c;
	int width, height;
	

	initscr();
	curs_set(0);
	cbreak();
	noecho();

	y = Y_MEDIUM(stdscr);
	x = X_MEDIUM(stdscr);

	MENU_H;
	MENU_W;

	user_menu = create_newwin(height, width, y, x);
	keypad(user_menu, TRUE);

	x = X_MEDIUM_SEQ(user_menu, info);
	y = Y_MEDIUM(user_menu);

	char info[] = "Use up and down arrow key to move and return to choose";
	mvwprintw(stdscr, LINES - 5, x, "%s", info);
	refresh();
		
	print_menu(user_menu, highlight);

	while(1){
		c = wgetch(user_menu);

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

		print_menu(user_menu, highlight);
		if(choice != 0) break;
	}

	if(choice == 1){
		destroy_win(user_menu); 
		nameList = fopen(USERLIST, "r");
		
		if(nameList != NULL){
			MENU_H;
			MENU_W;
			login_menu = create_newwin(height, width, y, x);

			char *un = "User: ";
			x = X_MEDIUM_SEQ(login_menu, un);
			mvwprintw(login_menu, y + 1, x, un);

			char *p = "Password: ";
			x = X_MEDIUM_SEQ(login_menu, un);
			mvwprintw(login_menu, y + 3, x, p);
			refresh();

			mvwscanw(login_menu, y + 1, X_MEDIUM_SEQ(login_menu, un), "User: %s", p1.user);
			mvwscanw(login_menu, y + 3, X_MEDIUM_SEQ(login_menu, p), "Password: %s", p1.passwd);
			hash = hashPassword(p1.passwd);
			
			while(fscanf(nameList, "(%d) User: %[^\n]\n", &userNumber, userName) != EOF){
				if(strcmp(userName, p1.user) == 0){
					check = 0;
					
					sprintf(filePath, USER_DIR, userName);

					profile = fopen(filePath, "r");
					fscanf(profile, "User: %[^,], Password: %lu", userName, &hashInFile);

					if(hash == hashInFile){
						destroy_win(login_menu);
					
						x = X_MEDIUM(stdscr);	
						y = Y_MEDIUM(stdscr);
						mvwprintw(stdscr, y, x, "Login succeed! Welcome %s!", userName);
						refresh();
						
						timeout(3000);
						getch();
						timeout(-1);

						fclose(nameList); fclose(profile);
						return userNumber;
					}

					else{
						destroy_win(login_menu);
						char *warning = "Password isn't correct! Try again!";
						
						mvwprintw(stdscr, Y_MEDIUM(stdscr), X_MEDIUM_SEQ(stdscr, warning), warning);			
						mvwprintw(stdscr, LINES - 1, X_MEDIUM(stdscr), "Press anything to exit!");
						getch();
						refresh();
						endwin();
						
						fclose(nameList); fclose(profile);
						return 0;
					}
				}

				if(check){
					destroy_win(login_menu);

					char *warning = "Username isn't exist! Please create a new one.";
					
					mvwprintw(stdscr, Y_MEDIUM(stdscr), X_MEDIUM_SEQ(stdscr, warning), warning);
					getch();
					refresh();
					endwin();
					
					fclose(nameList);
					return 0;
				}
			}
		}

		else{
			char *warning = "User list is empty! Please create a user first.";
			X_MEDIUM_SEQ(stdscr, warning);
			Y_MEDIUM(stdscr);

			mvwprintw(stdscr, y, x, warning);
			mvwprintw(stdscr, LINES - 1, , "Press anything to exit!");
			refresh();
			endwin();
			return 0;	
		}
	}

	if(choice == 2){
		nameList = fopen(USERLIST, "a+");

		if(nameList != NULL){
			destroy_win(user_menu);

			MENU_H;
			MENU_W;

			x = (getmaxx(stdscr) - width) / 2;
			y = Y_MEDIUM(stdscr);

			sign_up_menu = create_newwin(height, width, y, x);

			/* idk if this is the most efficient way to center sentences. 
			 * please let me know if there's another way. This macro is also so tiring tbh */
			char *welcome = "Welcome to RPG To-Do List app!";
			mvwprintw(sign_up_menu, 0, X_M(sign_up_menu, welcome), welcome);
			char *un = "Username: ";
			mvwprintw(sign_up_menu, y + 2, X_M(sign_up_menu, un), un);
			char *p = "Password: ";
			mvwprintw(sign_up_menu, y + 3, X_M(sign_up_menu, p), p);
	
			mvwscanw(sign_up_menu, y + 2, X_M(sign_up_menu, un), "Username: %s", p1.user);
			mvwscanw(sign_up_menu, y + 3, X_M(sign_up_menu, p), "Password: %s", p1.passwd);
			hash = hashPassword(p1.passwd);
			sprintf(filePath, USER_DIR, p1.user);

			while(fscanf(nameList, "(%d) User: %s\n", &userNumber, userName) != EOF);
				
			rewind(nameList);
			fprintf(nameList, "(%d) User: %s\n", userNumber + 1, p1.user);

			profile = fopen(filePath, "w");
			fprintf(profile, "User: %s, Password: %lu\n\nCurrency: 0\nExp: 0\nLevel: 0, Exp Bar ==> %s\n", p1.user, hash, p1.expBar);

			fclose(profile); fclose(nameList);
			return userNumber + 1;
		}

		else{
			nameList = fopen(USERLIST, "w");
			fprintf(nameList, "(1) User: %s\n", p1.user);
		
			profile = fopen(filePath, "w");
			fprintf(profile, "User: %s, Password: %lu\n\nCurrency: 0\nExp: 0\nLevel: 0, Exp Bar ==> %s\n", p1.user, hash, p1.expBar);
			
			fclose(nameList); fclose(profile);
			return 1;
		}
	}
	endwin();
	return 0;
}
