#include "settingsTui.h"

//Menu lists
char *user_menu_choices[] = {
				"Login",
				"Sign Up",
				NULL,
};

/*I didn't wanna create windows with fixed sizes.
 * So I'll recalculate the padding with this list*/
char *login_choices[] = {
				"Username: ",
				"Password: ",
				NULL,
};

char *signup_choices[] = {
				"Username: ",
				"Password: ",
				NULL,
};

char *yes_no_question[] = {
				"Yes",
				"No",
				NULL,
};

char *settings_menu_choices[] = {
				"Disable auto-login",
				"Change username",
				"Change password",
				"Exit",
				NULL,
};

char *menu_list_choices[] = {
				"Marketplace",
				"Tasks",
				"Inventory",
				"Cheats",
				"Settings",
				"Exit",
				NULL,
};

char *market_menu_choices[] = {
				"Buy",
				"Add Product",
				"Remove Product",
				"Change Price",
				"Exit",
				NULL,
};
