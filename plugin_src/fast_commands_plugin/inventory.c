#include "../../settings.h"

void inventory(char filePathI[100]){
	FILE *fptr;
	FILE *temp = fopen(TEMP, "w");
	char itemSelect[MAX_ITEM_NAME];
	int balance = 0;
	bool check = 0, isExist = 0;
	struct Item i1;
	
	fptr = fopen(filePathI, "r");

	printf("\n======Inventory======\n");

	if(fptr == NULL){
		fptr = fopen(filePathI, "w");
		fprintf(fptr, "Currency: %d\n\n", balance);
		fclose(fptr);
		fptr = fopen(filePathI, "r");
	}
	
	fscanf(fptr, "Currency: %d\n\n", &balance);
	printf("\nCurrency: %d\n", balance);

	while(fscanf(fptr, "%[^,], %d, Item Detaylari:\n%[^\n]\n\n", i1.itemName, &i1.itemCount, i1.itemDetails) != EOF){
		isExist = 1;
		printf("%s, %d\nDescription: %s\n\n", i1.itemName, i1.itemCount, i1.itemDetails);
	}

	printf("\n-------------------------------------------------------\n");
	printf("\nHangi itemi kullanmak istiyorsunuz (Cikis yapmak icin herhangi bir tusa basin): ");
	scanf(" %[^\n]", itemSelect);

	rewind(fptr);

	if(isExist){
		fscanf(fptr, "Currency: %d\n\n", &balance);
		fprintf(temp, "Currency: %d\n\n", balance);

		while(fscanf(fptr, "%[^,], %d, Item Detaylari:\n%[^\n]\n\n", i1.itemName, &i1.itemCount, i1.itemDetails) != EOF){
			if(strcmp(itemSelect, i1.itemName) != 0){
				fprintf(temp, "%s, %d, Item Detaylari:\n%s\n\n", i1.itemName, i1.itemCount, i1.itemDetails);
			}
			else{
				if((i1.itemCount - 1) != 0){
					fprintf(temp, "%s, %d, Item Detaylari:\n%s\n\n", i1.itemName, i1.itemCount - 1, i1.itemDetails);
				}
				check = 1;
			}
		}
	}	

		if(check){
			printf("\nItem kullanildi!\n");
		}
		else{
			printf("\nGirdiginiz item envanterinizde bulunamadi!\n");
		}
		

	fclose(fptr); fclose(temp);
	if(isExist){
			remove(filePathI);
			rename(TEMP, filePathI);
	}
}
