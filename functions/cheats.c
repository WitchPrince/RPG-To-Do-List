#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../settings.h"

void cheats(){
	struct Item i1;
	FILE *inventory, *temp;
	int decision, oldBalance, balance, currency;

	printf("\n-----------------------");
	printf("Cheat Menu");	
	printf("-----------------------\n");

	printf("Choose transaction:\n(1) Add Currency\n");
	scanf("%d", &decision);

	if(decision == 1){
		inventory = fopen(INVENTORY, "r");
		
		if(inventory == NULL){
			inventory = fopen(INVENTORY, "w");
			fprintf(inventory, "0\n\n");
			fclose(inventory);
			inventory = fopen(INVENTORY, "r");
		}

		temp = fopen(TEMP, "w");
		fscanf(inventory, "%d\n\n", &oldBalance);

		printf("How much do you want to add: ");
		scanf("%d", &currency);
		balance = oldBalance + currency;

		fprintf(temp, "%d\n\n", balance);
		while(fscanf(inventory, "%[^,], %d, Item Detaylari:\n%[^\n]\n\n", i1.itemName, &i1.itemCount, i1.itemDetails) != EOF){
			fprintf(temp, "%s, %d, Item Detaylari:\n%s\n\n", i1.itemName, i1.itemCount, i1.itemDetails);
		}

		fclose(temp); fclose(inventory);
			remove(INVENTORY);
			rename(TEMP, INVENTORY);
	}
}
