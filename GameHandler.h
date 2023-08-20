#ifndef GAME_HANDLER_H
#define GAME_HANDLER_H

#include <SDL2/SDL.h>
#include <string>

#include "Ball.h"
#include "Global.h"
#include "Paddle.h"
#include "PlayerScore.h"

class States
{
public:
    void initializeStart();

    void runStartScreen(SDL_Renderer *renderer, TTF_Font *font, int w, int h, int* winning_points );

    void ShowWinnerScreen(SDL_Renderer *renderer, TTF_Font *font, int winner);

    void renderText(SDL_Renderer *renderer, TTF_Font *font, std::string text, SDL_Color color, int offset);

    void ResetGame(Ball &ball, Paddle &paddleOne, Paddle &paddleTwo, PlayerScore &playerOneScoreText, PlayerScore &playerTwoScoreText);
};
#endif