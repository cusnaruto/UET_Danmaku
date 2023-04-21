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

void AssetManager::createEnemy(Vector2D pos, int width, int height, std::string id, std::string spriteId)
{
    auto& enemy(manager->addEntity());
    enemy.addComponent<TransformComponent>(pos.x, pos.y, width, height, 1);
    enemy.addComponent<SpriteComponent>(spriteId, false);
    enemy.addComponent<ColliderComponent>("enemy");
    enemy.addComponent<EnemyComponent>(0, 50, Vector2D(0, 0));
    enemy.addGroup(Game::groupEnemies);
}

void AssetManager::CreateEnemyBullet(Vector2D pos,Vector2D vel, int range, int speed, std::string id)
{
    auto& bullet(manager->addEntity());
    bullet.addComponent<TransformComponent>(pos.x, pos.y,29,24,1);
    bullet.addComponent<SpriteComponent>(id,false);
    bullet.addComponent<BulletComponent>(range, speed, vel);
    bullet.addComponent<ColliderComponent>("bullet");
    bullet.addGroup(Game::groupEnemyBullets);
}