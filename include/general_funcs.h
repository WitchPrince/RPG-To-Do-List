#ifndef GENERAL_FUNCS_H
#define GENERAL_FUNCS_H

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#include "limits.h"
#include "models.h"
#include "config.h"


int isExist(const char *i_name, const char *i_path);

int add_to_inventory(
	const char *i_name, 
	const char *i_path, 
	const unsigned int i_count
);

int add_to_market(
	const char *i_name, 
	const int i_price, 
	const char *i_details
);

int add_to_task_list(
	const char *t_name, 
	const int t_difficulty, 
	const int t_reward, 
	const int t_exp, 
	const char *t_details
);

#endif
