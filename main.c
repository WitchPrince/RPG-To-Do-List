#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "settings.h"

int main(){
	struct Profile p1;
	int decision = 1, number = userMenu();
	if(number == 0){
		printf("Sifre yanlis!");
		return 0;
	}

	char filePathP[100], filePathI[100];
	
	FILE *nameList = fopen(USERLIST, "r");

	while(fscanf(nameList, "(%d) User: %s", &p1.number, p1.user) != EOF){
		if(number == p1.number) break;
	}
	fclose(nameList);

	sprintf(filePathP, USER_DIR, p1.user);
	sprintf(filePathI, INVENTORY, p1.user);
	printf("\nRPG To-Do List uygulamasina hosgeldiniz!");
	while(decision != 0){
	
		printf("\nYapmak istediğiniz islemi numara ile seciniz.\n\n(1) Marketplace\n(2) Tasks\n(3) Inventory\n(4) Cheat Menu\n(5) Profile\n(6) Exit\nDecision: ");
		scanf("%d", &decision);
		printf("\n-------------------------------------------------------\n\n");

		if(decision == 1) marketMenu(filePathP, filePathI);

		else if(decision == 2) taskMenu(filePathP, filePathI);

		else if(decision == 3) inventory(filePathI);

		else if(decision == 4) cheats(p1.user);

		else if(decision == 5) profileMenu(number);

		else break;
	}

	return 0;
}
