#include "settings.h"
#include "plugin.h"

int main(int argc, char *argv[]){
	void *handle = NULL;

	if(argc >= 2){
		if(strcmp(argv[1], "--enable-plugin") == 0 || strcmp(argv[1], "-ep") == 0){
		if(argc < 3){
			printf("\nHata! Aktif edilecek eklentinin ismini girmediniz!\nKullanim: rpg -ep <plugin_file.so>\n");
			return 0;
		}

		FILE *modFile = fopen(ACTIVE_PLUGINS, "r");
		char pluginName[100];
		if(modFile != NULL){
			while(fscanf(modFile, "%s\n", pluginName) != EOF){
				if(strcmp(pluginName, argv[2]) == 0){
					printf("Hata! Bu eklenti zaten aktif!");
					fclose(modFile);
					return 0;
				}
			}
			fclose(modFile);
		}

		else{
			printf("Aktif pluginler dosyasi bulunamadi!");
			return 0;
		}
		modFile = fopen(AVAILABLE_PLUGINS, "r");

		if(modFile != NULL){
			while(fscanf(modFile, "%s\n", pluginName) != EOF){ 
				if(strcmp(pluginName, argv[2]) == 0){
					printf("\nEklenti bulundu! Aktif ediliyor...\n\n");
					FILE *addPlugin = fopen(ACTIVE_PLUGINS, "a");
					fprintf(addPlugin, "%s\n", pluginName);
					printf("\n%s eklentisi aktif edilmistir! Uygulamayi kapatip actiginizda uygulanacak!", pluginName);
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
				printf("Aktif pluginler dosyası bulunamadi!");
				return 0;
			}

			if(isItActive){
				rewind(modFile);
				while(fscanf(modFile, "%s\n", pluginName) != EOF){
					if(strcmp(pluginName, argv[2]) != 0){
						fprintf(temp, "%s\n", pluginName);
					}
					else printf("%s eklentisi deaktive edildi!", pluginName);
				}
				fclose(modFile); fclose(temp);
				remove(ACTIVE_PLUGINS);
				rename(TEMP_PLUGINS, ACTIVE_PLUGINS);
				return 0;
			}

			else printf("Hata! Girdiginiz eklenti zaten aktif degil!");
			fclose(modFile); fclose(temp);
		}
	}

	if(argc == 1){
		handle = dlopen("database/do-not-change-these/plugins/ui_manager_plugin.so", RTLD_NOW);	
	}

	else if(argc >= 2){
		handle = dlopen("database/do-not-change-these/plugins/fast_commands_plugin.so", RTLD_NOW);
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
		printf("Motor hatasi! Eklenti yuklenemedi: %s\n\n", dlerror());
	}

	return 0;
}
