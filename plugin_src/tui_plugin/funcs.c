#include "settingsTui.h"

void taskMenuTui(){}
void inventoryMenuTui(){}
void profileTui(){}
void cheatMenuTui(){}

//Some functions that I didn't wanted to add to the main file
void load_menu(char **menu){
	choices = menu;
	n_choices = 0;

	while(choices[n_choices] != NULL) 
		n_choices++;
}

void load_menu_ll(struct node *head){
	struct node *current = head;
	int node_lenght = 0;
	while(current != NULL){
		node_lenght++;
		current = current->next;
	}
	choices = malloc((node_lenght + 2) * sizeof(*choices));

	current = head;
	int i = 0;
	while(current != NULL){
		choices[i] = malloc(sizeof(char) * MAX_ITEM_NAME);
		strcpy(choices[i], current->name);
		current = current->next;
		i++;
	}
	choices[i] = malloc(sizeof(char) * 5);
	strcpy(choices[i], "Exit");
	choices[i + 1] = NULL;
	n_choices = i + 1;
}

void clear_choices_ll(){
	for(int i = 0; choices[i] != NULL; i++){
		free(choices[i]);
	}
	free(choices);
}

void clear_ll(struct node *head){	
	struct node *current = head;
	struct node *deleted = current;
	while(current != NULL){
		current = current->next;
		free(deleted);
		deleted = current;
	}
}

void print_menu(WINDOW *menu_win, int highlight, int page_num){
	box(menu_win, 0, 0);
	//ratio = (height * 2 / 3) - 2;
	ratio = height - 4;

	if(ratio <= 0) ratio = 1;

	max_page = (n_choices + ratio - 1) / ratio;

	if(page_num > max_page){
		char *error = "Error: 'page' parameter is bigger than max_page!";
		mvwprintw(menu_win, y, X_MEDIUM_SEQ(menu_win, strlen(error)), error);
		getch();
		exit(1);
	}

	int start_index = (page_num - 1) * ratio;
	int end_index = (start_index + ratio);
	if(end_index > n_choices) end_index = n_choices;

	int item_middler = end_index - start_index;
	y = (getmaxy(menu_win) - item_middler) / 2;

	for(int i = start_index; i < end_index; i++){
		if(highlight == i + 1){
			x = X_MEDIUM_SEQ(menu_win, strlen(choices[i]));
			wattron(menu_win, A_REVERSE);
			mvwprintw(menu_win, y, x, "%s", choices[i]);	
			wattroff(menu_win, A_REVERSE);
		}

		else{
			x = X_MEDIUM_SEQ(menu_win, strlen(choices[i]));
			mvwprintw(menu_win, y, x, "%s", choices[i]);
		}
		y++;
	}
	wrefresh(menu_win);
}

WINDOW *create_newwin(int height, int width, int starty, int startx){
	WINDOW *local_win;

	local_win = newwin(height, width, starty, startx);
	
	box(local_win, 0, 0);

	wrefresh(local_win);

	return local_win;
}

void destroy_win(WINDOW *local_win){
	/* ncurses manual was showing wborder solution to delete windows but since I want to delete 
	 * whole window with its context, I learned werase() is much more useful. But maybe I can change this
	 *  another time idk */
	//wborder(local_win, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
	werase(local_win);
	wrefresh(local_win);
	delwin(local_win);
}

unsigned long hashPassword(char *str){
	unsigned long hash = 5381;
	int c;
	while((c = *str++))
		hash = ((hash << 5) + hash) + c;
	return hash;
}

int get_menu_h(int padding){
	height = n_choices + 4;
	while(getmaxy(stdscr) - 4 < height){
		height -= 2;
	}	

	if(padding == 0)
		return height;

	else 
		return height - padding;
}

int get_menu_w(int padding){
	size_t biggest = strlen(choices[0]);
	for(int i = 1; i < n_choices; i++){
		if(strlen(choices[i]) > biggest) 
			biggest = strlen(choices[i]);
	}
	if(padding == 0) width = biggest + 6;
	else width = biggest - padding;

	return width;
}

int choose_keys(WINDOW *menu){
	keypad(menu, TRUE);
	page = 1;
	choice = 0;

	while(1){
		print_menu(menu, highlight, page);
		c = wgetch(menu);
		
		switch(c){
			case KEY_UP:
				if(highlight == 1){
					highlight = n_choices;
					page = max_page;
					break;
				}
				else --highlight;

				if(highlight <= (page - 1) * ratio) page--;
				if(page < 1) page = max_page;

				break;

			case KEY_DOWN:
				if(highlight == n_choices){
					highlight = 1;
					page = 1;
					break;
				}
				else ++highlight;

				if(highlight > page * ratio) page++;
				if(page > max_page) page = 1;

				break;

			case KEY_RIGHT:
				if(page < max_page){
					highlight += ratio;
					if(highlight > n_choices) highlight = n_choices;
					page++;
				}
				break;

			case KEY_LEFT:
				if(page > 1){
					highlight -= ratio;
					if(highlight <= 0) highlight = 1;
					page--;
				}
				break;

			case KEY_F(1):	
				destroy_win(menu);
				endwin();
				exit(1);
				break;

			case 10:
				choice = highlight;
				highlight = 1;
				break;
		}
		werase(menu);
		if(choice != 0) break;
	}

	return choice;
}
