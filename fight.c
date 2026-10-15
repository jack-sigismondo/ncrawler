#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "graphics.h"
// include player info so you can pass off armor and weapons

enum weapons { W_SWORD, W_KATANA, W_BOW, W_ };

struct fighter {

  int y;
  int x;

  int weapon;
  char *graphic;

  // 0 1 2
  // 3 4 5
  int position;

  int hp;
};

void fight_start(int difficulty, int entity) {

  // just goblins for now

  int ch;
  // halfdelay(1); // NOTE
  nodelay(stdscr, TRUE);
  srand(time(NULL));

  struct fighter fighter = {10, 25, 0, "fight/fighter-idle", 0};

  clear();

  for (;;) {

    ch = getch(); // TODO but what if it's held down? // TODO key released?

    // Change basd on position * whatever // modulo?

    switch (ch) {
    case KEY_LEFT:
      if (fighter.position != 0 && fighter.position != 3) {
        fighter.position -= 1;
        fighter.x -= 30;
        // update x and y
      }
      break;
    case KEY_RIGHT:
      if (fighter.position != 2 && fighter.position != 5) {
        fighter.position += 1;
        // update x and y
        fighter.x += 30;
      }
      break;
    case 'q':
      clear();
      return;
    default:
      break;
    }

    print_border();
    print_graphic(fighter.y, fighter.x, fighter.graphic);
  }
  refresh();
}

/*
switch (ch) { // if up and other directions in every case
case KEY_LEFT:
  if (fighter.x - 5 >= 2) {
    fighter.x -= 5;
  }
  if (strcmp(fighter.graphic, "fight/fighter-left-1") == 0) {
    fighter.graphic = "fight/fighter-left-2";
  } else {
    fighter.graphic = "fight/fighter-left-1";
  }
  break;
case KEY_RIGHT:
  if (fighter.x + 5 <= 118) {
    fighter.x += 5;
  }
  if (strcmp(fighter.graphic, "fight/fighter-right-1") == 0) {
    fighter.graphic = "fight/fighter-right-2";
  } else {
    fighter.graphic = "fight/fighter-right-1";
  }
  break;

case 'q': // HACK to be removed
  clear();
  return;
default:
  fighter.graphic = "fight/fighter-idle";
  break;
}

print_graphic(fighter.y, fighter.x, fighter.graphic);

print_border();
refresh();
}
}


typedef struct Runner {
int y;
int x;
int hp;

char *graphic;

} Runner;

Runner create_runner(int hp) {
Runner runner;
runner.y = 39;
runner.x = 61;
runner.hp = 100;
runner.graphic = "runner-idle";

return runner;
}

typedef struct Arrow {
int y;
int x;

int speed;

char *graphic;

} Arrow;

Arrow create_arrow(int delay,
                 int location) { // delay = int * 100 iterations worth of
wait Arrow arrow;

arrow.y = delay * -100;
arrow.x = location * 15;

arrow.graphic = "arrow-down";
return arrow;
}

void reset_arrow(Arrow *arrow, int difficulty) {

arrow->y = -100 + (difficulty * 25);
if (arrow->y > 0) {
  arrow->y = 0;
}

arrow->x = rand() % 116;
}

// Check if the arrow is hitting the player or floor
// 0 for neither, 1 for player, 2 for floor
int check_arrow(Arrow *arrow, Runner *runner) { // TODO

// arrow reaches head height
if (arrow->y >= 30) { // TODO change to runner's height

  int distance_apart = abs((runner->x + 6) - (arrow->x + 2));

  // arrow is around head's x coord
  if (distance_apart < 3) {

    return 1;
  }

  // arrow is at the floor
  if (arrow->y > 40) {
    mvaddch(arrow->y, arrow->x - 1, '*');
    mvaddch(arrow->y, arrow->x + 6, '*');
    return 2;
  }
}

return 0;
}

void arrow_start(int difficulty) {

int ch;
halfdelay(1); // NOTE
srand(time(NULL));
clear();

Runner runner = create_runner(100);

Arrow quiver[8];
for (int i = 0; i < 8; ++i) { // HACK
  quiver[i] = create_arrow(i, i);
}

int iterations = 0;
char iter_str[100];
char diff_str[100];

// GAME LOGIC
for (;;) {

  ++iterations;
  if (iterations > 100 * difficulty) {
    ++difficulty;
  }

  // Logging // TODO Remove when unneeded aside from difficulty changes
  snprintf(iter_str, sizeof(iter_str), "There have been %d iterations",
           iterations);
  snprintf(diff_str, sizeof(diff_str), "The difficulty is level %d",
           difficulty);
  mvaddstr(0, 0, iter_str);
  mvaddstr(1, 0, diff_str);

  // timeout(0);
  ch = getch();

  switch (ch) {
  case 'q': // HACK to be removed
    clear();
    return;

  case KEY_LEFT:
    runner.graphic = "runner-left";
    if (runner.x - 5 > 0) {
      runner.x -= 5;
    }
    break;

  case KEY_RIGHT:
    runner.graphic = "runner-right";
    if (runner.x + 5 < 110) {
      runner.x += 5;
    }

    break;

  default:
    runner.graphic = "runner-idle";
    break;
  }

  clear();
  print_graphic(runner.y, runner.x, runner.graphic);
  // TODO Change this to a generic graphic
  print_graphic(50, 0, "floor-generic");

  // Iterate for every arrow in the quiver
  for (int i = 0; i < sizeof(quiver) / sizeof(quiver[0]); ++i) {

    quiver[i].y += difficulty;
    print_graphic(quiver[i].y, quiver[i].x, quiver[i].graphic);

    switch (check_arrow(&quiver[i], &runner)) {
    case 1:    // Gameover
      exit(0); // HACK
      break;
    case 2: // Arrow hits the floor
      reset_arrow(&quiver[i], difficulty);
      break;
    default:
      break;
    }
  }
}
}

*/
