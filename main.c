#include <stdlib.h>
#include <stdio.h>
#include <ncurses.h>

// Framework
#include "graphics.c"
#include "logic.c"
#include "map.c"

// Minigames
#include "arrow.c"

// TODO get rid of ".txt" everywhere. Just append it to the string so you don't have to type it every time
// TODO adjust the height of the game
// TODO add actual screen border variables

int main(int argc, char *argv[]) {
	printf("Beginning of program.");


	Map *map = malloc(sizeof(Map));
	ReadMap(map, "1.txt");


	Player player = CreatePlayer(0);



	// ncurses initialization
	int ch = 0;
	initscr();
	raw();
	cbreak();  
	keypad(stdscr, TRUE);
	nonl(); // TODO What does this do?
	noecho();

	while (ch != 'q') {
		ch = getch(); // Originally at the end

		PrintGraphic(1, 2, "wall-left.txt");
		PrintGraphic(6, 21, "wall-left-fore.txt");

		PrintGraphic(8, 26, "wall-fore.txt");

		/* PrintGraphic(6, 50, "wall-right-fore.txt"); */
		PrintGraphic(1, 56, "wall-right.txt");

		// Should print over everything else
		/* PrintGraphic(6, 21, "wall.txt"); */

		// Keypress logic
		switch (ch) {
			case KEY_UP:
				MovePlayer(map, &player, ch);
				break;
			case KEY_DOWN:
				MovePlayer(map, &player, ch);
				break;
			case KEY_LEFT:
				MovePlayer(map, &player, ch);
				break;
			case KEY_RIGHT:
				MovePlayer(map, &player, ch);
				break;
			case 'a':
				ArrowStart(1);
			default:
				break;

		}
		// secondary print
		PrintMap(map);
		PrintBorder();
		refresh();
	}

	endwin();
	return 0;
}
