all:
	gcc main.c functions/taskMenu.c functions/marketMenu.c functions/inventory.c -o rpg

clean:
	rm rpg
