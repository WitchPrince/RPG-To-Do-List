#ifndef SETTINGSCLI_H
#define SETTINGSCLI_H

#include "settings.h"
#include "plugin.h"

//fonksiyonlar
void marketMenu(char *filePathP, char *filePathI);
void taskMenu(char *filePathP, char *filePathI);
void inventory(char *filePathI);
void profileMenu(char *filePathP);
void cheats(char userName[MAX_USER_NAME]);
void autoLogin(char user[MAX_USER_NAME]);
void logOut();

unsigned long hashPassword(char *str);

int userMenu();

#endif
