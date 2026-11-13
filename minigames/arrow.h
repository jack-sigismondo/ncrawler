#ifndef ARROW_H
#define ARROW_H

struct runner
{
    int y;
    int x;
    int hp;
    char *graphic;
};

typedef struct Arrow {
    int y;
    int x;
    int speed;
    char *graphic;
} Arrow;

struct runner
CreateRunner(int hp);

void
ArrowStart(int difficulty);

#endif // ARROW_H
