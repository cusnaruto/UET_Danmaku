#pragma once

#include <map>
#include <string>
#include <vector>
#include "TextureManager.hpp"
#include "Vector2D.hpp"
#include "ECS/ECS.hpp"
#include <cmath>

#include "SDL2/SDL_ttf.h"

class AssetManager
{
    public:
        AssetManager(Manager* man);
        ~AssetManager();

        //gameobjects

        void CreateBullet(Vector2D pos, Vector2D vel, int range, int speed, std::string id);
        void CreateEnemyBullet(Vector2D pos,Vector2D vel, int range, int speed, std::string id);

        //texture manager
        void AddTexture(std::string id, const char* path);
        SDL_Texture* getTexture(std::string id);
        void AddFont(std::string id,std::string path,int fontSize);
        TTF_Font* GetFont(std::string id);
        void createEnemy(Vector2D pos, int width, int height, std::string id, int hp);
        void CreateFlowerPattern(Vector2D pos, int petalCount, int bulletCount, int range, int bulletSpeed, std::string id);
    private:
        Manager* manager;
        std::map<std::string, SDL_Texture*> textures;
        std::map<std::string, TTF_Font*> fonts;

};