CC = gcc
CFLAGS = -std=c99 -Wall

SRCS = main.c functions/taskMenu.c functions/marketMenu.c functions/inventory.c functions/cheats.c functions/profile.c functions/userMenu.c

ifeq ($(OS),Windows_NT)
	TARGET = rpg.exe
	MKDIR_CMD = if not exist "database\users" mkdir "database\users"
	RM_CMD = del /Q /F $(TARGET) rpg.bat 2>nul || true
else
	TARGET = rpg
	MKDIR_CMD = mkdir -p database/users
	RM_CMD = rm -f $(TARGET) rpg_launcher
endif

.PHONY: all clean install uninstall directories

all: directories $(TARGET)

directories:
	@$(MKDIR_CMD)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -o $(TARGET)

ifeq ($(OS),Windows_NT)
install: all
	@echo @echo off > rpg.bat
	@echo cd /d "$(CURDIR)" >> rpg.bat
	@echo $(TARGET) >> rpg.bat
	@echo Sistem geneline kurulum yapiliyor (Yonetici izni gerekebilir)...
	@copy /Y rpg.bat "C:\Windows\rpg.bat" >nul || (echo HATA: C:\Windows dizinine erisim engellendi. Lutfen terminali Yonetici (Administrator) olarak calistirin! && exit 1)
	@echo Kurulum basarili! Herhangi bir terminalde 'rpg' yazarak baslatabilirsin.

uninstall:
	@echo Sistemden kaldiriliyor...
	@del /Q /F "C:\Windows\rpg.bat" 2>nul || (echo HATA: Kaldirma islemi icin terminali Yonetici (Administrator) olarak calistirin! && exit 1)
	@echo Kaldirma islemi tamamlandi. Proje dizinindeki .exe dosyasini manuel silebilirsiniz.
else
install: all
	@echo Sistem geneline kurulum yapiliyor...
	@echo '#!/bin/bash' > rpg_launcher
	@echo 'cd "$(CURDIR)" && ./$(TARGET)' >> rpg_launcher
	@chmod +x rpg_launcher
	@sudo mv rpg_launcher /usr/local/bin/$(TARGET)
	@echo Kurulum basarili! 'rpg' yazarak baslatabilirsin.

uninstall:
	@sudo rm -f /usr/local/bin/$(TARGET)
	@echo Kaldirma islemi tamamlandi.
endif

clean:
	@$(RM_CMD)
	@echo Temizlik tamamlandi.
