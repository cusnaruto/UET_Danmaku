#pragma once
#include "Component.hpp"
#include "../Vector2D.hpp"
class TransformComponent : public Component
{      
    public:
        Vector2D position;
        Vector2D velocity;

        int speed = 3;


        TransformComponent()
        {
            position.x = 0.0f;
            position.y = 0.0f;
        }

        TransformComponent(float x, float y)
        {
            position.x = x;
            position.y = y;
        }

        void init() override
        {
            velocity.x = 0;
            velocity.y = 0;
        }
        void update() override
        {
            position.x += velocity.x * speed;
            if ((position.x < 0) || (position.x + 62 > 1280))
            {
                position.x -= velocity.x * speed;
            }
            position.y += velocity.y * speed;
            if ((position.y < 0) || (position.x + 102 > 720))
            {
                position.y -= velocity.y * speed;
            }
        }
};