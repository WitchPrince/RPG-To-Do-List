#include "../../settings.h"

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
	strcpy(p1.expBar, "[__________]");
	unsigned long hash, hashInFile;
	char userName[MAX_USER_NAME], filePath[100];
	int userNumber = 1, decision, check = 1;

	printf("(1) Login\n(2) Sign Up\nEnter any key to exit!\nDecision: ");
	scanf("%d", &decision);

	if(decision == 1){
		nameList = fopen(USERLIST, "r");
		
		if(nameList != NULL){
			printf("Please enter your user name: ");
			scanf("%s", p1.user);
			while(fscanf(nameList, "(%d) User: %[^\n]\n", &userNumber, userName) != EOF){
				if(strcmp(userName, p1.user) == 0){
					check = 0;
					printf("Please enter your password: ");
					scanf("%s", p1.passwd);
					hash = hashPassword(p1.passwd);

					sprintf(filePath, USER_DIR, userName);

					profile = fopen(filePath, "r");
					fscanf(profile, "User: %[^,], Password: %lu", userName, &hashInFile);

					if(hash == hashInFile){
						printf("\nGiris basarili! Hosgeldiniz %s\n", userName);
						fclose(nameList); fclose(profile);
						return userNumber;
					}

					else{
						printf("\nSifre yanlis! Tekrar deneyin!\n");
						return 0;
					}
				}
			}
			if(check){
				printf("Bu isimde bir kullanici bulunamadi!");
				fclose(nameList);
				return 0;
			}
			if(profile != NULL) fclose(profile);
			if(nameList != NULL) fclose(nameList);
		} 

		//Namelist yok ise olusturacak
		else{
			printf("User list is empty! Please create a user first.\nUsername: ");
			scanf("%s", userName);
			printf("New Password: ");
			scanf("%s", p1.passwd);
			hash = hashPassword(p1.passwd); 
			
			//nameList'e ekleme
			nameList = fopen(USERLIST, "w");
			fprintf(nameList, "(1) User: %s\n", userName);
			fclose(nameList);
			
			//Profil dosyası oluşturma	
			sprintf(filePath, USER_DIR, userName);
			profile = fopen(filePath, "w");
			fprintf(profile, "User: %s, Password: %lu\n\nCurrency: 0\nExp: 0\nLevel: 0, Exp Bar ==> %s\n", userName, hash, p1.expBar);
			
			fclose(profile);
			return 1;
		}
	}

	if(decision == 2){
		nameList = fopen(USERLIST, "a+");
		char user[MAX_USER_NAME];

		printf("\nRPG To-Do uygulamasına hoşgeldiniz!\nKayıt olmak istediğiniz,\nKullanici adi: ");
		scanf("%s", userName);
		printf("Sifre: ");
		scanf("%s", p1.passwd);
		hash = hashPassword(p1.passwd);
		sprintf(filePath, USER_DIR, userName);

		if(nameList != NULL){
			while(fscanf(nameList, "(%d) User: %s\n", &userNumber, user) != EOF){
			}
			rewind(nameList);
			fprintf(nameList, "(%d) User: %s\n", userNumber + 1, userName);
		
			profile = fopen(filePath, "w");
			fprintf(profile, "User: %s, Password: %lu\n\nCurrency: 0\nExp: 0\nLevel: 0, Exp Bar ==> %s\n", userName, hash, p1.expBar);
			
			fclose(profile); fclose(nameList);	
			return userNumber + 1; 
		}
		else{
			nameList = fopen(USERLIST, "w");
			fprintf(nameList, "(1) User: %s\n", userName);
			
			profile = fopen(filePath, "w");
			fprintf(profile, "User: %s, Password: %lu\n\nCurrency: 0\nExp: 0\nLevel: 0, Exp Bar ==> %s\n", userName, hash, p1.expBar);
			fclose(nameList); fclose(profile);
			return 1;
		}
	}

	else{
		printf("Kendine iyi bak! Gorusuruz!");
		exit(1);
	}
}
