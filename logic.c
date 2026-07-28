#include <stdlib.h>
#include <stdlib.h>
#include <stdio.h>
#include <ncurses.h>

#include "logic.h"
#include "map.h"

int entity_count = 0;
// TODO How to keep track of entities?


Player CreatePlayer(int difficulty) {
    
    Player player;
    player.coord[0] = 9;
    player.coord[1] = 9;
    player.direction = 'n';

    if (difficulty == 0) {
	player.hp_max = 100;
	player.hp = 100;
	return player;
    }
    else {
	player.hp_max = 85;
	player.hp = 85;
	return player;
    }
}


// TODO switch directions to enums and - or + to change them and rotate them
int MovePlayer(Map *map, Player *player, char keypress) {
    
    switch (keypress) {
    case KEY_UP:
	switch (player->direction) {
	case 'n':
	    if ((player->coord[0] > 0) && (map->arr[player->coord[0] - 1][player->coord[1]] == M_PATH)) {
		player->coord[0] -= 1;
		
		return 1;
	    }
	    else { return 0; }
	    
	case 'e':
	    if ((player->coord[1] < 19) && (map->arr[player->coord[0]][player->coord[1] + 1] == M_PATH)) {
		player->coord[1] += 1;
		return 1;
	    }
	    else { return 0; }
	    
	case 's':
	    if ((player->coord[0] < 19) && (map->arr[player->coord[0] + 1][player->coord[1]] == M_PATH)) {
		player->coord[0] += 1;
		return 1;
	    }
	    else { return 0; }
	    
	case 'w':
	    if ((player->coord[1] > 0) && (map->arr[player->coord[0]][player->coord[1] - 1] == M_PATH)) {
		player->coord[1] -= 1;
		return 1;
	    }
	    else { return 0; }

    case KEY_DOWN:
	return 0; // FIXME
	break;
	
    case KEY_LEFT:
	switch (player->direction) {
	case 'n': player->direction = 'w'; return 1;
	case 'e': player->direction = 'n'; return 1;
	case 's': player->direction = 'e'; return 1;
	case 'w': player->direction = 's'; return 1;
	}
	break;
	
    case KEY_RIGHT:
	switch (player->direction) {
	case 'n': player->direction = 'e'; return 1;
	case 'e': player->direction = 's'; return 1;
	case 's': player->direction = 'w'; return 1;
	case 'w': player->direction = 'n'; return 1;
	}
	break;
    
    return 0;
	}
    }
}
