#ifndef GAME_HANDLER_H
#define GAME_HANDLER_H

#include <SDL2/SDL.h>

#include "Ball.h"
#include "Global.h"
#include "Paddle.h"
#include "PlayerScore.h"

class States {
   public:
    void initializeStart();

    void ShowWinnerScreen(SDL_Renderer* renderer, TTF_Font* font, int winner);

    void ShowRematchOptionScreen(SDL_Renderer* renderer, TTF_Font* font);

    void ResetGame(Ball& ball, Paddle& paddleOne, Paddle& paddleTwo, PlayerScore& playerOneScoreText, PlayerScore& playerTwoScoreText);
};
#endif