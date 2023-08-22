#ifndef PADDLE_H
#define PADDLE_H

#include "Global.h"
#include <SDL2/SDL.h>

class Paddle
{
public:
    Paddle(Vec2 position, Vec2 velocity);

    void Update(float dt);

    void Draw(SDL_Renderer *renderer);

    Vec2 position;
    Vec2 velocity;
    SDL_Rect rect{};
};

#endif