#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
// Framework
#include "logic.h"
#include "graphics.h"
#include "map.h"
// Minigames
#include "arrow.h" // FIXME move to minigames folder
#include "fight.h"

// TODO
// Main battle screen

int main(int argc, char *argv[]) {

  Map *map = malloc(sizeof(Map));
  ReadMap(map, "1");
  int map_follows_player = 0;

  srand(time(NULL));  

  Player player = CreatePlayer(0);

  // HACK
  int entities[] = {0, 1, 2};
  size_t entities_size = sizeof(entities)/sizeof(entities[0]);

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
	  ArrowStart(1);
	  break;
      case 'r':
	  RevealMap(player.y, player.x, 20, map);
	  break;
      case 'f':
	  FightStart(0, entities, entities_size);
      case 's':
	  map_follows_player = abs(map_follows_player - 1); // toggles 0-1??? check
	  break;
      default:
	  break;
      }

    PrintEnvironment(map, &player); // problem TODO
    // secondary print
    PrintBorderDungeon();

    PrintDebugInt(map_follows_player);

    PrintMap(map, map_follows_player);
    refresh();
  }

  endwin();
  return 0;
}
