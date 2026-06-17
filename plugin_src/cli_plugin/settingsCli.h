#ifndef SETTINGSCLI_H
#define SETTINGSCLI_H

//fonksiyonlar
void marketMenu(char *filePathP, char *filePathI);
void taskMenu(char *filePathP, char *filePathI);
void inventory(char *filePathI);
void profileMenu(char *filePathP);
int userMenu();
void cheats(char userName[MAX_USER_NAME]);
unsigned long hashPassword(char *str);
void autoLogin(char user[MAX_USER_NAME]);
void logOut();

#endif
