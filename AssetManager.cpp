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