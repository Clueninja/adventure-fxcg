

#include "../../../include/fxcg/display.h"
#include "../../../include/fxcg/keyboard.h"
#include "../../../include/fxcg/misc.h"
#include "levels.h"
#include "player.h"

void get_xy_from_dir(struct Player *player, int *x, int *y){
    switch (player->dir){
    case Up:
        *x = player->x;
        *y = player->y-1;
        break;
    case Down:
        *x = player->x;
        *y = player->y+1;
        break;
    case Left:
        *x = player->x-1;
        *y = player->y;
        break;
    case Right:
        *x = player->x+1;
        *y = player->y;
        break;
    }
}

int check_player_killed(struct Player *player, struct Enemy *enemies){
    for (int e=0; e<MAX_ENEMIES && player->running; e++){
        if(!enemies[e].loaded) continue;
        if (player->x == enemies[e].x && player->y == enemies[e].y){
            player->running =0;
        }
    }
    if (player->running) return 0;
    game_over_screen ();
    return 1;
}


void move_player(struct Player* player, int x,int y, struct Enemy* enemies){
    if (player->x +x <1 || player->x +x >21) return;
    if (player->y +y <1 || player->y +y >8) return;

    if (levels[player->level][player->y+y-1][player->x+x+1]=='#')return;
    player->x +=x;
    player->y+=y;

}

int check_enemy_hit(int x,int y, struct Enemy* enemies){
    for (int e=0; e<MAX_ENEMIES; e++){
        if (enemies[e].x == x && enemies[e].y == y){
            // enemy hit by sword
            enemies[e].x = 0;
            enemies[e].y = 0;
        }
    }
    return 0;
}

void attack(struct Player *player, struct Enemy *enemies){
    int x=0,y=0;
    get_xy_from_dir (player, &x, &y);
    switch (player->dir){
    case Up:
        PrintXY(x, y,"  ^", 0x20,TEXT_COLOR_BLACK);
        break;
    case Down:
        PrintXY(x, y,"  v", 0x20,TEXT_COLOR_BLACK);
        break;
    case Left:
        PrintXY(x, y,"  <", 0x20,TEXT_COLOR_BLACK);
        break;
    case Right:
        PrintXY(x, y,"  >", 0x20,TEXT_COLOR_BLACK);
        break;
    }
    check_enemy_hit(x,y, enemies);
}

void draw_player(struct Player * player){
    PrintXY(player->x, player->y,"  @", 0,TEXT_COLOR_RED);
}
