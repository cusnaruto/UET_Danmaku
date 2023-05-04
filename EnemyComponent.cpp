#include "EnemyComponent.hpp"
#include <math.h>

void EnemyComponent::update()
{
    
}


void EnemyComponent::hitByBullet() {
    health--;
    if (health <= 0) { 
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

