#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../settings.h"

void taskMenu(){
		FILE *fptr = fopen(TASKS, "r");
		struct Tasks k1;
		int decision;
		bool check = 0;

			if(fptr == NULL){
				printf("Mevcut gorev yok!");
			}
			
			else {
				printf("\n-------------------------------------------------------\n");
				char i;
				while(1){
					i = fgetc(fptr);
					if(i == EOF) break;
					else	printf("%c", i);
				}
				printf("\n-------------------------------------------------------\n");
				fclose(fptr);
			}

			printf("\nHangi islemi yapmak istiyorsunuz?\n(1) Add quest\n(2) Complete quest\n(3) Change quest parameters\n(4) Show finished quests\n(5) Delete quest\nDecision: ");
			scanf("%d", &decision);

			if(decision == 1){
				fptr = fopen(TASKS, "r");
				int oto, detay;
				char isim[MAX_TASK_NAME];

				if(fptr == NULL){
					printf("Hata! Dosya acilamadi! database klasorundeki tasks.txt dosyasını kontrol edin!");
					return;
				}
				printf("Gorev adi (Maks 80 karakter!): ");
				scanf(" %[^\n]", k1.taskName);
					
				while(fscanf(fptr, "Gorev: %[^,], Zorluk: %d, Odul: %d, Exp: %d\nGorev Detaylari:\n %[^\n]\n\n", isim, &k1.hardness, &k1.reward, &k1.exp, k1.taskDetails) == EOF){
					while(strcmp(isim, k1.taskName) == 0){
						printf("Bu isimde baska bir gorev mevcut. Lutfen baska bir isim giriniz!");
						scanf(" %[^\n]", k1.taskName);
					}
				}
				fclose(fptr);
				fptr = fopen(TASKS, "a");

				printf("Gorev zorlugu (1-5): ");
				scanf("%d", &k1.hardness);
				printf("Odul ve exp otomatik hesaplansin mi? (1/0): ");
				scanf("%d", &oto);

				if(oto == 1){
					k1.reward = k1.hardness * 50;
					k1.exp = k1.hardness * 5;
				}
				else{
					printf("Gorev odulu: ");
					scanf("%d", &k1.reward);
					printf("Gorev exp'si: ");
					scanf("%d", &k1.exp);
				}

				printf("Gorev detayi eklemek ister misiniz (1/0): ");
				scanf("%d", &detay);

				if(detay == 1){
					printf("Gorev detayi (Max 300 harf!):\n");
					while(getchar() != '\n');

					fgets(k1.taskDetails, sizeof(k1.taskDetails), stdin);

					fprintf(fptr, "Gorev: %s, Zorluk: %d, Odul: %d, Exp: %d\nGorev Detaylari:\n%s\n\n", k1.taskName, k1.hardness, k1.reward, k1.exp, k1.taskDetails);
				}
				else{
					 char filler[30] = ("Gorev detayi eklenmemis!");
				fprintf(fptr, "Gorev: %s, Zorluk: %d, Odul: %d, Exp: %d\nGorev Detaylari:\n%s\n\n", k1.taskName, k1.hardness, k1.reward, k1.exp, filler);
				}



				fclose(fptr);
			}

			if(decision == 2){
				FILE *finished = fopen(FINISHED, "a");
				FILE *fptr = fopen(TASKS, "r");
				FILE *temp = fopen(TEMP, "w");

				char searchTask[MAX_TASK_NAME];
				printf("Tamamlamak istediginiz gorevin ismini yaziniz: ");
				scanf("%s", searchTask);

				while(fscanf(fptr, "Gorev: %[^,], Zorluk: %d, Odul: %d, Exp: %d\nGorev Detaylari:\n %[^\n]\n\n", k1.taskName, &k1.hardness, &k1.reward, &k1.exp, k1.taskDetails) == EOF){
					if(strcmp(searchTask, k1.taskName) != 0){
						fprintf(temp, "Gorev: %s, Zorluk: %d, Odul: %d, Exp: %d\nGorev Detaylari:\n%s\n\n", k1.taskName, k1.hardness, k1.reward, k1.exp, k1.taskDetails); 
					}
					else{
						fprintf(finished, "Gorev: %s, Zorluk: %d, Odul: %d, Exp: %d\nGorev Detaylari:\n%s\n\n", k1.taskName, k1.hardness, k1.reward, k1.exp, k1.taskDetails);
						check = 1;
					}
				}

				fclose(fptr); fclose(finished); fclose(temp);

				if(check == 0){
					printf("Gorev bulunamadi!");
					return;
				}
				else{
					printf("Gorev tamamlandı!");
				}
			
				remove(TASKS);
				rename(TEMP, TASKS);
			}

			if(decision == 3){
				FILE *fptr = fopen(TASKS, "r");
			       	FILE *temp = fopen(TEMP, "w");
				
				char searchName[MAX_TASK_NAME];
				int foundHardness, foundReward, foundExp;
				
				printf("Hangi görevin parametrelerini degistirmek istiyorsunuz?");
				scanf("%s", searchName);

				while(fscanf(fptr, "Gorev: %[^,], Zorluk: %d, Odul: %d, Exp: %d\nGorev Detaylari:\n %[^\n]\n\n", k1.taskName, &k1.hardness, &k1.reward, &k1.exp, k1.taskDetails) == EOF){
					if(strcmp(searchName, k1.taskName) != 0)
						fprintf(temp, "Gorev: %s, Zorluk: %d, Odul: %d, Exp: %d\nGorev Detaylari:\n%s\n\n", k1.taskName, k1.hardness, k1.reward, k1.exp, k1.taskDetails);
					else{
						printf("Hangi parametreyi degistirmek istiyorsunuz:\n(1) Task Name\n(2) Hardness\n(3) Reward\n(4) Exp\n(5) Details\nDecision: ");
						scanf("%d", &decision);

							if(decision == 1){
								printf("Yeni gorev adini giriniz: ");
								scanf("%[^\n]", searchName);
								fprintf(temp, "Gorev: %s, Zorluk: %d, Odul: %d, Exp: %d\nGorev Detaylari:\n%s\n\n", searchName, k1.hardness, k1.reward, k1.exp, k1.taskDetails);
								printf("Gorev adi degistirildi!");
							}

							else if(decision == 2){
								printf("Yeni zorluk duzeyini giriniz (1-5): ");
								scanf("%d", &k1.hardness);
								fprintf(temp, "Gorev: %s, Zorluk: %d, Odul: %d, Exp: %d\nGorev Detaylari:\n%s\n\n", k1.taskName, k1.hardness, k1.reward, k1.exp, k1.taskDetails);
								printf("Gorev zorluk seviyesi degistirildi!");
							}

							else if(decision == 3){
								printf("Yeni odul miktarini giriniz: ");
								scanf("%d", &k1.reward);
								fprintf(temp, "Gorev: %s, Zorluk: %d, Odul: %d, Exp: %d\nGorev Detaylari:\n%s\n\n", k1.taskName, k1.hardness, k1.reward, k1.exp, k1.taskDetails);
								printf("Gorev odul miktari degistirildi!");
							}

							else if(decision == 4){
								printf("Yeni exp miktarini giriniz: ");
								scanf("%d", &k1.exp);
								fprintf(temp, "Gorev: %s, Zorluk: %d, Odul: %d, Exp: %d\nGorev Detaylari:\n%s\n\n", k1.taskName, k1.hardness, k1.reward, k1.exp, k1.taskDetails);
								printf("Gorev exp miktari degistirildi!");
							}

							else if(decision == 5){
								printf("Yeni detayi giriniz: ");
								while(getchar() != '\n');

								fgets(k1.taskDetails, sizeof(k1.taskDetails), stdin);
								fprintf(temp, "Gorev: %s, Zorluk: %d, Odul: %d, Exp: %d\nGorev Detaylari:\n%s\n\n", k1.taskName, k1.hardness, k1.reward, k1.exp, k1.taskDetails);
							}

							check = 1;
					}
				}

				if(check == 0){
					printf("Girdiginiz gorev listede yok! Gorev adini dogru girdiginizden emin olun!");
				}

				else{
					printf("İslem basarili");
				}

				fclose(temp); fclose(fptr);
				remove(TASKS);
				rename(TEMP, TASKS);
			}

			if(decision == 4){
				FILE *finished = fopen(FINISHED, "r");
		
				if(finished == NULL){
					printf("Mevcut gorev yok!");
				}
			
				else {
					printf("\n-------------------------------------------------------\n");
					char i;
					
					while(1){
						i = fgetc(finished);
						if(i == EOF) break;
						else	printf("%c", i);
					}
				
					printf("\n-------------------------------------------------------\n");
					fclose(finished);
				}

			}

			if(decision == 5){
				FILE *fptr = fopen(TASKS, "r");
				FILE *temp = fopen(TEMP, "w");
				char deleteQuest[MAX_TASK_NAME];

				printf("Silmek istediginiz gorevin adi: ");
				scanf(" %[^\n]", deleteQuest);

				while(fscanf(fptr, "Gorev: %[^,], Zorluk: %d, Odul: %d, Exp: %d\nGorev Detaylari:\n %[^\n]\n\n", k1.taskName, &k1.hardness, &k1.reward, &k1.exp, k1.taskDetails) == EOF){
					if(strcmp(deleteQuest, k1.taskName) != 0){
						fprintf(temp, "Gorev: %s, Zorluk: %d, Odul: %d, Exp: %d\nGorev Detaylari:\n %s\n\n", k1.taskName, k1.hardness, k1.reward, k1.exp, k1.taskDetails);
					}
					else check = 1;
				}
					if(check == 0){
						printf("Girdiginiz isimde bir gorev bulunamadi!");
					}

					else{
						printf("Silme islemi basarili");
					}

					fclose(fptr); fclose(temp);

					remove(TASKS);
					rename(TEMP, TASKS);
				}
				
}

