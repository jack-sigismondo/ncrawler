#ifndef GRAPHICS_H
#define GRAPHICS_H

// Take a string and print it for debugging
void PrintDebugString(char *string);

// Take a int and print it for debugging
void PrintDebugInt(int num);

// Take a (y,x) pair and print the filename found in graphics/
// NEEDS TO USE MVADDCH
// Why?: It enables printing outside of the current frame
void PrintGraphic(int y, int x, char *filename);

// Outlay the regular dungeon pov boundaries
void PrintBorderDungeon();

// Outlay the most basic game container
void PrintBorder();

#endif // GRAPHICS_H
