#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../settings.h"

void marketMenu(){
		FILE *fptr;
		FILE *temp;
		FILE *inventory;
		FILE *profile;

		struct Market m1;
		struct Item i1;
		struct Profile p1;

		int decision, check = 1;

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
			bool foundInMarket = 0;
	       		int balance, oldBalance;	
			char wanted[MAX_ITEM_NAME];
			fptr = fopen(MARKET, "r");
			inventory = fopen(INVENTORY, "r");

			if(fptr == NULL){
				printf("Market dosyasi bos! Lutfen urun ekleyin!");
				return;
			}

			if(inventory == NULL){
				inventory = fopen(INVENTORY, "w");
				fprintf(inventory, "0\n\n");
				fclose(inventory);
			}

			printf("Hangi urunu almak istiyorsunuz: ");
			scanf("%s", wanted);
			
			while(fscanf(fptr, "Product: %[^,], Price: %d\nItem Details:%[^\n]\n\n", m1.name, &m1.price, m1.detail) != EOF){
				if(strcmp(wanted, m1.name) == 0) foundInMarket = 1;
			}
			fclose(fptr);

			if(foundInMarket == 0){
				printf("Urun bulunamadi!");
				return;
			}

			//Bakiye okuma & yazdirma
			else{
				temp = fopen(TEMP, "w");

				fscanf(inventory, "Currency: %d\n\n", &oldBalance);
				if(oldBalance >= m1.price){
					balance = oldBalance - m1.price;
					fprintf(temp, "Currency: %d\n\n", balance);
				}
				else{
					printf("Bakiyeniz yetersiz!");
					return;
				}
			}
		
			//Envanterde bu itemden hiç yoksa ekleme yapılmıyor. Bu sorunu çöz.	
			while(fscanf(inventory, " %[^,], %d, Item Detaylari:\n%[^\n]\n\n", i1.itemName, &i1.itemCount, i1.itemDetails) != EOF){
				check = 0;
				if(strcmp(wanted, i1.itemName) == 0){
					fprintf(temp, "%s, %d, Item Detaylari:\n%s\n\n", i1.itemName, i1.itemCount + 1, i1.itemDetails);
					printf("Urun alindi ve envanterinize eklendi! Kalan bakiyeniz: %d", balance);
				}	
			}	

			if(check){
				fprintf(temp, "%s, 1, Item Detaylari:\n%s\n\n", m1.name, m1.detail);
			}


			fclose(temp); fclose(inventory);
			remove(INVENTORY);
			rename(TEMP, INVENTORY);

			if(foundInMarket == 1){
				temp = fopen(TEMP, "w");
				profile = fopen(PROFILE, "r");

				if(profile == NULL){
					profile = fopen(PROFILE, "w");
					printf("Profile dosyasi bulunamadi. Yenisi olusturuluyor...\nKullanici adi: ");
					scanf("%s", p1.user);
					fprintf(profile, "User: %s, Currency: 0, Exp: 0", p1.user);
					fclose(profile);
					profile = fopen(PROFILE, "r");
				}

				fscanf(profile, "User: %[^,], Currency: %d, Exp: %d", p1.user, &p1.currency, &p1.exp);
				fprintf(temp, "User: %s, Currency: %d, Exp: %d", p1.user, balance, p1.exp);
				
				fclose(profile); fclose(temp);
				remove(PROFILE);
				rename(TEMP, PROFILE);	
			}
	}

	if(decision == 2){
		fptr = fopen(MARKET, "a");
			
		while(decision != 0){
			printf("\nEklenecek urunun ismi: ");
			scanf(" %[^\n]", m1.name);
			printf("Urunun fiyati: ");
			scanf("%d", &m1.price);
			printf("Urun detayi: ");
			scanf(" %[^\n]", m1.detail);

			fprintf(fptr, "Product: %s, Price: %d\nItem Details: %s\n\n", m1.name, m1.price, m1.detail);

			printf("\nBaska urun eklemek ister misiniz? (1/0): ");
			scanf("%d", &decision);
		}
		fclose(fptr);
	}

	if(decision == 3){
		fptr = fopen(MARKET, "r");
		temp = fopen(TEMP, "w");
		
		if(fptr == NULL || temp == NULL){
			printf("Market dosyasi bos! Urun ekleyin.");
			return;
		}
		
		char deleteName[50];
		bool check;

		printf("Silmek istediginiz urunun ismini giriniz: ");
		scanf("%s", deleteName);

		if(fptr != NULL || temp != NULL){
			while(fscanf(fptr, "Product: %[^,], Price: %d\nItem Details: %[^\n]\n\n", m1.name, &m1.price, m1.detail) != EOF){
				if(strcmp(m1.name, deleteName) != 0){
					fprintf(temp, "Product: %s, Price: %d\n", m1.name, m1.price);
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

		char searchName[50];
		int changePrice, check = 0;

		printf("Hangi urunun fiyatini degistirmek istiyorsunuz: ");
		scanf("%s", searchName);
		printf("Yeni fiyat: ");
		scanf("%d", &changePrice);

		while(fscanf(fptr, "Product: %[^,], Price: %d\nItem Details: %[^\n]\n\n", m1.name, &m1.price, m1.detail) != EOF){
			if(strcmp(searchName, m1.name) != 0){
				fprintf(temp, "Product: %s, Price: %d\nItem Details: %s\n\n", m1.name, m1.price, m1.detail);
			}
			else{
				fprintf(temp, "Product: %s, Price: %d\nItem Details: %s\n\n", m1.name, changePrice, m1.detail);
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
		else printf("%s urununun yeni degeri: %d", m1.name, changePrice);
	}
}
