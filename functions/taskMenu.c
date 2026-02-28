#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../settings.h"

void taskMenu(char filePathP[100], char filePathI[100]){
		FILE *fptr = fopen(TASKS, "r");
		FILE *temp;
		FILE *inventory;
		FILE *profile;

		struct Tasks k1;
		struct Profile p1;
		int subDecision;
		bool check = 0;
	 	unsigned long hash;
		strcpy(p1.expBar, "[__________]"); 

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

			printf("\nHangi islemi yapmak istiyorsunuz?\n(1) Add quest\n(2) Complete quest\n(3) Change quest parameters\n(4) Show finished quests\n(5) Delete quest\n(6) Exit\nDecision: ");
			scanf("%d", &subDecision);

			if(subDecision == 1){
				int oto, detay;
				bool isDuplicate;
				char name[MAX_TASK_NAME];

				printf("Gorev adi (Maks 80 karakter!): ");
				scanf(" %[^\n]", k1.taskName);
					
				do{
					isDuplicate = 0;
					fptr = fopen(TASKS, "r");

					if(fptr != NULL){
						while(fscanf(fptr, "Gorev: %[^,], Zorluk: %d, Odul: %d, Exp: %d\nGorev Detaylari:\n %[^\n]\n\n", name, &k1.hardness, &k1.reward, &k1.exp, k1.taskDetails) != EOF){
							if(strcmp(name, k1.taskName) == 0){
								isDuplicate = 1;
								printf("Bu isimde baska bir gorev mevcut. Lutfen baska bir isim giriniz!");
								scanf(" %[^\n]", k1.taskName);
								break;
							}
						}
						fclose(fptr);
					}
				}while(isDuplicate);

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
					scanf(" %[^\n]", k1.taskDetails);

					fprintf(fptr, "Gorev: %s, Zorluk: %d, Odul: %d, Exp: %d\nGorev Detaylari:\n%s\n\n", k1.taskName, k1.hardness, k1.reward, k1.exp, k1.taskDetails);
				}
				else{
					 char filler[30] = ("Gorev detayi eklenmemis!");
				fprintf(fptr, "Gorev: %s, Zorluk: %d, Odul: %d, Exp: %d\nGorev Detaylari:\n%s\n\n", k1.taskName, k1.hardness, k1.reward, k1.exp, filler);
				}



				fclose(fptr);
			}

			else if(subDecision == 2){
				FILE *finished = fopen(FINISHED, "a");
				fptr = fopen(TASKS, "r");
				temp = fopen(TEMP, "w");
				int reward, expGain;

				char searchTask[MAX_TASK_NAME];

				if(fptr == NULL){
					printf("Gorev listesi bos! Gorev ekleyiniz!");
					fclose(fptr); fclose(temp); fclose(finished);
					remove(TEMP);
					return;
				}
				printf("Tamamlamak istediginiz gorevin ismini yaziniz: ");
				scanf(" %[^\n]", searchTask);

				while(fscanf(fptr, "Gorev: %[^,], Zorluk: %d, Odul: %d, Exp: %d\nGorev Detaylari:\n %[^\n]\n\n", k1.taskName, &k1.hardness, &k1.reward, &k1.exp, k1.taskDetails) != EOF){
					if(strcmp(searchTask, k1.taskName) != 0){
						fprintf(temp, "Gorev: %s, Zorluk: %d, Odul: %d, Exp: %d\nGorev Detaylari:\n%s\n\n", k1.taskName, k1.hardness, k1.reward, k1.exp, k1.taskDetails); 
					}
					else{
						fprintf(finished, "Gorev: %s, Zorluk: %d, Odul: %d, Exp: %d\nGorev Detaylari:\n%s\n\n", k1.taskName, k1.hardness, k1.reward, k1.exp, k1.taskDetails);
						reward = k1.reward;
						expGain = k1.exp;
						check = 1;
					}
				}

				fclose(finished); fclose(temp); fclose(fptr);
			
				remove(TASKS);
				rename(TEMP, TASKS);

				//Reward gain system

				if(check == 0){
					printf("Gorev bulunamadi!");
					return;
				}
				else{
					temp = fopen(TEMP, "w");
					inventory = fopen(filePathI, "r");

					struct Item i1;
					int balance, oldBalance, exp;
				
					if(inventory == NULL){
						inventory = fopen(filePathI, "w");
						fprintf(inventory, "Currency: 0\n\n");
						fclose(inventory);
						inventory = fopen(filePathI, "r");
					}
					fscanf(inventory, "Currency: %d\n\n", &oldBalance);

					balance = oldBalance + reward;						fprintf(temp, "Currency: %d\n\n", balance);

					while(fscanf(inventory, "%[^,], %d, Item Detaylari:\n%[^\n]\n\n", i1.itemName, &i1.itemCount, i1.itemDetails) != EOF){
						fprintf(temp, "%s, %d, Item Detaylari:\n%s\n\n", i1.itemName, i1.itemCount, i1.itemDetails);
					}
					fclose(temp); fclose(inventory);
					remove(filePathI);
					rename(TEMP, filePathI);

					temp = fopen(TEMP, "w");
					profile = fopen(filePathP, "r");

					if(profile == NULL){
						profile = fopen(filePathP, "w");
						char userName[MAX_USER_NAME];
						printf("Profil bulunamadi! Yeni profil olusturuluyor...\nKullanici adiniz (Max 30 harf): ");
						scanf("%s", userName);
						
						printf("Yeni sifre: ");
						scanf("%s", p1.passwd);

						hash = hashPassword(p1.passwd);
						fprintf(profile, "User: %s, Password: %lu\n\nCurrency: %d\nExp: 0\nLevel: 0, Exp Bar ==> %s\n", userName, hash, balance, p1.expBar);
						fclose(profile);
						profile = fopen(filePathP, "r");
					}
					
					fscanf(profile, "User: %[^,], Password: %lu\n\nCurrency: %d\nExp: %d\nLevel: %d, Exp Bar ==> %s\n", p1.user, &hash, &p1.currency, &p1.exp, &p1.level, p1.expBar);
					exp = p1.exp + expGain; 
					
					fprintf(temp, "User: %s, Password: %lu\n\nCurrency: %d\nExp: %d\nLevel: %d, Exp Bar ==> %s\n", p1.user, hash, balance, exp, p1.level, p1.expBar);

					fclose(temp); fclose(profile);
					remove(filePathP);
					rename(TEMP, filePathP);

					printf("Gorev tamamlandı!");
				}
			}

			else if(subDecision == 3){
				FILE *fptr = fopen(TASKS, "r");
			       	FILE *temp = fopen(TEMP, "w");
				
				char searchName[MAX_TASK_NAME];
				
				if(fptr == NULL){
					printf("Gorev listesi bos! Gorev ekleyiniz!");
					fclose(fptr); fclose(temp);
					return;
				}
				printf("Hangi görevin parametrelerini degistirmek istiyorsunuz?");
				scanf(" %[^\n]", searchName);

				while(fscanf(fptr, "Gorev: %[^,], Zorluk: %d, Odul: %d, Exp: %d\nGorev Detaylari:\n %[^\n]\n\n", k1.taskName, &k1.hardness, &k1.reward, &k1.exp, k1.taskDetails) != EOF){
					if(strcmp(searchName, k1.taskName) != 0)
						fprintf(temp, "Gorev: %s, Zorluk: %d, Odul: %d, Exp: %d\nGorev Detaylari:\n%s\n\n", k1.taskName, k1.hardness, k1.reward, k1.exp, k1.taskDetails);
					else{
						printf("Hangi parametreyi degistirmek istiyorsunuz:\n(1) Task Name\n(2) Hardness\n(3) Reward\n(4) Exp\n(5) Details\nDecision: ");
						scanf("%d", &subDecision);

							if(subDecision == 1){
								printf("Yeni gorev adini giriniz: ");
								scanf(" %[^\n]", searchName);
								fprintf(temp, "Gorev: %s, Zorluk: %d, Odul: %d, Exp: %d\nGorev Detaylari:\n%s\n\n", searchName, k1.hardness, k1.reward, k1.exp, k1.taskDetails);
								printf("Gorev adi degistirildi!");
							}

							else if(subDecision == 2){
								printf("Yeni zorluk duzeyini giriniz (1-5): ");
								scanf("%d", &k1.hardness);
								fprintf(temp, "Gorev: %s, Zorluk: %d, Odul: %d, Exp: %d\nGorev Detaylari:\n%s\n\n", k1.taskName, k1.hardness, k1.reward, k1.exp, k1.taskDetails);
								printf("Gorev zorluk seviyesi degistirildi!");
							}

							else if(subDecision == 3){
								printf("Yeni odul miktarini giriniz: ");
								scanf("%d", &k1.reward);
								fprintf(temp, "Gorev: %s, Zorluk: %d, Odul: %d, Exp: %d\nGorev Detaylari:\n%s\n\n", k1.taskName, k1.hardness, k1.reward, k1.exp, k1.taskDetails);
								printf("Gorev odul miktari degistirildi!");
							}

							else if(subDecision == 4){
								printf("Yeni exp miktarini giriniz: ");
								scanf("%d", &k1.exp);
								fprintf(temp, "Gorev: %s, Zorluk: %d, Odul: %d, Exp: %d\nGorev Detaylari:\n%s\n\n", k1.taskName, k1.hardness, k1.reward, k1.exp, k1.taskDetails);
								printf("Gorev exp miktari degistirildi!");
							}

							else if(subDecision == 5){
								printf("Yeni detayi giriniz: ");
								while(getchar() != '\n');

								scanf(" %[^\n]", k1.taskDetails);
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

			else if(subDecision == 4){
				FILE *finished = fopen(FINISHED, "r");
		
				if(finished == NULL){
					printf("Bitmis gorev yok!");
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

			else if(subDecision == 5){
				FILE *fptr = fopen(TASKS, "r");
				FILE *temp = fopen(TEMP, "w");
				char deleteQuest[MAX_TASK_NAME];

				if(fptr == NULL){
					printf("Gorev listesi bos! Gorev ekleyiniz!");
					return;
				}

				printf("Silmek istediginiz gorevin adi: ");
				scanf(" %[^\n]", deleteQuest);

				while(fscanf(fptr, "Gorev: %[^,], Zorluk: %d, Odul: %d, Exp: %d\nGorev Detaylari:\n %[^\n]\n\n", k1.taskName, &k1.hardness, &k1.reward, &k1.exp, k1.taskDetails) != EOF){
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

			else if(subDecision == 6){
				return;
			}
				
}

