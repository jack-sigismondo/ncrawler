#include <stdlib.h>
#include <ncurses.h>
#include <strings.h>
#include "graphics.h"

// NOTE You must print from left to right




// Take a graphic struct and print it along given y and x values
void PrintGraphic(Graphic graphic, int y, int x) {

    for (int i = 0; i < graphic.size_y; ++i) {
	mvaddstr(y++, x, graphic.art[i]);
    }
}


Graphic LoadGraphic(char* file_name) {
    
    Graphic graphic = {0, 0};
    
    char file_path[30] = "graphics/";
    strcat(file_path, file_name); // HACK
    FILE *file_ptr = fopen(file_path, "r");
    
    char line[150];
    while (fgets(line, sizeof(line), file_ptr) != NULL) {
	strcpy(graphic.art[graphic.size_y], line);
	++graphic.size_y;
    }

    return graphic;
}


Graphic gleft_wall;
Graphic gleft_forewall;

Graphic gright_wall;
Graphic gright_forewall;

void LoadGraphics() {
    gleft_wall = LoadGraphic("left-wall.txt");
    gleft_forewall = LoadGraphic("left-forewall.txt");
    
    gright_wall = LoadGraphic("right-wall.txt");
    gright_forewall = LoadGraphic("right-forewall.txt");
}
