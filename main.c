#include "settings.h"
#include "plugin.h"

int main(int argc, char *argv[]){
	
	struct Profile p1;
	int decision = 1, number, check = 0; 
	char filePathP[100], filePathI[100], tempUser[MAX_USER_NAME];

	FILE *log = fopen(AUTO, "r");
	FILE *nameList = fopen(USERLIST, "r");

	if(log != NULL){	
		fscanf(log, "%d\n", &check);
		fscanf(log, "%s", p1.user);
 		fclose(log);
	
		while(fscanf(nameList, "(%d) User: %s", &p1.number, tempUser) != EOF){
			if(strcmp(p1.user, tempUser) == 0){
				number = p1.number;
				fclose(nameList);
				break;
			}
		}
	}

	if(check == 0){    
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


	if(argc == 1){
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
	}

	else if(argc >= 2){
		FILE *taskAlias = fopen(ALIAS, "r");
		char alias[50];
		bool check = 1;
		
		while(fscanf(taskAlias, "%[^\n]\n", alias) != EOF){
			if(strcmp(alias, argv[1]) == 0){
				check = 0;
				break;
			}
		}
		fclose(taskAlias);

		if(check){
			printf("Hatali arguman girdiniz. Daha fazla bilgi icin 'rpg --help' deneyin!");
			return 0;
		}

		if(strcmp(argv[1], "--help") == 0 || strcmp(argv[1], "-h") == 0){
			if(argc > 2){
				printf("Hata! Fazla parametre girdiniz!");
				return 0;
			}
			int status = system("man rpg");
			
			if (status != 0) {
				printf("Kılavuz dosyasi acilamadi. Lutfen 'make install' ile kurulum yaptiginizdan emin olun.\n");
			}
			
		}

		else if(strcmp(argv[1], "--task-add") == 0 || strcmp(argv[1], "-ta") == 0){
			if(argc < 5) {
				printf("Hata! Eksik parametre girdiniz!\nKullanim: rpg -ta \"Gorev Adi\" <zorluk derecesi (1-5)> <autoCalc(1/0)>\n");
				return 0;
			}	

			char *taskName = argv[2];
			int hardness = atoi(argv[3]);
			int autoCalc = atoi(argv[4]);
			char details[MAX_TASK_DETAILS] = "";

			addTaskDirectly(taskName, hardness, autoCalc, 0, 0, details);
		}

		else if(strcmp(argv[1], "--complete") == 0 || strcmp(argv[1], "-c") == 0){
			if(argc < 3){
        			printf("Hata! Tamamlanacak gorevi girmediniz!\nKullanim: rpg -c \"Gorev Adi\"\n");
        			return 0;
    			}
    			
			completeTaskDirectly(argv[2], filePathP, filePathI);
		}

		else if(strcmp(argv[1], "--change-task-parameters") == 0 || strcmp(argv[1], "-ctp") == 0){
			if(argc < 5){
        			printf("Hata: Eksik parametre!\n");
        			printf("Kullanim: rpg -ctp \"Gorev Adi\" <parametre_no> \"yeni_deger\"\n");
        			printf("Parametre No: 1:Ad, 2:Zorluk, 3:Odul, 4:Exp, 5:Detay\n");
        			return 0;
    			}
			
			int paramType = atoi(argv[3]);
    			changeTaskParamDirectly(argv[2], paramType, argv[4]);
		}

		else if(strcmp(argv[1], "--show-finished") == 0 || strcmp(argv[1], "-sf") == 0){
			showFinishedTasks();
		}

		else if(strcmp(argv[1], "--delete-task") == 0 || strcmp(argv[1], "-dt") == 0){
			if(argc < 3){
        			printf("Hata: Silinecek gorevi girmediniz!\nKullanim: rpg -dt \"Gorev Adi\"\n");
        			return 0;
    			}
			deleteTaskDirectly(argv[2]);
		}

		else if(strcmp(argv[1], "--quit-account") == 0 || strcmp(argv[1], "-qa") == 0){
			remove(AUTO);
			printf("Cikis yapildi!");
		}

		else if(strcmp(argv[1], "--enable-plugin") == 0 || strcmp(argv[1], "-ep") == 0){

		}

		else if(strcmp(argv[1], "--disable-plugin") == 0 || strcmp(argv[1], "-dp") == 0){

		}

		return 0;
	}

	return 0;
}
