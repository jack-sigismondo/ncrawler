#include <stdlib.h>
#include <ncurses.h>
#include <string.h>
#include "graphics.h"


void PrintDebugString(char* string) {
	mvaddstr(30, 2, "The string you entered is:");
	mvaddstr(31, 2, string);
}


void PrintDebugInt(int num) {
	mvaddstr(32, 2, "The number you entered is:");
	char string[10];
	snprintf(string, sizeof(string), "%d", num);
	mvaddstr(33, 2, string);
}


void PrintGraphic(int y, int x, char* file_name) {

  int init_y = y; // HACK unneccessary I think
  int init_x = x;


  char file_path[30] = "graphics/";
  strcat(file_path, file_name); // HACK
  FILE *file_ptr = fopen(file_path, "r");

  
  int ch; // NOTE This is an int to handle EOF
  while ((ch = fgetc(file_ptr)) != EOF) {

    if (ch == '\n') {
      x = init_x;
      y += 1;
    }

    else { mvaddch(y, x++, ch); }

  }

  /* refresh(); // NOTE shouldn't be here maybe */
  
  fclose(file_ptr);

}


void PrintBorder() {

    for (int x = 0; x < 120; ++x) {

	// Top bar
	mvaddch(0, x, '|');
	// Middle bar
	mvaddch(26, x, '|');
	// Bottom bar
	mvaddch(60, x, '|');

	// Advance the cursor
	x += 1;

	// Top bar
	mvaddch(0, x, '-');
	// Middle bar
	mvaddch(26, x, '-');
	// Bottom bar
	mvaddch(60, x, '-');
	
    }

    for (int y = 1; y < 60; ++y) {

	// Left bar
	mvaddch(y, 0, '-');
	mvaddch(y, 1, '|');

	//Middle bar
	mvaddch(y, 75, '|');
	mvaddch(y, 76, '-');

	// Right bar
	mvaddch(y, 119, '|');
	mvaddch(y, 120, '-');

	++y;
	
	// Left bar
	mvaddch(y, 0, '|');
	mvaddch(y, 1, '-');

	// Middle bar
	mvaddch(y, 75, '-');
	mvaddch(y, 76, '|');

	// Right bar
	mvaddch(y, 119, '-');
	mvaddch(y, 120, '|');
    }

    // -.-
    mvaddch(0, 120, '|');
    
}
