@echo off
set MINGW_PATH=%~dp0mingw64\bin
"%MINGW_PATH%\g++.exe" main.cpp Game.cpp GameHandler.cpp PlayerScore.cpp Paddle.cpp CheckWallCollision.cpp CheckPaddleCollision.cpp Ball.cpp -I src\include -L src\lib -o Pong -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf -lSDL2_mixer -static-libgcc -static-libstdc++
.\Pong