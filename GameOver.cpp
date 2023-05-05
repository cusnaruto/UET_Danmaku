#include "GameOver.hpp"
#include "TextureManager.hpp"
#include <SDL2/SDL_mixer.h>

GameOver::GameOver()
{}

GameOver::~GameOver()
{}

void GameOver::show(Game& game) {
    SDL_Texture* menuTexture = TextureManager::LoadTexture("assets/gameover.png");
    SDL_Rect menuRect;
    SDL_QueryTexture(menuTexture, nullptr, nullptr, &menuRect.w, &menuRect.h);
    menuRect.x = 0;
    menuRect.y = 0;

    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
        {
            printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
        }
    Mix_Chunk* youlose = Mix_LoadWAV("assets/lose.mp3");
    Mix_PlayChannel(-1,youlose,0);
    bool overActive = true;
    SDL_Event event;
    while (overActive) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                game.quit();
                overActive = false;
                break;
        }
        }

        SDL_RenderClear(game.renderer);
        SDL_RenderCopy(game.renderer, menuTexture, nullptr, &menuRect);
        SDL_RenderPresent(game.renderer);

    }
    SDL_DestroyTexture(menuTexture);
    Mix_FreeChunk(youlose);
    youlose = NULL;
    Mix_Quit();
}