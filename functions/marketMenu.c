#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../settings.h"

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

