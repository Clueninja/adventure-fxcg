
#include "enemies.h"

#include "../../../include/fxcg/display.h"
#include "../../../include/stdlib.h"
#include "levels.h"

void draw_enemies(struct Enemy * enemies){
    for (int e=0; e<MAX_ENEMIES; e++){
        if(!enemies[e].loaded) continue;
        PrintXY (enemies[e].x,enemies[e].y, "  X", 0, TEXT_COLOR_RED);
    }
}

int can_move(int new_x, int new_y, int level){
    if (new_x<1 || new_y<1) return 0;
    if (levels[level][new_y-1][new_x+1] == '#') return 0;
    // currently no way to check if an enemy is already at the position
    return 1;
}
// level is passed in instead of Player * because inconsistancy is great
void move_enemies(struct Enemy * enemies, int level){

    for (int e=0; e<MAX_ENEMIES; e++)
    {
        if (!enemies[e].loaded) continue;
        int new_x = 0;
        int new_y = 0;
        int r = sys_rand();
        switch (r%4){
            case 0:
                new_x = enemies[e].x +1;
                new_y = enemies[e].y;

                break;
            case 1:
                new_x = enemies[e].x -1;
                new_y = enemies[e].y;
                break;
            case 2:
                new_x = enemies[e].x;
                new_y = enemies[e].y+1;
                break;
            case 3:
                new_x = enemies[e].x;
                new_y = enemies[e].y-1;
                break;
        }
        if (can_move (new_x, new_y, level)){
            enemies[e].x = new_x;
            enemies[e].y = new_y;
        }
    }
}
// Player only needs to be passed in for the level number
void load_enemies(struct Player *player , struct Enemy * enemies){
    for (int e=0; e<MAX_ENEMIES; e++){
        enemies[e].loaded=0;
    }
    int e=0;
    for (int x=0; x<23; x++){
      for (int y=0; y<8; y++){
        if (levels[player->level][y][x] == 'X'){
            enemies[e].x = x+1;
            enemies[e].y = y+1;
            enemies[e].loaded = 1;
            e++;
        }
      }
    }
}
