#include "../../settings.h"

void marketMenu(char filePathP[100], char filePathI[100]){
		FILE *fptr;
		FILE *temp;
		FILE *inventory;
		FILE *profile;

		struct Market m1;
		struct Item i1;
		struct Profile p1;
		strcpy(p1.expBar, "[__________]");

		int decision, check = 1;
		unsigned long hash;

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
		printf("Hangi islemi yapmak istiyorsunuz?\n\n(1) Buy\n(2) Add Product\n(3) Remove Product\n(4) Change Price\n(5) Exit\nDecision: ");
		scanf("%d", &decision);

	if(decision == 1){
			bool foundInMarket = 1;
	       		int balance, oldBalance, count;	
			char wanted[MAX_ITEM_NAME];
			fptr = fopen(MARKET, "r");
			inventory = fopen(filePathI, "r");
			temp = fopen(TEMP, "w");

			if(fptr == NULL){
				printf("Market dosyasi bos! Lutfen urun ekleyin!");
				return;
			}

			if(inventory == NULL){
				inventory = fopen(filePathI, "w+");
				fprintf(inventory, "Currency: 0\n\n");
				rewind(inventory);
			}

			printf("Hangi urunu almak istiyorsunuz: ");
			scanf(" %[^\n]", wanted);
			printf("Kac tane almak istiyorsunuz: ");
			scanf("%d", &count);
			
			while(fscanf(fptr, "(%d) Product: %[^,], Price: %d\nItem Details:%[^\n]\n\n", &m1.id, m1.name, &m1.price, m1.detail) != EOF){
				if(strcmp(wanted, m1.name) == 0) {				
					foundInMarket = 0;
					break;
				}
			}
			
			if(foundInMarket){
				printf("Urun bulunamadi!");
				fclose(inventory); fclose(fptr); fclose(temp);
				return;
			}

			//Bakiye okuma & yazdirma
			else{
				fscanf(inventory, "Currency: %d\n\n", &oldBalance);
				if(oldBalance >= m1.price * count){
					balance = oldBalance - m1.price * count;
				}
				else{
					printf("Bakiyeniz yetersiz!");
					fclose(inventory); fclose(fptr); fclose(temp);
					return;
				}
			}
		
			while(fscanf(inventory, " %[^,], %d, Item Detaylari:\n%[^\n]\n\n", i1.itemName, &i1.itemCount, i1.itemDetails) != EOF){
				if(strcmp(wanted, i1.itemName) == 0) check = 0;
			}
			rewind(inventory);	
		
			int tempBalance;
			fscanf(inventory, "Currency: %d\n\n", &tempBalance);

			fprintf(temp, "Currency: %d\n\n", balance);
			if(check){
				fprintf(temp, "%s, %d, Item Detaylari:\n%s\n\n", m1.name, count, m1.detail);
			}
			
			while(fscanf(inventory, " %[^,], %d, Item Detaylari:\n%[^\n]\n\n", i1.itemName, &i1.itemCount, i1.itemDetails) != EOF){
				if(strcmp(wanted, i1.itemName) == 0){
					fprintf(temp, "%s, %d, Item Detaylari:\n%s\n\n", i1.itemName, i1.itemCount + count, i1.itemDetails);
					printf("Urun alindi ve envanterinize eklendi! Kalan bakiyeniz: %d", balance);
				}
				else{
					fprintf(temp, "%s, %d, Item Detaylari:\n%s\n\n", i1.itemName, i1.itemCount, i1.itemDetails);
				}
			}

			fclose(fptr); fclose(temp); fclose(inventory);
			remove(filePathI);
			rename(TEMP, filePathI);

			if(foundInMarket == 0){
				temp = fopen(TEMPU, "w");
				profile = fopen(filePathP, "r");

				if(profile == NULL){
					profile = fopen(filePathP, "w");
					printf("Profile dosyasi bulunamadi. Yenisi olusturuluyor...\nKullanici adi: ");
					scanf("%s", p1.user);
					printf("Yeni sifre: ");
					scanf("%s", p1.passwd);
					hash = hashPassword(p1.passwd);

					fprintf(profile, "User: %s, Password: %lu\n\nCurrency: 0\nExp: 0\nLevel: 0, Exp Bar ==> %s\n", p1.user, hash, p1.expBar);
					fclose(profile);
					profile = fopen(filePathP, "r");
				}

				fscanf(profile, "User: %[^,], Password: %lu\n\nCurrency: %d\nExp: %d\nLevel: %d, Exp Bar ==> %s\n", p1.user, &hash, &p1.currency, &p1.exp, &p1.level, p1.expBar);
				fprintf(temp, "User: %s, Password: %lu\n\nCurrency: %d\nExp: %d\nLevel: %d, Exp Bar ==> %s\n", p1.user, hash, balance, p1.exp, p1.level, p1.expBar);
				
				fclose(profile); fclose(temp);
				remove(filePathP);
				rename(TEMPU, filePathP);	
			}
	}

	else if(decision == 2){
		fptr = fopen(MARKET, "a+");
		m1.id = 0;

		while(fscanf(fptr, "(%d) Product: %[^,], Price: %d\nItem Details: %s\n\n", &m1.id, m1.name, &m1.price, m1.detail) != EOF);

		if(m1.id == 0) m1.id = 1;
		else           m1.id += 1;
		rewind(fptr);

		while(decision != 0){
			printf("\nEklenecek urunun ismi: ");
			scanf(" %[^\n]", m1.name);
			printf("Urunun fiyati: ");
			scanf("%d", &m1.price);
			printf("Urun detayi: ");
			scanf(" %[^\n]", m1.detail);

			fprintf(fptr, "(%d) Product: %s, Price: %d\nItem Details: %s\n\n", m1.id, m1.name, m1.price, m1.detail);

			printf("\nBaska urun eklemek ister misiniz? (1/0): ");
			scanf("%d", &decision);
			m1.id++;
		}
		fclose(fptr);
	}

	else if(decision == 3){
		fptr = fopen(MARKET, "r");
		temp = fopen(TEMP, "w");
		
		if(fptr == NULL){
			printf("\nMarket dosyasi bos! Urun ekleyin.");
			fclose(temp);
			remove(TEMP);
			return;
		}
		
		char deleteName[50];
		bool check = 0;

		printf("\nSilmek istediginiz urunun ismini giriniz: ");
		scanf("%s", deleteName);
		while(fscanf(fptr, "(%d) Product: %[^,], Price: %d\nItem Details: %[^\n]\n\n", &m1.id, m1.name, &m1.price, m1.detail) != EOF){
			if(strcmp(m1.name, deleteName) != 0){
				fprintf(temp, "(%d) Product: %s, Price: %d\nItem Details: %s\n\n", m1.id, m1.name, m1.price, m1.detail);
			}
			else check = 1;
		}

		fclose(fptr); fclose(temp);

		remove(MARKET);
		rename(TEMP, MARKET);
	
		m1.id = 0;
		if(check == 1){
			printf("Urun bulundu ve silindi!");
			fptr = fopen(MARKET, "r");
			if(fscanf(fptr, "(%d) Product: %s, Price: %d\nItem Details: %s", &m1.id, m1.name, &m1.price, m1.detail) != EOF){
				if(m1.id == 0){
					fclose(fptr);
					remove(MARKET);
				}
			}
		} 
		else printf("Urun bulunamadi!");
		fclose(fptr);
	}

	else if(decision == 4){
		fptr = fopen(MARKET, "r");
		FILE *temp = fopen(TEMP, "w");

		char searchName[50];
		int changePrice, check = 0;

		printf("Hangi urunun fiyatini degistirmek istiyorsunuz: ");
		scanf("%s", searchName);
		printf("Yeni fiyat: ");
		scanf("%d", &changePrice);

		while(fscanf(fptr, "(%d) Product: %[^,], Price: %d\nItem Details: %[^\n]\n\n", &m1.id, m1.name, &m1.price, m1.detail) != EOF){
			if(strcmp(searchName, m1.name) != 0){
				fprintf(temp, "(%d) Product: %s, Price: %d\nItem Details: %s\n\n", m1.id, m1.name, m1.price, m1.detail);
			}
			else{
				fprintf(temp, "(%d) Product: %s, Price: %d\nItem Details: %s\n\n", m1.id, m1.name, changePrice, m1.detail);
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

	else{
		return;
	}
}
