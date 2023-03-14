#ifndef Game_hpp
#define Game_hpp
#include <SDL2/SDL.h>
#include <iostream>

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

private:
        bool isRunning;
        SDL_Window* window;
        SDL_Renderer* renderer;     
};
#endif /* Game_hpp */