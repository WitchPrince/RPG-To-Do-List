#ifndef SETTINGS_H
#define SETTINGS_H

//Metin uzunlukları etc
#define MAX_NAME 50
#define MAX_TASK_NAME 80
#define MAX_TASK_DETAILS 300

//Dizinler
#define MARKET "database/market.txt"
#define TEMP "database/temp.txt"
#define TASKS "database/tasks.txt"
#define FINISHED "database/finished-tasks.txt"

//structlar
struct Market {
	char isim[MAX_NAME];
	int price, count;
};

struct Tasks{
	char taskName[MAX_TASK_NAME];
	char taskDetails[MAX_TASK_DETAILS];
	int hardness, reward, exp;
};
//fonksiyonlar
void marketMenu();
void taskMenu();

#endif
