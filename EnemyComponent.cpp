#include "EnemyComponent.hpp"
#include <math.h>
#include "SDL2/SDL_mixer.h"

void EnemyComponent::update()
{
    
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
