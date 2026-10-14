#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "map.h"

// TODO add a legend keybind
// Copy the original array to reference the transposition
void TransposeMap(Map *map, char direction) {

  int new_arr[20][20];
  int new_revealed[20][20];

  int map_size = sizeof(map->arr) / sizeof(map->arr[0]);

  // set a counter then do a single while
  int turns; // TODO delete this entire thing just arg turns
  switch (direction) {
  case 'l':
    turns = 1;
    map->direction = (map->direction + 1) % 4; // same logic as player direction
    break;
  case 'b':
    turns = 2;
    map->direction = (map->direction + 2) % 4; // same logic as player direction
    break;
  case 'r':
    turns = 3;
    map->direction = (map->direction + 3) % 4; // same logic as player direction
    break;
  default:
    return;
  }

  while (turns != 0) {
    memcpy(new_arr, map->arr, 20 * 20 * sizeof(int));
    memcpy(new_revealed, map->revealed, 20 * 20 * sizeof(int));

    for (int i = 0; i < map_size; ++i) {
      for (int j = 0; j < map_size; ++j) {
        // y = 19 - x ; x = y
        map->arr[i][j] = new_arr[19 - j][i];
        map->revealed[i][j] = new_revealed[19 - j][i];
      }
    }

    turns -= 1;
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
void ReadMap(Map *map, char *file_name) {

  // Sanwich file_name between maps/ and .txt
  char file_path[30] = "maps/";
  strcat(file_path, file_name);
  strcat(file_path, ".txt");

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

    // For 'A' and up, delete the gap from ASCII 9 to A
    if (ch >= 65) {
      ch -= 7;
    }

    // Delete remaining 48 since ASCII 0 starts at 48
    ch -= 48;

    // Use this occassion to also hide the map initially
    map->revealed[y][x] = 0;

    // Read the code and move x ->
    map->arr[y][x++] = ch;
  }

  map->direction = 0;
  map->name = file_name;

  fclose(file_ptr);
}

void reveal_map(int y, int x, int reveal_size, Map *map) {
  // Find bounds left -> you get how much right
  // Find bounds up -> you get how much below

  int leftward_bound = (reveal_size < x) ? (x - reveal_size) : 0;
  int rightward_bound = ((reveal_size + x) < 19) ? (x + reveal_size) : 19;

  int upper_bound = (reveal_size < y) ? (y - reveal_size) : 0;
  int lower_bound = ((reveal_size + y) < 19) ? (y + reveal_size) : 19;

  for (int i = upper_bound; i <= lower_bound; ++i) {
    for (int j = leftward_bound; j <= rightward_bound; ++j) {
      map->revealed[i][j] = 1;
    }
  }
}

void PrintAtMap(int y, int x, char c) {

  mvaddch(2 + y, 78 + x, c);
  return;
}

void PrintMap(Map *map, int map_follows_player) {

  // Transpose the map, print it, then transpose back
  // if this option is enabled
  int original_direction = map->direction;
  if (map_follows_player == 0) {
    while (map->direction != 0) {
      TransposeMap(map, 'l');
    }
  }

  int y = 2;
  int x = 78;

  for (int i = 0; i < (sizeof(map->arr) / sizeof(map->arr[0])); ++i) {
    for (int j = 0; j < (sizeof(map->arr) / sizeof(map->arr[0])); ++j) {

      // Skip over the double char placement
      if (map->revealed[i][j] == 0) {
        x += 2;
        continue;
      }

      int map_tile = map->arr[i][j];
      switch (map_tile) {
      case M_EMPTY:
        mvaddch(y, x++, '[');
        mvaddch(y, x++, ']'); // HACK Switch back to ' '
        break;
      case M_PATH:
        mvaddch(y, x++, ' ');
        mvaddch(y, x++, ' ');
        break;
      case M_PATH_SEEN:
        mvaddch(y, x++, '[');
        mvaddch(y, x++, ']');
        break;
      case M_LEVER: // TODO Inquisite the entity list // Switch from /O to
                    // \0
        mvaddch(y, x++, '/');
        mvaddch(y, x++, 'O');
        break;
      case M_LOCKED_DOOR: // TODO add an unlocked state
        mvaddch(y, x++, 'L');
        mvaddch(y, x++, 'K');
        break;

      case M_PLAYER: // TODO check for direction
        mvaddch(y, x++, 'd');
        mvaddch(y, x++, '!');
        break;

      case M_STAIRS: // TODO Make entity // TODO Item that turns path into
                     // stairs
        mvaddch(y, x++, 'z');
        mvaddch(y, x++, 'Z');
        break;
      case M_BLOCKED:
        mvaddch(y, x++, ' ');
        mvaddch(y, x++, ' ');
        break;
      case M_BLOCKED_SEEN:
        mvaddch(y, x++, 'X');
        mvaddch(y, x++, 'X');
        break;
      default:
        mvaddch(y, x++, ' ');
        mvaddch(y, x++, ' ');
        break;
      }
    }
    ++y;
    x = 78;
  }

  // Transpose back to original if map_follows_player
  if (map_follows_player == 0) {
    while (map->direction != original_direction) {
      TransposeMap(map, 'l');
    }
  }
}
