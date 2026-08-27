#ifndef SETTINGSFCP_H
#define SETTINGSFCP_H

#include "plugin.h"
#include "settings.h"

//fast functions
void showFinishedTasks();
void addTaskDirectly(char *taskName, int hardness, int autoCalc, int reward, int exp, char *details);
void completeTaskDirectly(char *taskName, char filePathP[100], char filePathI[100]);
void deleteTaskDirectly(char *taskName);
void changeTaskParamDirectly(char *taskName, int paramType, char *newValueStr);
void autoLogin(char user[MAX_USER_NAME]);
void logOut();

void list_all_plugins();
void list_active_plugins();

int userMenu();

unsigned long hashPassword(char *str);

#endif
