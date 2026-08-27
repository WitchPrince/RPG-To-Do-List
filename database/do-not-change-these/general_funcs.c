#include "../../settings.h"
//#include "../../plugin_src/cli_plugin/settingsCli.h"

int isExist(const char *i_name, const char *i_path){
	FILE *inventory = fopen(i_path, "r");
	int _dummy;
	int _dummy2;
	char *_dummy3;
	char *readed;

	fscanf(inventory, "Currency: %d\n\n", &_dummy);
	
	while(fscanf(inventory, "%[^,], %d, Item Details:\n%[^\n]\n\n", readed, &_dummy2, _dummy3) != EOF || strcmp(i_name, readed));

	return !strcmp(i_name, readed);
}

int add_to_inventory(const char *i_name, const char *i_path, unsigned int i_count){
	//Error Codes
	//0: File error. Some file or files doesn't exist.
	//1: Success

	int exist = isExist(i_name, i_path);
	int _dummy;
	int _dummy2;

	char *name;

	struct Item i1;
	struct Profile p1;
	struct Market m1;

	FILE *inventory;
	FILE *temp;
	FILE *market = fopen(MARKET, "r");

	if(inventory == NULL && temp == NULL && market == NULL) return 0;

	while(fscanf(market, "(%d) Product: %s, Price: %d\nItem Details:%s\n\n", _dummy, name, _dummy2, i1.itemDetails) != EOF && strcmp(i_name, name));
	fclose(market);

	if(exist){
		temp = fopen(TEMPU, "w");
		inventory = fopen(i_path, "r");

		fscanf(inventory, "Currency: %d\n\n", &p1.currency);
		fprintf(temp, "Currency: %d\n\n", p1.currency);
		while(fscanf(inventory, "%[^,], %d, Item Details:\n%[^\n]\n\n", i1.itemName, &i1.itemCount, i1.itemDetails) != EOF){
			fprintf(temp, "%s, %d, Item Details:\n%s\n\n", i1.itemName, i1.itemCount, i1.itemDetails);
		}

		fclose(inventory); fclose(temp);
		remove(filePathI);
		rename(TEMPU, filePathI);

		return 1;
	}

	else{
		inventory = fopen(filePathI, "a");
		fprintf(inventory, "%s, %d, Item Details:\n%s\n\n", i_name, i_count, i1.itemDetails);
		fclose(inventory);

		return 1;
	}
}

int add_to_market(const char *i_name, const i_price, const char *i_details){
	//Error codes
	//0: File couldn't found.
	//1: Success
	//2: Product is already in the market list.

	FILE *market = fopen(MARKET, "r");
	FILE *temp;
	
	struct Market m1;

	bool check = false;

	if(market == NULL){
		return 0;
	}

	while(fscanf(market, "(%d) Product: %[^,], Price: %d\nItem Details: [^\n]\n\n", &m1.id, m1.name, m1.price, m1.detail) != EOF){
		if(!strcmp(m1.name, i_name)){
			check = true;
		}
	}

	if(!check){
		temp = fopen(TEMP, "w");
		rewind(market);
	
		while(fscanf(market, "(%d) Product: %[^,], Price: %d\nItem Details: [^\n]\n\n", &m1.id, m1.name, m1.price, m1.detail) != EOF){
			fprintf(temp, "(%d) Product: %s, Price: %d\nItem Details: %s\n\n", m1.id, m1.name, m1.price, m1.detail);
		}
		m1.id++;
		
		fprintf(temp, "(%d) Product: %s, Price: %d\nItem Details: %s\n\n", m1.id, i_name, i_price, i_details);

		fclose(temp);
		fclose(market);
		remove(market);
		rename(TEMP, MARKET);		
	}

	else{
		fclose(temp);
		fclose(market);
		remove(TEMP);
		return 2;
	}
}

int add_to_task_list(const char *t_name, const int t_difficulty, const int t_reward, const int t_exp, const char *t_details){
	//Error Codes
	//0: File error
	//1: Success
	//2: Task name is already in use.
	
	FILE *tasks = fopen(TASKS, "r");
	if(tasks == NULL) return 0;

	struct Tasks t1;

	while(fscanf(tasks, "Task name: %[^,], Difficulty: %d, Reward: %d, Exp: %d\nTask Details:\n%[^\n]\n\n", t1.taskName, &t1.difficulty, &t1.reward, &t1.exp, t1.taskDetails) != EOF){
		if(!strcmp(t_name, t1.taskName)){
			fclose(tasks);
			return 2;
		}
	}
	fclose(tasks);
	tasks = fopen(TASKS, "a");
	if(tasks == NULL) return 0;

	fprintf(tasks, "Task name: %s, Difficulty: %d, Reward: %d, Exp: %d\nTask Details:\n%s\n\n", t_name, t_difficulty, t_reward, t_exp, t_details);

	fclose(tasks);
	return 1;
}
