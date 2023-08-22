#include "GameHandler.h"

#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

#include <chrono>
#include <string>

void States::initializeStart()
{
    // Initialize SDL components
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    }
    if (TTF_Init() == -1)
    {
        printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
    }
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
    }
}

void States::runStartScreen(SDL_Renderer *renderer, TTF_Font *font, TTF_Font *fontTitle, int w, int h, int *winning_points)
{
    bool quit = false;
    SDL_Event e;
    *winning_points = 5; // By default the winning point is 5;

    {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    renderText(renderer, fontTitle, "PingPong", {0, 255, 0}, -800);
    renderText(renderer, font, "Choose the Points to Win ?", {255, 255, 255}, -600);
    renderText(renderer, font, "1) 3", {255, 255, 255}, -450);
    renderText(renderer, font, "2) 5", {255, 255, 255}, -300);
    renderText(renderer, font, "3) 7", {255, 255, 255}, -150);
    renderText(renderer, font, "4) 10", {255, 255, 255}, 0);
    renderText(renderer, font, "5) 15", {255, 255, 255}, 150);
    renderText(renderer, font, "6) 20", {255, 255, 255}, 300);

    renderText(renderer, font, "_____________________________________________",  {255, 255, 255}, 400, 0, (WINDOW_HEIGHT/3));
    renderText(renderer, font, "|                                CONTROLS                        |", {255, 255, 255}, 450, 0, (WINDOW_HEIGHT/3));
    renderText(renderer, font, "|                          Player 1                  Player 2|", {255, 255, 255}, 550, 0, (WINDOW_HEIGHT/3));
    renderText(renderer, font, "|Paddle Up:           W                    UpArrowKey|", {255, 255, 255}, 650, 0, (WINDOW_HEIGHT/3));
    renderText(renderer, font, "|Paddle Down:       S                DownArrowKey|", {255, 255, 255}, 750, 0, (WINDOW_HEIGHT/3));
    renderText(renderer, font, "_____________________________________________", {255, 255, 255}, 780, 0, (WINDOW_HEIGHT/3));

    SDL_RenderPresent(renderer);
}

    while (!quit)
    {
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT || e.key.keysym.sym == SDLK_ESCAPE)
            {
                quit = true; // Exit with default settings
            }
            else if (e.key.keysym.sym == SDLK_1)
            {
                *winning_points = 3;
                quit = true; // Exit start screen on any of these key presses
            }
            else if (e.key.keysym.sym == SDLK_2)
            {
                *winning_points = 5;
                quit = true; // Exit start screen on any of these key presses
            }
            else if (e.key.keysym.sym == SDLK_3)
            {
                *winning_points = 7;
                quit = true; // Exit start screen on any of these key presses
            }
            else if (e.key.keysym.sym == SDLK_4)
            {
                *winning_points = 10;
                quit = true; // Exit start screen on any of these key presses
            }
            else if (e.key.keysym.sym == SDLK_5)
            {
                *winning_points = 15;
                quit = true; // Exit start screen on any of these key presses
            }
            else if (e.key.keysym.sym == SDLK_6)
            {
                *winning_points = 20;
                quit = true; // Exit start screen on any of these key presses
            }
        }
    }
}

void States::ShowWinnerScreen(SDL_Renderer *renderer, TTF_Font *font, int winner)
{
    SDL_Color textColor = {0x00, 0xFF, 0x00, 0xFF};
    std::string winnerText = "Player " + std::to_string(winner) + " wins!";

    // Render a black background rectangle
    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
    SDL_RenderClear(renderer);

    // Render the winner's text on the black background
    SDL_Surface *textSurface = TTF_RenderText_Solid(font, winnerText.c_str(), textColor);
    SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

    int textWidth, textHeight;
    SDL_QueryTexture(textTexture, nullptr, nullptr, &textWidth, &textHeight);

    SDL_Rect textRect = {(WINDOW_WIDTH - textWidth) / 2, (WINDOW_HEIGHT - textHeight) / 4, textWidth, textHeight};

    SDL_RenderCopy(renderer, textTexture, nullptr, &textRect);

    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);

    SDL_RenderPresent(renderer);
}

void States::renderText(SDL_Renderer *renderer, TTF_Font *font, std::string text, SDL_Color color, int y_offset, int x_offset, int x_align, int y_align)
{
    // Render a black background rectangle
    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
    // SDL_RenderClear(renderer);

    SDL_Surface *textSurface = TTF_RenderText_Solid(font, text.c_str(), color);
    SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

    int textWidth, textHeight;
    SDL_QueryTexture(textTexture, nullptr, nullptr, &textWidth, &textHeight);

    SDL_Rect textRect = {x_align + ((x_offset*(WINDOW_WIDTH - textWidth)) / 2), y_align + ((WINDOW_HEIGHT - textHeight + y_offset) / 2), textWidth, textHeight};

    SDL_RenderCopy(renderer, textTexture, nullptr, &textRect);

    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);

    SDL_RenderPresent(renderer);
}

void States::ResetGame(Ball &ball, Paddle &paddleOne, Paddle &paddleTwo, PlayerScore &playerOneScoreText, PlayerScore &playerTwoScoreText)
{
    // Reset ball position and velocity
    ball.position = Vec2(WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f);
    ball.velocity = Vec2(BALL_SPEED, 0.0f);

    // Reset paddle positions and velocities
    paddleOne.position = Vec2(50.0f, WINDOW_HEIGHT / 2.0f);
    paddleOne.velocity = Vec2(0.0f, 0.0f);

    paddleTwo.position = Vec2(WINDOW_WIDTH - 50.0f, WINDOW_HEIGHT / 2.0f);
    paddleTwo.velocity = Vec2(0.0f, 0.0f);

    // Reset scores
    playerOneScoreText.SetScore(0);
    playerTwoScoreText.SetScore(0);
}
