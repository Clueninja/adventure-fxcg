#include "levels.h"
#include "../../../include/fxcg/display.h"
#include "../../../include/fxcg/keyboard.h"
#include "../../../include/fxcg/misc.h"

// stores starting positions of the enemies, walls, entrance and exits
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
  "  #P                  #",
  "  ################### #",
  "  # X           X     #",
  "  # ######## ##########",
  "  #  X  #    #X #     #",
  "  #D  X # X   #   #  D#",
  "  #####################"
},
    {
  "  #####################",
  "  #P          X       #",
  "  ##### ############# #",
  "  # X    X#     X     #",
  "  # ######## ##########",
  "  #  X  #    #X #     #",
  "  #D  X # X   #   #  D#",
  "  #####################"
},
};


// idk if this is still used
const int level_start[NUM_LEVELS][2] = {
    {2,2},
    {2,2},
    {2,2}
};

// Draw the game over screen and close the game when EXE is pressed
void game_over_screen(){
    PrintXY (6, 4, "   WASTED", 0x20, TEXT_COLOR_RED);
    PrintXY (5, 6, "   Press EXE", 0x20, TEXT_COLOR_BLACK);
    PrintXY (5, 7, "   Exit the Game", 0x20, TEXT_COLOR_BLACK);
    int key;
    do{
        GetKey(&key);
    }while(key!=KEY_CTRL_EXE);
}
// Draw the game won screen and closes the game
void game_won_screen(){
    PrintXY (1, 3, "   Well Done, You Have", 0x20, TEXT_COLOR_RED);
    PrintXY (1, 4, "   Completed the Game", 0x20, TEXT_COLOR_RED);
    PrintXY (5, 5, "   Press EXE", 0x20, TEXT_COLOR_BLACK);
    PrintXY (5, 6, "   Exit the Game", 0x20, TEXT_COLOR_BLACK);
    int key;

    do{
        GetKey(&key);
    }while(key!=KEY_CTRL_EXE);
}
// draws the current level on the screen, it could be faster but then it would be all the same colour
void draw_level(int level){
    const char *blank = "                       ";
    char chr[4];
    chr[0] = ' ';
    chr[1] = ' ';
    chr[3] = '\0';
    for (int y=0; y<8; y++){
        PrintXY (1, y+1, blank, 0, TEXT_COLOR_BLACK);
        for (int x = 2; x<23; x++){
            chr[2] = levels[level][y][x];
            switch (chr[2]){
            case '#':
                PrintXY (x-1, y+1, chr, 0, TEXT_COLOR_GREEN);
                break;
            case 'D':
                PrintXY (x-1, y+1, chr, 0, TEXT_COLOR_PURPLE);
                break;
            }
        }
    }
}
// Checks if the player has made it to the exit
int check_level_end(struct Player * player){
    if(levels[player->level][player->y-1][player->x+1] == 'D') return 1;
    return 0;
}
// loads the level, guards if the player level is greater than the number of levels
int load_level(struct Player *player, struct Enemy *enemies){
    if(player->level>NUM_LEVELS) return 1;
    player->x = level_start[player->level][0];
    player->y = level_start[player->level][1];
    player->attacking = 0;
    player->dir = Up;
    load_enemies (player, enemies);
    return 0;
}
