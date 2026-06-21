#include "settingsTui.h"

//Global Variables
int n_choices, height, width, x, y, c, choice = 0, highlight = 1, page, max_page, ratio;

char **choices, filePathP[100], filePathI[100], userName[MAX_USER_NAME];

static void *tui_handle = NULL;

static int init(){
	return 0;
}

static int run(int argc, char *argv[]){
	initscr();
	int userNumber = userMenuTui();

	if(userNumber == 0){
		endwin();
		return 0;
	}

	struct Profile p1;
	FILE *user = fopen(USERLIST, "r");
	
	if(user == NULL){
		char *warning = "Userlist is empty! Create a user first.";
		
		x = X_MEDIUM_SEQ(stdscr, strlen(warning));
		y = Y_MEDIUM(stdscr);

		attron(A_BLINK);
		mvprintw(y, x, warning);
		getch();
		attroff(A_BLINK);
		endwin();

		return 0;
	}

	while(fscanf(user, "(%d) User: %s\n", &p1.number, p1.user) != EOF)
		if(userNumber == p1.number) break;

	sprintf(filePathP, USER_DIR, p1.user);
	sprintf(filePathI, INVENTORY, p1.user);

	main_menu();

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
