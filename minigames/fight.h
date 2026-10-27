#ifndef FIGHT_H
#define FIGHT_H
// I guess this is fine here?
#include <stdio.h>

// TODO if you cut the spider's string make him drop

enum weapons { W_SWORD, W_KATANA, W_BOW, W_ };

typedef struct Fighter
{

    int y;
    int x;

    int weapon;
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

// Swing your fighter's weapon, kill monsters and enact a swing timeout
void
AttackInDirection(Fighter *fighter, int direction);

// Loop logic for skull enemy
void
UpdateSkull(Enemy *skull);

// Main game logic
void
FightStart(int difficulty, int entities[], size_t entities_size);

#endif // FIGHT_H
