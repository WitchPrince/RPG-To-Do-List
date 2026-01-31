all:
	gcc main.c functions/taskMenu.c functions/marketMenu.c -o rpg

clean:
	rm rpg
