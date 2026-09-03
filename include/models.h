#ifndef MODELS_H
#define MODELS_H

#include "limits.h"

//structlar
struct Market {
	char name[MAX_NAME];
	char detail[MAX_ITEM_DETAILS];
	int price, id;
};

struct Tasks{
	char taskName[MAX_TASK_NAME];
	char taskDetails[MAX_TASK_DETAILS];
	int difficulty, reward, exp;
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

struct node{
	struct node *next;
	struct node *prev;
	char name[MAX_ITEM_NAME];
	char details[MAX_ITEM_DETAILS];
	int count;
};

#endif
