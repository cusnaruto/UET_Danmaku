#ifndef Game_hpp
#define Game_hpp
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>
#include <vector>
#include "MainMenu.hpp"


class ColliderComponent;
class AssetManager;
class Game {

public:
        Game();
        ~Game();
        
        void init(const char* title, int xPos, int yPos, int width, int height, bool fullscreen);
        void handleEvent();
        void update();
        void render();
        void clean();
        void spawnBullet();
        void spawnEnemyBullet();
        void respawnPlayer();
        void quit();
        bool running()
        {
            return isRunning;
        }
        static float deltaTime;
        static int enemiesKilled;
        static SDL_Renderer *renderer;
        static SDL_Event event;
        static std::vector<ColliderComponent*> colliders;
        static AssetManager* assets;
        enum groupLabels : std::size_t
        {
                groupBullets,
                groupPlayers,
                groupEnemies,
                groupColliders,
                groupLayouts,
                groupEnemyBullets,
                groupBosses,
        };
private:
        bool isRunning;
        SDL_Window* window; 
};

#endif /* Game_hpp */