#include "../settingsTui.h"

void buyMenuTui(){
	//bool foundInMarket = 1;
	//int balance, oldBalance, count, highlight = 1;
	//char wanted[MAX_ITEM_NAME];

	FILE *profile = fopen(filePathP, "r");
	FILE *market = fopen(MARKET, "r");

	struct Market m1;
	struct Profile p1;

	if(market == NULL){
		char *warning = "Market file isn't exist. Add some product so file can be created.";
		mvprintw(Y_MEDIUM(stdscr), X_MEDIUM_SEQ(stdscr, strlen(warning)), warning);
		refresh();
		getch();
		return;
	}

	if(profile != NULL){
		char *__temp = malloc(sizeof(char) * MAX_USER_NAME);
		unsigned long __temp2;
		fscanf(profile, "User: %[^,], Password: %lu\n\nCurrency: %d\n", __temp, &__temp2, &p1.currency);
		free(__temp);
		fclose(profile);
	}

	//This code block is for creating buy_menu_choices list since I couldn't know how long it could be. Tbh it looks inefficient but I didn't want to create a new file for saving each list. It could be change in the future. Please comment if there's another way.
	int i = 0;
	while(fscanf(market, "(%d) Product: %[^,], Price: %d\nItem Details:%[^\n]\n\n", &m1.id, m1.name, &m1.price, m1.detail) != EOF){
		buy_menu_choices[i] = malloc(strlen(m1.name) + 1);	
		strcpy(buy_menu_choices[i], m1.name);
		i++;
	}
	buy_menu_choices[i] = NULL;

	//these 3 lines are temporary, only for development stage. This is also a reminder to myself lol
	rewind(market);

	char *wanted_product;
	int wanted_count;
	while(1){
		load_menu(buy_menu_choices);
		WINDOW *buyMenu;
	
		if(info_panel_check) {
			height = getmaxy(stdscr) - 2;
			width = getmaxx(stdscr) * 2 / 3 - 1;
			buyMenu = create_newwin(height, width, 1, 1);
		}
		else{
			height = get_menu_h(0);
			width = get_menu_w(0);
			buyMenu = create_newwin(height, width, Y_MEDIUM(stdscr), X_MEDIUM(stdscr));
		}
	
		print_menu(buyMenu, highlight, 1);

		choice = choose_keys(buyMenu);
		wanted_product = buy_menu_choices[choice - 1];
		while(fscanf(market, "(%d) Product: %[^,], Price: %d\nItem Details:%[^\n]\n\n", &m1.id, m1.name, &m1.price, m1.detail) != EOF || strcmp(m1.name, wanted_product));	
		wclear(buyMenu);

		char *question = malloc(sizeof(char) * 256);
		snprintf(question, 256, "How many '%s' do you want (0-255):", wanted_product);
		mvwprintw(buyMenu, Y_MEDIUM(buyMenu), X_MEDIUM_SEQ(buyMenu, strlen(question)), question);
		free(question);

		mvwscanw(buyMenu, Y_MEDIUM(buyMenu) + 2, X_MEDIUM(buyMenu), "%d", &wanted_count);
		wclear(buyMenu);
		if(p1.currency >= wanted_count * m1.price){
			p1.currency = p1.currency - wanted_count * m1.price;
			wclear(buyMenu);

			int control = add_to_inventory(m1.name, filePathI, wanted_count);
			if(control == 1){
				char *SUCCESS = "Purchase completed!";
				mvwprintw(buyMenu, Y_MEDIUM(buyMenu), X_MEDIUM_SEQ(buyMenu, strlen(SUCCESS)), SUCCESS);
			}
			else if(control == 0){
				char *ERROR = "Some file error has occured!";
				mvwprintw(buyMenu, Y_MEDIUM(buyMenu), X_MEDIUM_SEQ(buyMenu, strlen(ERROR)), ERROR);
			}
		}
		destroy_win(buyMenu);
	}

	getch();

	for(i = 0; i < n_choices; i++){
		free(buy_menu_choices[i]);
	}
}
