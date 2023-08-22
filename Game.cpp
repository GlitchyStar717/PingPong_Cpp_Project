#include "Game.h"

#include <chrono>
#include <string>

#include "GameHandler.h"

Game::Game() {
    this->window = NULL;
    this->renderer = NULL;

    States state1;
    state1.initializeStart();

    window = SDL_CreateWindow("Pong", 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, 0);

    // Initialize the font
    Font = TTF_OpenFont("Retro_Gaming.ttf", 33);
    FontTitle = TTF_OpenFont("Retro_Gaming.ttf", 80);

    // Initialize sound effects
    wallHitSound = Mix_LoadWAV("WallHit.wav");
    paddleHitSound = Mix_LoadWAV("PaddleHit.wav");
    PointSound = Mix_LoadWAV("Point.wav");
}

SDL_Renderer *Game::getRenderer() {
    return this->renderer;
}
TTF_Font *Game::getFont() {
    return this->Font;
}

TTF_Font *Game::getFontTitle() {
    return this->FontTitle;
}

Mix_Chunk *Game::getWallHitSound() {
    return this->wallHitSound;
}
Mix_Chunk *Game::getPaddleHitSound() {
    return this->paddleHitSound;
}
Mix_Chunk *Game::getPointSound() {
    return this->PointSound;
}

void Game::GameStart() {
    States state1;
    state1.initializeStart();
    int restart = 1;
    int winningPoints;
    // Game logic
    while (restart == 1) {
        state1.runStartScreen(getRenderer(), getFont(), getFontTitle(), WINDOW_WIDTH, WINDOW_HEIGHT, &winningPoints);
        restart = 0;
        // Create the player score text fields
        PlayerScore playerOneScoreText(Vec2(WINDOW_WIDTH / 4, 20), getRenderer(), getFont());

        PlayerScore playerTwoScoreText(Vec2(3 * WINDOW_WIDTH / 4, 20), getRenderer(), getFont());

        // Create the ball
        Ball ball(
            Vec2(WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f),
            Vec2(BALL_SPEED, 0.0f));

        // Create the paddles
        Paddle paddleOne(
            Vec2(50.0f, WINDOW_HEIGHT / 2.0f),
            Vec2(0.0f, 0.0f));

        Paddle paddleTwo(
            Vec2(WINDOW_WIDTH - 50.0f, WINDOW_HEIGHT / 2.0f),
            Vec2(0.0f, 0.0f));

        // int playerOneScore = 0;
        // int playerTwoScore = 0;
        int nextMatch = 0;  // 0 means no action, -1 means exit, 1 means restart

        bool running = true;
        bool buttons[4] = {};
        bool GAME_FINISHED = false;

        float dt = 0.0f;  // For calculating frameTime for smooth and platform/performance independent speed
        int winner = 0;   // 0 means no winner yet

        while (running) {
            if (playerOneScoreText.getScore() > winningPoints) {
                // running = false;
                winner = 1;
                GAME_FINISHED = true;
            }
            if (playerTwoScoreText.getScore() > winningPoints) {
                // running = false;
                winner = 2;
                GAME_FINISHED = true;
            }
            auto startTime = std::chrono::high_resolution_clock::now();

            SDL_Event event;
            while (SDL_PollEvent(&event)) {
                if (event.type == SDL_QUIT) {
                    running = false;
                } else if (event.type == SDL_KEYDOWN) {
                    if (event.key.keysym.sym == SDLK_ESCAPE) {
                        running = false;
                    } else if (event.key.keysym.sym == SDLK_w) {
                        buttons[Buttons::PaddleOneUp] = true;
                    } else if (event.key.keysym.sym == SDLK_s) {
                        buttons[Buttons::PaddleOneDown] = true;
                    } else if (event.key.keysym.sym == SDLK_UP) {
                        buttons[Buttons::PaddleTwoUp] = true;
                    } else if (event.key.keysym.sym == SDLK_DOWN) {
                        buttons[Buttons::PaddleTwoDown] = true;
                    }
                } else if (event.type == SDL_KEYUP) {
                    if (event.key.keysym.sym == SDLK_w) {
                        buttons[Buttons::PaddleOneUp] = false;
                    } else if (event.key.keysym.sym == SDLK_s) {
                        buttons[Buttons::PaddleOneDown] = false;
                    } else if (event.key.keysym.sym == SDLK_UP) {
                        buttons[Buttons::PaddleTwoUp] = false;
                    } else if (event.key.keysym.sym == SDLK_DOWN) {
                        buttons[Buttons::PaddleTwoDown] = false;
                    }
                }
            }

            if (buttons[Buttons::PaddleOneUp]) {
                paddleOne.velocity.y = -PADDLE_SPEED;
            } else if (buttons[Buttons::PaddleOneDown]) {
                paddleOne.velocity.y = PADDLE_SPEED;
            } else {
                paddleOne.velocity.y = 0.0f;
            }

            if (buttons[Buttons::PaddleTwoUp]) {
                paddleTwo.velocity.y = -PADDLE_SPEED;
            } else if (buttons[Buttons::PaddleTwoDown]) {
                paddleTwo.velocity.y = PADDLE_SPEED;
            } else {
                paddleTwo.velocity.y = 0.0f;
            }

            // Update the paddle positions
            paddleOne.Update(dt);
            paddleTwo.Update(dt);

            // Update the ball position
            ball.Update(dt);

            // Check collisions
            if (Contact contact = CheckPaddleCollision(ball, paddleOne);
                contact.type != CollisionType::None) {
                ball.CollideWithPaddle(contact);

                Mix_PlayChannel(-1, getPaddleHitSound(), 0);
            } else if (contact = CheckPaddleCollision(ball, paddleTwo);
                       contact.type != CollisionType::None) {
                ball.CollideWithPaddle(contact);

                Mix_PlayChannel(-1, getPaddleHitSound(), 0);
            } else if (contact = CheckWallCollision(ball);
                       contact.type != CollisionType::None) {
                ball.CollideWithWall(contact);

                if (contact.type == CollisionType::Left) {
                    Mix_PlayChannel(-1, getPointSound(), 0);
                    ++playerTwoScoreText;

                    playerTwoScoreText.SetScore(playerTwoScoreText.getScore());
                } else if (contact.type == CollisionType::Right) {
                    Mix_PlayChannel(-1, getPointSound(), 0);
                    ++playerOneScoreText;

                    playerOneScoreText.SetScore(playerOneScoreText.getScore());
                } else {
                    Mix_PlayChannel(-1, getWallHitSound(), 0);
                }
            }

            // Clear the window to black
            // SDL_SetRenderDrawColor(getRenderer(), 0x0, 0x0, 0x0, 0xFF);
            SDL_SetRenderDrawColor(getRenderer(), 0x2A, 0xBF, 0x6B, 0xAA);
            // 2ABF6B
            SDL_RenderClear(getRenderer());

            // Set the draw color to be white
            SDL_SetRenderDrawColor(getRenderer(), 0xFF, 0xFF, 0xFF, 0xFF);

            // Draw the net
            for (int y = 0; y < WINDOW_HEIGHT; ++y) {
                if (y % 10) {
                    SDL_RenderDrawPoint(getRenderer(), WINDOW_WIDTH / 2, y);
                }
            }

            // Draw the ball

            SDL_SetRenderDrawColor(getRenderer(), 0xF1, 0xE8, 0x5C, 0xFF);
            // F1E85C
            ball.Draw(getRenderer());

            // Draw the paddles
            // F93E3D , 6981D9, 0a22fc
            SDL_SetRenderDrawColor(getRenderer(), 0xF9, 0x3E, 0x3D, 0xFF);
            paddleOne.Draw(getRenderer());
            SDL_SetRenderDrawColor(getRenderer(), 0x0A, 0x22, 0xFC, 0xFF);
            paddleTwo.Draw(getRenderer());

            SDL_SetRenderDrawColor(getRenderer(), 0xFF, 0xFF, 0xFF, 0xFF);
            // Display the scores
            playerOneScoreText.Draw();
            playerTwoScoreText.Draw();

            // Present the backbuffer
            SDL_RenderPresent(getRenderer());

            // Calculate frame time
            auto stopTime = std::chrono::high_resolution_clock::now();
            dt = std::chrono::duration<float, std::chrono::milliseconds::period>(stopTime - startTime).count();

            if (GAME_FINISHED) {
                state1.ShowWinnerScreen(getRenderer(), getFontTitle(), winner);
                state1.renderText(getRenderer(), getFont(), "Press R for Rematch and Esc to quit", {255, 255, 255}, 0);
                running = false;
                nextMatch = 0;
                while (nextMatch == 0) {  // While event is being collected/ While there is some event. store the event in e.
                    while (SDL_PollEvent(&event)) {
                        if (event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_QUIT || event.key.keysym.sym == SDLK_ESCAPE)
                            nextMatch = -1;
                        else if (event.key.keysym.sym == SDLK_r) {
                            nextMatch = 1;
                            break;
                        }
                    }
                }
                GAME_RUNNING = false;
            }
            if (nextMatch == 1) {
                // Restart the game
                state1.ResetGame(ball, paddleOne, paddleTwo, playerOneScoreText, playerTwoScoreText);
                GAME_FINISHED = false;
                nextMatch = 0;
                restart = 1;
            }
        }
    }
}
void Game::Close() {
    Mix_FreeChunk(wallHitSound);
    Mix_FreeChunk(paddleHitSound);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_CloseFont(getFont());
    Mix_Quit();
    TTF_Quit();
    SDL_Quit();
}