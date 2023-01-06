

#ifndef LEVELS_H
#define LEVELS_H

#define NUM_LEVELS 3

#include "player.h"
#include "enemies.h"

extern const char* levels[NUM_LEVELS][8];

extern const int level_start[NUM_LEVELS][2];
extern const int level_end[NUM_LEVELS][2];
void game_won_screen();
void game_over_screen();
int load_level(struct Player*, struct Enemy*);
void draw_level(int);

int check_level_end(struct Player *);

#endif

