# PingPong Game in C++ using SDL

## Build Instructions:

### Windows:
### Option 1:
Run the a.exe file directly for running the game

### Option 2:
Run the runcode.bat file and wait for the compilation of the new executable. The runcode.bat will automatically run the new executable file.

### Option 3:
In a powershell, go to this directory, then run the following command : 
"g++ main.cpp Game.cpp GameHandler.cpp PlayerScore.cpp Paddle.cpp CheckWallCollision.cpp CheckPaddleCollision.cpp Ball.cpp -I src/include -L src/lib -o a -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf -lSDL2_mixer"
Then Run the executable by running the command :
".\a"

## About the project:
The project is a pong game with some added functionalities and colorful graphics. The game is designed using OOP from c++. The purpose of desining the project is to learn OOP and to use programming in real world applications. We have used SDL2 as a library to handle user input and outputs and rendering textures and graphics. The SDL2 and all other necessary additions like SDL_TTF and SDL_mixer for handling fonts and audio are also provided in this source code in the src folder. The music used is copyright free and stored in the audio folder.