#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../settings.h"

void marketMenu(){
		FILE *fptr;
		struct Market m1;
		struct Item i1;
		int decision, count = 0;

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

	if(decision == 1){ 
			FILE *inventory = fopen(INVENTORY, "r");
			fptr = fopen(MARKET, "r");

			if(inventory == NULL){
				printf("Envanter dosyasi bulunamadi. Yenisi olusturuluyor...\n");
				inventory = fopen(INVENTORY, "w");
				fprintf(inventory, "0\n\n");
				fclose(inventory);
				inventory = fopen(INVENTORY, "r");
			}

			int balance;
			if(fscanf(inventory, "%d", &balance) != 1) balance = 0;

			char wanted[MAX_ITEM_NAME];
			int productFound = 0;

			printf("Almak istediginiz urun: ");
			scanf(" %[^\n]", wanted);

			while(fscanf(fptr, "Product: %[^,], Price: %d\nItem Detaylari: %[^\n]\n\n", m1.isim, &m1.price, m1.detail) != EOF){
				
				if(strcmp(wanted, m1.isim) == 0){
					productFound = 1;

					rewind(inventory);
					int tempBalance; 
					fscanf(inventory, "%d", &tempBalance);

					count = 0; 
					while(fscanf(inventory, " %[^,], %d, Item Detaylari:\n %[^\n]\n\n", i1.itemName, &i1.itemCount, i1.itemDetails) != EOF){
						if(strcmp(wanted, i1.itemName) == 0){
							count = i1.itemCount;
						}
					}
					
					fclose(inventory);
					inventory = fopen(INVENTORY, "a");

					if(balance >= m1.price){
						fprintf(inventory, "%s, %d, Item Detaylari:\n%s\n\n", m1.isim, count + 1, m1.detail);
						printf("Oge envanterinize eklendi!\n");
					}
					else{
						printf("Bakiyeniz yeterli degil!\n");
					}
					
					break; 
				}
			}

			if(productFound == 0){
				printf("Bu urun markette mevcut degil.\n");
				if(inventory) fclose(inventory);
			} else {
				if(inventory) fclose(inventory);
			}

			if(fptr) fclose(fptr);
		}

		if(decision == 2){
			fptr = fopen(MARKET, "a");
			
			while(decision != 0){
				printf("\nEklenecek urunun ismi: ");
				scanf(" %[^\n]", m1.isim);
				printf("Urunun fiyati: ");
				scanf("%d", &m1.price);
				printf("Urun detayi: ");
				scanf(" %[^\n]", m1.detail);

				fprintf(fptr, "Product: %s, Price: %d\nItem Detaylari: %s\n\n", m1.isim, m1.price, m1.detail);

				printf("\nBaska urun eklemek ister misiniz? (1/0): ");
				scanf("%d", &decision);
			}
			fclose(fptr);
		}

		if(decision == 3){
			fptr = fopen(MARKET, "r");
			FILE *temp = fopen(TEMP, "w");

			char deleteName[50];
			//char readedName[50];
			//int readedPrice;
			bool check;

			printf("Silmek istediginiz urunun ismini giriniz: ");
			scanf("%s", deleteName);

			if(fptr == NULL || temp == NULL){
				printf("Dosya acilamadi!");
				return;
			}

			else{
				while(fscanf(fptr, "Product: %[^,], Price: %d\nItem Details: %[^\n]\n\n", m1.isim, &m1.price) != EOF){
					if(strcmp(m1.isim, deleteName) != 0){
						fprintf(temp, "Product: %s, Price: %d\n", m1.isim, m1.price);
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
					fprintf(temp, "Product: %s, Price: %d\n", foundName, &foundPrice);
				}
				else{
					fprintf(temp, "Product: %s, Price: %d\n", foundName, &changePrice);
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
			else printf("%s urununun yeni degeri: %d", searchName, &changePrice);
		}
}

