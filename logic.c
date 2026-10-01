#include <stdlib.h>
#include <stdlib.h>
#include <stdio.h>
#include <ncurses.h>

#include "logic.h"
#include "map.h"

int entity_count = 0;
// TODO How to keep track of entities?



Player CreatePlayer(int difficulty) { // TODO change to not return the actual
									  // player but create him with malloc

	Player player;
	player.y = 8; // FIXME
	player.x = 8;
	player.direction = 0; // n e s w ; 0 1 2 3

	if (difficulty == 0) {
		player.hp_max = 100;
		player.hp = 100;
	}
	else {
		player.hp_max = 85;
		player.hp = 85;
	}

	return player;
}


void UpdateEntitiesFromMap(Map *map, Player *player /* entities */) {

	int map_size = sizeof(map->arr) / sizeof(map->arr[0]);
	
	for (int y = 0; y < map_size; ++y) {
		for (int x = 0; x < map_size; ++x) {
			if (map->arr[y][x] == M_PLAYER) {
				player->y = y;
				player->x = x;
			}
		}
	}
}


void PrintEnvironment(Map *map, Player *player) {
	// this is straight spaghetti nonsense and was accomplished basically by
	// walking through the program and trial n error. ideally it would be done
	// cleaner more systematically but drawing out ascii walls and corners while
	// fitting them together like puzzle pieces takes too long for me to mess
	// with this now

	int w = 0;

	for (int y = 0; y < 120; ++y) {
		for (int x = 0; x < 120; ++x) {
			mvaddch(y, x, ' ');
		}
	}

	int l_arrow = 1;
	int r_arrow = 1;

	if (map->arr[player->y - 1][player->x] == M_EMPTY) {
		PrintGraphic(3, 8, "wall-face");

		if (map->arr[player->y][player->x - 1] == M_EMPTY) {
			PrintGraphic(1, 2, "wall-left-1");
			l_arrow = 0;
		}
		else if (map->arr[player->y - 1][player->x - 1] == M_EMPTY) {
			PrintGraphic(3, 2, "wall-face-left");
		}

		if (map->arr[player->y][player->x + 1] == M_EMPTY) {
			PrintGraphic(1, 68, "wall-right-1");
			r_arrow = 0;
		}
		else if (map->arr[player->y - 1][player->x + 1] == M_EMPTY) {
			PrintGraphic(3, 68, "wall-face-right");
		}

		if (l_arrow) {
			PrintGraphic(23, 4, "arrow-direction-left");
		}

		if (r_arrow) {
			PrintGraphic(23, 64, "arrow-direction-right");
		}

		return;
	}


	else if (player->y - 2 >= 0 &&
			map->arr[player->y - 2][player->x] == M_EMPTY) {
			w = 1;
	}

	else if (player->y - 3 >= 0 &&
			map->arr[player->y - 3][player->x] == M_EMPTY) {

		PrintGraphic(8, 25, "wall-face-fore");
	}

	PrintGraphic(20, 35, "arrow-direction-up");

	// LEFT SIDE
	int wlf = 0;

	if (player->y - 3 >= 0 &&
		map->arr[player->y - 3][player->x - 1] == M_EMPTY &&
		map->arr[player->y - 2][player->x - 1] != M_EMPTY) {

		PrintGraphic(8, 2, "wall-face-left-fore");
	}

	else if (player->y - 3 >= 0 &&
		map->arr[player->y - 3][player->x - 1] == M_EMPTY &&
		map->arr[player->y - 2][player->x - 1] == M_EMPTY) {

		PrintGraphic(6, 21, "wall-left-fore");
		wlf = 1;	
	}

	if (map->arr[player->y - 1][player->x - 1] == M_EMPTY) {
		PrintGraphic(3, 2, "wall-left-2");

		if (map->arr[player->y - 2][player->x - 1] == M_EMPTY) {
			PrintGraphic(6, 21, "wall-left-fore");
		}
	}

	else if (wlf) {
		PrintGraphic(6, 2, "wall-left-corner");
	}

	if (map->arr[player->y][player->x - 1] == M_EMPTY) {
		PrintGraphic(1, 2, "wall-left-1");
	}

	// END OF LEFT SIDE
	
	// RIGHT SIDE
	int wrf = 0;

	if (player->y - 3 >= 0 &&
		map->arr[player->y - 3][player->x + 1] == M_EMPTY &&
		map->arr[player->y - 2][player->x + 1] != M_EMPTY) {

		PrintGraphic(8, 50, "wall-face-right-fore");
	}

	else if (player->y - 3 >= 0 &&
		map->arr[player->y - 3][player->x + 1] == M_EMPTY &&
		map->arr[player->y - 2][player->x + 1] == M_EMPTY) {

		PrintGraphic(6, 50, "wall-right-fore");
		wrf = 1;	
	}

	if (map->arr[player->y - 1][player->x + 1] == M_EMPTY) {
		PrintGraphic(3, 56, "wall-right-2");

		if (map->arr[player->y - 2][player->x + 1] == M_EMPTY) {
			PrintGraphic(6, 50, "wall-right-fore");
		}
	}

	else if (wrf) {
		PrintGraphic(6, 56, "wall-right-corner");
	}

	if (map->arr[player->y][player->x + 1] == M_EMPTY) {
		PrintGraphic(1, 68, "wall-right-1");
	}
	
	// END OF RIGHT SIDE

	if (w) {
		PrintGraphic(6, 20, "wall");
	}

	if (map->arr[player->y][player->x - 1] != M_EMPTY) {
		PrintGraphic(23, 4, "arrow-direction-left");
	}

	if (map->arr[player->y][player->x + 1] != M_EMPTY) {
		PrintGraphic(23, 64, "arrow-direction-right");
	}

}


void PrintEnvironmentOld(Map *map, Player *player) {
	// straight spaghetti trial and error. ideally i would improve this

	// clear screen // FIXME remove if possible
	for (int y = 0; y < 120; ++y) {
		for (int x = 0; x < 120; ++x) {
			mvaddch(y, x, ' ');
		}
	}

	int left_col[3]; // from player up, 1 == blocked and 0 == free
	int right_col[3]; // from player up, 1 == blocked and 0 == free

	// Print middle
	if (map->arr[player->y - 1][player->x] == M_EMPTY) { // FIXME BLOCKED
		PrintGraphic(1, 2, "wall-face");
		return;
	}

	if (player->y - 2 >= 0) {

		if (map->arr[player->y - 2][player->x - 1] == M_EMPTY) {
			if (map->arr[player->y - 1][player->x - 1] != M_EMPTY) {

				PrintGraphic(6, 2, "wall-left-corner");
				PrintGraphic(6, 21, "wall-left-fore");
			}
		}
	}

	else if (player->y - 3 >= 0 && 
			map->arr[player->y - 3][player->x - 1] == M_EMPTY) {
		PrintGraphic(8, 2, "wall-face-left-fore");
	}


	if (map->arr[player->y][player->x - 1] == M_EMPTY) {
		if (map->arr[player->y - 1][player->x - 1] == M_EMPTY) {
			PrintGraphic(1, 2, "wall-left");
		} // add a bool var here like left wall obscuring
		else {
			PrintGraphic(1, 2, "wall-left-1");
		}

	}



	if (player->y - 2 >= 0 &&
			map->arr[player->y - 2][player->x] == M_EMPTY) {
		PrintGraphic(6, 21, "wall");
	}



	else if (player->y - 3 >= 0 &&
			map->arr[player->y - 3][player->x] == M_EMPTY) {
		PrintGraphic(8, 26, "wall-face-fore");
	}










	return;

	/*

	// PrintGraphic(1, 2, "wall-left-1");

	// PrintGraphic(8, 2, "wall-face-left-fore"); // works

	// PrintGraphic(1, 2, "wall-left-1");

	PrintGraphic(3, 2, "wall-left-2");
	// PrintGraphic(6, 21, "wall-left-fore"); // works
	PrintGraphic(8, 26, "wall-face-fore"); // works

	PrintGraphic(6, 56, "wall-right-corner"); // works


	PrintGraphic(6, 50, "wall-right-fore");	// works
											// PrintGraphic(3, 56, "wall-right-2"); // works

											PrintGraphic(1, 68, "wall-right-1");

	// PrintGraphic(6, 2, "wall-left-corner");

	// PrintGraphic(6, 21, "wall");
	// PrintGraphic(1, 2, "wall-left-1");
	// PrintGraphic(3, 9, "wall-left-2");



	// clear screen // FIXME remove
	for (int y = 0; y < 120; ++y) {
	for (int x = 0; x < 120; ++x) {
	mvaddch(y, x, ' ');
	}
	}


	// Print middle
	if (map->arr[player->y - 1][player->x] == M_EMPTY) { // FIXME m_empty
	PrintGraphic(1, 2, "wall-face");
	return; // return to prevent array error
	}
	else if (player->y - 2 >= 0 &&
	map->arr[player->y - 2][player->x] == M_EMPTY) {
	PrintGraphic(6, 21, "wall");
	}


	// Print left
	//




	// Print right
	//



	// PrintGraphic(1, 2, "wall-left"); // works
	// PrintGraphic(6, 2, "wall-left-corner");
	// PrintGraphic(6, 21, "wall-left-fore"); // works

	// PrintGraphic(8, 2, "wall-face-left-fore"); // works

	// PrintGraphic(8, 25, "wall-face-fore"); // works

	// PrintGraphic(8, 50, "wall-face-fore");

	// PrintGraphic(8, 50, "wall-face-right-fore"); // works

	// PrintGraphic(1, 56, "wall-right"); // works

	// Should print over everything else
	// PrintGraphic(6, 21, "wall"); // ehh

	// PrintGraphic(6, 56, "wall-right-corner"); // works

	*/

}

int MovePlayer(Map *map, Player *player, int keypress) {

	switch(keypress) {
		case KEY_UP:
			if (map->arr[player->y - 1][player->x] == M_PATH) {
				map->arr[player->y][player->x] = M_PATH;
				map->arr[player->y - 1][player->x] = M_PLAYER;
				player->y -= 1;
			}
			break;
		case KEY_DOWN:
			if (map->arr[player->y + 1][player->x] == M_PATH) {
				map->arr[player->y][player->x] = M_PATH;
				map->arr[player->y + 1][player->x] = M_PLAYER;
				player->y += 1;
			}
			break;
		case KEY_LEFT:
			// % 4 keeps the number rotation within 0-3 for nesw
			player->direction = (player->direction + 3) % 4; 
			TransposeMap(map, 'r');
			UpdateEntitiesFromMap(map, player);
			break;
		case KEY_RIGHT:
			player->direction = (player->direction + 1) % 4;
			TransposeMap(map, 'l');
			UpdateEntitiesFromMap(map, player);
			break;
	}

	return 1;
}
