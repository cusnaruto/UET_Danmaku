#pragma once

#include "ECS.hpp"
#include "Component.hpp"
#include "../Vector2D.hpp"
class BulletComponent : public Component
{
    public:
        BulletComponent(int rng, int spd, Vector2D vel) : range(rng), speed(spd), velocity(vel)
        {}
        ~BulletComponent()
        {}
        void init() override
        {
            transform = &entity->getComponent<TransformComponent>();
            transform->velocity = velocity;
        }
        void update() override
        {
            distance += speed;

            if (distance > range)
            {
                entity->destroy();
            }
            else if (transform->position.x > 525 || 
                    transform->position.x < 30 ||
                    transform->position.y > 580 ||
                    transform->position.y < 20) 
            {
                entity->destroy();
            }
        }

    private:

    TransformComponent* transform;
    
    int range = 0;
    int speed = 0;
    int distance = 0;
    Vector2D velocity;
};