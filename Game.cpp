#include "Game.hpp"
#include "TextureManager.hpp"
#include "ECS/Component.hpp"
#include "Vector2D.hpp"
#include "Collision.hpp"

Manager manager;
auto& Player(manager.addEntity());
auto& bullet(manager.addEntity());

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

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
    
    Player.addComponent<TransformComponent>(2);
    Player.addComponent<SpriteComponent>("assets/marisad.png");
    Player.addComponent<KeyboardController>();
    Player.addComponent<ColliderComponent>("player");

   bullet.addComponent<TransformComponent>(300.0f, 300.0f, 20,20,1);
   bullet.addComponent<SpriteComponent>("assets/greenbullet.png");
   bullet.addComponent<ColliderComponent>("bullet");
}

void Game::handleEvent()
{

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
    manager.refresh();
    manager.update();   

    if (Collision::AABB(Player.getComponent<ColliderComponent>().collider, 
        bullet.getComponent<ColliderComponent>().collider))
    {
        std::cout << "Collide" << std::endl;
    }
}

void Game::render()
{
    SDL_RenderClear(renderer);
    manager.draw();
    SDL_RenderPresent(renderer);
}

void Game::clean()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    std::cout << "cweaned!" << std::endl;
}

//