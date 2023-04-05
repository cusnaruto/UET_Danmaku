#include "Game.hpp"
#include "TextureManager.hpp"
#include "ECS/Component.hpp"
#include "Vector2D.hpp"
#include "Collision.hpp"
#include "AssetManager.hpp"

Manager manager;
auto& Player(manager.addEntity());
auto& bullet(manager.addEntity());
auto& Layout(manager.addEntity());
auto& Background(manager.addEntity());

AssetManager* Game::assets = new AssetManager(&manager);
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

    assets->AddTexture("bullet", "assets/greenbullet.png");
    assets->AddTexture("player", "assets/reimu.png");
    assets->AddTexture("layout", "assets/gameplaylayout.png");
    assets->AddTexture("background","assets/bg.png");

    Player.addComponent<TransformComponent>(285.0f,525.0f,49,32,1);
    Player.addComponent<SpriteComponent>("player",true);
    Player.addComponent<KeyboardController>();
    Player.addComponent<ColliderComponent>("player");
    Player.addGroup(groupPlayers);

    assets->CreateBullet(Vector2D(300,300), Vector2D(0,2),200, 2,"bullet");
    assets->CreateBullet(Vector2D(200,300), Vector2D(0,2),200, 2,"bullet");
    
    Layout.addComponent<TransformComponent>(0.0f,0.0f,600,800,1);
    Layout.addComponent<SpriteComponent>("layout",false);
    Layout.addComponent<ColliderComponent>("layout");
    Layout.addGroup(groupLayouts);

    Background.addComponent<TransformComponent>(15.0f,18.0f,562,562,1);
    Background.addComponent<SpriteComponent>("background",false);
    Background.addComponent<ColliderComponent>("background");
    Background.addGroup(groupLayouts);

}

auto& players(manager.getGroup(Game::groupPlayers));
auto& colliders(manager.getGroup(Game::groupColliders));
auto& bullets(manager.getGroup(Game::groupBullets));



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
    for (auto& b : bullets)
    {
        if(Collision::AABB(Player.getComponent<ColliderComponent>().collider, b->getComponent<ColliderComponent>().collider))
        {
            b->destroy();
            Player.getComponent<TransformComponent>().position = playerPos;
        }
    }
}



void Game::render()
{
    SDL_RenderClear(renderer);
    Background.draw();
    Layout.draw();
    for (auto& p : players)
    {
        p->draw();
    }
    for (auto& b : bullets)
    {
        b->draw();
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