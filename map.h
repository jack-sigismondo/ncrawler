#ifndef MAP_H
#define MAP_H


typedef struct Map {
    int arr[20][20];

    char name[20];
    
} Map;


typedef enum MapCode {
    M_EMPTY, //0
    M_PATH,
    M_PATH_SEEN,
    M_BLOCKED,
    M_BLOCKED_SEEN,
    M_PLAYER, // 5
    M_VISITED,
    M_ENEMY, // ++enemy is now a strong_enemy
    M_STRONG_ENEMY,
    M_STAIRS,
    M_POI, // A
    M_TREASURE,
    M_KEY,
    M_LEVER,
    M_LOCKED_DOOR, //E // And unlock it
    // TODO 
} MapCode;



// Really can get rid of this after I understand it
void EmptyMap(Map *map);

// Take a map, empty it and fill it to a size roughly based on "multiplier"
void GenerateMap(Map *map, int multiplier);

// Take a map and print it's arr
void PrintMap(Map *map);

// Take a char and print it on a map coord
void PrintAtMap(int y, int x, char c);

// Take a direction ('l'/'r') and return a new transposed map // TODO
void TransposeMap(Map *map, char direction);

#endif // MAP_H
