#include "Game.hpp"

SDL_Texture* playerTex;
SDL_Rect srcRect, destRect;
int cnt = 0;

Game::Game()
{

}
Game::~Game()
{

}

void Game::init(const char* title, int xPos, int yPos, int width, int height, bool fullscreen)
{
    int flags = 0;
    if (fullscreen)
    {
        flags = SDL_WINDOW_FULLSCREEN;
    }
    if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
        std::cout << "Subsys init!" << std::endl;
        window = SDL_CreateWindow(title,xPos,yPos,width,height,flags);
        if (window)
        {
            std::cout << "window created! :3" << std::endl;
        }
        renderer = SDL_CreateRenderer(window,-1,0);
        if (renderer)
        {
            SDL_SetRenderDrawColor(renderer,255,255,255,255);
            std::cout << "renderer created! :3" << std::endl;
        }
        isRunning = true;
    } else {
        isRunning = false;
    }
    SDL_Surface* tempSurface = IMG_Load("assets/marisad.png");
    playerTex = SDL_CreateTextureFromSurface (renderer, tempSurface);
    SDL_FreeSurface(tempSurface);
}

void Game::handleEvent()
{
    SDL_Event event;
    SDL_PollEvent(&event);
    switch (event.type)
    {
    case SDL_QUIT:
        isRunning = false;
        break;
    
    default:
        break;
    }
}

void Game::update()
{
    cnt++;
    destRect.h = 64;
    destRect.w = 128;
    destRect.x = cnt;
    destRect.y = cnt;
}

void Game::render()
{
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, playerTex, NULL, &destRect);
    SDL_RenderPresent(renderer);
}

void Game::clean()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    std::cout << "cweaned!" << std::endl;
}
