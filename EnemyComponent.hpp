#pragma once

#include "ECS/Component.hpp"
#include "ECS/ECS.hpp"
#include "Vector2D.hpp"
#include "Collision.hpp"

class EnemyComponent : public Component
{
    public:
        EnemyComponent(int spd, int hp, Vector2D vel) : speed(spd), health(hp), velocity(vel)
        {}
        ~EnemyComponent()
        {}
        void init() override{
            transform = &entity->getComponent<TransformComponent>();
            transform->velocity = velocity;
            sprite = &entity->getComponent<SpriteComponent>();
            sprite->Play("Idle");
            }
        void update() override;
        int getHealth() const { return health; }
        void hitByBullet();
    private:
        Manager manager;
        TransformComponent* transform;
        SpriteComponent *sprite;
        int health;
        int speed;
        std::string tag;
        Vector2D velocity;
};