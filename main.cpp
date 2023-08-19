#include "Game.h"






int main(int argc, char* args[]) {
    Game game1;  
    game1.GameStart();
    if(!game1.GAME_RUNNING){
        game1.Close();
    }
        return 0;
    }
