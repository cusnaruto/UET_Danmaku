#pragma once

#include "ECS/Component.hpp"
#include "ECS/ECS.hpp"
#include "Vector2D.hpp"
#include "Collision.hpp"
#include <SDL2/SDL.h>
class EnemyComponent : public Component
{
    public:
        EnemyComponent(int spd, int hp, Vector2D vel, std::string id) : speed(spd), health(hp), velocity(vel), ID(id)
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
        bool isDead();

        std::string getID() const {return ID;}
    private:
        TransformComponent* transform;
        SpriteComponent *sprite;
        Manager* manager;
        int health;
        int speed;
        std::string tag;
        std::string ID;
        Vector2D velocity;


};