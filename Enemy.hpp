#pragma once
#include "ECS/ECS.hpp"
#include "ECS/Component.hpp"
#include "SpriteComponent.hpp"
#include "TransformComponent.hpp"

class Enemy : public Entity {
public:
    Enemy(SDL_Renderer* renderer, int initialHealth, float speed);
    void spawn();
    void shootBullet(SDL_Point playerPosition);
    void update(float deltaTime);

private:
    SpriteComponent* spriteComponent;
    TransformComponent* transformComponent;
    HealthBar* healthBar;
    Animation* animation;
    int health;
    float speed;
    int currentFrame;
    int frameCount;
    int frameWidth;
    int frameHeight;
};