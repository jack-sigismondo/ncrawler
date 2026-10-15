#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>

// Framework
#include "graphics.c"
#include "logic.c"
#include "map.c"

// Minigames
#include "arrow.c"

#include "fight.c"

// TODO
// Main battle screen

int main(int argc, char *argv[]) {

  Map *map = malloc(sizeof(Map));
  ReadMap(map, "1");
  int map_follows_player = 0;

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
    ch = getch();

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
      arrow_start(1);
      break;
    case 'r':
      reveal_map(player.y, player.x, 20, map);
      break;
    case 'f':
      fight_start(0, 0);
    case 's':
      map_follows_player = abs(map_follows_player - 1); // toggles 0-1??? check
      break;
    default:
      break;
    }

    PrintEnvironment(map, &player); // problem TODO
    // secondary print
    print_border_dungeon();

    PrintDebugInt(map_follows_player);

    PrintMap(map, map_follows_player);
    refresh();
  }

  endwin();
  return 0;
}
