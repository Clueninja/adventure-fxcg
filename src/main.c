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

int main(){
    // no heap :(
    struct Enemy enemies[MAX_ENEMIES];

    struct Player player;
    player.running=1;
    player.level=0;

    if (load_level (&player, enemies)) return 0;

    int key;
    while(player.running){
        draw_level(player.level);
        //TODO: Find the correct order for these to happen
        if (player.attacking){
            attack(&player, enemies);
        }
        player.attacking=0;

        move_enemies (enemies, player.level);
        draw_enemies (enemies);
        draw_player(&player);
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
        if (check_player_killed(&player, enemies)) return 0;
        if (check_level_end(&player)){
            player.level+=1;
            if (player.level==NUM_LEVELS){game_won_screen(); return 0;}
            if (load_level (&player, enemies)) return 0;
        }
    }
  return 1;
}


