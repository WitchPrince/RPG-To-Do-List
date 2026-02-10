# Derleyici ve Bayraklar (Flags)
CC = gcc
# -std=c99: Standart C99 kullan (bool desteği ve uyumluluk için)
# -Wall: Tüm uyarıları göster (Hata ayıklamak için)
CFLAGS = -std=c99 -Wall

# Hedef dosya ismi
TARGET = rpg

# Kaynak dosyalar
SRCS = main.c functions/taskMenu.c functions/marketMenu.c functions/inventory.c functions/cheats.c

all:
	$(CC) $(CFLAGS) $(SRCS) -o $(TARGET)

install: all
	@echo "Sistem geneline kurulum yapiliyor..."
	@echo '#!/bin/bash' > rpg_launcher
	@echo 'cd "$(CURDIR)" && ./$(TARGET)' >> rpg_launcher
	@chmod +x rpg_launcher
	@sudo mv rpg_launcher /usr/local/bin/$(TARGET)
	@echo "Kurulum basarili! 'rpg' yazarak baslatabilirsin."

uninstall:
	@sudo rm -f /usr/local/bin/$(TARGET)
	@echo "Kaldirma islemi tamamlandi."

clean:
	rm -f $(TARGET)
