#include "AssetManager.hpp"
#include "ECS/Component.hpp"
AssetManager::AssetManager(Manager* man) : manager(man)
{

}
AssetManager::~AssetManager()
{
}

void AssetManager::CreateBullet(Vector2D pos,Vector2D vel, int range, int speed, std::string id)
{
    auto& bullet(manager->addEntity());
    bullet.addComponent<TransformComponent>(pos.x, pos.y,29,24,1);
    bullet.addComponent<SpriteComponent>(id,false);
    bullet.addComponent<BulletComponent>(range, speed, vel);
    bullet.addComponent<ColliderComponent>("bullet");
    bullet.addGroup(Game::groupBullets);
}

void AssetManager::createEnemy(Vector2D pos, int width, int height, std::string id, int hp)
{
    auto& enemy(manager->addEntity()); 
    enemy.addComponent<TransformComponent>(pos.x, pos.y, width, height, 1.5);
    enemy.addComponent<SpriteComponent>(id,false);
    enemy.addComponent<EnemyComponent>(0, hp, Vector2D(0, 0));
    enemy.addComponent<ColliderComponent>("enemy");
    enemy.addGroup(Game::groupEnemies);
}

void AssetManager::AddTexture(std::string id, const char* path)
{
    textures.emplace(id, TextureManager::LoadTexture(path));
}

SDL_Texture* AssetManager::getTexture(std::string id)
{
    return textures[id];
}

void AssetManager::AddFont(std::string id,std::string path,int fontSize)
{
    fonts.emplace(id, TTF_OpenFont(path.c_str(), fontSize));
}
TTF_Font* AssetManager::GetFont(std::string id)
{
    return fonts[id];
}


void AssetManager::CreateEnemyBullet(Vector2D pos,Vector2D vel, int range, int speed, std::string id)
{
    auto& bullet(manager->addEntity());
    bullet.addComponent<TransformComponent>(pos.x, pos.y,12,12,1);
    bullet.addComponent<SpriteComponent>(id,false);
    bullet.addComponent<BulletComponent>(range, speed, vel);
    bullet.addComponent<ColliderComponent>("bullet");
    bullet.addGroup(Game::groupEnemyBullets);   
}


void AssetManager::CreateFlowerPattern(Vector2D pos, int petalCount, int bulletCount, int range, int bulletSpeed, std::string id)
{
    int radius = 20;
    int speed = 3;
    float angleStep = 2 * M_PI / petalCount;

    for (int i = 0; i < petalCount; ++i) {
        float angle = i * angleStep;

        for (int j = 0; j < bulletCount; ++j) {
            float bulletAngle = j * (2 * M_PI / bulletCount);
            float dx = radius * cos(bulletAngle);
            float dy = radius * sin(bulletAngle);

            auto& bullet(manager->addEntity());
            bullet.addComponent<TransformComponent>(pos.x + dx, pos.y + dy, 10, 10, 1);
            bullet.addComponent<SpriteComponent>(id,false);
            bullet.addComponent<BulletComponent>(range, bulletSpeed, Vector2D(speed * cos(angle), speed * sin(angle)));
            bullet.addComponent<ColliderComponent>("bullet");
            bullet.addGroup(Game::groupEnemyBullets);
        }
    }
}

