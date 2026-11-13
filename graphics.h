#ifndef GRAPHICS_H
#define GRAPHICS_H

// Take a (y,x) pair and print the filename found in graphics/
// NEEDS TO USE MVADDCH!
// Why?: It enables printing outside of the current frame.
void
PrintGraphic(int y, int x, char *filename);
/* Feed ideally a 2x2 array of ints and a graphic
 * and populate their values */
void
get_graphic_sizes(int *height, int *width, char *file_name);

// Outlay the regular dungeon pov boundaries.
void
PrintBorderDungeon();

// Outlay the most basic game container.
void
PrintBorder();

#endif // GRAPHICS_H
