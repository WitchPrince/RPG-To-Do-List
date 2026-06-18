#include "../settingsTui.h"

void buyMenuTui(){
	bool foundInMarket = 1;
	int balance, oldBalance, count, highlight = 1;
	char wanted[MAX_ITEM_NAME];

	FILE *market = fopen(MARKET, "r");
	FILE *inventory = fopen(filePathI, "r");
	FILE *temp = fopen(TEMP, "w");

	struct Market m1;

	if(market == NULL){
		char *warning = "Market file isn't exist. Add some product so file can be created.";
		mvprintw(Y_MEDIUM(stdscr), X_MEDIUM_SEQ(stdscr, strlen(warning)), warning);
		return;
	}
	
	int i = 0;
	while(fscanf(market, "(%d) Product: %[^,], Price: %d\nItem Details:%[^\n]\n\n", &m1.id, m1.name, &m1.price, m1.detail) != EOF){
		buy_menu_choices[i] = malloc(strlen(m1.name) + 1);	
		strcpy(buy_menu_choices[i], m1.name);
		i++;
	}
	buy_menu_choices[i] = NULL;

	//these 2 lines are temporary, only for development stage. This is also a reminder to myself lol
	fclose(inventory); fclose(market); fclose(temp);
	remove(TEMP);
	
	load_menu(buy_menu_choices);
	WINDOW *buyMenu = create_newwin(getmaxy(stdscr) - 4, getmaxx(stdscr) * 2 / 3, 2, 2);

	print_menu(buyMenu, highlight);
	getch();

	for(i = 0; i < n_choices; i++){
		free(buy_menu_choices[i]);
	}
	destroy_win(buyMenu);
}
