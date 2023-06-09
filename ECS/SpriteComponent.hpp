#pragma once

#include "Component.hpp"
#include "SDL2/SDL.h"
#include "../TextureManager.hpp"
#include "Animation.hpp"
#include <map>
#include <unordered_map>
#include "../AssetManager.hpp"

class SpriteComponent : public Component
{
    private:
        TransformComponent *transform;
        SDL_Texture *texture;
        
        std::unordered_map<std::string, std::shared_ptr<Animation>> Animations;
        bool animated = false;
        int frames = 0;
        int speed = 100;
    
    public:
    SDL_Rect srcRect, destRect;
        int animIndex = 0;
    
        std::map<const char*, Animation> animations;

        SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;

        SpriteComponent() = default;
        SpriteComponent(std::string id)
        {
           setTex(id);
        }
        SpriteComponent(std::string id, bool isAnimated)
        {
            animated = isAnimated;
            
            Animation idle = Animation(0,8,100);
            Animation moveLeft = Animation(1,8,100);
            Animation moveRight = Animation(2,8,100);
            
            animations.emplace("Idle",idle);
            animations.emplace("Left",moveLeft);
            animations.emplace("Right",moveRight);

            Play("Idle");

            setTex(id);
        }
        ~SpriteComponent()
        {      
        }
        void setTex(std::string id)
        {
            texture = Game::assets->getTexture(id);
        }
        void init() override
        {
            transform = &entity->getComponent<TransformComponent>();
            srcRect.x = 0;
            srcRect.y = 0;
            srcRect.w = transform->width;
            srcRect.h = transform->height;
        }
        void update() override
        {
            if (animated)
            {
                srcRect.x = srcRect.w * static_cast<int>((SDL_GetTicks() / speed) % frames);
                srcRect.y = animIndex*transform->height;
            }

            destRect.x = static_cast<int>(transform->position.x);
            destRect.y = static_cast<int>(transform->position.y);
            destRect.w = transform->width * transform->scale;
            destRect.h = transform->height * transform->scale;
            
        }
        void draw() override
        {
            TextureManager::Draw(texture, srcRect, destRect, spriteFlip);
        }
        
        void Play(const char* animName)
        {
            frames = animations[animName].frames;
            animIndex = animations[animName].index;
            speed = animations[animName].speed;
        }
};