#include "../../plugin.h"
#include "../../settings.h"

static void *fast_com_handle = NULL;

static int init(){
	return 0;
}

static int run(int argc, char *argv[]){
	FILE *taskAlias = fopen(ALIAS, "r");
	FILE *log = fopen(AUTO, "r");
	FILE *nameList = fopen(USERLIST, "r");
		
	struct Profile p1;	
	memset(&p1, 0, sizeof(struct Profile));
	char tempUser[100], alias[50], filePathP[100], filePathI[100];
	int check = 1, number, logCheck = 0;
		
	if(log != NULL){	
		fscanf(log, "%d\n", &logCheck);
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

	if(logCheck == 0){    
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
			printf("Kilavuz dosyasi acilamadi. Lutfen 'make install' ile kurulum yaptiginizdan emin olun.\n");
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

	return 0;
}

static void cleanup(){
	if(fast_com_handle){
		dlclose(fast_com_handle);
	}
}

Plugin *get_plugin_info(){
	static Plugin p = {
		.moduleName = "Fast_Commands_Plugin",
		.init = init,
		.run = run,
		.cleanup = cleanup
	};
	return &p;
}
