CC = gcc
CFLAGS = -std=c99 -Wall

TARGET = rpg

SRCS = main.c functions/taskMenu.c functions/marketMenu.c functions/inventory.c functions/cheats.c functions/profile.c functions/userMenu.c

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
