#include "settingsCli.h"

void autoLogin(char user[MAX_USER_NAME]){
	int login;
	printf("Do you want automatic login to remain on for your account? (1/0): ");
	scanf("%d", &login);
	if(login == 1){
		FILE *log = fopen(AUTO, "w");
		fprintf(log, "%s", user);
	}
}

void logOut(){
	int login;
	printf("Do you want to log out of your account? (1/0): ");
	scanf("%d", &login);
	if(login){
		remove(AUTO);
	}
}
