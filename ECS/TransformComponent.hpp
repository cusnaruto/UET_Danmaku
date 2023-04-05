#pragma once
#include "Component.hpp"
#include "../Vector2D.hpp"
class TransformComponent : public Component
{      
    public:
        Vector2D position;
        Vector2D velocity;

        int height = 49;
        int width = 32;
        int scale = 1;

        int speed = 3;

        TransformComponent(int sc)
        {
            position.x = 285;
            position.y = 525;
            scale = sc;
        }
        TransformComponent()
        {
            position.Zero();
        }

        TransformComponent(float x, float y)
        {
            position.Zero();
        }

        TransformComponent(float x, float y,int h, int w, float s)
        {
            position.x = x;
            position.y = y;
            height = h;
            width = w;
            scale = s;
        }

        void init() override
        {
            velocity.Zero();
        }
        void update() override
        {
            position.x += velocity.x * speed;
            if ((position.x < 36) || (position.x + 37 > 530 ))  //38,18,485,565
            {
                position.x -= velocity.x * speed;
            }
            position.y += velocity.y * speed;
            if ((position.y < 18) || (position.y + 19 > 555))
            {
                position.y -= velocity.y * speed;
            }
        }
};