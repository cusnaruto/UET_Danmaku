#include "MainMenu.hpp"
#include "TextureManager.hpp"
#include <SDL2/SDL_mixer.h>

void MainMenu::show(Game& game) {
    // Load the menu background image
    SDL_Texture* menuTexture = TextureManager::LoadTexture("assets/mainmenu.png");
    // Create a rectangle to hold the menu background image dimensions
    SDL_Rect menuRect;
    SDL_QueryTexture(menuTexture, nullptr, nullptr, &menuRect.w, &menuRect.h);
    menuRect.x = 0;
    menuRect.y = 0;

    // Load the background music
    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
        {
            printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
        }
    Mix_Music* bgmMusic = Mix_LoadMUS("assets/mainmenubgm.mp3");
    if( Mix_PlayingMusic() == 0 )
            {
                Mix_PlayMusic( bgmMusic, -1 );
            }

    bool menuActive = true;
    SDL_Event event;
    while (menuActive) {
        // Poll for events
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                game.quit();
                menuActive = false;
                break;
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym) {
                        case SDLK_z:
                            // Start the game if the player presses 'z'
                            menuActive = false;
                            break;
                        case SDLK_ESCAPE:
                            // Quit the game if the player presses 'Esc'
                            game.quit();
                            menuActive = false;
                            break;
                    }
                    break;
            }
        }

        // Clear the renderer and draw the menu background image
        SDL_RenderClear(game.renderer);
        SDL_RenderCopy(game.renderer, menuTexture, nullptr, &menuRect);
        SDL_RenderPresent(game.renderer);

        // Play the background music
        if (!Mix_PlayingMusic()) {
            Mix_PlayMusic(bgmMusic, -1);
        }
    }

    // Clean up resources
    SDL_DestroyTexture(menuTexture);
    Mix_FreeMusic(bgmMusic);
    bgmMusic = NULL;
    Mix_Quit();
}