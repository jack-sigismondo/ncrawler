#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fight.h"
#include "graphics.h"
#include "logic.h"
// TODO Include player info so you can pass off armor and weapons
// TODO if you cut the spider's string make him drop
// TODO rename controllable thing to spell, idk why I named it that initially stupid

// TODO move this somewhere
int placements = 1;

void
FightStart(int difficulty, int entities[], size_t entities_size)
{
	halfdelay(1); // NOTE

	// TODO turn into a function with arg being the player entity
	Fighter fighter = (Fighter)
		{
			.y = 13,
			.x = 26,
			.hp = 100,
			.timeout = 0,
			.position = 0,
			.graphic = "fight/fighter-idle",
			.weapon = (struct weapon) /* FIXME remove hardcoding */
			{
				.category = W_CONTROLLABLE,
				.graphic_prefix = "fight/spell",
				.damage = 100,
				.max_timeout = 25,
			},
		};

	Enemy enemies[10];
	// For all enemies
	for (int i = 0, spacer = 1; i < entities_size; ++i, ++spacer)
	{
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
	}

	int hp = 100; // FIXME Use player's hp
	int ch = -1;
	int chprev = -1;
	int condir = -1;			/* Controllable direction */

	for (;;)
	{
		erase();
		PrintBorder();
		PrintGraphic(fighter.y, fighter.x, fighter.graphic);

		/* TODO delete */
		mvaddch(fighter.weapon.y_upper_bound, fighter.weapon.x_upper_bound, '$');
		mvaddch(fighter.weapon.y_lower_bound, fighter.weapon.x_lower_bound, '$');
		mvprintw(50, 50, "Fighter timeout is %d", fighter.timeout);

		if (placements)
			print_placements(fighter.position);
		
		for (int i = 0; i < entities_size; ++i)
		{
			switch(enemies[i].name)
			{
			case E_SKULL:
				UpdateSkull(&enemies[i], &fighter);
				break;
			default:
				break;
			}
		}

		if (fighter.timeout > 0)
		{
			/* NOTE originally right before fighter.timeout -= 1
			 * if a problem try putting it back */
			AttackInDirection(&fighter, ch);
			
			if (fighter.weapon.category == W_CONTROLLABLE)
			{
				PrintGraphic(fighter.weapon.y_lower_bound, fighter.weapon.x_lower_bound, "fight/spell");
				if ((ch = getch()) == -1)
					ch = condir;
				else
					condir = ch;
			}
			else
			{
				getch();
			}
			
			
			fighter.timeout -= 1;
			chprev = ch;
			continue;
		}

		/* Hold the ' ' input */
		if (chprev != ' ')
			chprev = ch;
		
		ch = getch();
		/* for the spell direction */
		if (chprev == ' ' && ch != -1)
			condir = ch;

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

void
AttackInDirection(Fighter *fighter, int direction)
{ // TODO go through and check for enemies
	/* TODO controllable projectile attack */

	int f_height, f_width;
	get_graphic_sizes(&f_height, &f_width, "fight/fighter-idle");
	
	switch(fighter->weapon.category)
	{
	case W_SWORD: 				/* TODO make into broad melee category */

		/* before the swing begins */
		if (fighter->timeout == 0)
			fighter->timeout = fighter->weapon.max_timeout;

		/* when the swing ends */
		if (fighter->timeout == 1)
		{
			fighter->weapon.y_lower_bound = -999;
			fighter->weapon.y_upper_bound = -999;
			fighter->weapon.x_lower_bound = -999;
			fighter->weapon.x_upper_bound = -999;
		}
		
		/*
		 * weapon height, width
		 * fighter height, width
		 * fighter values are assigned immediately
		 * weapon values assigned per case basis
		 * used to calculate where to print the weapon graphics
		 */
		int w_height, w_width;	/* FIXME change to s_width maybe */
		char graphic_path[256];

		switch(direction)
		{
		case KEY_UP:
			
			snprintf(graphic_path, sizeof(graphic_path), "%s%s", fighter->weapon.graphic_prefix, "-up");
			get_graphic_sizes(&w_height, &w_width, graphic_path);
			
			fighter->weapon.y_upper_bound = fighter->y;
			fighter->weapon.y_lower_bound = fighter->y - w_height;
			fighter->weapon.x_upper_bound = fighter->x + (f_width / 2) + w_width;
			fighter->weapon.x_lower_bound = fighter->x + (f_width / 2);

			PrintGraphic(fighter->y - w_height, fighter->x + (f_width / 2), graphic_path);
			break;
			
		case KEY_DOWN:

			snprintf(graphic_path, sizeof(graphic_path), "%s%s", fighter->weapon.graphic_prefix, "-down");
			get_graphic_sizes(&w_height, &w_width, graphic_path);
			
			fighter->weapon.y_upper_bound = fighter->y + f_height + w_height;
			fighter->weapon.y_lower_bound = fighter->y + f_height;
			fighter->weapon.x_upper_bound = fighter->x + (f_width / 2) + w_width;
			fighter->weapon.x_lower_bound = fighter->x + (f_width / 2);

			PrintGraphic(fighter->y + f_height, fighter->x + (f_width / 2), graphic_path);
			break;
			
		case KEY_LEFT:

			snprintf(graphic_path, sizeof(graphic_path), "%s%s", fighter->weapon.graphic_prefix, "-left");
			get_graphic_sizes(&w_height, &w_width, graphic_path);
			
			fighter->weapon.y_upper_bound = fighter->y + (f_height / 2) + w_height;
			fighter->weapon.y_lower_bound = fighter->y + (f_height / 2);
			fighter->weapon.x_upper_bound = fighter->x;
			fighter->weapon.x_lower_bound = fighter->x - w_width;

			PrintGraphic(fighter->y + (f_height / 2), fighter->x - w_width, graphic_path);
			break;
			
		case KEY_RIGHT:

			snprintf(graphic_path, sizeof(graphic_path), "%s%s", fighter->weapon.graphic_prefix, "-right");
			get_graphic_sizes(&w_height, &w_width, graphic_path);
			
			fighter->weapon.y_upper_bound = fighter->y + (f_height / 2) + w_height;
			fighter->weapon.y_lower_bound = fighter->y + (f_height / 2);
			fighter->weapon.x_upper_bound = fighter->x + f_width + w_width;
			fighter->weapon.x_lower_bound = fighter->x + f_width;

			PrintGraphic(fighter->y + (f_height / 2), fighter->x + f_width, graphic_path);
			break;
		}
		break;
		
	case W_CONTROLLABLE:
		/*
		 * a little spell you can move around after casting
		 * continues in whatever current direction you're pressing
		 * ends when you hit an enemy or reach the screen boundary
		 * printing is done in the main loop function
		 */

		/* TODO add printing here */

		/* When the spell ends */
		if (fighter->timeout == 1)
		{
			fighter->weapon.y_lower_bound = -999;
			fighter->weapon.y_upper_bound = -999;
			fighter->weapon.x_lower_bound = -999;
			fighter->weapon.x_upper_bound = -999;
		}
		
		int s_height, s_width;
		get_graphic_sizes(&s_height, &s_width, "fight/spell");
		
		switch(direction)
		{
		case KEY_UP:
			if (fighter->timeout == 0)
			{
				fighter->timeout = fighter->weapon.max_timeout;
				fighter->weapon.y_lower_bound = fighter->y - s_height;
				fighter->weapon.y_upper_bound = fighter->y;
				fighter->weapon.x_lower_bound = fighter->x;
				fighter->weapon.x_upper_bound = fighter->x + s_width;
			}
			else
			{
				fighter->weapon.y_lower_bound -= 2;
				fighter->weapon.y_upper_bound -= 2;
			}
			break;
			
		case KEY_DOWN:
			if (fighter->timeout == 0)
			{
				fighter->timeout = fighter->weapon.max_timeout;
				fighter->weapon.y_lower_bound = fighter->y + f_height;
				fighter->weapon.y_upper_bound = fighter->y + f_height + s_height;
				fighter->weapon.x_lower_bound = fighter->x;
				fighter->weapon.x_upper_bound = fighter->x + s_width;
			}
			else
			{
				fighter->weapon.y_lower_bound += 2;
				fighter->weapon.y_upper_bound += 2;
			}
			break;

		case KEY_LEFT:
			if (fighter->timeout == 0)
			{
				fighter->timeout = fighter->weapon.max_timeout;
				fighter->weapon.y_lower_bound = fighter->y;
				fighter->weapon.y_upper_bound = fighter->y + s_height;
				fighter->weapon.x_lower_bound = fighter->x - s_width;
				fighter->weapon.x_upper_bound = fighter->x;
			}
			else
			{
				fighter->weapon.x_lower_bound -= 4;
				fighter->weapon.x_upper_bound -= 4;
			}
			break;

		case KEY_RIGHT:
			if (fighter->timeout == 0)
			{
				fighter->timeout = fighter->weapon.max_timeout;
				fighter->weapon.y_lower_bound = fighter->y;
				fighter->weapon.y_upper_bound = fighter->y + s_height;
				fighter->weapon.x_lower_bound = fighter->x + f_width;
				fighter->weapon.x_upper_bound = fighter->x + f_width + s_width;
			}
			else
			{
				fighter->weapon.x_lower_bound += 4;
				fighter->weapon.x_upper_bound += 4;
			}
			break;
			
		}
		break;
	}
}

void
UpdateSkull(Enemy *skull, Fighter *fighter) // TODO fix the directions
{
	if (!skull->alive)
		return;

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

	/* Check if your attack connects to kill the enemy */
	int s_height, s_width;
	get_graphic_sizes(&s_height, &s_width, skull->graphic);
	
	for (int y = fighter->weapon.y_lower_bound; y < fighter->weapon.y_upper_bound; ++y)
	{
		for (int x = fighter->weapon.x_lower_bound; x < fighter->weapon.x_upper_bound; ++x)
		{
			if (x >= skull->x && x <= skull->x + s_width &&
				y >= skull->y && y <= skull->y + s_height)
			{
				skull->alive = 0;
				/* FIXME add player bonus */
				/* FIXME add tracker to see if any more enemies are even alive */
			}
		}
	}
}

void
print_placements(int fighter_position)
{
	if (fighter_position != 0)
		PrintGraphic(15, 30, "fight/placement");
	if (fighter_position != 1)
		PrintGraphic(15, 30*2, "fight/placement");
	if (fighter_position != 2)
		PrintGraphic(15, 30*3, "fight/placement");
	if (fighter_position != 3)
		PrintGraphic(15*2+3, 30, "fight/placement");
	if (fighter_position != 4)
		PrintGraphic(15*2+3, 30*2, "fight/placement");
	if (fighter_position != 5)
		PrintGraphic(15*2+3, 30*3, "fight/placement");
}
