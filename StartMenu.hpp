#include "ECS/ECS.hpp"
#include "ECS/Component.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>


class StartMenu {
public:
    void init(SDL_Renderer* renderer) {
        this->renderer = renderer;
        font = TTF_OpenFont("assets/visby.ttf", 48);
        if (!font) {
            std::cout << "Font error" << std::endl;
        }
        textColor = {255, 255, 255, 255}; // white color
        textSurface = TTF_RenderText_Solid(font, "Press Z to start", textColor);
        if (!textSurface) {
            std::cout << "TextSurface error" << std::endl;
        }
        textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
        if (!textTexture) {
            std::cout << "TexTure error" << std::endl;
        }
        textRect.x = 100;
        textRect.y = 100;
        textRect.w = textSurface->w;
        textRect.h = textSurface->h;
    }

    void render() {
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
        SDL_RenderPresent(renderer);
    }

private:
    SDL_Renderer* renderer;
    TTF_Font* font;
    SDL_Color textColor;
    SDL_Surface* textSurface;
    SDL_Texture* textTexture;
    SDL_Rect textRect;
};