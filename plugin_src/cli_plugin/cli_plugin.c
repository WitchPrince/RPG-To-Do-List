#include "../../plugin.h"
#include "../../settings.h"

static void *cli_handle = NULL;

static int init(){
	return 0;
}

static int run(int argc, char *argv[]){

	struct Profile p1;
	memset(&p1, 0, sizeof(struct Profile));

	int decision = 1, number, check = 0; 
	char filePathP[100], filePathI[100], tempUser[MAX_USER_NAME];

	FILE *log = fopen(AUTO, "r");
	FILE *nameList = fopen(USERLIST, "r");

	if(log != NULL){	
		fscanf(log, "%d\n", &check);
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

	if(log == NULL || check == 0){    
		number = userMenu();
		if(number == 0){
			printf("Sifre yanlis!");
			return 0;
		}
		
		nameList = fopen(USERLIST, "r");
		while(fscanf(nameList, "(%d) User: %s", &p1.number, p1.user) != EOF){
			if(number == p1.number) break;
		}
		fclose(nameList);
	
		autoLogin(p1.user);
	}

	sprintf(filePathP, USER_DIR, p1.user);
	sprintf(filePathI, INVENTORY, p1.user);

	printf("\nRPG To-Do List uygulamasina hosgeldiniz!");
	while(decision != 0){
		printf("\nYapmak istediğiniz islemi numara ile seciniz.\n\n(1) Marketplace\n(2) Tasks\n(3) Inventory\n(4) Cheat Menu\n(5) Profile\n(6) Settings\n(7) Exit\nDecision: ");
		scanf("%d", &decision);
		printf("\n-------------------------------------------------------\n\n");

		if(decision == 1) marketMenu(filePathP, filePathI);
	
		else if(decision == 2) taskMenu(filePathP, filePathI);

		else if(decision == 3) inventory(filePathI);

		else if(decision == 4) cheats(p1.user);

		else if(decision == 5) profileMenu(number);
			
		else if(decision == 6) logOut();

		else break;
	}

	return 0;
}

static void cleanup(){
	if(cli_handle){
		dlclose(cli_handle);
	}
}

Plugin *get_plugin_info(){
	static Plugin p = {
		.moduleName = "CLI_Plugin",
		.init = init,
		.run = run,
		.cleanup = cleanup
	};
	return &p;
}


