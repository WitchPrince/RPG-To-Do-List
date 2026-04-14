#include "../../plugin.h"
#include "../../settings.h"

static void *ui_handle = NULL;

static int init(){
	return 0;
}

static int run(int argc, char *argv[]){
	bool cli = 1, tui = 0;
	char moduleName[100], path[100];

	FILE *pref = fopen(ACTIVE_PLUGINS, "r");

	if(pref != NULL){
		while(fscanf(pref, "%[^\n]\n", moduleName) != EOF){
			if(strcmp(moduleName, "tui_plugin.so") == 0){
				cli = 0;
				tui = 1;
			}
		}
		fclose(pref);
	}

	if(cli){
		sprintf(path, "database/do-not-change-these/plugins/cli_plugin.so");
	}

	else{
		sprintf(path, "database/do-not-change-these/plugins/tui_plugin.so");
	}

	ui_handle = dlopen(path, RTLD_NOW);

	if(!ui_handle && tui == 1){
		printf("Hata! Tui modulu etkinlestirilemedi. Modulu ve ncurses'i kontrol edin!\n\n CLI modundan devam ediliyor!\n");
		sprintf(path, "database/do-not-change-these/plugins/cli_plugin.so");
		ui_handle = dlopen(path, RTLD_NOW);
	}

	if(ui_handle){
		get_plugin_info_func get_info = (get_plugin_info_func)dlsym(ui_handle, "get_plugin_info");

		if(get_info){
			Plugin *ui_plugin = get_info();
			ui_plugin->init();
			ui_plugin->run(argc, argv);
			ui_plugin->cleanup();
		}

		else{
			printf("Arayuz eklentisi bulunamadi!: %s\n", dlerror());
		}
	}

	else{
		printf("Arayüz eklentisi bulunamadi: %s\n", dlerror());
	}

	return 1;
}

static void cleanup(){
	if(ui_handle){
		dlclose(ui_handle);
	}
}

Plugin *get_plugin_info(){
	static Plugin p = {
		.moduleName = "UI_Router_Manager",
		.init = init,
		.run = run,
		.cleanup = cleanup
	};
	return &p;
} 
