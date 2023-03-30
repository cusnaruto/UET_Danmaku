#pragma once
#include "../Game.hpp"
#include "ECS.hpp"
#include "Component.hpp"

class KeyboardController : public Component
{
    public:
        TransformComponent *transform;

        void init() override
        {
            transform = &entity->getComponent<TransformComponent>();
        }

        void update() override
        {
            if (Game::event.type == SDL_KEYDOWN && Game::event.key.repeat == 0)
            {
                    switch (Game::event.key.keysym.sym)
                    {
                        case SDLK_UP:
                            transform->velocity.y = -1;
                            break;
                        case SDLK_LEFT:
                            transform->velocity.x = -1;
                            break;
                        case SDLK_DOWN:
                            transform->velocity.y = +1;
                            break;
                        case SDLK_RIGHT:
                            transform->velocity.x = +1;
                            break;
                        default:
                            break;
                    }
            }
            else if (Game::event.type == SDL_KEYUP && Game::event.key.repeat == 0)
            {
                    switch (Game::event.key.keysym.sym)
                    {
                        case SDLK_UP:
                            transform->velocity.y = 0;
                            break;
                        case SDLK_LEFT:
                            transform->velocity.x = 0;
                            break;
                        case SDLK_DOWN:
                            transform->velocity.y = 0;
                            break;
                        case SDLK_RIGHT:
                            transform->velocity.x = 0;
                            break;
                        default:
                            break;
                    }
            }

        }
};
