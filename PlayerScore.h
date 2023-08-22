#ifndef PLAYER_SCORE_H
#define PLAYER_SCORE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "Global.h"

class PlayerScore
{
    int score = 0;

public:
    PlayerScore(Vec2 position, SDL_Renderer *renderer, TTF_Font *font);
    ~PlayerScore();
    void SetScore(int score);
    void showWinScore(int score);
    int getScore();

    void Draw();
    void operator++();

    SDL_Renderer *renderer;
    TTF_Font *font;
    SDL_Surface *surface{};
    SDL_Texture *texture{};
    SDL_Rect rect{};
};

#endif