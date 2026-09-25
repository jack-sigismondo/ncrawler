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
	player.coord[0] = 9;
	player.coord[1] = 9;
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


int MovePlayer(Map *map, Player *player, int keypress) {

	switch(keypress) { // mod by 4 to change direction
		case KEY_UP: // TODO add movement checks
			break;
		case KEY_DOWN: // TODO add movement checks
			break;
		case KEY_LEFT:
			// % 4 keeps the number rotation within 0-3 for nesw
			player->direction = (player->direction + 3) % 4; 
			PrintDebugInt(player->direction);
			TransposeMap(map, 'l');
			break;
		case KEY_RIGHT:
			player->direction = (player->direction + 1) % 4;
			PrintDebugInt(player->direction);
			TransposeMap(map, 'r');
			break;
	}

	return 1;
}
