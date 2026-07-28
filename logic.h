#ifndef LOGIC_H
#define LOGIC_H

// TODO Interact button that does something based on what the entity is


// An entity is everything besides maybe the player and map spaces. It is keys, enemies, levers, maybe even spots on the map
typedef struct Entity {
    int id;
    int type;
    char name[20];
    char description[30];

    void *object;

} Entity;

typedef enum EntityType {
    E_PLAYER,
    E_KEY,
    
    
    
    
} EntityType;





typedef struct Player {

    char name[15];
    int hp;
    int hp_max;
    int difficulty;

    int coord[2];
    char direction; // n s e w
    
    // TODO
    // Armor (in strings and int array)
} Player;

Player CreatePlayer(int difficulty);


typedef struct Key { // Could maybe go on a wall
    int init_coord[2];
    int unlock_coord[2];

    int picked_up; // Bool

} Key;


// Takes a player and moves if possible, returning 1 on a success (or 0 on fail)
/* int MovePlayer(Player *player, Map *map, int keypress); */


#endif // LOGIC_H
