#include "../settingsTui.h"

void marketMenuTui(){
	WINDOW *marketMenu;
	struct Profile p1;
	strcpy(p1.expBar, "[__________]");

	int highlight = 1, choice = 0;

	while(1){
		load_menu(market_menu_choices);
		if(info_panel_check){
			height = getmaxy(stdscr) - 2;
			width = getmaxx(stdscr) * 2 / 3 - 1;
			marketMenu = create_newwin(height, width, 1, 1);
		}

		else{
			height = get_menu_h(0);
			width = get_menu_w(0);
			marketMenu = create_newwin(height, width, Y_MEDIUM(stdscr), X_MEDIUM(stdscr));
		}
		print_menu(marketMenu, highlight, 1);

		choice = choose_keys(marketMenu);
		destroy_win(marketMenu);
		switch(choice){
			case 1:
				buyMenuTui();
				break;
			case 2: 
				//addProduct();
				break;
			case 3: 
				//removeProduct();
				break;
			case 4: 
				//changePrice();
				break;
			case 5:
				return;
		}
		choice = 0;
	}
}
