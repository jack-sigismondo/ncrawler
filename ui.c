#include <ncurses.h>
#include "ui.h"



void PrintBorder(/* Screen Reso?*/) {

    // TODO
    // Print area name
    // and floor number

    for (int i = 2; i < 120; i += 6) {
	mvaddstr(0, i, "|-/-\\-"); // Top
	mvaddstr(60, i-1, "-/-\\-|"); // Bottom // FIXME Not even really needed

	if (i < 70) {
	    mvaddstr(26, i, "|-/-\\-|");
	}
	
    }

    // Sides
    for (int i = 0; i < 60; ++i) { // HACK
	mvaddstr(i, 0, "|-");
	mvaddstr(i, 119, "|-");
	mvaddstr(i, 75, "-|");
	
	++i;
	mvaddstr(i, 0, "-|");
	mvaddstr(i, 119, "-|");
	mvaddstr(i, 75, "|-");
    }

    return;
}
