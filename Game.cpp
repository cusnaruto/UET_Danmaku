#include "Game.hpp"
#include "TextureManager.hpp"
#include "ECS/Component.hpp"
#include "Vector2D.hpp"
#include "Collision.hpp"
#include "AssetManager.hpp"
#include "EnemyComponent.hpp"
#include <sstream>

Manager manager;

AssetManager* Game::assets = new AssetManager(&manager);
SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

Mix_Music *gMusic = NULL;

auto& Player(manager.addEntity());
auto& Enemy(manager.addEntity());
auto& bullet(manager.addEntity());
auto& Layout(manager.addEntity());
auto& Background(manager.addEntity());
auto& label(manager.addEntity());


std::vector<ColliderComponent*> Game::colliders;
std::vector<Entity*> Enemies;

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
    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
        {
            printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
            isRunning = false;
        }
        gMusic = Mix_LoadMUS( "assets/stagebgm.mp3" );
        if( Mix_PlayingMusic() == 0 )
            {
                Mix_PlayMusic( gMusic, -1 );
            }
    if (TTF_Init() == -1)
    {
        std::cout << "font error" << std::endl;
    }

    assets->AddTexture("mybullet", "assets/playerbullet.png");
    assets->AddTexture("enemy", "assets/fairy.png");
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
    bullet.addComponent<TransformComponent>(NULL,NULL,23,21,1);
    bullet.addComponent<SpriteComponent>("bullet",true);
    bullet.addComponent<ColliderComponent>("mybullet");
    bullet.addGroup(groupBullets);
    
    Enemy.addComponent<TransformComponent>(285.0f,200.0f,29,23,2);
    Enemy.addComponent<SpriteComponent>("enemy",false);
    Enemy.addComponent<ColliderComponent>("enemy");
    Enemy.addComponent<EnemyComponent>(0,50,Vector2D(0,0));
    Enemy.addGroup(groupEnemies);
    

    Layout.addComponent<TransformComponent>(0.0f,0.0f,600,800,1);
    Layout.addComponent<SpriteComponent>("layout",false);
    Layout.addComponent<ColliderComponent>("layout");
    Layout.addGroup(groupLayouts);

    Background.addComponent<TransformComponent>(15.0f,18.0f,562,562,1);
    Background.addComponent<SpriteComponent>("background",false);
    Background.addComponent<ColliderComponent>("background");
    Background.addGroup(groupLayouts);
    
    assets->createEnemy(Vector2D(50, 50), 29, 23, "enemy");
    assets->createEnemy(Vector2D(100, 100), 29, 23, "enemy");
    assets->createEnemy(Vector2D(150, 150), 29, 23, "enemy");
}   

void Game::spawnBullet()
{
    Vector2D player = Player.getComponent<TransformComponent>().position;
    assets->CreateBullet(Vector2D(player.x+6,player.y-15), Vector2D(0,-4),1000, 2,"mybullet");
}
float xPos = 250;
void Game::spawnEnemy() {
    Enemy.addComponent<TransformComponent>(xPos,200.0f,29,23,2);
    Enemy.addComponent<SpriteComponent>("enemy",false);
    Enemy.addComponent<ColliderComponent>("enemy");
    Enemy.addGroup(groupEnemies);
    xPos += 30;
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
        if (event.key.keysym.sym == SDLK_k)
        {
            spawnEnemy();   
            std::cout << "Enemy sawnded" << std::endl;                                 
        }
        break;
    }
}

void Game::update() {
    SDL_Rect playerCol = Player.getComponent<ColliderComponent>().collider;
    Vector2D playerPos = Player.getComponent<TransformComponent>().position;

    std::stringstream ss;
    ss << "Player position: " << playerPos;
    label.getComponent<UILabel>().SetLabelText(ss.str(), "arial");

    manager.refresh();
    manager.update();

    std::vector<Entity*> Enemies;
    for (auto& entity : manager.getGroup(Game::groupEnemies)) {
        Enemies.emplace_back(entity);
    }

    for (auto& b : bullets) {
        for (auto& enemy : Enemies) {
            if (Collision::AABB(enemy->getComponent<ColliderComponent>().collider, b->getComponent<ColliderComponent>().collider)) {
                std::cout << "Hit enemy!" << std::endl;
                b->destroy();
                enemy->getComponent<EnemyComponent>().hitByBullet();
            }
        }
    }

    if (playerPos.x < 36) {
        Player.getComponent<TransformComponent>().position.x = 36;
    } else if (playerPos.x + 37 > 530) {
        Player.getComponent<TransformComponent>().position.x = 530 - 37;
    }
    if (playerPos.y < 18) {
        Player.getComponent<TransformComponent>().position.y = 18;
    } else if (playerPos.y + 19 > 555) {
        Player.getComponent<TransformComponent>().position.y = 555 - 19;
    }
}




void Game::render()
{
    SDL_RenderClear(renderer);
    Background.draw();
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
    Layout.draw();
    label.draw();
    SDL_RenderPresent(renderer);
}

void Game::clean()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    Mix_FreeMusic( gMusic );
    gMusic = NULL;
    Mix_Quit();
    SDL_Quit();
    std::cout << "cweaned!" << std::endl;
}
