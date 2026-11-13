#ifndef FIGHT_H
#define FIGHT_H
// I guess this is fine here?
#include <stdio.h>

enum weapons
{
	W_SWORD, W_CONTROLLABLE
};	

struct weapon
{
	int category;
	char *graphic_prefix;
	int damage;
	int max_timeout;
	
	int y_upper_bound;
	int y_lower_bound;
	int x_upper_bound;
	int x_lower_bound;
};

typedef struct Fighter
{
	int y;
	int x;
	
	struct weapon weapon;
	char *graphic;

	// 0 1 2
	// 3 4 5
	int position;

	int timeout;

	int hp;

} Fighter; // FIXME

typedef struct Enemy // FIXME
{
	int name;
	int y;
	int x;

	int direction; // nesw
	char *graphic;
	char *graphic_projectile;
	int alive;
} Enemy;

void
FightStart(int difficulty, int entities[], size_t entities_size);

// Swing your fighter's weapon, kill monsters and enact a swing timeout
void
AttackInDirection(Fighter *fighter, int direction);

// Loop logic for skull enemy
void
UpdateSkull(Enemy *skull, Fighter *fighter);

/* Print possible fighter positions for a visual aid */
void
print_placements(int fighter_position);


#endif // FIGHT_H
