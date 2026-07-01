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
	int number;
	char tempUser[MAX_USER_NAME];
	
	//Idk if I need memset for reset this struct at this point. Because project got much more
	//complicated than I expected. But there's no harm for using it.
	struct Profile p1;
	memset(&p1, 0, sizeof(struct Profile));

	FILE *log = fopen(AUTO, "r");
	FILE *nameList = fopen(USERLIST, "r");
	if(log != NULL){
		fscanf(log, "%s", p1.user);
		fclose(log);

		if(nameList != NULL){
			while(fscanf(nameList, "(%d) User: %s", &p1.number, tempUser) != EOF){
				if(strcmp(p1.user, tempUser) == 0){
					number = p1.number;
					fclose(nameList);
					break;
				}
			}
		}
	}

	else{
		number = userMenuTui();
		
		if(number == 0){
			endwin();
			return 0;
		}

		nameList = fopen(USERLIST, "r");
	
		if(nameList == NULL){
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
		
		else{
			while(fscanf(nameList, "(%d) User: %s", &p1.number, p1.user) != EOF){
				if(number == p1.number) break;
			}
			fclose(nameList);
		}
		autoLoginTui(p1.user);
	}

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
