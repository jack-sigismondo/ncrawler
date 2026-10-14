#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>

#include "graphics.h"
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
  } else {
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

  // Clear the screen
  for (int y = 0; y < 120; ++y) {
    for (int x = 0; x < 120; ++x) {
      mvaddch(y, x, ' ');
    }
  }

  int l_arrow = 1;
  int r_arrow = 1;

  if (map->arr[player->y - 1][player->x] == M_EMPTY) {
    print_graphic(3, 8, "wall-face");

    if (map->arr[player->y][player->x - 1] == M_EMPTY) {
      print_graphic(1, 2, "wall-left-1");
      l_arrow = 0;
    } else if (map->arr[player->y - 1][player->x - 1] == M_EMPTY) {
      print_graphic(3, 2, "wall-face-left");
    }

    if (map->arr[player->y][player->x + 1] == M_EMPTY) {
      print_graphic(1, 68, "wall-right-1");
      r_arrow = 0;
    } else if (map->arr[player->y - 1][player->x + 1] == M_EMPTY) {
      print_graphic(3, 68, "wall-face-right");
    }

    if (l_arrow == 1) {
      print_graphic(23, 4, "arrow-direction-left");
    }

    if (r_arrow == 1) {
      print_graphic(23, 64, "arrow-direction-right");
    }

    return;
  }

  else if (player->y - 2 >= 0 &&
           map->arr[player->y - 2][player->x] == M_EMPTY) {
    w = 1;
  }

  else if (player->y - 3 >= 0 &&
           map->arr[player->y - 3][player->x] == M_EMPTY) {

    print_graphic(8, 25, "wall-face-fore");
  }

  print_graphic(20, 35, "arrow-direction-up");

  // LEFT SIDE
  int wlf = 0;

  if (player->y - 3 >= 0 && map->arr[player->y - 3][player->x - 1] == M_EMPTY &&
      map->arr[player->y - 2][player->x - 1] != M_EMPTY) {

    print_graphic(8, 2, "wall-face-left-fore");
  }

  else if (player->y - 3 >= 0 &&
           map->arr[player->y - 3][player->x - 1] == M_EMPTY &&
           map->arr[player->y - 2][player->x - 1] == M_EMPTY) {

    print_graphic(6, 21, "wall-left-fore");
    wlf = 1;
  }

  if (map->arr[player->y - 1][player->x - 1] == M_EMPTY) {
    print_graphic(3, 2, "wall-left-2");

    if (map->arr[player->y - 2][player->x - 1] == M_EMPTY) {
      print_graphic(6, 21, "wall-left-fore");
    }
  }

  else if (wlf) {
    print_graphic(6, 2, "wall-left-corner");
  }

  if (map->arr[player->y][player->x - 1] == M_EMPTY) {
    print_graphic(1, 2, "wall-left-1");
  }

  // END OF LEFT SIDE

  // RIGHT SIDE
  int wrf = 0;

  if (player->y - 3 >= 0 && map->arr[player->y - 3][player->x + 1] == M_EMPTY &&
      map->arr[player->y - 2][player->x + 1] != M_EMPTY) {

    print_graphic(8, 50, "wall-face-right-fore");
  }

  else if (player->y - 3 >= 0 &&
           map->arr[player->y - 3][player->x + 1] == M_EMPTY &&
           map->arr[player->y - 2][player->x + 1] == M_EMPTY) {

    print_graphic(6, 50, "wall-right-fore");
    wrf = 1;
  }

  if (map->arr[player->y - 1][player->x + 1] == M_EMPTY) {
    print_graphic(3, 56, "wall-right-2");

    if (map->arr[player->y - 2][player->x + 1] == M_EMPTY) {
      print_graphic(6, 50, "wall-right-fore");
    }
  }

  else if (wrf) {
    print_graphic(6, 56, "wall-right-corner");
  }

  if (map->arr[player->y][player->x + 1] == M_EMPTY) {
    print_graphic(1, 68, "wall-right-1");
  }

  // END OF RIGHT SIDE

  if (w) {
    print_graphic(6, 20, "wall");
  }

  if (map->arr[player->y][player->x - 1] != M_EMPTY) {
    print_graphic(23, 4, "arrow-direction-left");
  }

  if (map->arr[player->y][player->x + 1] != M_EMPTY) {
    print_graphic(23, 64, "arrow-direction-right");
  }
}

int MovePlayer(Map *map, Player *player, int keypress) {

  switch (keypress) {
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
    TransposeMap(map, 'l');
    UpdateEntitiesFromMap(map, player);
    break;

  case KEY_RIGHT:
    player->direction = (player->direction + 1) % 4;
    TransposeMap(map, 'r');
    UpdateEntitiesFromMap(map, player);
    break;
  }
  reveal_map(player->y, player->x, 2, map);
  return 1;
}


