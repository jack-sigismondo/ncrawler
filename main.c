#include <stdlib.h>
#include <stdio.h>
#include <ncurses.h>

#include "graphics.c"
#include "graphics.h"
#include "logic.h"
#include "map.c"
#include "ui.c"
#include "logic.c"

int main(int argc, char *argv[]) {
    printf("Beginning of program.");

    

    // TESTING
    Map map = {1, 2};
    GenerateMap(&map, 1);
    
    Player player = CreatePlayer(0);

    /* MovePlayer(&map, &player, KEY_UP); */

    
    /* return 0; */
    // TESTING
    
    // ncurses initialization
    int ch;
    initscr();
    raw();
    cbreak();  
    keypad(stdscr, TRUE);
    noecho();

    LoadGraphics();

    /* PrintMap(map); */

    for (;;) {
	ch = getch();

	/* PrintGraphic(gleft_wall, 1, 2); */

	

	PrintGraphic(gleft_corner_wall, 6, 2);


	PrintGraphic(gwall, 6, 21);
	
	/* PrintGraphic(gleft_forewall, 6, 21); */

	/* PrintGraphic(gforewall, 8, 26); */

	/* PrintGraphic(gright_forewall, 6, 50); */

	PrintGraphic(gright_corner_wall, 6, 56);

	
	
	
	//PrintGraphic(gright_wall, 1, 56);
	/* PrintGraphic(gwallface, 1, 2); */


	PrintBorder();
	

	refresh();
	
	// TODO logic section

	// Keypress logic
	switch (ch) {
	case KEY_UP:
	case KEY_DOWN:
	case KEY_LEFT:
	case KEY_RIGHT:
	    MovePlayer(&map, &player, ch);
	    PrintMap(map);
	    refresh();
	    break;
	    
	case 'q':
	    // HACK
	    exit(0);
	    
	default:
	    continue;
	}

	refresh();
    }
    
    endwin();
    printf("End of program.");
    return 0;
}  
