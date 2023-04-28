#include "EnemyComponent.hpp"
#include <math.h>
#include "SDL2/SDL_mixer.h"

void EnemyComponent::update()
{
    TransformComponent* transform = &entity->getComponent<TransformComponent>();
    transform->velocity.x = speed;
    // Check collision with walls
    Vector2D pos = transform->position;
    if (pos.x < 36)
    {
        transform->position.x = 36;
        transform->velocity.x *= -1;
    }
    else if (pos.x + 37 >= 530)
    {
        transform->position.x = 492;
        transform->velocity.x *= -1;
    }
    if (pos.y < 18)
    {
        transform->position.y = 19;
        transform->velocity.y *= -1;
    }
    else if (pos.y + 19 >= 555)
    {
        transform->position.x = 535;
        transform->velocity.y *= -1;
    }
}


void EnemyComponent::hitByBullet() {
    health--;
    Mix_Chunk *enemyDie = NULL;
    enemyDie = Mix_LoadWAV( "assets/tan01.wav" );
    std::cout << health << std::endl;
    if (health <= 0) {
        Mix_PlayChannel(-1,enemyDie,0);
        entity->destroy();
    }
}