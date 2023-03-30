#pragma once

#include "Component.hpp"
#include "SDL2/SDL.h"

class SpriteComponent : public Component
{
    private:
        TransformComponent *transform;
        SDL_Texture *texture;
        SDL_Rect srcRect, destRect;
    
    public:
        SpriteComponent() = default;
        SpriteComponent(const char* path)
        {
           setTex(path);
        }
        void setTex(const char* path)
        {
            texture = TextureManager::LoadTexture(path);
        }
        void init() override
        {
            transform = &entity->getComponent<TransformComponent>();
            srcRect.x = 0;
            srcRect.y = 0;
            srcRect.w = 62;
            srcRect.h = 102;
            destRect.w = 62;
            destRect.h = 102;
        }
        void update() override
        {
            destRect.x = (int)transform->position.x;
            destRect.y = (int)transform->position.y;
        }
        void draw() override
        {
            TextureManager::Draw(texture, srcRect, destRect);
        }
};