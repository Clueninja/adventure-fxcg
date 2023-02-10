
#ifndef ENEMIES_H
#define ENEMIES_H



#define MAX_ENEMIES 20
//extern const char* enemies[NUM_LEVELS][8];

struct Enemy{
  int x,y, loaded;
};


#include "player.h"
// Draws Enemies on the screen
void draw_enemies(struct Enemy *);
// Moves the Enemies if possible
void move_enemies(struct Enemy *, int);
// loads the enemies from a level that is stored in the Player
void load_enemies(struct Player *,struct Enemy *);
#endif
