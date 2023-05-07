#include "YouWin.hpp"
#include "TextureManager.hpp"
#include <SDL2/SDL_mixer.h>

YouWin::YouWin()
{}

YouWin::~YouWin()
{}

void YouWin::show(Game& game) {
    SDL_Texture* menuTexture = TextureManager::LoadTexture("assets/youwon.png");
    SDL_Rect menuRect;
    SDL_QueryTexture(menuTexture, nullptr, nullptr, &menuRect.w, &menuRect.h);
    menuRect.x = 0;
    menuRect.y = 0;
    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
        {
            printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
        }
    Mix_Chunk* youWin = Mix_LoadWAV("assets/win.wav");
    Mix_PlayChannel(-1,youWin,0);

    bool winActive = true;
    SDL_Event event;
    while (winActive) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                game.quit();
                winActive = false;
                break;
        }
        }

        SDL_RenderClear(game.renderer);
        SDL_RenderCopy(game.renderer, menuTexture, nullptr, &menuRect);
        SDL_RenderPresent(game.renderer);
    }
    SDL_DestroyTexture(menuTexture);
    Mix_FreeChunk(youWin);
    youWin = NULL;
    Mix_Quit();
}