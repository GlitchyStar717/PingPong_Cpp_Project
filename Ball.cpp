#include "Ball.h"
#include "SDL.h"
#include <random>
#include<iostream>


Ball::Ball(Vec2 position, Vec2 velocity)
    : position(position), velocity(velocity)
{
    start = std::chrono::system_clock::now();
    rect.x = static_cast<int>(position.x);
    rect.y = static_cast<int>(position.y);
    rect.w = BALL_WIDTH;
    rect.h = BALL_HEIGHT;
}

void Ball::Update(float dt)
{
     
    present = std::chrono::system_clock::now();
 
    std::chrono::duration<double> elapsed_seconds = present - start;

    duration = elapsed_seconds.count();
    

    if(duration < 1.0f){
    position += velocity * dt * ((duration+1)/2.5);
    }
    else{
    position += velocity * dt ;
    }

}

void Ball::Draw(SDL_Renderer *renderer)
{
    rect.x = static_cast<int>(position.x);
    rect.y = static_cast<int>(position.y);

    SDL_RenderFillRect(renderer, &rect);
}

void Ball::CollideWithPaddle(Contact const &contact)
{
    position.x += contact.penetration;
    velocity.x = -velocity.x;

    if (contact.type == CollisionType::Top)
    {
        velocity.y = -0.75f * BALL_SPEED;
    }
    else if (contact.type == CollisionType::Bottom)
    {
        velocity.y = 0.75f * BALL_SPEED;
    }
}

void Ball::CollideWithWall(Contact const &contact)
{
    if ((contact.type == CollisionType::Top) || (contact.type == CollisionType::Bottom))
    {
        position.y += contact.penetration;
        velocity.y = -velocity.y;
    }
    else if (contact.type == CollisionType::Left)
    {
        position.x = WINDOW_WIDTH / 2.0f;
        position.y = WINDOW_HEIGHT / 2.0f;
        velocity.x = BALL_SPEED;
        velocity.y = generate_random_y_speed();
        start = std::chrono::system_clock::now();

    }
    else if (contact.type == CollisionType::Right)
    {
        position.x = WINDOW_WIDTH / 2.0f;
        position.y = WINDOW_HEIGHT / 2.0f;
        velocity.x = -BALL_SPEED;
        velocity.y = generate_random_y_speed();
        start = std::chrono::system_clock::now();

    }
}

float Ball::generate_random_y_speed(){
    std::random_device rd;
    std::mt19937 gen(rd());
    
    // Define a distribution for floating-point numbers between -0.6 and 0.6
    std::uniform_real_distribution<float> dist(-0.6f, 0.6f);
    
    // Return a random float between -0.6 and 0.6
    return dist(gen);
}
