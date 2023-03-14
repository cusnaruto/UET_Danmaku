#include "Game.hpp"

Game *game = nullptr;
int main( int argc, char **argv ){
    game = new Game();
    game ->init("UET_Danmaku", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,1280,720,false);
    while (game->running()){
        game->handleEvent();
        game->update();
        game->render();
    }
    game->clean();
    return 0;
}

