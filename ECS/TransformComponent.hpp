#pragma once
#include "Component.hpp"
#include "../Vector2D.hpp"
class TransformComponent : public Component
{      
    public:
        Vector2D position;

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
        void update() override
        {
            
        }
};