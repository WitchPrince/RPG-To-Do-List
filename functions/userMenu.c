#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../settings.h"

unsigned long hashPassword(char *str) {
    unsigned long hash = 5381;
    int c;
    while ((c = *str++))
        hash = ((hash << 5) + hash) + c; 
    return hash;
}

int userMenu(){
	FILE *nameList;
	FILE *profile;

	struct Profile p1;
	strcpy(p1.expBar, "__________");
	unsigned long hash, hashInFile;
	char userName[MAX_USER_NAME], passwd[MAX_USER_NAME], filePath[100];
	int userNumber, balance, exp, level;

	printf("(1) Login\n(2) Sign Up\nEnter any key to exit!\nDecision: ");
	scanf("%d", &decision);

	if(decision == 1){
		nameList = fopen(USERLIST, "r")
		
		if(nameList != NULL){
			printf("Please enter your user name: ");
			scanf("%s", p1.user);
			while(fscanf(nameList, "(%d) User: %[^,]", &userNumber, userName) != EOF){
				while(strcmp(userName, p1.user) == 0){
					check = 0;
					printf("Please enter your password: ");
					scanf("%s", p1.passwd);
					hash = hashPassword("p1.passwd");

					sprintf(filePath, USER_DIR, userName);

					profile = fopen(filePath, "r");
					fscanf(profile, "User: %[^,], Password: %lu\n\nCurrency: %d\nExp: %d\nLevel: %d\n [%[^\n]\n", userName, &hashInFile, &balance, &exp, &level, p1.expBar);

					if(strcmp(hash, hashInFile) == 0){
						printf("\nGiris basarili! Hosgeldiniz %s", userName);
						fclose(nameList); fclose(profile);
						return userNumber;
					}

					else{
						printf("\nSifre yanlis! Tekrar deneyin!\n");
					}
				}
			}
			if(check){
				printf("Bu isimde bir kullanici bulunamadi!");
				return 0;
			}
			fclose(profile); fclose(nameList);
		}

		//Namelist yok ise olusturacak
		else{
			printf("User list is empty! Please create a user first. Username: ");
			scanf("%s", userName);
			printf("New Password: ");
			scanf("%s", p1.passwd);
			hash = hashPassword("p1.passwd"); 
			
			//nameList'e ekleme
			nameList = fopen(USERLIST, "w");
			fprintf(nameList, "(1) User: %s", userName);
			
			//Profil dosyası oluşturma	

			sprintf(filePath, USER_DIR, userName);
			profile = fopen(filePath, "w");
			fprintf(profile, "User: %s, Password: %lu\n\nCurrency: %d\nExp: %d\nLevel: 0\n[%s]\n", userName, hash, balance, exp, level, p1.expBar);
			
			fclose(nameList); fclose(profile);
			return 1;
		}
	}

	else if(decision == 2){
		nameList = fopen(USERLIST, "a+");

		printf("RPG To-Do uygulamasına hoşgeldiniz!\nKayıt olmak istediğiniz,\nKullanici adi: ");
		scanf("%s", userName);
		printf("Sifre: ");
		scanf("%s", passwd);
		hash = hashPassword(p1.passwd);

		if(nameList != NULL){
			while(fscanf(nameList, "(%d) User: %s", &userNumber, userName) != EOF);
			rewind(nameList);
			fprintf(nameList, "(%d) User: %s", userNumber + 1, userName);
		}
		else fprintf(nameList, "(1) User: %s", userName);
	
		sprintf(filePath, USER_DIR, userName);
		profile = fopen(filePath, "w");

		fprintf(profile, "User: %s, Password: %lu\n\nCurrency: 0\nExp: 0\nLevel: 0\n[%s]\n", userName, hash, p1.expBar);
	}

	else{
		fclose(nameList);
		printf("Kendine iyi bak! Gorusuruz!");
		exit(1);
	}
}
