#include "settingsCli.h"

void showFinishedTasks(){
	FILE *finished = fopen(FINISHED, "r");

	if(finished == NULL){
		printf("There's no finished tasks!");
	}
			
	else {
		printf("\n-------------------------------------------------------\n");
		char i;
					
		while(1){
			i = fgetc(finished);
			if(i == EOF) break;
			else	printf("%c", i);
		}
				
		printf("\n-------------------------------------------------------\n");
		fclose(finished);
	}
}

void taskMenu(char *filePathP, char *filePathI){
		FILE *fptr = fopen(TASKS, "r");
		FILE *temp;
		FILE *inventory;
		FILE *profile;

		struct Tasks k1;
		struct Profile p1;
		int subDecision;
		bool check = 0;
	 	unsigned long hash;
		strcpy(p1.expBar, "[__________]"); 

			if(fptr == NULL){
				printf("There's no active tasks!");
			}
			
			else {
				char i;
				while(1){
					i = fgetc(fptr);
					if(i == EOF) break;
					else	printf("%c", i);
				}
				printf("\n-------------------------------------------------------\n");
				fclose(fptr);
			}

			printf("\n(1) Add quest\n(2) Complete quest\n(3) Change quest parameters\n(4) Show finished quests\n(5) Delete quest\n(6) Exit\nDecision: ");
			scanf("%d", &subDecision);

			if(subDecision == 1){
				int oto, detay;

				printf("\nTask name (Max 80 character!): ");
				scanf(" %[^\n]", k1.taskName);
					
				printf("Task difficulty (1-5): ");
				scanf("%d", &k1.difficulty);
				printf("Auto-calculate for rewards and exp? (1/0): ");
				scanf("%d", &oto);

				if(oto == 1){
					k1.reward = k1.difficulty * 50;
					k1.exp = k1.difficulty * 5;
				}
				else{
					printf("Task reward: ");
					scanf("%d", &k1.reward);
					printf("Task exp: ");
					scanf("%d", &k1.exp);
				}

				printf("Add task details? (1/0): ");
				scanf("%d", &detay);

				if(detay == 1){
					printf("Task details (Max 300 character!):\n");
					scanf(" %299[^\n]", k1.taskDetails);

					fprintf(fptr, "Task: %s, Difficulty: %d, Reward: %d, Exp: %d\nTask Details:\n%s\n\n", k1.taskName, k1.difficulty, k1.reward, k1.exp, k1.taskDetails);
				}
				
				else strcpy(k1.taskDetails, "No detail.");

				add_to_task_list(k1.taskName, k1.difficulty, k1.reward, k1.exp, k1.taskDetails);
			}

			else if(subDecision == 2){
				FILE *finished = fopen(FINISHED, "a");
				fptr = fopen(TASKS, "r");
				temp = fopen(TEMP, "w");
				int reward, expGain;

				char searchTask[MAX_TASK_NAME];

				if(fptr == NULL){
					printf("\nTask list is empty!\n");
					fclose(fptr); fclose(temp); fclose(finished);
					remove(TEMP);
					return;
				}
				printf("\nWhich task is completed? : ");
				scanf(" %[^\n]", searchTask);

				while(fscanf(fptr, "Task: %[^,], Difficulty: %d, Reward: %d, Exp: %d\nTask Details:\n%[^\n]\n\n", k1.taskName, &k1.difficulty, &k1.reward, &k1.exp, k1.taskDetails) != EOF){
					if(strcmp(searchTask, k1.taskName) != 0){
						fprintf(temp, "Task: %s, Difficulty: %d, Reward: %d, Exp: %d\nTask Details:\n%s\n\n", k1.taskName, k1.difficulty, k1.reward, k1.exp, k1.taskDetails); 
					}
					else{
						fprintf(finished, "Task: %s, Difficulty: %d, Reward: %d, Exp: %d\nTask Details:\n%s\n\n", k1.taskName, k1.difficulty, k1.reward, k1.exp, k1.taskDetails);
						reward = k1.reward;
						expGain = k1.exp;
						check = 1;
					}
				}

				fclose(finished); fclose(temp); fclose(fptr);
			
				remove(TASKS);
				rename(TEMP, TASKS);

				//Reward gain system

				if(check == 0){
					printf("Task couldn't found!");
					return;
				}
				else{
					temp = fopen(TEMP, "w");
					inventory = fopen(filePathI, "r");

					struct Item i1;
					int balance, oldBalance, exp;
				
					if(inventory == NULL){
						inventory = fopen(filePathI, "w");
						fprintf(inventory, "Currency: 0\n\n");
						fclose(inventory);
						inventory = fopen(filePathI, "r");
					}
					fscanf(inventory, "Currency: %d\n\n", &oldBalance);

					balance = oldBalance + reward;						fprintf(temp, "Currency: %d\n\n", balance);

					while(fscanf(inventory, "%[^,], %d, Item Details:\n%[^\n]\n\n", i1.itemName, &i1.itemCount, i1.itemDetails) != EOF){
						fprintf(temp, "%s, %d, Item Details:\n%s\n\n", i1.itemName, i1.itemCount, i1.itemDetails);
					}
					fclose(temp); fclose(inventory);
					remove(filePathI);
					rename(TEMP, filePathI);

					temp = fopen(TEMP, "w");
					profile = fopen(filePathP, "r");

					fscanf(profile, "User: %[^,], Password: %lu\n\nCurrency: %d\nExp: %d\nLevel: %d, Exp Bar ==> %s\n", p1.user, &hash, &p1.currency, &p1.exp, &p1.level, p1.expBar);

					exp = p1.exp + expGain; 
					p1.level = exp / 100;
					
					if(exp % 100 != 0){
						strcpy(p1.expBar, "[");
							for(int a = 10; a <= exp % 100; a+=10){
								strcat(p1.expBar, "=");
							}
							for(int a = 10; a < 100 - (exp % 100); a += 10){
								strcat(p1.expBar, "_");
							}
						strcat(p1.expBar, "]");
					}

					fprintf(temp, "User: %s, Password: %lu\n\nCurrency: %d\nExp: %d\nLevel: %d, Exp Bar ==> %s\n", p1.user, hash, balance, exp, p1.level, p1.expBar);

					fclose(temp); fclose(profile);
					remove(filePathP);
					rename(TEMP, filePathP);

					printf("Task completed!");
				}
			}

			else if(subDecision == 3){
				FILE *fptr = fopen(TASKS, "r");
			       	FILE *temp = fopen(TEMP, "w");
				
				char searchName[MAX_TASK_NAME];
				
				if(fptr == NULL){
					printf("Task list is empty!");
					fclose(fptr); fclose(temp);
					return;
				}
				printf("Task name: ");
				scanf(" %[^\n]", searchName);

				while(fscanf(fptr, "Task: %[^,], Difficulty: %d, Reward: %d, Exp: %d\nTask Details:\n %[^\n]\n\n", k1.taskName, &k1.difficulty, &k1.reward, &k1.exp, k1.taskDetails) != EOF){
					if(strcmp(searchName, k1.taskName) != 0)
						fprintf(temp, "Task: %s, Difficulty: %d, Reward: %d, Exp: %d\nTask Details:\n%s\n\n", k1.taskName, k1.difficulty, k1.reward, k1.exp, k1.taskDetails);
					else{
						printf("Which parameter do you want to change:\n(1) Task Name\n(2) Hardness\n(3) Reward\n(4) Exp\n(5) Details\nDecision: ");
						scanf("%d", &subDecision);

							if(subDecision == 1){
								printf("New task name: ");
								scanf(" %[^\n]", searchName);
								fprintf(temp, "Task: %s, Difficulty: %d, Reward: %d, Exp: %d\nTask Details:\n%s\n\n", searchName, k1.difficulty, k1.reward, k1.exp, k1.taskDetails);
								printf("Task name has changed!");
							}

							else if(subDecision == 2){
								printf("New difficulty level (1-5): ");
								scanf("%d", &k1.difficulty);
								fprintf(temp, "Task: %s, Difficulty: %d, Reward: %d, Exp: %d\nTask Details:\n%s\n\n", k1.taskName, k1.difficulty, k1.reward, k1.exp, k1.taskDetails);
								printf("Task difficulty level has changed!");
							}

							else if(subDecision == 3){
								printf("New reward amount: ");
								scanf("%d", &k1.reward);
								fprintf(temp, "Task: %s, Difficulty: %d, Reward: %d, Exp: %d\nTask Details:\n%s\n\n", k1.taskName, k1.difficulty, k1.reward, k1.exp, k1.taskDetails);
								printf("Task reward amount has changed!");
							}

							else if(subDecision == 4){
								printf("New exp amount: ");
								scanf("%d", &k1.exp);
								fprintf(temp, "Task: %s, Difficulty: %d, Reward: %d, Exp: %d\nTask Details:\n%s\n\n", k1.taskName, k1.difficulty, k1.reward, k1.exp, k1.taskDetails);
								printf("Task exp amount has changed!");
							}

							else if(subDecision == 5){
								printf("New detail: ");
								while(getchar() != '\n');

								scanf(" %[^\n]", k1.taskDetails);
								fprintf(temp, "Task: %s, Difficulty: %d, Reward: %d, Exp: %d\nTask Details:\n%s\n\n", k1.taskName, k1.difficulty, k1.reward, k1.exp, k1.taskDetails);
								printf("Task detail has changed!");
							}

							check = 1;
					}
				}

				if(check == 0){
					printf("%s is not exist! Please enter a valid task name.", searchName);
				}

				else{
					printf("Success!");
				}

				fclose(temp); fclose(fptr);
				remove(TASKS);
				rename(TEMP, TASKS);
			}

			else if(subDecision == 4){
				showFinishedTasks();
			}

			else if(subDecision == 5){
				FILE *fptr = fopen(TASKS, "r");
				FILE *temp = fopen(TEMP, "w");
				char deleteQuest[MAX_TASK_NAME];

				if(fptr == NULL){
					printf("Task list is empty!");
					return;
				}

				printf("Which task do you want to delete: ");
				scanf(" %[^\n]", deleteQuest);

				while(fscanf(fptr, "Task: %[^,], Difficulty: %d, Reward: %d, Exp: %d\nTask Details:\n %[^\n]\n\n", k1.taskName, &k1.difficulty, &k1.reward, &k1.exp, k1.taskDetails) != EOF){
					if(strcmp(deleteQuest, k1.taskName) != 0){
						fprintf(temp, "Task: %s, Difficulty: %d, Reward: %d, Exp: %d\nTask Details:\n %s\n\n", k1.taskName, k1.difficulty, k1.reward, k1.exp, k1.taskDetails);
					}
					else check = 1;
				}
					if(check == 0){
						printf("%s is not exist!", deleteQuest);
					}

					else{
						printf("%s has deleted!", deleteQuest);
					}

					fclose(fptr); fclose(temp);

					remove(TASKS);
					rename(TEMP, TASKS);
			}

			else if(subDecision == 6){
				return;
			}
				
}


void addTaskDirectly(char *taskName, int difficulty, int autoCalc, int reward, int exp, char *details) {
	if(autoCalc == 1) {
        	reward = difficulty * 50;
        	exp = difficulty * 5;
   	}

    	else{
		printf("\nTask reward: ");
	    	scanf("%d", &reward);
	    	printf("\nTask exp: ");
	    	scanf("%d", &exp);
	}

	if(strlen(details) == 0) {
        	strcpy(details, "No details!");
    	}

	add_to_task_list(taskName, difficulty, reward, exp, details);

	printf("Task added successfully!\n");
}

void deleteTaskDirectly(char *taskName) {
	FILE *fptr = fopen(TASKS, "r");
	FILE *temp = fopen(TEMP, "w");
	struct Tasks k1;
    	bool check = 0;

    	if(fptr == NULL){
        	printf("Task list is empty!\n");
        	return;
    	}

    	while(fscanf(fptr, "Task: %[^,], Difficulty: %d, Reward: %d, Exp: %d\nTask Details:\n %[^\n]\n\n", k1.taskName, &k1.difficulty, &k1.reward, &k1.exp, k1.taskDetails) != EOF){
        	if(strcmp(taskName, k1.taskName) != 0){
            		fprintf(temp, "Task: %s, Difficulty: %d, Reward: %d, Exp: %d\nTask Details:\n %s\n\n", k1.taskName, k1.difficulty, k1.reward, k1.exp, k1.taskDetails);
        	}
		
		else {
            		check = 1;
        	}
    	}

    	if(check == 0) printf("%s is not exist!\n", taskName);
    	else printf("Silme islemi basarili!\n");

    	fclose(fptr); fclose(temp);
    	remove(TASKS); rename(TEMP, TASKS);
}

void changeTaskParamDirectly(char *taskName, int paramType, char *newValueStr) {
    	FILE *fptr = fopen(TASKS, "r");
	FILE *temp = fopen(TEMP, "w");
    	struct Tasks k1;
    	bool check = 0;

    	if(fptr == NULL){
        	printf("Task list is empty!\n");
        	fclose(temp);
        	return;
    	}

    	while(fscanf(fptr, "Task: %[^,], Difficulty: %d, Reward: %d, Exp: %d\nTask Details:\n %[^\n]\n\n", k1.taskName, &k1.difficulty, &k1.reward, &k1.exp, k1.taskDetails) != EOF){
        	if(strcmp(taskName, k1.taskName) != 0){
            		fprintf(temp, "Task: %s, Difficulty: %d, Reward: %d, Exp: %d\nTask Details:\n%s\n\n", k1.taskName, k1.difficulty, k1.reward, k1.exp, k1.taskDetails);
        	}
		
		else {
            		check = 1;
            		if(paramType == 1) strcpy(k1.taskName, newValueStr);
            		else if(paramType == 2) k1.difficulty = atoi(newValueStr);
            		else if(paramType == 3) k1.reward = atoi(newValueStr);
            		else if(paramType == 4) k1.exp = atoi(newValueStr);
            		else if(paramType == 5) strcpy(k1.taskDetails, newValueStr);

            		fprintf(temp, "Task: %s, Difficulty: %d, Reward: %d, Exp: %d\nTask Details:\n%s\n\n", k1.taskName, k1.difficulty, k1.reward, k1.exp, k1.taskDetails);
            		printf("Parameter has changed!\n");
        	}
    	}	

    	if(check == 0) printf("%s is not exist!\n", taskName);
    	fclose(temp); fclose(fptr);
    	remove(TASKS); rename(TEMP, TASKS);
}

void completeTaskDirectly(char *taskName, char filePathP[100], char filePathI[100]) {
    	FILE *finished = fopen(FINISHED, "a");
    	FILE *fptr = fopen(TASKS, "r");
    	FILE *temp = fopen(TEMP, "w");
    	struct Tasks k1;
    	struct Profile p1;
    	int reward, expGain;
    	bool check = 0;

    	if(fptr == NULL){
        	printf("Task list is empty!\n");
        	fclose(temp); fclose(finished); remove(TEMP);
        	return;
    	}

    	while(fscanf(fptr, "Task: %[^,], Difficulty: %d, Reward: %d, Exp: %d\nTask Details:\n %[^\n]\n\n", k1.taskName, &k1.difficulty, &k1.reward, &k1.exp, k1.taskDetails) != EOF){
        	if(strcmp(taskName, k1.taskName) != 0){
        		fprintf(temp, "Task: %s, Difficulty: %d, Reward: %d, Exp: %d\nTask Details:\n%s\n\n", k1.taskName, k1.difficulty, k1.reward, k1.exp, k1.taskDetails);
        	}
	
		else {
        		fprintf(finished, "Task: %s, Difficulty: %d, Reward: %d, Exp: %d\nTask Details:\n%s\n\n", k1.taskName, k1.difficulty, k1.reward, k1.exp, k1.taskDetails);
        		reward = k1.reward; expGain = k1.exp; check = 1;
        	}
    	}
    	fclose(finished); fclose(temp); fclose(fptr);
    	remove(TASKS); rename(TEMP, TASKS);

    	if(check == 0){
   		printf("Task couldn't found!\n");
    		return;
    	}

    	FILE *inventory = fopen(filePathI, "r");
    	temp = fopen(TEMP, "w");
    	struct Item i1;
    	int balance, oldBalance, exp;

    	if(inventory == NULL){
        	inventory = fopen(filePathI, "w");
        	fprintf(inventory, "Currency: 0\n\n");
        	fclose(inventory); inventory = fopen(filePathI, "r");
    	}

    	fscanf(inventory, "Currency: %d\n\n", &oldBalance);
    	balance = oldBalance + reward;
    	fprintf(temp, "Currency: %d\n\n", balance);
    	
	while(fscanf(inventory, "%[^,], %d, Item Details:\n%[^\n]\n\n", i1.itemName, &i1.itemCount, i1.itemDetails) != EOF){
        	fprintf(temp, "%s, %d, Item Details:\n%s\n\n", i1.itemName, i1.itemCount, i1.itemDetails);
    	}
    
	fclose(temp); fclose(inventory);
    	remove(filePathI);
    	rename(TEMP, filePathI);

    	FILE *profile = fopen(filePathP, "r");
    	temp = fopen(TEMP, "w");
    	unsigned long hash;

    	fscanf(profile, "User: %[^,], Password: %lu\n\nCurrency: %*d\nExp: %d\nLevel: %d, Exp Bar ==> %s\n", p1.user, &hash, &p1.exp, &p1.level, p1.expBar);

    	exp = p1.exp + expGain;
    	p1.level = exp / 100;

    	if(exp % 100 != 0){
        	strcpy(p1.expBar, "[");
        	for(int a = 10; a <= exp % 100; a+=10) strcat(p1.expBar, "=");
        	for(int a = 10; a < 100 - (exp % 100); a += 10) strcat(p1.expBar, "_");
        	strcat(p1.expBar, "]");
    	}
    	fprintf(temp, "User: %s, Password: %lu\n\nCurrency: %d\nExp: %d\nLevel: %d, Exp Bar ==> %s\n", p1.user, hash, balance, exp, p1.level, p1.expBar);

    	fclose(temp); fclose(profile); remove(filePathP); rename(TEMP, filePathP);

    	printf("Task completed! (+%d Gold, +%d Exp)\n", reward, expGain);
}
