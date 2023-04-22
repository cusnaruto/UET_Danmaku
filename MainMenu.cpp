#include "MainMenu.hpp"
#include "TextureManager.hpp"

void MainMenu::show(Game& game) {
    // Load the menu background image
    SDL_Texture* menuTexture = TextureManager::LoadTexture("assets/mainmenu.png");
    // Create a rectangle to hold the menu background image dimensions
    SDL_Rect menuRect;
    SDL_QueryTexture(menuTexture, nullptr, nullptr, &menuRect.w, &menuRect.h);
    menuRect.x = 0;
    menuRect.y = 0;

    bool menuActive = true;
    SDL_Event event;
    while (menuActive) {
        // Poll for events
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym) {
                        case SDLK_z:
                            // Start the game if the player presses 'z'
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
        Mix_Quit();
    }

    // Clean up resources
    SDL_DestroyTexture(menuTexture);
}