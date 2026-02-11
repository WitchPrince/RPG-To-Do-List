#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../settings.h"

void profileMenu(){

	FILE *profile = fopen(PROFILE, "r");
	FILE *inventory = fopen(PROFILE, "r");
	char userName[MAX_USER_NAME];
	int balance;

	if(profile == NULL){
		printf("Profil bulunamadi! Yeni profil olusturuluyor...\nKullanici adiniz (Max 30 harf): ");
		scanf("%s", userName);
		profile = fopen(PROFILE, "w");

		fscanf(inventory, "Currency: %d", &balance);
		fprintf(profile, "User: %s, Currency: %d, Exp: 0", userName, balance);
		fclose(profile);
		profile = fopen(PROFILE, "r");
	}

	char i;

	while(1){
				i = fgetc(profile);
				if(i == EOF) break;
				else printf("%c", i);
			}
	printf("\n\nMenuye donmek icin Enter tusuna basın.");	
	getchar();
	getchar();

	fclose(profile);	
}
