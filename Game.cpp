#include "Game.hpp"
#include "TextureManager.hpp"
#include "ECS/Component.hpp"
#include "Vector2D.hpp"
#include "Collision.hpp"

Manager manager;
auto& Player(manager.addEntity());
auto& bullet(manager.addEntity());
auto& Layout(manager.addEntity());
auto& Background(manager.addEntity());

enum groupLabels : std::size_t
{
    groupBullet,
    groupPlayers,
    groupEnemies,
    groupColliders,
    groupLayouts
};

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

std::vector<ColliderComponent*> Game::colliders;

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
    
    Player.addComponent<TransformComponent>(285.0f,525.0f,49,32,1);
    Player.addComponent<SpriteComponent>("assets/reimu.png",true);
    Player.addComponent<KeyboardController>();
    Player.addComponent<ColliderComponent>("player");
    Player.addGroup(groupPlayers);

    bullet.addComponent<TransformComponent>(300.0f, 300.0f, 24,29,2);
    bullet.addComponent<SpriteComponent>("assets/greenbullet.png");
    bullet.addComponent<ColliderComponent>("bullet");
    bullet.addGroup(groupBullet);

    Layout.addComponent<TransformComponent>(0.0f,0.0f,600,800,1);
    Layout.addComponent<SpriteComponent>("assets/gameplaylayout.png",false);
    Layout.addComponent<ColliderComponent>("layout");
    Layout.addGroup(groupLayouts);

    Background.addComponent<TransformComponent>(35.0f,18.0f,562,483,2);
    Background.addComponent<SpriteComponent>("assets/bg.png",false);
    Background.addComponent<ColliderComponent>("layout");
    Background.addGroup(groupLayouts);

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

void Game::update() {
	manager.refresh();
	manager.update();
}
auto& players(manager.getGroup(groupPlayers));
auto& bullets(manager.getGroup(groupBullet));



void Game::render()
{
    SDL_RenderClear(renderer);
    Background.draw();
    Layout.draw();
    for (auto& p : players)
    {
        p->draw();
    }
    for (auto& e : bullets)
    {
        e->draw();
    }
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