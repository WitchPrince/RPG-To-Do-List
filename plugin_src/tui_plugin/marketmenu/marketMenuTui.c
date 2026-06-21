#include "../settingsTui.h"

void marketMenuTui(){
	struct Profile p1;
	strcpy(p1.expBar, "[__________]");

	int highlight = 1, choice = 0;

	while(1){
		load_menu(market_menu_choices);

		height = get_menu_h(0);
		width = get_menu_w(20);

		WINDOW *marketMenu = create_newwin(height, width, Y_MEDIUM(stdscr), X_MEDIUM(stdscr));

		print_menu(marketMenu, highlight, 1);

		choice = choose_keys(marketMenu);
	
		switch(choice){
			case 1:
				destroy_win(marketMenu);
				//buyMenuTui();
				break;
			case 2: 
				destroy_win(marketMenu);
				//addProduct();
				break;
			case 3: 
				destroy_win(marketMenu);
				//removeProduct();
				break;
			case 4: 
				destroy_win(marketMenu);
				//changePrice();
				break;
			case 5:
				destroy_win(marketMenu);
				return;
		}
		choice = 0;
	}
}
