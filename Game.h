#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

#include "Ball.h"
#include "CheckPaddleCollision.h"
#include "CheckWallCollision.h"
#include "GameHandler.h"
#include "Global.h"
#include "Paddle.h"
#include "PlayerScore.h"

class Game {
   private:
    SDL_Window* window ;
    SDL_Renderer* renderer ;

    // Initialize the font
    TTF_Font* Font ;

    // Initialize sound effects
    Mix_Chunk* wallHitSound ;
    Mix_Chunk* paddleHitSound ;

   public:
    Game();

    SDL_Renderer* getRenderer();
    TTF_Font* getFont();
    Mix_Chunk* getWallHitSound();
    Mix_Chunk* getPaddleHitSound() ;
    bool GAME_RUNNING = true;

    void GameStart();
    void Close();
};
#endif