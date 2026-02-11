#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "settings.h"

int main(){
	int decision = 1;

	printf("RPG To-Do List uygulamasina hosgeldiniz!");
	while(decision != 0){
	
		printf("\nYapmak istediğiniz islemi numara ile seciniz.\n\n(1) Marketplace\n(2) Tasks\n(3) Inventory\n(4) Cheat Menu\n(5) Profile\n(6) Exit\nDecision: ");
		scanf("%d", &decision);
		printf("\n-------------------------------------------------------\n\n");

		if(decision == 1) marketMenu();

		else if(decision == 2) taskMenu();

		else if(decision == 3) inventory();

		else if(decision == 4) cheats();

		else if(decision == 5) profileMenu();

		else break;
	}

	return 0;
}
