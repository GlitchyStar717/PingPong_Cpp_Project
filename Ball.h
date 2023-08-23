#ifndef BALL_H
#define BALL_H
#include "Global.h"
#include <SDL.h>
#include<chrono>

class Ball
{
    int ball_delay_at_start;
    float duration;
    std::chrono::time_point<std::chrono::system_clock> start, present;


public:
    Ball(Vec2 position, Vec2 velocity);

    void Update(float dt);

    void Draw(SDL_Renderer *renderer);

    void CollideWithPaddle(Contact const &contact);

    void CollideWithWall(Contact const &contact);

    float generate_random_y_speed();


    Vec2 position;
    Vec2 velocity;
    SDL_Rect rect{};
};
#endif

