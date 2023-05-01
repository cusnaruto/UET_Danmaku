#include "Game.hpp"

Game *game = nullptr;
int main( int argc, char **argv ){
    const int FPS = 60;
    const int frameDelay = 1000/FPS;
    
    Uint32 frameStart;
    
    int frameTime;
    
    game = new Game();
    game ->init("UET_Danmaku", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,800,600,false);
    while (game->running()){
        Uint32 timeNow = SDL_GetTicks();
        Uint32 prevTime = 0;
        Game::deltaTime = (timeNow - prevTime) / 1000.0f;
        prevTime = timeNow;
        frameStart = SDL_GetTicks();

        game->handleEvent();
        game->update();
        game->render();

        frameTime = SDL_GetTicks() - frameStart;

        if (frameDelay > frameTime)
        {
            SDL_Delay(frameDelay - frameTime);
        }
    }
    game->clean();
    return 0;
}

//g++ -Wall -g -o Danmaku.exe main.cpp Game.cpp TextureManager.cpp -I src\include -L src\lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer 