#include "levels.h"

const char * levels[NUM_LEVELS][8]= {{
  "  #####################",
  "  #P                  #",
  "  ##################  #",
  "  #                   #",
  "  #  ##################",
  "  #  #       #   #   D#",
  "  #      #     #   #  #",
  "  #####################"
},
  {
  "  #####################",
  "  #                   #",
  "  #P                  #",
  "  ##################  #",
  "  #                   #",
  "  #        X          #",
  "  #D                  #",
  "  #####################"
},
};



const int level_start[NUM_LEVELS][2] = {
    {2,2},
    {3,3},
};

const int level_end[NUM_LEVELS][2] = {
    {20,7},
    {0,0},
};

int load_level(struct Player *player, struct Enemy *enemies){
    if(player->level>NUM_LEVELS) return 1;
    player->x = level_start[player->level][0];
    player->y = level_start[player->level][1];
    player->attacking = 0;
    player->dir = Up;
    load_enemies (player, enemies);
    return 0;
}
