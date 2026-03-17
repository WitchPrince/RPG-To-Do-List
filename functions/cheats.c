#include "../settings.h"

void cheats(char userName[MAX_USER_NAME]){
	struct Item i1;
	struct Profile p1;
	FILE *inventory, *temp, *profile;
	int decision, oldBalance, balance, currency;
	unsigned long hashInFile;
	char filePathP[100], filePathI[100];

	sprintf(filePathP, USER_DIR, userName);
	sprintf(filePathI, INVENTORY, userName);

	strcpy(p1.expBar, "[__________]");

	printf("\n-----------------------");
	printf("Cheat Menu");	
	printf("-----------------------\n");

	printf("Choose transaction:\n(1) Add Currency\n(2) Exit\nDecision: ");
	scanf("%d", &decision);

	if(decision == 1){
		inventory = fopen(filePathI, "r");
		
		if(inventory == NULL){
			inventory = fopen(filePathI, "w");

			fprintf(inventory, "Currency: 0\n\n");
			fclose(inventory);

			inventory = fopen(filePathI, "r");
		}

		temp = fopen(TEMP, "w");
		fscanf(inventory, "Currency: %d\n\n", &oldBalance);

		printf("How much do you want to add: ");
		scanf("%d", &currency);
		balance = oldBalance + currency;

		fprintf(temp, "Currency: %d\n\n", balance);
		while(fscanf(inventory, " %[^,], %d, Item Detaylari:\n%[^\n]\n\n", i1.itemName, &i1.itemCount, i1.itemDetails) != EOF){
			fprintf(temp, "%s, %d, Item Detaylari:\n%s\n\n", i1.itemName, i1.itemCount, i1.itemDetails);
		}

		fclose(temp); fclose(inventory);
		remove(filePathI);
		rename(TEMP, filePathI);
		
		temp = fopen(TEMP, "w");
		profile = fopen(filePathP, "r");
	
		fscanf(profile, "User: %[^,], Password: %lu\n\nCurrency: %d\nExp: %d\nLevel: %d, Exp Bar ==> %s\n", userName, &hashInFile, &p1.currency, &p1.exp, &p1.level, p1.expBar);
	
		fprintf(temp, "User: %s, Password: %lu\n\nCurrency: %d\nExp: %d\nLevel: %d, Exp Bar ==> %s\n", userName, hashInFile, balance, p1.exp, p1.level, p1.expBar);

		fclose(temp); fclose(profile);
		remove(filePathP);
		rename(TEMP, filePathP);
	}

	else if(decision == 2){
		return;
	}
}
