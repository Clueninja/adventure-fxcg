
#ifndef ENEMIES_H
#define ENEMIES_H



#define MAX_ENEMIES 20
//extern const char* enemies[NUM_LEVELS][8];

struct Enemy{
  int x,y, loaded;
};


#include "player.h"
void draw_enemies(struct Enemy *);

void move_enemies(struct Enemy *, int);

void load_enemies(struct Player *,struct Enemy *);
#endif
