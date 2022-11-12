#include "../../../include/fxcg/display.h"
#include "../../../include/fxcg/keyboard.h"
#include "../../../include/fxcg/misc.h"
#include <string.h>
#include <stdlib.h>

#include "player.h"
#include "enemies.h"
#include "levels.h"

#define SCREEN_WIDTH 384
#define SCREEN_HEIGHT 192




int check_level_end(struct Player * player){
    if(levels[player->level][player->y-1][player->x+1] == 'D') return 1;
    //if (player->x == level_end[player->level][0] && player->y == level_end[player->level][1]) return 1;
    return 0;
}

unsigned short Bdisp_GetPointWB_VRAM(int x, int y)
{
	return Bdisp_GetPoint_VRAM(x, y+24);
}
void draw_level(int level){
    for (int y=0; y<8; y++){
        char buffer[24];
        strcpy(buffer, levels[level][y]);
        //for (int x = 0; x<23; x++){
        //    if (buffer[x] != '#' && buffer[x]!=' ') buffer[x] = ' ';
        //}
        PrintXY (1, y+1, buffer, 0, TEXT_COLOR_GREEN);
    }
}
int check_player_killed(struct Player *player){
    if (player->running) return 0;

    PrintXY (6, 4, "   WASTED", 0x20, TEXT_COLOR_RED);
    PrintXY (5, 6, "   Press EXE", 0x20, TEXT_COLOR_BLACK);
    PrintXY (5, 7, "   Exit the Game", 0x20, TEXT_COLOR_BLACK);
    int key;
    do{
        GetKey(&key);
    }while(key!=KEY_CTRL_EXE);
    return 1;
}

int check_game_won(struct Player *player){
    if (player->level<NUM_LEVELS) return 0;
    draw_level (player->level-1);
    PrintXY (1, 4, "   Well Done, You Have", 0x20, TEXT_COLOR_RED);
    PrintXY (1, 5, "   Completed the Game", 0x20, TEXT_COLOR_RED);
    PrintXY (5, 6, "   Press EXE", 0x20, TEXT_COLOR_BLACK);
    PrintXY (5, 7, "   Exit the Game", 0x20, TEXT_COLOR_BLACK);
    int key;

    do{
        GetKey(&key);
    }while(key!=KEY_CTRL_EXE);
    return 1;
}

int main(){
    struct Enemy enemies[MAX_ENEMIES];

    struct Player player;
    player.running=1;
    player.level=0;

    if (load_level (&player, enemies)) return 0;

    int key;
    while(player.running){
        draw_level(player.level);
        draw_enemies(enemies);
        draw_player(&player);
        if (player.attacking){
            attack(&player, enemies);
        }
        player.attacking=0;

        GetKey(&key);
        switch(key)
        {
            case KEY_CTRL_UP:
                move_player (&player, 0, -1, enemies);
                player.dir = Up;
                break;
            case KEY_CTRL_LEFT:
                move_player (&player, -1, 0,enemies);
                player.dir = Left;
                break;
            case KEY_CTRL_RIGHT:
                move_player (&player, 1, 0,enemies);
                player.dir = Right;
                break;
            case KEY_CTRL_DOWN:
                move_player (&player, 0, 1,enemies);
                player.dir = Down;
                break;
            case KEY_CHAR_7:
                player.attacking=1;
                break;
            case KEY_CTRL_EXE:
                player.running=0;
                break;
        }
        move_enemies (enemies, player.level);
        if (check_player_killed(&player)) return 0;
        if (check_level_end(&player)){
            player.level+=1;
            if (check_game_won(&player)) return 0;
            if (load_level (&player, enemies)) return 0;
        }


    }
  return 0;
}


