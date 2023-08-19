#include "GameHandler.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

#include <chrono>
#include <string>




void States::initializeStart(){
    // Initialize SDL components
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) ;
    TTF_Init();
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

    
}

void States::ShowWinnerScreen(SDL_Renderer* renderer, TTF_Font* font, int winner) {
    SDL_Color textColor = {0xFF, 0xFF, 0xFF, 0xFF};
    std::string winnerText = "Player " + std::to_string(winner) + " wins!";

    // Render a black background rectangle
    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
    SDL_RenderClear(renderer);

    // Render the winner's text on the black background
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, winnerText.c_str(), textColor);
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

    int textWidth, textHeight;
    SDL_QueryTexture(textTexture, nullptr, nullptr, &textWidth, &textHeight);

    SDL_Rect textRect = {(WINDOW_WIDTH - textWidth) / 2, (WINDOW_HEIGHT - textHeight) / 4, textWidth, textHeight};

    SDL_RenderCopy(renderer, textTexture, nullptr, &textRect);

    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);

    SDL_RenderPresent(renderer);

    // Wait for a moment to allow the player to see the winner screen
    // SDL_Delay(3000);  // Adjust the duration as needed
}

void States::ShowRematchOptionScreen(SDL_Renderer* renderer, TTF_Font* font) {
    SDL_Color textColor = {0xFF, 0xFF, 0xFF, 0xFF};
    std::string rematchText = "Rematch? Press R for rematch or ESC to quit.";

    // Render a black background rectangle
    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
    // SDL_RenderClear(renderer);

    // Render the rematch option text on the black background
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, rematchText.c_str(), textColor);
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

    int textWidth, textHeight;
    SDL_QueryTexture(textTexture, nullptr, nullptr, &textWidth, &textHeight);

    SDL_Rect textRect = {(WINDOW_WIDTH - textWidth) / 2, (WINDOW_HEIGHT - textHeight) / 2, textWidth, textHeight};

    SDL_RenderCopy(renderer, textTexture, nullptr, &textRect);

    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);

    SDL_RenderPresent(renderer);
}

void States::ResetGame(Ball& ball, Paddle& paddleOne, Paddle& paddleTwo, PlayerScore& playerOneScoreText, PlayerScore& playerTwoScoreText) {
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
