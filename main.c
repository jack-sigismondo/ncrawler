#include <stdlib.h>
#include <stdio.h>
#include <ncurses.h>

#include "graphics.c"
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

    
    


    for (;;) {
	ch = getch();
	
	
	PrintGraphic(gleft_wall, 1, 2);
	
	PrintGraphic(gleft_forewall, 6, 21);
	
	PrintGraphic(gright_forewall, 6, 50);
	PrintGraphic(gright_wall, 1, 56);
	


	PrintBorder();
	PrintMap(map);

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
	    return 0;
	    
	default:
	    continue;
	}

	refresh();
    }
    
    endwin();
    printf("End of program.");
    return 0;
}  
