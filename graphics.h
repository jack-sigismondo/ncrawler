#ifndef GRAPHICS_H
#define GRAPHICS_H


// Take a string and print it for debugging
void PrintDebugString(char* string);

// Take a int and print it for debugging
void PrintDebugInt(int num);

// Take a (y,x) pair and print the filename found in graphics/
void PrintGraphic(int y, int x, char* filename);

// Outlay the regular dungeon pov boundaries
void PrintBorder();

#endif // GRAPHICS_H
