#ifndef BALL_H
#define BALL_H
#include "Global.h"
#include <SDL.h>

class Ball
{
public:
    Ball(Vec2 position, Vec2 velocity);

    void Update(float dt);

    void Draw(SDL_Renderer *renderer);

    void CollideWithPaddle(Contact const &contact);

    void CollideWithWall(Contact const &contact);

    Vec2 position;
    Vec2 velocity;
    SDL_Rect rect{};
};
#endif