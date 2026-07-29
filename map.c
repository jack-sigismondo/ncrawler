#include <stdlib.h>
#include <stdio.h>
#include <ncurses.h>
#include <time.h>

#include "map.h"

void PrintAtMap(int y, int x, char symbol[2]) { 
    mvaddch(2 + y, 2 * x + 78, symbol[0]);
    mvaddch(2 + y, 2 * x + 78 + 1, symbol[1]);
}



void EmptyMap(Map *map) {
    
    for (int i = 0; i < (sizeof(map->arr) / sizeof(map->arr[0])); ++i) {
	for (int j = 0; j < (sizeof(map->arr) / sizeof(map->arr[0])); ++j) {
	    
	    map->arr[i][j] = M_EMPTY; // HACK This should actually be empty once the map is generated
	}
    }
}


void GenerateMap(Map *map, int multiplier) {
    EmptyMap(map);
    // Try going from player to left then right

    int y = 9;
    int x = 9;
    
    map->arr[y][x] = M_PLAYER;

    srand(time(NULL)); // TODO might need to move this to once in main

    // TODO
    


    refresh(); // TODO remove

    // TODO block off inaccessable
}


void PrintMap(Map map) { // FIXME This is a horrible system and needs an entity system to draw on the map
    
    // for i -> for j -> if certain mapcode, print certain string
    // if map is smaller than 20x20 just don't print it
    // I guess this means create an ideally centered map if it's gonna be smaller

    int y = 2;
    int x = 78; // FIXME Don't make this a magic number

    for (int i = 0; i < (sizeof(map.arr) / sizeof(map.arr[0])); ++i) {
	for (int j = 0; j < (sizeof(map.arr) / sizeof(map.arr[0])); ++j) {
	    switch (map.arr[i][j]) {
	    case M_PATH:
		mvaddch(y, x++, ' ');
		mvaddch(y, x++, ' ');
		break;
	    case M_EMPTY:
		mvaddch(y, x++, '[');
		mvaddch(y, x++, ']');
		break;
	    case M_PLAYER:
		mvaddch(y, x++, '#');
		mvaddch(y, x++, '!');
		break;
	    default:
		x += 2;
		continue;
	    }
	}
	++y;
	x = 78; // FIXME Don't make this a magic number
    }

    refresh();
    
}
