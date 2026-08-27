#include "settings.h"
#include "plugin.h"

int main(int argc, char *argv[]){
	void *handle = NULL;

	if(argc >= 2){
		if(strcmp(argv[1], "--enable-plugin") == 0 || strcmp(argv[1], "-ep") == 0){
		if(argc < 3){
			printf("\nError! Plugin name is blank!\nUsage: rpg -ep <plugin_file.so>\n");
			return 0;
		}

		FILE *modFile = fopen(ACTIVE_PLUGINS, "r");
		char pluginName[100];
		if(modFile != NULL){
			while(fscanf(modFile, "%s\n", pluginName) != EOF){
				if(strcmp(pluginName, argv[2]) == 0){
					printf("This plugin is already active!");
					fclose(modFile);
					return 0;
				}
			}
			fclose(modFile);
		}

		else{
			printf("Active plugin file is empty! New file will be created...\n");
			modFile = fopen(ACTIVE_PLUGINS, "w");
			fclose(modFile);
			printf("New plugin file has been created!");
		}
		modFile = fopen(AVAILABLE_PLUGINS, "r");

		if(modFile != NULL){
			while(fscanf(modFile, "database/do-not-change-these/plugins/%s\n", pluginName) != EOF){ 
				if(strcmp(pluginName, argv[2]) == 0){
					printf("\nPlugin found! Activating now...\n\n");
					FILE *addPlugin = fopen(ACTIVE_PLUGINS, "a");
					fprintf(addPlugin, "%s\n", pluginName);
					printf("\n%s plugin has been activated! Please restart the app.", pluginName);
					fclose(addPlugin); fclose(modFile);
					return 0;
					}
			}
		}
		fclose(modFile);
		return 0;
	}

		else if(strcmp(argv[1], "--disable-plugin") == 0 || strcmp(argv[1], "-dp") == 0){
			FILE *modFile = fopen(ACTIVE_PLUGINS, "r");
			FILE *temp = fopen(TEMP_PLUGINS, "w");
			char pluginName[100];
			bool isItActive = 0;

			if(modFile != NULL && temp != NULL){
				while(fscanf(modFile, "%s\n", pluginName) != EOF){
					if(strcmp(pluginName, argv[2]) == 0){
						isItActive = 1;
					}
				}
			}

			else{
				printf("Active plugins file is empty!");
				return 0;
			}

			if(isItActive){
				rewind(modFile);
				while(fscanf(modFile, "%s\n", pluginName) != EOF){
					if(strcmp(pluginName, argv[2]) != 0){
						fprintf(temp, "%s\n", pluginName);
					}
					else printf("%s plugin has been deactivated!", pluginName);
				}
				fclose(modFile); fclose(temp);
				remove(ACTIVE_PLUGINS);
				rename(TEMP_PLUGINS, ACTIVE_PLUGINS);
				return 0;
			}

			else printf("Plugin isn't active!");
			fclose(modFile); fclose(temp);
			return 0;
		}
	}

	if(argc == 1){
		handle = dlopen("database/do-not-change-these/plugins/ui_manager_plugin.so", RTLD_NOW);	
		if(handle == NULL){
			fprintf(stderr, "plugin error: %s\n", dlerror());
		}
	}

	else if(argc >= 2){
		handle = dlopen("database/do-not-change-these/plugins/fast_commands_plugin.so", RTLD_NOW);
		if(handle == NULL){
			fprintf(stderr, "plugin error: %s\n", dlerror());
		}
	}

	if(handle){
		get_plugin_info_func get_info = (get_plugin_info_func)dlsym(handle, "get_plugin_info");
		if(get_info){
			Plugin *p = get_info();
			p->init();
			p->run(argc, argv);
			p->cleanup();
		}
		dlclose(handle);
	}
	else{
		printf("Engine error! Plugin couldn't load: %s\n\n", dlerror());
	}

	return 0;
}
