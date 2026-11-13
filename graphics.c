#include <ncurses.h>
#include <string.h>

#include "graphics.h"

void
PrintGraphic(int y, int x, char *file_name)
{
    int init_x = x;
    // Sandwich file_name with the folder and .txt
    char file_path[200] = "graphics/";
    strcat(file_path, file_name);
    strcat(file_path, ".txt");
    // Check for typos/errors.
    FILE *file_ptr = fopen(file_path, "r");
    if (file_ptr == NULL)
    {
	printf("Error: Could not find file");
	return;
    }
    // Read the file char by char.
    int ch; // NOTE This is an int to handle EOF.
    while ((ch = fgetc(file_ptr)) != EOF)
    {
	if (ch == '\n')
	{
	    x = init_x;
	    y += 1;
	}
	else
	    mvaddch(y, x++, ch);
    }
    fclose(file_ptr);
}

void
get_graphic_sizes(int *height, int *width, char *file_name)
{
	// Sandwich file_name with the folder and .txt
    char file_path[200] = "graphics/";
    strcat(file_path, file_name);
    strcat(file_path, ".txt");
	
	FILE *fp = fopen(file_path, "r");
	if (fp == NULL)
		return;

	int ch;
	*height = 0; // NOTE
	*width = 0;
	int max_width = 0;

	while ((ch = fgetc(fp)) != EOF)
	{
		if (ch == '\n')
		{
			*height += 1;
			if (*width > max_width)
				max_width = *width;
			*width = 0;
		}
		else
			*width += 1;
	}
	*width = max_width;
}

void
PrintBorderDungeon()
{
    for (int x = 0; x < 120; ++x) {
	// Top bar
	mvaddch(0, x, '|');
	// Middle bar
	mvaddch(28, x, '|');
	// Bottom bar
	mvaddch(50, x, '|');

	// Advance the cursor.
	x += 1;

	// Top bar
	mvaddch(0, x, '-');
	// Middle bar
	mvaddch(28, x, '-');
	// Bottom bar
	mvaddch(50, x, '-');
    }

    for (int y = 1; y < 51; ++y)
    {
	// Left bar
	mvaddch(y, 0, '-');
	mvaddch(y, 1, '|');
	// Middle bar
	mvaddch(y, 75, '|');
	mvaddch(y, 76, '-');
	// Right bar
	mvaddch(y, 119, '|');
	mvaddch(y, 120, '-');

	// Advance the cursor.
	y += 1;

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

void
PrintBorder()
{
    for (int x = 0; x < 120; ++x)
    {
	// Top bar
	mvaddch(0, x, '|');
	// Bottom bar
	mvaddch(50, x, '|');

	// Advance the cursor
	x += 1;

	// Top bar
	mvaddch(0, x, '-');
	// Bottom bar
	mvaddch(50, x, '-');
    }
    for (int y = 1; y < 51; ++y)
    {
	// Left bar
	mvaddch(y, 0, '-');
	mvaddch(y, 1, '|');
	// Right bar
	mvaddch(y, 119, '|');
	mvaddch(y, 120, '-');
	
	// Advance the cursor.
	y += 1;
	
	// Left bar
	mvaddch(y, 0, '|');
	mvaddch(y, 1, '-');
	// Right bar
	mvaddch(y, 119, '-');
	mvaddch(y, 120, '|');
    }
    // -.-
    mvaddch(0, 120, '|');
}
