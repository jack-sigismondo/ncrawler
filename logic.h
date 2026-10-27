#ifndef LOGIC_H
#define LOGIC_H

#include "map.h"

// TODO Interact button that does something based on what the entity is


// An entity is everything besides maybe the player and map spaces. It is keys,
// enemies, levers, maybe even spots on the map

typedef enum EntityCode
{
    E_SKULL,
    E_SKULLSHOOTER,
    E_MOUSE,  
    E_SPIDER,
} EntityCode;

typedef struct Entity { // FIXME
    int id;
    int type;
    char name[20];
    char description[30];
    void *object;

} Entity;

typedef enum EntityType { // FIXME
	E_PLAYER,
	E_KEY,
} EntityType;

typedef struct Player
{

	char name[15];
	int hp;
	int hp_max;
	int difficulty;

	int y;
	int x;
	int direction;

	// TODO
	// Armor (in strings and int array)
} Player;

typedef struct key // TODO remove
{
	int init_coord[2];
	int unlock_coord[2];

	int picked_up; // Bool

} Key;

Player
CreatePlayer(int difficulty);

void
UpdateEntitiesFromMap(Map *map, Player *player /* entities */);

int
MovePlayer(Map *map, Player *player, int keypress);

void
PrintEnvironment(Map *map, Player *player);

#endif // LOGIC_H
