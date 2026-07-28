#ifndef GRAPHICS_H
#define GRAPHICS_H



    



typedef struct Graphic {
  int size_y;
  int size_x;
  char art[60][150];
} Graphic;


// Give a graphic and it's coords and print it
void PrintGraphic(Graphic graphic, int y, int x);

// Return a graphic with the given filename affixed to the graphics folder's path
Graphic LoadGraphic(char* file_name);

// All Graphics
extern Graphic gleft_wall;
extern Graphic gleft_forewall;

extern Graphic gright_wall;
extern Graphic gright_forewall;
void LoadGrahics();

#endif // GRAPHICS_H
