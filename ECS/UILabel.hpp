#pragma once
#include "ECS.hpp"
#include "../AssetManager.hpp"
#include "../Game.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>

class UILabel : public Component
{
    public:
        UILabel(int xPos, int yPos, std::string text, std::string font, SDL_Color& color)
            : labelText(text), labelFont(font), texColor(color)
        {
            position.x = xPos;
            position.y = yPos;

            SetLabelText(labelText, labelFont);
        }
        ~UILabel()
        {}

        void SetLabelText(std::string text, std::string font)
        {
            SDL_Surface* surf = TTF_RenderText_Blended(Game::assets->GetFont(font), text.c_str(),texColor);
            labelTexture = SDL_CreateTextureFromSurface(Game::renderer, surf);
            SDL_FreeSurface(surf);
            SDL_QueryTexture(labelTexture, nullptr, nullptr, &position.w, &position.h);
        }
        void draw() override
        {
            SDL_RenderCopy(Game::renderer, labelTexture, nullptr, &position);
        }
    private:
        SDL_Rect position;
        std::string labelText;
        std::string labelFont;
        SDL_Color texColor;
        SDL_Texture* labelTexture;
};