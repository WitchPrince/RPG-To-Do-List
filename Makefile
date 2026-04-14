CC = gcc
CFLAGS = -std=c99 -Wall
LDFLAGS = -ldl

CORE_SRCS = main.c

PLUGIN_SRC_DIR = plugin_src
PLUGIN_OUT_DIR = database/do-not-change-these/plugins

PLUGIN_DIRS = $(wildcard $(PLUGIN_SRC_DIR)/*)
PLUGIN_SOS = $(patsubst $(PLUGIN_SRC_DIR)/%, $(PLUGIN_OUT_DIR)/%.so, $(PLUGIN_DIRS))

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

all:	directories	$(TARGET) plugins	update-plugins

directories:
	@$(MKDIR_CMD)
	@mkdir -p $(PLUGIN_OUT_DIR)

$(TARGET): $(CORE_SRCS)
	$(CC) $(CFLAGS) $(CORE_SRCS) -o $(TARGET) $(LDFLAGS)

$(PLUGIN_OUT_DIR)/%.so: $(PLUGIN_SRC_DIR)/%
	@echo "Eklenti paketi derleniyor: $(@F)"
	@$(CC) $(CFLAGS) -shared -fPIC $</*.c -o $@ $(shell cat $</flags.txt 2>/dev/null || echo "")

plugins: $(PLUGIN_SOS)

update-plugins:
	@echo "Kullanilabilir eklenti listesi güncelleniyor..."
	@ls -1 $(PLUGIN_OUT_DIR)/*.so > database/do-not-change-these/plugins/available_plugins.txt 2>/dev/null || true

ifeq ($(OS),Windows_NT)
install: all
	@echo @echo off > rpg.bat
	@echo cd /d "$(CURDIR)" >> rpg.bat
	@echo $(TARGET) %%* >> rpg.bat
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
	@echo 'cd "$(CURDIR)" && ./$(TARGET) "$$@"' >> rpg_launcher
	@chmod +x rpg_launcher
	@sudo mv rpg_launcher /usr/local/bin/$(TARGET)
	@sudo mkdir -p /usr/local/share/man/man1
	@sudo cp rpg.1 /usr/local/share/man/man1/
	@sudo gzip -f /usr/local/share/man/man1/rpg.1
	@sudo mandb -q
	@echo Kurulum basarili! 'rpg' yazarak baslatabilir, 'man rpg' ile kılavuza ulasabilirsin!

uninstall:
	@sudo rm -f /usr/local/bin/$(TARGET)
	@echo Kaldirma islemi tamamlandi.
endif

clean:
	@$(RM_CMD)
	@rm -f $(PLUGIN_OUT_DIR)/*.so
	@echo Temizlik tamamlandi.
