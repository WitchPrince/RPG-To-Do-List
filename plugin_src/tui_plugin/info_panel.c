#include "settingsTui.h"

int info_panel(){
	//Profile at right
	struct Profile p1;
	FILE *profile = fopen(filePathP, "r");
	unsigned long hash;
	char *lvl = "Level: ";
	char expBar[23];
	
	fscanf(profile, "User: %[^,], Password: %lu\n\nCurrency: %d\nExp: %d\nLevel: %d, Exp Bar ==> %[^\n]\n", p1.user, &hash, &p1.currency, &p1.exp, &p1.level, p1.expBar);
	fclose(profile);
	strcpy(expBar, p1.expBar);

	height = getmaxy(stdscr) - 2;
	width = (getmaxx(stdscr) / 3) - 1;
	WINDOW *right_inventory = create_newwin(height, width, 1, (getmaxx(stdscr) * 2 / 3) + 1);

	if(width > 24){
		int i = 1;
		while(i < 11){
			if(p1.expBar[i] == '_') break;
			if(p1.expBar[i] == '=') i++;
		}
		i = (i - 1) * 2;
		expBar[0] = '[';
		int count = 1;
		while(count < 21){
			if(count <= i){
				expBar[count] = '=';
			}
			else{
				expBar[count] = '_';
			}
			count++;
		}
		expBar[21] = ']';
		expBar[22] = '\0';
	}

	mvwprintw(right_inventory, 2, X_MEDIUM_SEQ(right_inventory, strlen(p1.user)), "%s", p1.user);
	mvwhline(right_inventory, 4, 1, '-', getmaxx(right_inventory) - 2);

	mvwprintw(right_inventory, 6, 1, "Currency: %d", p1.currency);

	mvwprintw(right_inventory, height - 4, 1, "Exp: %d", p1.exp);
	mvwprintw(right_inventory, height - 3, X_MEDIUM_SEQ(right_inventory,strlen(lvl) + 1),"%s%d", lvl, p1.level);
	mvwprintw(right_inventory, height - 2, X_MEDIUM_SEQ(right_inventory, strlen(expBar)), "%s", expBar);

	wrefresh(right_inventory);

	return 1;
}
