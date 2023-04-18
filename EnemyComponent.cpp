#include "EnemyComponent.hpp"
#include <math.h>


void EnemyComponent::update()
{
    TransformComponent* transform = &entity->getComponent<TransformComponent>();
    transform->velocity.x = speed;
    if (health == 0)
    {
        entity->destroy();
    }
    // Check collision with walls
    Vector2D pos = transform->position;
    if (pos.x < 36)
    {
        transform->velocity.x *= -1;
    }
    else if (pos.x + 37 >= 530)
    {
        transform->velocity.x *= -1;
    }
    if (pos.y < 18)
    {
        transform->velocity.y *= -1;
    }
    else if (pos.y + 19 >= 555)
    {
        transform->velocity.y *= -1;
    }  
}

void EnemyComponent::hitByBullet() {
    health--;
    std::cout << health << std::endl;
    if (health <= 0) {
        entity->destroy();
    }
}