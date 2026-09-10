#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <time.h>

#include "graphics.h"


// TODO Rename this file to arrow dodge something

typedef struct Runner {
    int y;
    int x;
    int hp;

    char* graphic;

} Runner;

Runner CreateRunner(int hp) {
    Runner runner;
    runner.y = 49;
    runner.x = 61;
    runner.hp = 100;
    runner.graphic = "runner-idle.txt";

    return runner;
}    
    

typedef struct Arrow {
    int y;
    int x;

    int speed;

    char* graphic;

} Arrow;


Arrow CreateArrow(int delay, int location) { // delay = int * 100 iterations worth of wait
    Arrow arrow;
    
    arrow.y = delay * -100;
    arrow.x = location * 15;

    arrow.graphic = "arrow-down.txt";
    return arrow;
}


void ResetArrow(Arrow* arrow, int difficulty) {

    arrow->y = -100 + (difficulty * 25);
    if (arrow->y > 0) { arrow->y = 0; }
    
    arrow->x = rand() % 116;

}


// Check if the arrow is hitting the player or floor
// 0 for air, 1 for player, 2 for floor
int CheckCollision(Arrow* arrow, Runner* runner) { // TODO
    
    if (arrow->y >= 40) {
	
	int distance_apart = abs((runner->x + 6) - (arrow->x + 2));
	
	// Collision with player (
	if (distance_apart < 3) {
	    
	    return 1;
	}

	// Collision with ground
	if (arrow->y > 48) {
	    mvaddch(arrow->y, arrow->x -1, '*');
	    mvaddch(arrow->y, arrow->x +6, '*');
	    return 2;
	}
    }

    return 0;
}


void ArrowStart(int difficulty) {

    int ch;
    halfdelay(1); // NOTE
    srand(time(NULL));
    clear();

    Runner runner = CreateRunner(100);
    
    Arrow quiver[8];
    for (int i = 0; i < 8; ++i) { // HACK
	quiver[i] = CreateArrow(i, i);
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
	snprintf(iter_str, sizeof(iter_str), "There have been %d iterations", iterations);
	snprintf(diff_str, sizeof(diff_str), "The difficulty is level %d", difficulty);
	mvaddstr(0, 0, iter_str);
	mvaddstr(1, 0, diff_str);

	// timeout(0);
	ch = getch();

	switch (ch) {
	case 'q': // HACK to be removed
	    clear();
	    return;
	    
	case KEY_LEFT:
	    runner.graphic = "runner-left.txt";
	    if (runner.x - 5 > 0) { runner.x -= 5; }
	    break;
	    
	case KEY_RIGHT:
	    runner.graphic = "runner-right.txt";
	    if (runner.x + 5 < 110) { runner.x += 5; }
	    
	    break;
	    
	default:
	    runner.graphic = "runner-idle.txt";
	    break;
	}
	
	clear();
	PrintGraphic(runner.y, runner.x, runner.graphic);
	// TODO Change this to a generic graphic
	mvaddstr(60, 0, "========================================================================================================================");

	// Iterate for every arrow in the quiver
	for (int i = 0; i < sizeof(quiver) / sizeof(quiver[0]); ++i) {

	    quiver[i].y += difficulty;
	    PrintGraphic(quiver[i].y, quiver[i].x, quiver[i].graphic);

	    switch(CheckCollision(&quiver[i], &runner)) {
	    case 1: // Gameover
		exit(0); // HACK
		break;
	    case 2: // Arrow hits the floor
		ResetArrow(&quiver[i], difficulty);
		break;
	    default:
		break;
	    }
	}
    }
}
