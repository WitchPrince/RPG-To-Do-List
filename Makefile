all:
	gcc main.c functions/taskMenu.c functions/marketMenu.c functions/inventory.c -o rpg

clean:
	rm rpg

install: all
	@echo '#!/bin/bash' > rpg_launcher
	@echo 'cd "$(CURDIR)" && ./rpg' >> rpg_launcher
	@chmod +x rpg_launcher
	@sudo mv rpg_launcher /usr/local/bin/rpg
	@echo "Setup complete! Start by typing 'rpg' on terminal."

uninstall:
	@sudo rm -f /usr/local/bin/rpg
	@echo "Rpg is removed! See you next time."
