

#ifndef PLAYER_H
#define PLAYER_H



enum Dir{
    Up,Down,Left,Right
};
struct Player{
    int x,y, attacking, level, running;
    enum Dir dir;
};
#include "enemies.h"

void move_player(struct Player *, int,int, struct Enemy *);

void draw_player(struct Player *);

void attack(struct Player *, struct Enemy *);

#endif

