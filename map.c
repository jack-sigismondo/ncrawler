#include <stdlib.h>
#include <stdio.h>
#include <ncurses.h>
#include <time.h>

#include "map.h"

// TODO add a legend keybind
// Copy the original array to reference the transposition
void TransposeMap(Map *map, char direction) {

	int new_map[20][20];
	int map_size = sizeof(map->arr) / sizeof(map->arr[0]); 
	
	// set a counter then do a single while
	int right_turns;
	switch (direction) {
		case 'r':
			right_turns = 1;
			break;
		case 'b':
			right_turns = 2;
			break;
		case 'l':
			right_turns = 3;
			break;
		default:
			return;
	}

	while (right_turns != 0) {
		memcpy(new_map, map->arr, 20*20 * sizeof(int));
		for (int i = 0; i < map_size; ++i) {
			for (int j = 0; j < map_size; ++j) {
				// y = 19 - x ; x = y
				map->arr[i][j] = new_map[19 - j][i];
			}
		}

		right_turns -= 1;
	}
}


void EmptyMap(Map *map) {

	for (int i = 0; i < (sizeof(map->arr) / sizeof(map->arr[0])); ++i) {
		for (int j = 0; j < (sizeof(map->arr) / sizeof(map->arr[0])); ++j) {

			map->arr[i][j] = M_EMPTY;
		}
	}
}


// Take a text file and convert it into a map layout
// 19x19 grid of enums i.e. (0 to whatever)
void ReadMap(Map *map, char* file_name) {

	char file_path[30] = "maps/";
	strcat(file_path, file_name); // HACK
	FILE *file_ptr = fopen(file_path, "r");

	int ch; // NOTE This is an int to handle EOF

	int x = 0;
	int y = 0;

	while ((ch = fgetc(file_ptr)) != EOF) {

		if (ch == '\n') {
			x = 0;
			y += 1;
			continue;
		}

		// for 'A' and up, delete the gap from ASCII 9 to A
		if (ch >= 65) {
			ch -= 7;
		}

		// delete remaining 48 since ASCII 0 starts at 48
		ch -= 48;

		map->arr[y][x++] = ch;

	}

	fclose(file_ptr);
}


void PrintAtMap(int y, int x, char c) {

	mvaddch(2 + y, 78 + x, c);
	return;
}


void PrintMap(Map *map) {

	int y = 2;
	int x = 78;

	for (int i = 0; i < (sizeof(map->arr) / sizeof(map->arr[0])); ++i) {
		for (int j = 0; j < (sizeof(map->arr) / sizeof(map->arr[0])); ++j) {

			int map_tile = map->arr[i][j];
			switch(map_tile) {
				case M_EMPTY:
					mvaddch(y, x++, '['); mvaddch(y, x++, ']'); // HACK Switch back to ' '
					break;
				case M_PATH:
					mvaddch(y, x++, ' '); mvaddch(y, x++, ' ');
					break;
				case M_PATH_SEEN:
					mvaddch(y, x++, '['); mvaddch(y, x++, ']');
					break;
				case M_LEVER: // TODO Inquisite the entity list // Switch from /O to \0
					mvaddch(y, x++, '/'); mvaddch(y, x++, 'O');
					break;
				case M_LOCKED_DOOR: // TODO add an unlocked state
					mvaddch(y, x++, 'L'); mvaddch(y, x++, 'K');
					break;


				case M_PLAYER: // TODO check for direction
					mvaddch(y, x++, 'd'); mvaddch(y, x++, '!');
					break;


				case M_STAIRS: // TODO Make entity // TODO Item that turns path into stairs
					mvaddch(y, x++, 'z'); mvaddch(y, x++, 'Z');
					break;
				case M_BLOCKED:
					mvaddch(y, x++, ' '); mvaddch(y, x++, ' ');
					break;
				case M_BLOCKED_SEEN:
					mvaddch(y, x++, 'X'); mvaddch(y, x++, 'X');
					break;
				default:
					mvaddch(y, x++, ' '); mvaddch(y, x++, ' ');
					break;
			}
		}
		++y;
		x = 78;
	}
}
