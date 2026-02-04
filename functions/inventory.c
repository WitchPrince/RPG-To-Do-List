#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../settings.h"

void inventory(){
	FILE *fptr = fopen(INVENTORY, "r");
	FILE *temp = fopen(TEMP, "w");
	char itemSelect[MAX_ITEM_NAME];
	int decision;
	int balance;
	bool check = 0, isExist = 0;
	struct Item i1;
	fscanf(fptr, "%d", &balance);

	printf("\n======Inventory======\n");

	while(fscanf(fptr, " %[^,], %d, Item Detaylari:\n %[^\n]\n\n", i1.itemName, &i1.itemCount, i1.itemDetails) != EOF){
		printf("%s, %d\nDescription: %s\n\n", i1.itemName, i1.itemCount, i1.itemDetails);
	}

	rewind(fptr);

	printf("Hangi itemi kullanmak istiyorsunuz: ");
	scanf(" %[^\n]", itemSelect);


	while(fscanf(fptr, " %[^,], %d, Item Detaylari:\n %[^\n]\n\n", i1.itemName, &i1.itemCount, i1.itemDetails) != EOF){
		isExist = 1;
	}

	fclose(fptr);
	fptr = fopen(INVENTORY, "r");

	if(isExist){
		while(fscanf(fptr, " %[^,], %d, Item Detaylari:\n %[^\n]\n\n", i1.itemName, &i1.itemCount, i1.itemDetails) != EOF){
			if(strcmp(itemSelect, i1.itemName) != 0){
				fprintf(temp, "%s, %d, %s", i1.itemName, i1.itemCount, i1.itemDetails);
			}
			else{
				fprintf(temp, "%s, %d, %s", i1.itemName, i1.itemCount - 1, i1.itemDetails);
				check = 1;
			}
		}
	}
		if(check == 0){
			printf("Girdiginiz item envanterinizde bulunamadi!");
		}
		else{
			printf("Item kullanildi!");
		}
		

	fclose(fptr); fclose(temp);
	remove(INVENTORY);
	rename(TEMP, INVENTORY);
}
