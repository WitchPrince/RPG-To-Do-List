#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../settings.h"

void profileMenu(int userNumber){
	FILE *nameList = fopen(USERLIST, "r");
	FILE *profile;
	struct Profile p1;
	int userNo;
	char filePath[100];
	
	while(fscanf(nameList, "(%d) User: %s", &userNo, p1.user) != EOF){
		if(userNo == userNumber) break;
	}
	fclose(nameList);
	sprintf(filePath, USER_DIR, p1.user);
	profile = fopen(filePath, "r");
	
	char i;
	while(1){
				i = fgetc(profile);
				if(i == EOF) break;
				else printf("%c", i);
			}
	fclose(profile);	
	printf("\n\nMenuye donmek icin Enter tusuna basın.");	
	getchar();
	getchar();
}
