#ifndef GRAPHICS_H
#define GRAPHICS_H

// Take a string and print it for debugging
void PrintDebugString(char *string);

// Take a int and print it for debugging
void PrintDebugInt(int num);

// Take a (y,x) pair and print the filename found in graphics/
void print_graphic(int y, int x, char *filename);

// Outlay the regular dungeon pov boundaries
void print_border_dungeon();

#endif // GRAPHICS_H
