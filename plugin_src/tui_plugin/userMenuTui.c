#include "settingsTui.h"

int userMenuTui(){

	load_menu(user_menu_choices);
	
	WINDOW *user_menu;
	WINDOW *login_menu;
	WINDOW *sign_up_menu;

	FILE *nameList;
	FILE *profile;

	struct Profile p1;
	strcpy(p1.expBar, "[__________]");
	unsigned long hash, hashInFile;
	int userNumber = 0, check = 1;
	int highlight = 1, choice = 0;
	
	curs_set(0);
	cbreak();
	noecho();

	height = get_menu_h(10);
	width = get_menu_w(30);
	y = Y_MEDIUM(stdscr);
	x = X_MEDIUM(stdscr);

	user_menu = create_newwin(height, width, y, x);
	keypad(user_menu, TRUE);

	char *info = "Use up and down arrow keys to move and return to choose";
	char *un = "Username: ";
	char *p = "Password: ";
		
	x = X_MEDIUM_SEQ(user_menu, strlen(info));
	y = Y_MEDIUM(user_menu);

	mvwprintw(stdscr, LINES - 5, x, "%s", info);
	refresh();
		
	print_menu(user_menu, highlight, 1);

	choice = choose_keys(user_menu);

	if(choice == 1){
		destroy_win(user_menu); 
		
		height = get_menu_h(20);
		width = get_menu_w(60);
		login_menu = create_newwin(height, width, Y_MEDIUM(stdscr), X_MEDIUM(stdscr));

		nameList = fopen(USERLIST, "r");
		
		if(nameList != NULL){
			curs_set(1);
			echo();
			mvwprintw(login_menu, H_MEDIUM(login_menu) - 1, X_MEDIUM_SEQ(login_menu, (strlen(un) + MAX_USER_NAME)), un);
			wrefresh(login_menu);
			wgetnstr(login_menu, p1.user, MAX_USER_NAME);

			x = X_MEDIUM_SEQ(login_menu, (strlen(p) + MAX_PASSWD));
			mvwprintw(login_menu, H_MEDIUM(login_menu) + 1, x, p);
			wrefresh(login_menu);
			wgetnstr(login_menu, p1.passwd, MAX_PASSWD);

			curs_set(0);
			noecho();

			hash = hashPassword(p1.passwd);
			
			while(fscanf(nameList, "(%d) User: %[^\n]\n", &userNumber, userName) != EOF){
				if(strcmp(userName, p1.user) == 0){
					check = 0;

					sprintf(filePathP, USER_DIR, userName);
					
					profile = fopen(filePathP, "r");
					fscanf(profile, "User: %[^,], Password: %lu", userName, &hashInFile);

					if(hash == hashInFile){
						destroy_win(login_menu);
						char *enter_success = "Login succeed! Welcome!";	
						mvwprintw(stdscr, Y_MEDIUM(stdscr), X_MEDIUM_SEQ(stdscr, strlen(enter_success)), enter_success);
						refresh();
						
						getch();
						fclose(nameList); fclose(profile);
						return userNumber;
					}

					else{
						destroy_win(login_menu);
						char *warning = "Password isn't correct! Try again!";
						char *exit = "Press anything to exit!";
						
						mvwprintw(stdscr, H_MEDIUM(stdscr), X_MEDIUM_SEQ(stdscr, strlen(warning)), warning);			
						mvwprintw(stdscr, LINES - 3, X_MEDIUM_SEQ(stdscr, strlen(exit)), exit);
						getch();
						refresh();
						endwin();
						
						fclose(nameList); fclose(profile);
						return 0;
					}
				}


			}
			if(check){
				destroy_win(login_menu);
				char *warning = "Username isn't exist! Please create a new one.";
					
				mvwprintw(stdscr, Y_MEDIUM(stdscr), X_MEDIUM_SEQ(stdscr, strlen(warning)), warning);
				getch();
				refresh();
				endwin();
					
				fclose(nameList);
				return 0;
			}
		}

		else{
			destroy_win(login_menu);
			char *warning = "User list is empty! Please create a user first.";
			char *exit_ch = "Press anything to exit!";

			mvwprintw(stdscr, H_MEDIUM(stdscr), X_MEDIUM_SEQ(stdscr, strlen(warning)), warning);
			mvwprintw(stdscr, LINES - 3, X_MEDIUM_SEQ(stdscr, strlen(exit_ch)), exit_ch);
			refresh();
			getch();
			endwin();
			return 0;	
		}
	}

	if(choice == 2){
		nameList = fopen(USERLIST, "a+");

		if(nameList != NULL){
			destroy_win(user_menu);

			height = get_menu_h(20);
			width = get_menu_w(60);

			sign_up_menu = create_newwin(height, width, Y_MEDIUM(stdscr), X_MEDIUM(stdscr));

			y = H_MEDIUM(sign_up_menu);
			/* idk if this is the most efficient way to center sentences. 
			 * please let me know if there's another way. This macro is also so tiring tbh */
			char *welcome = "Welcome to RPG To-Do List app!";
			mvwprintw(sign_up_menu, 1, X_MEDIUM_SEQ(sign_up_menu, strlen(welcome)), welcome);
		
			curs_set(1);	
			echo();	
			
			mvwprintw(sign_up_menu, y - 1, X_MEDIUM_SEQ(sign_up_menu, (strlen(un) + MAX_USER_NAME)), un);
			wrefresh(sign_up_menu);
			wgetnstr(sign_up_menu, p1.user, MAX_USER_NAME);

			while(fscanf(nameList, "(%d) User: %s\n", &userNumber, userName) != EOF){
				if(strcmp(userName, p1.user) == 0){
					destroy_win(sign_up_menu);
					char *warning = "A user has already using that name! Pick up another one.";
					mvwprintw(stdscr, H_MEDIUM(stdscr), X_MEDIUM_SEQ(stdscr, strlen(warning)), warning);
					fclose(nameList);
					return 0;
				}
			}

			mvwprintw(sign_up_menu, y + 1, X_MEDIUM_SEQ(sign_up_menu, (strlen(p) + MAX_PASSWD)), p);
			wrefresh(sign_up_menu);
			wgetnstr(sign_up_menu, p1.passwd, MAX_PASSWD);
			destroy_win(sign_up_menu);

			curs_set(0);
			noecho();

			hash = hashPassword(p1.passwd);
			sprintf(filePathP, USER_DIR, p1.user);
		
			char tempName[MAX_USER_NAME];	
			while(fscanf(nameList, "(%d) User: %s\n", &userNumber, tempName) != EOF);
				
			rewind(nameList);
			fprintf(nameList, "(%d) User: %s\n", userNumber + 1, p1.user);

			profile = fopen(filePathP, "w");
			fprintf(profile, "User: %s, Password: %lu\n\nCurrency: 0\nExp: 0\nLevel: 0, Exp Bar ==> %s\n", p1.user, hash, p1.expBar);

			fclose(profile); fclose(nameList);
			return userNumber + 1;
		}

		else{
			nameList = fopen(USERLIST, "w");
			fprintf(nameList, "(1) User: %s\n", p1.user);
		
			profile = fopen(filePathP, "w");
			fprintf(profile, "User: %s, Password: %lu\n\nCurrency: 0\nExp: 0\nLevel: 0, Exp Bar ==> %s\n", p1.user, hash, p1.expBar);
			
			fclose(nameList); fclose(profile);
			return 1;
		}
	}
	endwin();
	return 0;
}
