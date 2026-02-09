#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../settings.h"

void inventory(){
	FILE *fptr = fopen(INVENTORY, "r");
	FILE *temp = fopen(TEMP, "w");
	char itemSelect[MAX_ITEM_NAME];
	int decision, balance = 0;
	bool check = 0, isExist = 0;
	struct Item i1;

	printf("\n======Inventory======\n");

	if(fptr == NULL){
		fptr = fopen(INVENTORY, "w");
		fprintf(fptr, "%d\n\n", balance);
		fclose(fptr);
		fptr = fopen(INVENTORY, "r");
	}
	
	fscanf(fptr, "%d\n\n", &balance);

	while(fscanf(fptr, "%[^,], %d, Item Detaylari:\n%[^\n]\n\n", i1.itemName, &i1.itemCount, i1.itemDetails) != EOF){
		isExist = 1;
		printf("%s, %d\nDescription: %s\n\n", i1.itemName, i1.itemCount, i1.itemDetails);
	}

	rewind(fptr);

	printf("Hangi itemi kullanmak istiyorsunuz: ");
	scanf(" %[^\n]", itemSelect);

	fclose(fptr);
	fptr = fopen(INVENTORY, "r");

	if(isExist){
		fscanf(fptr, " %d\n\n", &balance);
		fprintf(temp, "%d\n\n", balance);

		while(fscanf(fptr, "%[^,], %d, Item Detaylari:\n%[^\n]\n\n", i1.itemName, &i1.itemCount, i1.itemDetails) != EOF){
			if(strcmp(itemSelect, i1.itemName) != 0){
				fprintf(temp, "%s, %d, Item Detaylari:\n%s\n\n", i1.itemName, i1.itemCount, i1.itemDetails);
			}
			else{
				if((i1.itemCount - 1) != 0){
					fprintf(temp, "%s, %d, Item Detaylari:\n%s\n\n", i1.itemName, i1.itemCount - 1, i1.itemDetails);
					check = 1;
				}
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
