#include "Game.hpp"
#include "TextureManager.hpp"
#include "ECS/Component.hpp"
#include "Vector2D.hpp"
#include "Collision.hpp"
#include "AssetManager.hpp"
#include <sstream>

Manager manager;
auto& Player(manager.addEntity());
auto& Enemy(manager.addEntity());
auto& bullet(manager.addEntity());
auto& Layout(manager.addEntity());
auto& Background(manager.addEntity());
auto& label(manager.addEntity());

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

    if (TTF_Init() == -1)
    {
        std::cout << "font error" << std::endl;
    }

    assets->AddTexture("mybullet", "assets/playerbullet.png");
    assets->AddTexture("enemy", "assets/dekafumo.jpg");
    assets->AddTexture("player", "assets/reimu.png");
    assets->AddTexture("layout", "assets/gameplaylayout.png");
    assets->AddTexture("background","assets/bg.png");
    assets->AddFont("visby", "assets/visby.ttf", 16);

    Player.addComponent<TransformComponent>(285,500,49,32,1);
    Player.addComponent<SpriteComponent>("player", true);
    Player.addComponent<KeyboardController>();
    Player.addComponent<ColliderComponent>("player");
    Player.addGroup(groupPlayers);

    SDL_Color white = {255,255,255,255};
    label.addComponent<UILabel>(630,135, "727 wysi", "visby", white);

    assets->CreateBullet(Vector2D(300,300), Vector2D(0,2),200, 2,"mybullet");
    assets->CreateBullet(Vector2D(200,300), Vector2D(0,2),200, 2,"mybullet");
    bullet.addComponent<TransformComponent>(NULL,NULL,21,23,1);
    bullet.addComponent<SpriteComponent>("bullet",true);
    bullet.addComponent<ColliderComponent>("mybullet");
    bullet.addGroup(groupEnemies);
    
    Enemy.addComponent<TransformComponent>(285.0f,200.0f,200,200,1);
    Enemy.addComponent<SpriteComponent>("enemy",false);
    Enemy.addComponent<ColliderComponent>("enemy");
    Enemy.addGroup(groupEnemies);

    Layout.addComponent<TransformComponent>(0.0f,0.0f,600,800,1);
    Layout.addComponent<SpriteComponent>("layout",false);
    Layout.addComponent<ColliderComponent>("layout");
    Layout.addGroup(groupLayouts);

    Background.addComponent<TransformComponent>(15.0f,18.0f,562,562,1);
    Background.addComponent<SpriteComponent>("background",false);
    Background.addComponent<ColliderComponent>("background");
    Background.addGroup(groupLayouts);

}

void Game::spawnBullet()
{
    Vector2D player = Player.getComponent<TransformComponent>().position;
    assets->CreateBullet(Vector2D(player.x+6,player.y-15), Vector2D(0,-4),1000, 2,"mybullet");
}
auto& players(manager.getGroup(Game::groupPlayers));
auto& colliders(manager.getGroup(Game::groupColliders));
auto& bullets(manager.getGroup(Game::groupBullets));
auto& enemies(manager.getGroup(Game::groupEnemies));


void Game::handleEvent()
{
    Vector2D playerPos = Player.getComponent<TransformComponent>().position;
    Uint32 lastBulletTime = 0;
    SDL_PollEvent(&event);
    switch (event.type)
    {
    case SDL_QUIT:
        isRunning = false;
        break;
    case SDL_KEYDOWN:
        if (event.key.keysym.sym == SDLK_z)
        {
            spawnBullet();                                    
        }
        break;
    }
}

void Game::update() {
	Vector2D playerPos = Player.getComponent<TransformComponent>().position;
    int i = 727;
    std::stringstream ss;
    ss << i;
    label.getComponent<UILabel>().SetLabelText(ss.str(),"visby");
	manager.refresh();
    manager.update();
    if (playerPos.x < 36)
    {
        Player.getComponent<TransformComponent>().position.x = 36;
    }
    else if (playerPos.x + 37 > 530)
    {
        Player.getComponent<TransformComponent>().position.x = 530 - 37;
    }
    if (playerPos.y < 18)
    {
        Player.getComponent<TransformComponent>().position.y = 18;
    }
    else if (playerPos.y + 19 > 553)
    {
        Player.getComponent<TransformComponent>().position.y = 553 - 19;
    }
    for (auto& b : bullets)
    {
        b->getComponent<BulletComponent>().update();
        if(Collision::AABB(Enemy.getComponent<ColliderComponent>().collider, b->getComponent<ColliderComponent>().collider))
        {
            b->destroy();
            std::cout << "hit enemies" << std::endl;
        }
        if (b->getComponent<TransformComponent>().height <= 20)
        {
            b->destroy();
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
    for (auto& e : enemies)
    {
        e->draw();
    }
    for (auto& b : bullets)
    {
        b->getComponent<SpriteComponent>().draw();
    }
    label.draw();
    SDL_RenderPresent(renderer);
}

void Game::clean()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    std::cout << "cweaned!" << std::endl;
}