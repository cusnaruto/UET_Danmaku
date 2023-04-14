#pragma once

#include "Component.hpp"
#include "ECS.hpp"
#include "../Vector2D.hpp"

class EnemyComponent : public Component
{
    public:
        EnemyComponent(int wid, int hgt,int spd, int hp, Vector2D vel) : width(wid),height(hgt), speed(spd), health(hp), velocity(vel)
        {}
        ~EnemyComponent()
        {}
        void init() override{
            transform = &entity->getComponent<TransformComponent>();
            transform->velocity = velocity;
            sprite = &entity->getComponent<SpriteComponent>();
            sprite->Play("Idle");
            }
        
    private:
        TransformComponent* transform;
        SpriteComponent *sprite;
        int width;
        int height;
        int speed;
        int health;
        Vector2D velocity;
};
