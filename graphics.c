#include <stdlib.h>
#include <ncurses.h>
#include <strings.h>
#include "graphics.h"

// NOTE You must print from left to right

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


// Take a graphic struct and print it along given y and x values
void PrintGraphicOld(Graphic graphic, int y, int x) { // TODO Change to y, x, graphic // Change to mvaddch

  
  

    /* for (int i = 0; i < graphic.size_y; ++i) { */
    /* 	mvaddstr(y++, x, graphic.art[i]); */
    /* } */
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

// TODO See if I even need this here, or if I need the extern for anything

Graphic gleft_wall;
Graphic gleft_forewall;

Graphic gright_wall;
Graphic gright_forewall;

Graphic gwallface;
Graphic gwall;
Graphic gforewall;

Graphic gright_corner_wall;
Graphic gleft_corner_wall;

Graphic gleft_sword;
Graphic gright_sword;

Graphic gdown_arrow;
Graphic gup_arrow;

Graphic gleft_run;
Graphic gright_run;
Graphic gstanding;


void LoadGraphics() {
    gleft_wall = LoadGraphic("left-wall.txt");
    gleft_forewall = LoadGraphic("left-forewall.txt");
    
    gright_wall = LoadGraphic("right-wall.txt");
    gright_forewall = LoadGraphic("right-forewall.txt");

    gwallface = LoadGraphic("wallface.txt");
    gwall = LoadGraphic("wall.txt");
    gforewall = LoadGraphic("forewall.txt");

    gright_corner_wall = LoadGraphic("r-corner-wall.txt");
    gleft_corner_wall = LoadGraphic("l-corner-wall.txt");

    gleft_sword = LoadGraphic("l-sword.txt");
    gright_sword = LoadGraphic("r-sword.txt");

    gdown_arrow = LoadGraphic("d-arrow.txt");
    gup_arrow = LoadGraphic("u-arrow.txt");


    gleft_run = LoadGraphic("l-run.txt");
    gright_run = LoadGraphic("r-run.txt");
    gstanding = LoadGraphic("standing.txt");

}
