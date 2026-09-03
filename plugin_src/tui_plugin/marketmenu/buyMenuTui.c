#include "../settingsTui.h"

static int check_files();

void buyMenuTui(){
	struct Market m1;
	struct Profile p1;
	struct node *head = NULL;
	struct node *current;

	if(check_files() == -1){
		return;
	}
	
	FILE *profile = fopen(filePathP, "r");
	FILE *market = fopen(MARKET, "r");

	unsigned long __temp1;
	fscanf(profile, "User: %[^,], Password: %lu\n\nCurrency: %d\n", p1.user, &__temp1, &p1.currency);
	fclose(profile);

	while(fscanf(market, "(%d) Product: %[^,], Price: %d\nItem Details:%[^\n]\n\n", &m1.id, m1.name, &m1.price, m1.detail) != EOF){
		if(head == NULL){
			head = addNode(NULL);
			current = head;
			strcpy(current->name, m1.name);
			strcpy(current->details, m1.detail);
			continue;
		}
		current->next = addNode(head);
		current = current->next;
		strcpy(current->name, m1.name);
		strcpy(current->details, m1.detail);
	}

	rewind(market);

	char *wanted_product;
	int wanted_count;
	while(1){
		load_menu_ll(head);
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
		wanted_product = choices[choice - 1];

		if(!strcmp(wanted_product, "Exit")){
			destroy_win(buyMenu);
			break;
		}

		while(fscanf(market, "(%d) Product: %[^,], Price: %d\nItem Details:%[^\n]\n\n", &m1.id, m1.name, &m1.price, m1.detail) != EOF && strcmp(m1.name, wanted_product));	
		wclear(buyMenu);

		char *question = malloc(sizeof(char) * 256);
		snprintf(question, 256, "How many '%s' do you want (0-255):", wanted_product);
		mvwprintw(buyMenu, Y_MEDIUM(buyMenu), X_MEDIUM_SEQ(buyMenu, strlen(question)), question);
		free(question);

		//mvwscanw(buyMenu, Y_MEDIUM(buyMenu) + 2, X_MEDIUM(buyMenu), "%d", &wanted_count);
		wscanw(buyMenu, "%d", &wanted_count);
		wclear(buyMenu);
		if(p1.currency >= wanted_count * m1.price){
			p1.currency = p1.currency - wanted_count * m1.price;
			wclear(buyMenu);

			int control = buy_from_market(m1.name, filePathI, wanted_count);
			if(control == 1){
				char *SUCCESS = "Purchase completed!";
				mvwprintw(buyMenu, Y_MEDIUM(buyMenu), X_MEDIUM_SEQ(buyMenu, strlen(SUCCESS)), SUCCESS);
			}
			else if(control == 0){
				char *ERROR = "Some file error has occured!";
				mvwprintw(buyMenu, Y_MEDIUM(buyMenu), X_MEDIUM_SEQ(buyMenu, strlen(ERROR)), ERROR);
			}
		}
		clear_choices_ll();
		destroy_win(buyMenu);
	}
	clear_choices_ll();
	clear_ll(head);
	getch();
}

static int check_files(){
	FILE *market = fopen(MARKET, "r");
	if(market == NULL){
		char *warning = "Market file isn't exist. Add some product so file can be created.";
		mvprintw(Y_MEDIUM(stdscr), X_MEDIUM_SEQ(stdscr, strlen(warning)), warning);
		refresh();
		getch();
		return -1;
	}
	fclose(market);

	FILE *profile = fopen(filePathP, "r");
	if(profile == NULL){
		char *warning = "Profile file isn't exist. Probably some file corruption has occured. Please create a new profile!";
		mvprintw(Y_MEDIUM(stdscr), X_MEDIUM_SEQ(stdscr, strlen(warning)), warning);
		refresh();
		getch();
		return -1;
	}
	fclose(profile);

	return 1;
}
