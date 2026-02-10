#ifndef SETTINGS_H
#define SETTINGS_H

#include <stdbool.h>

//metin uzunluklari etc.
#define MAX_NAME 50

//Task Management
#define MAX_TASK_NAME 80
#define MAX_TASK_DETAILS 300
#define MAX_ITEM_NAME 25
#define MAX_ITEM_DETAILS 200

/*User Management (still on development)
#define MAX_USER_NAME 20
#define MAX_PW 20*/


//Dizinler
#define MARKET "database/market.txt"
#define TEMP "database/temp.txt"
#define TASKS "database/tasks.txt"
#define FINISHED "database/finished-tasks.txt"
#define INVENTORY "database/inventory.txt"

//structlar
struct Market {
	char name[MAX_NAME];
	char detail[MAX_ITEM_DETAILS];
	int price, count;
};

struct Tasks{
	char taskName[MAX_TASK_NAME];
	char taskDetails[MAX_TASK_DETAILS];
	int hardness, reward, exp;
};

struct Item{
	char itemName[MAX_ITEM_NAME];
	char itemDetails[MAX_ITEM_DETAILS];
	char rarity;
	int  itemCount;
};

//fonksiyonlar
void marketMenu();
void taskMenu();
void inventory();

#endif
