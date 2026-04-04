#ifndef SETTINGS_H
#define SETTINGS_H

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <dlfcn.h>

//=================================================
//some syntax templates for remembering file syntax
//=================================================
//==========
//Inventory:
//Currency: %d\n%s, %d, Item Detaylari:\n%s\n\n

//=======
//Market:
//(%d) Product: %s, Price: %d\nItem Details:%s\n\n

//==========
//Task Menu:
//Gorev: %s, Zorluk: %d, Odul: %d, Exp: %d\nGorev Detaylari:\n%s\n\n

//=========
//Namelist:
//(%d) User: %s\n

//========
//Profile:
//User: %s, Password: %lu\n\nCurrency: %d\nExp: %d\nLevel: %d, Exp Bar ==> %s\n

//metin uzunluklari etc.
#define MAX_NAME 50

//Task Management
#define MAX_TASK_NAME 80
#define MAX_TASK_DETAILS 300
#define MAX_ITEM_NAME 25
#define MAX_ITEM_DETAILS 200
#define MAX_USER_NAME 30
#define MAX_PASSWD 20

//Macrolar
#define USER_DIR "database/users/%s.txt"

//Dizinler
#define MARKET "database/market.txt"
#define TEMP "database/temp.txt"
#define TEMPU "database/users/temp.txt"
#define TASKS "database/tasks.txt"
#define FINISHED "database/finished-tasks.txt"
#define INVENTORY "database/users/%s-inventory.txt"
#define USERLIST "database/users/userList.txt"
#define ALIAS "database/do-not-change-these/alias.txt"
#define AUTO "database/do-not-change-these/auto-login.txt"

//structlar
struct Market {
	char name[MAX_NAME];
	char detail[MAX_ITEM_DETAILS];
	int price, id;
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

struct Profile{
	char user[MAX_USER_NAME], passwd[MAX_PASSWD], expBar[13];
	int currency, exp, level, number;
};

//fonksiyonlar
void marketMenu(char filePathP[100], char filePathI[100]);
void taskMenu(char filePathP[100], char filePathI[100]);
void inventory(char filePathI[100]);
void profileMenu(int userNumber);
int userMenu();
void cheats(char userName[MAX_USER_NAME]);
unsigned long hashPassword(char *str);
void autoLogin(char user[MAX_USER_NAME]);
void logOut();

//fast functions
void showFinishedTasks();
void addTaskDirectly(char *taskName, int hardness, int autoCalc, int reward, int exp, char *details);
void completeTaskDirectly(char *taskName, char filePathP[100], char filePathI[100]);
void deleteTaskDirectly(char *taskName);
void changeTaskParamDirectly(char *taskName, int paramType, char *newValueStr);

#endif
