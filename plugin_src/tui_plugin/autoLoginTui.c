#include "settingsTui.h"

void autoLoginTui(char user[MAX_USER_NAME]){
	WINDOW *auto_login_background = create_newwin(getmaxy(stdscr), getmaxx(stdscr), 0, 0);

	char *question = "Do you want automatic login to remain on for your account?";
	mvwprintw(auto_login_background, Y_MEDIUM(auto_login_background), X_MEDIUM_SEQ(auto_login_background, strlen(question)), "%s", question);
	wrefresh(auto_login_background);

	load_menu(yes_no_question);
	height = get_menu_h(0);
	width = get_menu_w(0);

	WINDOW *yes_no_menu = create_newwin(height, width, Y_MEDIUM(auto_login_background) + 1, X_MEDIUM(auto_login_background));

	print_menu(yes_no_menu, 1, 1);
	int decision = choose_keys(yes_no_menu);
	destroy_win(yes_no_menu);

	if(decision == 1){
		FILE *log = fopen(AUTO, "w");
		
		if(log != NULL){
			fprintf(log, "%s", user);
			fclose(log);
		}
		else{
			fprintf(stderr, "Log file couldn't open!");
			destroy_win(auto_login_background);
			return;
		}
	}

	else remove(AUTO);
	destroy_win(auto_login_background);
}

void logOut(){
	WINDOW *auto_login_background = create_newwin(getmaxy(stdscr), getmaxx(stdscr), 0, 0);
	char *question = "Do you want to log out of your account?";

	mvwprintw(auto_login_background, Y_MEDIUM(auto_login_background), X_MEDIUM_SEQ(auto_login_background, strlen(question)), "%s", question);
	wrefresh(auto_login_background);

	load_menu(yes_no_question);
	height = get_menu_h(0);
	width = get_menu_w(0);

	WINDOW *yes_no_menu = create_newwin(height, width, Y_MEDIUM(auto_login_background) + 1, X_MEDIUM(auto_login_background));

	print_menu(yes_no_menu, 1, 1);
	int decision = choose_keys(yes_no_menu);
	destroy_win(yes_no_menu);

	if(decision == 1) remove(AUTO);

	destroy_win(auto_login_background);
}
