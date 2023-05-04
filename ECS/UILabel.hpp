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
        UILabel(int xpos, int ypos, std::string text) :
		    labelText(text)
        {
            position.x = xpos;
		    position.y = ypos;
            texColor.r = 255;
            texColor.g = 255;
            texColor.b = 255;
            texColor.a = 255;
		    labelTexture = NULL;
        }
        ~UILabel()
        {}

        void SetLabelText(TTF_Font* font)
        {
            SDL_Surface* surf = TTF_RenderText_Solid(font, labelText.c_str(), texColor);
            labelTexture = SDL_CreateTextureFromSurface(Game::renderer, surf);
            SDL_FreeSurface(surf);
            SDL_QueryTexture(labelTexture, nullptr, nullptr, &position.w, &position.h);
        }
        void SetText(const std::string& text) { labelText = text; }
	    std::string GetText() const {return labelText; }
        void draw() override
        {
            SDL_RenderCopy(Game::renderer, labelTexture, nullptr, &position);
        }
        void destroy()
        {
		SDL_DestroyTexture(labelTexture);
		labelTexture = NULL;
	    }
        void setColor(Uint8 red,Uint8 green, Uint8 blue, Uint8 alpha)
        {
        texColor.r = red;
        texColor.g = green;
        texColor.b = blue;
        texColor.a = alpha;
        }
    private:
        SDL_Rect position;
        std::string labelText;
        std::string labelFont;
        SDL_Color texColor;
        SDL_Texture* labelTexture;
};