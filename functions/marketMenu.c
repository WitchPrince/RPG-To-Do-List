#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../settings.h"

void marketMenu(){
		FILE *fptr;
		FILE *temp;
		FILE *inventory;
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
			bool found = 0, check = 0;
	       		int balance, oldBalance;	
			char wanted[MAX_ITEM_NAME];
			fptr = fopen(MARKET, "r");
			temp = fopen(TEMP, "w");
			inventory = fopen(INVENTORY, "r");

			fscanf(inventory, "%d\n\n", &oldBalance);

			printf("Hangi urunu almak istiyorsunuz: ");
			scanf("%s", wanted);

			
			while(fscanf(fptr, "Product: %[^,], Price: %d\nItem Details: %[^\n]\n\n", m1.isim, &m1.price, m1.detail) != EOF){
				if(strcmp(wanted, m1.isim) == 0){
					found = 1;
					if(oldBalance >= m1.price){
						balance = oldBalance - m1.price;
						fprintf(temp, "%d\n\n", balance);
					}
					else
						fprintf(temp, "%d\n\n", oldBalance);
				}	
			}
			
			while(1){
				if(fscanf(inventory, " %[^,], %d, Item Detaylari:\n %[^\n]\n\n", i1.itemName, &i1.itemCount, i1.itemDetails) != EOF){
					check = 1;

					if(strcmp(wanted, i1.itemName) == 0){
						if(oldBalance >= m1.price){	
							fprintf(temp, "%s, %d, Item Detaylari:\n%s\n\n", i1.itemName, i1.itemCount + 1, i1.itemDetails);
							printf("Urun alindi ve envanterinize eklendi! Kalan bakiyeniz: %d", balance);
						}

						else{
							printf("Bakiyeniz yetersiz!");
						}
					}	
					else{
						fprintf(temp, "%s, %d, Item Detaylari:\n%s\n\n", i1.itemName, i1.itemCount, i1.itemDetails);
					}
				}

				else{
					if(check == 0){
						fprintf(temp, "%s, 1, Item Detaylari:\n%s\n\n", m1.isim, m1.detail);
						break;
					}

					else break;
				}
			}

			if(found == 0){
				printf("Girdiginiz urun listede bulunmuyor!");
			}

			fclose(temp); fclose(fptr); fclose(inventory);
			
			remove(INVENTORY);
			rename(TEMP, INVENTORY);
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

			fprintf(fptr, "Product: %s, Price: %d\nItem Details: %s\n\n", m1.isim, m1.price, m1.detail);

			printf("\nBaska urun eklemek ister misiniz? (1/0): ");
			scanf("%d", &decision);
		}
		fclose(fptr);
	}

	if(decision == 3){
		fptr = fopen(MARKET, "r");

		char deleteName[50];
		bool check;

		printf("Silmek istediginiz urunun ismini giriniz: ");
		scanf("%s", deleteName);

		if(fptr == NULL || temp == NULL){
			printf("Dosya acilamadi!");
			return;
		}

		else{
			while(fscanf(fptr, "Product: %[^,], Price: %d\nItem Details: %[^\n]\n\n", m1.isim, &m1.price, m1.detail) != EOF){
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

		while(fscanf(fptr, "Product: %[^,], Price: %d\nItem Details: %[^\n]\n\n", m1.isim, &m1.price, m1.detail) != EOF){
			if(strcmp(searchName, m1.isim) != 0){
				fprintf(temp, "Product: %s, Price: %d\nItem Details: %s\n\n", m1.isim, m1.price, m1.detail);
			}
			else{
				fprintf(temp, "Product: %s, Price: %d\nItem Details: %s\n\n", m1.isim, changePrice, m1.detail);
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
		else printf("%s urununun yeni degeri: %d", m1.isim, changePrice);
	}
}
