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
    Mix_Chunk *enemyDie = NULL;
    enemyDie = Mix_LoadWAV( "assets/tan01.wav" );
    std::cout << health << std::endl;
    if (health <= 0) {
        Mix_PlayChannel(-1,enemyDie,0);
        entity->destroy();
        Game::enemiesKilled += 1;
    }
}

bool EnemyComponent::isDead()
{
    if (health == 0)
    {
        return true;
    }
    else return false;
}

void EnemyComponent::updateRandomMovement(float deltaTime)
{
    // Generate a random direction vector
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dis(0, 2 * M_PI);

    double randomAngle = dis(gen);
    Vector2D direction(cos(randomAngle), sin(randomAngle));

    // Calculate new position based on direction and speed
    Vector2D newPosition = transform->position + (direction * speed * deltaTime);

    // Check if the new position is within the screen bounds
    if (newPosition.x >= 37 && newPosition.x <= 530 - transform->width
        && newPosition.y >= 19 && newPosition.y <= 555 - transform->height)
    {
        // Set the enemy's position to the new position
        transform->position = newPosition;
    }
}
