#pragma once

#include "ECS.hpp"
#include "Component.hpp"
#include "../Vector2D.hpp"
#include <string>

class BulletComponent : public Component
{
    public:
        BulletComponent() : range(0), speed(0), distance(0), velocity(0, 0) {}
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


    void setVelocity(int vx, int vy) {
    transform->velocity.x = vx;
    transform->velocity.y = vy;
    }
     float phase = 0.0f;

    Vector2D velocity;
    private:
    TransformComponent* transform;
    int range = 0;
    int speed = 0;
    int distance = 0;
    
};