#pragma once

#include "ECS.hpp"
#include "Component.hpp"
#include "../Vector2D.hpp"
#include <string>

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
            else if (transform->position.x >= 600 || 
                    transform->position.x == 0 ||
                    transform->position.y >= 700 ||
                    transform->position.y == 0) 
            {
                entity->destroy();
            }
        }
        void collide();

    private:
    TransformComponent* transform;
    int range = 0;
    int speed = 0;
    int distance = 0;
    Vector2D velocity;
};