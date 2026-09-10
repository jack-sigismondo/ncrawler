#ifndef GRAPHICS_H
#define GRAPHICS_H


typedef struct Graphic {
  int size_y;
  int size_x;
  char art[60][150];
} Graphic;


// Give a graphic and it's coords and print it
void PrintGraphic(int y, int x, char* file_name);
void PrintGraphicOld(Graphic graphic, int y, int x);

// Return a graphic with the given filename affixed to the graphics folder's path
Graphic LoadGraphic(char* file_name);

// All Graphics
extern Graphic gleft_wall;
extern Graphic gleft_forewall;

extern Graphic gright_wall;
extern Graphic gright_forewall;

extern Graphic gwallface;
extern Graphic gwall; // Print as left-forewall
extern Graphic gforewall;


extern Graphic gright_corner_wall;
extern Graphic gleft_corner_wall;

extern Graphic gleft_sword;
extern Graphic gright_sword;

extern Graphic gdown_arrow;
extern Graphic gup_arrow;

extern Graphic gleft_run;
extern Graphic gright_run;
extern Graphic gstanding;


void LoadGraphics();

#endif // GRAPHICS_H
