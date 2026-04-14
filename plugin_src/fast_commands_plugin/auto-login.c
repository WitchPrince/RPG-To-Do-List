#include "../../settings.h"

void autoLogin(char user[MAX_USER_NAME]){
	int login;
	printf("Hizli giris icin hesabiniz hep acik kalsin mi (1/0): ");
	scanf("%d", &login);
	if(login == 1){
		FILE *log = fopen(AUTO, "w");
		fprintf(log, "1\n");
		fprintf(log, "%s", user);
	}
	else return;
}

void logOut(){
	int login;
	printf("Hesabinizdan cikis yapmak istiyor musunuz (1/0): ");
	scanf("%d", &login);
	if(login){
		remove(AUTO);
		return;
	}
}
