#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "settings.h"

void marketMenu(){
		FILE *fptr;
		struct Market m1;
		int decision;

		if((fptr = fopen(MARKET, "r")) == NULL){
			printf("Dosya mevcut degil! Lutfen urun ekleyerek dosyayı olusturunuz.\n");
		}

		else{
			char i;
			while(1){
				i = fgetc(fptr);
				if(i == EOF) break;
				else printf("%c", i);
			}
		fclose(fptr);
		}
		printf("\n-------------------------------------------------------\n");
		printf("Hangi islemi yapmak istiyorsunuz?\n\n(1) Buy\n(2) Add Product\n(3) Remove Product\n(4)Change Price\nDecision: ");
		scanf("%d", &decision);

		/*if(decision == 1){ 
		
		}*/

		if(decision == 2){
			fptr = fopen(MARKET, "a");
			
			while(decision != 0){
				printf("\nEklenecek urunun ismi: ");
				scanf("%s", m1.isim);
				printf("Urunun fiyati: ");
				scanf("%d", &m1.price);

				fprintf(fptr, "Product: %s, Price: %d\n", m1.isim, m1.price);

				printf("\nBaska urun eklemek ister misiniz? (1/0): ");
				scanf("%d", &decision);
			}
			fclose(fptr);
		}

		if(decision == 3){
			fptr = fopen(MARKET, "r");
			FILE *temp = fopen(TEMP, "w");

			char deleteName[50];
			char readedName[50];
			int readedPrice;
			bool check;

			printf("Silmek istediginiz urunun ismini giriniz: ");
			scanf("%s", deleteName);

			if(fptr == NULL || temp == NULL){
				printf("Dosya acilamadi!");
				return;
			}

			else{
				while(fscanf(fptr, "Product: %[^,], Price: %d\n", readedName, &readedPrice) != EOF){
					if(strcmp(readedName, deleteName) != 0){
						fprintf(temp, "Product: %s, Price: %d\n", readedName, readedPrice);
					}
					else check = 1;
				}
			}

			fclose(fptr); fclose(temp);

			remove(MARKET);
			rename(TEMP, MARKET);

			if(check == 1) printf("Urun bulundu ve silindi!");
			else printf("Urun bulunamadi!");
		}

		if(decision == 4){
			fptr = fopen(MARKET, "r");
			FILE *temp = fopen(TEMP, "w");

			char searchName[50], foundName[50];
			int changePrice, foundPrice, check = 0;

			printf("Hangi urunun fiyatini degistirmek istiyorsunuz: ");
			scanf("%s", searchName);
			printf("Yeni fiyat: ");
			scanf("%d", &changePrice);

			while(fscanf(fptr, "Product: %[^,], Price: %d\n", foundName, &foundPrice) != EOF){
				if(strcmp(searchName, foundName) != 0){
					fprintf(temp, "Product: %s, Price: %d\n", foundName, foundPrice);
				}
				else{
					fprintf(temp, "Product: %s, Price: %d\n", foundName, changePrice);
					check = 1;
				}
			}

			fclose(fptr); fclose(temp);

			remove(MARKET);
			rename(TEMP, MARKET);

			if(check == 0){
				printf("Aranan urun markette bulunamadi!");
				return;
			}
			else printf("%s urununun yeni degeri: %d", searchName, changePrice);
		}

	}

void taskMenu(){
		FILE *fptr = fopen(TASKS, "r");
		struct Tasks k1;
		int decision;

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

			printf("\nHangi islemi yapmak istiyorsunuz?\n(1) Add quest\n(2) Complete quest\n(3) Change quest parameters\n(4) View Quest Details\n(5) Delete quest\nDecision: ");
			scanf("%d", &decision);

			if(decision == 1){
				fptr = fopen(TASKS, "a");
				int oto;
				if(fptr == NULL){
					printf("Hata! Dosya acilamadi! database klasorundeki tasks.txt dosyasını kontrol edin!");
					return;
				}
				printf("Gorev adi (Maks 80 karakter!): ");
				scanf("%s", k1.taskName);
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

				fprintf(fptr, "Gorev: %s, Zorluk: %d, Odul: %d, Exp: %d\n", k1.taskName, k1.hardness, k1.reward, k1.exp);
				fclose(fptr);
			}

			if(decision == 2){
				FILE *finished = fopen(FINISHED, "a");
				FILE *fptr = fopen(TASKS, "r");
				FILE *temp = fopen(TEMP, "w");
				bool check = 0;

				char searchTask[80];
				printf("Tamamlamak istediginiz gorevin ismini yaziniz: ");
				scanf("%s", searchTask);

				while(fscanf(fptr, "Gorev: %[^,], Zorluk: %d, Odul: %d, Exp: %d\n", k1.taskName, &k1.hardness, &k1.reward, &k1.exp) != EOF){
					if(strcmp(searchTask, k1.taskName) != 0){
						fprintf(temp, "Gorev: %s, Zorluk: %d, Odul: %d, Exp: %d\n", k1.taskName, k1.hardness, k1.reward, k1.exp); 
					}
					else{
						fprintf(finished, "Gorev: %s, Zorluk: %d, Odul: %d, Exp: %d\n", k1.taskName, k1.hardness, k1.reward, k1.exp);
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
				scanf("%d", searchName);

				while(fscanf(fptr, "Gorev: %[^,], Zorluk: %d, Odul: %d, Exp: %d", k1.taskName, k1.hardness, k1.reward, k1.exp)){
					if(strcmp(searchName, k1.taskName) != 0)
						fprintf(temp, "Gorev: %s, Zorluk: %d, Odul: %d, Exp: %d", k1.taskName, k1.hardness, k1.reward, k1.exp);
					else{
						printf("Hangi parametreyi degistirmek istiyorsunuz:\n(1) Task Name\n(2) Hardness\n(3) Reward\n (4) Exp\n");
						scanf("%d", &decision);

							if(decision == 1){
								printf("Yeni gorev adini giriniz: ");
								scanf("%s", searchName);
								fprintf(temp, "Gorev: %s, Zorluk. %d, Odul: %d, Exp: %d", searchName, k1.hardness, k1.reward, k1.exp);
								printf("Gorev adi degistirildi!");
							}

							else if(decision == 2){
								printf("Yeni zorluk duzeyini giriniz (1-5): ");
								scanf("%d", &k1.hardness);
								fprintf(temp, "Gorev: %s, Zorluk: %d, Odul: %d, Exp: %d", k1.taskName, k1.hardness, k1.reward, k1.exp);
								printf("Gorev zorluk seviyesi degistirildi!");
							}

							else if(decision == 3){
								printf("Yeni odul miktarini giriniz: ");
								scanf("%d", &k1.reward);
								fprintf(temp, "Gorev: %s, Zorluk: %d, Odul: %d, Exp: %d", k1.taskName, k1.hardness, k1.reward, k1.exp);
								printf("Gorev odul miktari degistirildi!");
							}

							else if(decision == 4){
								printf("Yeni exp miktarini giriniz: ");
								scanf("%d", &k1.exp);
								fprintf(temp, "Gorev: %s, Zorluk: %d, Odul: %d, Exp: %d", k1.taskName, k1.hardness, k1.reward, k1.exp);
								printf("Gorev exp miktari degistirildi!");
							}
					}
				}
			}
}


