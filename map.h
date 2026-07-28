#ifndef MAP_H
#define MAP_H

// 0 - empty
// 1 - player
// 2 - visited
// 3 - enemy
// 4 - strong enemy
// 5 - staircase
// 6 - point of interest
// 7 - 

typedef enum MapCode {
    M_EMPTY,
    M_PATH,
    M_BLOCKED,
    M_BLOCKED_SEEN,
    M_PLAYER,
    M_VISITED,
    M_ENEMY, // ++enemy is now a strong_enemy
    M_STRONG_enemy,
    M_STAIRS,
    M_POI,
    // TODO Maybe add lootcodes?
} MapCode;

typedef struct Map {
    int size_y;
    int size_x;
    int arr[20][20];
    // TODO Needs loot
} Map;

void PrintAtMap(int coord[2], char symbol[2]);

// Really can get rid of this after I understand it
void EmptyMap(Map *map);

// Take a map, empty it and fill it to a size roughly based on "multiplier"
void GenerateMap(Map *map, int multiplier);

// Take a map and print it's arr
void PrintMap(Map map);

#endif // MAP_H
