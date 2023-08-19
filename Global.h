#ifndef GLOBAL_H
#define GLOBAL_H

// #include <SDL2/SDL.h>
// #include <SDL2/SDL_mixer.h>
// #include <SDL2/SDL_ttf.h>

// #include <chrono>
// #include <string>

const int WINDOW_WIDTH = 1280;
const int WINDOW_HEIGHT = 720;
const float PADDLE_SPEED = 1.0f;
const int PADDLE_WIDTH = 10;
const int PADDLE_HEIGHT = 100;
const float BALL_SPEED = 1.0f;
const int BALL_WIDTH = 15;
const int BALL_HEIGHT = 15;


enum Buttons {
    PaddleOneUp = 0,
    PaddleOneDown,
    PaddleTwoUp,
    PaddleTwoDown,
};

enum class CollisionType {
    None,
    Top,
    Middle,
    Bottom,
    Left,
    Right
};

struct Contact {
    CollisionType type;
    float penetration;
};


class Vec2 {
   public:
    Vec2()
        : x(0.0f), y(0.0f) {}

    Vec2(float x, float y)
        : x(x), y(y) {}

    Vec2 operator+(Vec2 const& rhs) {
        return Vec2(x + rhs.x, y + rhs.y);
    }

    Vec2& operator+=(Vec2 const& rhs) {
        x += rhs.x;
        y += rhs.y;

        return *this;
    }

    Vec2 operator*(float rhs) {
        return Vec2(x * rhs, y * rhs);
    }

    float x, y;
};


#endif    