#ifndef Game_hpp
#define Game_hpp
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <vector>

class ColliderComponent;

class Game {

public:
        Game();
        ~Game();
        
        void init(const char* title, int xPos, int yPos, int width, int height, bool fullscreen);
        
        void handleEvent();
        void update();
        void render();
        void clean();
        
        bool running()
        {
            return isRunning;
        }
        static SDL_Renderer *renderer;
        static SDL_Event event;
        static std::vector<ColliderComponent*> colliders;

private:
        bool isRunning;
        SDL_Window* window; 
};
#endif /* Game_hpp */