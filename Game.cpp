#include "Game.hpp"
#include "TextureManager.hpp"
#include "ECS/Component.hpp"
#include "Vector2D.hpp"
#include "Collision.hpp"

Manager manager;
auto& Player(manager.addEntity());
auto& bullet(manager.addEntity());

enum groupLabels : std::size_t
{
    groupBullet,
    groupPlayers,
    groupEnemies,
    groupColliders
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
    
    Player.addComponent<TransformComponent>(0.0f,0.0f,49,32,2);
    Player.addComponent<SpriteComponent>("assets/reimu.png",8,100);
    Player.addComponent<KeyboardController>();
    Player.addComponent<ColliderComponent>("player");
    Player.addGroup(groupPlayers);

    bullet.addComponent<TransformComponent>(300.0f, 300.0f, 24,29,2);
    bullet.addComponent<SpriteComponent>("assets/greenbullet.png");
    bullet.addComponent<ColliderComponent>("bullet");
    bullet.addGroup(groupBullet);
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
	Vector2D playerPos = Player.getComponent<TransformComponent>().position;
	manager.refresh();
	manager.update();
	if (Collision::AABB(Player.getComponent<ColliderComponent>().collider, bullet.getComponent<ColliderComponent>().collider)) {
		Player.getComponent<TransformComponent>().position = playerPos;
		std::cout << "Collision!" << std::endl;
	}
}
auto& players(manager.getGroup(groupPlayers));
auto& bullets(manager.getGroup(groupBullet));



void Game::render()
{
    SDL_RenderClear(renderer);
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