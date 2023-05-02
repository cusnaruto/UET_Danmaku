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
    Mix_Music* bgmMusic = Mix_LoadMUS("assets/lose.mp3");
    if( Mix_PlayingMusic() == 0 )
            {
                Mix_PlayMusic( bgmMusic, -1 );
            }

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

        if (!Mix_PlayingMusic()) {
            Mix_PlayMusic(bgmMusic, -1);
        }
    }

    SDL_DestroyTexture(menuTexture);
    Mix_FreeMusic(bgmMusic);
    bgmMusic = NULL;
    Mix_Quit();
}