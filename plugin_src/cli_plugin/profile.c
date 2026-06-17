#include "../../settings.h"
#include "settingsCli.h"

void profileMenu(char *filePathP){
	FILE *profile;
	struct Profile p1;
	
	sprintf(filePathP, USER_DIR, p1.user);
	profile = fopen(filePathP, "r");
	
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
