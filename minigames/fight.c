#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>

#include "fight.h"
#include "graphics.h"
#include "logic.h"
// TODO Include player info so you can pass off armor and weapons.

void
AttackInDirection(Fighter *fighter, int direction)
{ // TODO go through and check for enemies
    switch(fighter->weapon)
    {
	case W_SWORD:
	    // If not currently swinging, start a swing timer.
	    if (fighter->timeout == 0) fighter->timeout = 5;
	    // Swing in specified direction.
	    switch(direction)
	    {
		case KEY_UP:
		    PrintGraphic(fighter->y - 8, fighter->x + 2, "fight/sword-up");
		    break;
		case KEY_DOWN:
		    PrintGraphic(fighter->y + 8, fighter->x + 2, "fight/sword-down");
		    break;
		case KEY_LEFT:
		    PrintGraphic(fighter->y + 3, fighter->x + -16, "fight/sword-left");
		    break;
		case KEY_RIGHT:
		    PrintGraphic(fighter->y + 3, fighter->x + 9, "fight/sword-right");
		    break;
		default: // NOTE
		    break;            
	    }
	    break;
	// TODO Add more weapons.
	default:
	    exit(0); // HACK
	    break;
    }
}

void
UpdateSkull(Enemy *skull) // TODO fix the directions
{
    // TODO Slow to move until they're on screen for a bit
    // TODO OR add ! or some exclamation mark
    
    // If facing East
    if (skull->direction == 3)
    {
        // Print an exclamation mark warning every other frame.
        if (skull->x >= 120 && (skull->x % 3 == 0))
            PrintGraphic(skull->y, 110, "fight/exclamation");
	    
        skull->x -= 2;
    }
    // If facing West
    else
    {
        if (skull->x <= 0 && (skull->x % 3 == 0))
            PrintGraphic(skull->y, 5, "fight/exclamation");
	    
        skull->x += 2;
    }
    if (skull->x < 120) // NOTE
        PrintGraphic(skull->y, skull->x, skull->graphic);
}

void
FightStart(int difficulty, int entities[], size_t entities_size)
{   
    halfdelay(1); // NOTE
    
    Fighter fighter = (Fighter)
    {
        .y = 13,
	.x = 26,
	.hp = 100,
	.timeout = 0,
	.position = 0,
	.weapon = 0,
	.graphic = "fight/fighter-idle"
    };

    Enemy enemies[10];
    // For all enemies
    for (int i = 0, spacer = 1; i < entities_size; ++i, ++spacer)
        switch (entities[i])
	{
	    case E_SKULL:
		// NOTE Really good way to initialize structs
		enemies[i] = (Enemy)
		{
		    .name = E_SKULL,
		    .y = 13 + (rand() % 2) * 18,
                    .x = 60, // Start in the middle of the screen
                    .graphic = "fight/skull-closed",
                    .alive = 1
		};
		// Either add to the left or right to space out the enemy
		// Then multiply by an increasing value to account for their appearance queue            
		(rand() % 2 == 1) ? (enemies[i].x -= 120 * spacer) : (enemies[i].x += 120 * spacer);
		// If on the right adjust direction accordingly
		(enemies[i].x > 120) ? (enemies[i].direction = 3) : (enemies[i].direction = 1);
		break;
	    default:
		enemies[i] = (Enemy) {.name = -1};
		break;
        }

    int hp = 100; // FIXME Use player's hp

    int ch = 0;
    int chprev = 0;

    int score = 0;    
    for (;;)
    {
        ch = getch(); // TODO try seperating these put chprev to the switch(ch)

        // Some generic printing
        clear();                
        PrintBorder();
        PrintGraphic(fighter.y, fighter.x, fighter.graphic);
        // Display indicators for where the player can move
        if (fighter.position != 0)
	    PrintGraphic(15, 30, "fight/placement");
        if (fighter.position != 1)
	    PrintGraphic(15, 30*2, "fight/placement");
        if (fighter.position != 2)
	    PrintGraphic(15, 30*3, "fight/placement");
        if (fighter.position != 3)
	    PrintGraphic(15*2+3, 30, "fight/placement");
        if (fighter.position != 4)
	    PrintGraphic(15*2+3, 30*2, "fight/placement");
        if (fighter.position != 5)
	    PrintGraphic(15*2+3, 30*3, "fight/placement");

        // TODO Try monster logic before and after getch
        for (int i = 0; i < entities_size; ++i)
	{
            switch(enemies[i].name)
	    {
		case E_SKULL:
		    UpdateSkull(&enemies[i]);
		    break;
		default:
		    break;
            }
        }
        // switch ch to null TODO???
        if (fighter.timeout > 0)
	{
            ch = chprev; // Keep the direction constant
            AttackInDirection(&fighter, ch);
            fighter.timeout -= 1;
            // Cease further player logic
            continue;
        }
        // Prevent another refresh stealing queued attack input.
        if (chprev != ' ')
            chprev = ch;
        // Fighter moving logic
        switch (ch)
	{
	    case KEY_LEFT:
		if (chprev == ' ')
		{
		    AttackInDirection(&fighter, ch);
		    chprev = ch; // Bypass 'if (chprev != ' ') { chprev = ch; }'
		    break;
		}
		else if (fighter.position != 0 && fighter.position != 3)
		{
		    fighter.position -= 1;
		    fighter.x -= 30;
		}
		break;
	    case KEY_RIGHT:
		if (chprev == ' ')
		{
		    AttackInDirection(&fighter, ch);
		    chprev = ch; // Bypass 'if (chprev != ' ') { chprev = ch; };
		    break;
		}
		else if (fighter.position != 2 && fighter.position != 5)
		{
		    fighter.position += 1;
		    // update x and y
		    fighter.x += 30;
		}
		break;
	    case KEY_DOWN:
		if (chprev == ' ')
		{
		    AttackInDirection(&fighter, ch);
		    chprev = ch; // Bypass 'if (chprev != ' ') { chprev = ch; }'
		    break;
		}
		else if (fighter.position <= 2)
		{
		    fighter.position += 3;
		    fighter.y += 18;
		}
		break;
	    case KEY_UP:
		if (chprev == ' ')
		{
		    AttackInDirection(&fighter, ch);
		    chprev = ch; // Bypass 'if (chprev != ' ') { chprev = ch; }'
		    break;
		}
		else if (fighter.position >= 3)
		{
		    fighter.position -= 3;
		    fighter.y -= 18;
		}
		break;
	    case 'q': // HACK
		clear();
		return;
	    default:
		break;
	}
    }
}
