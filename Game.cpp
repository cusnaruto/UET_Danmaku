#include "Game.hpp"
#include "TextureManager.hpp"
#include "ECS/Component.hpp"
#include "Vector2D.hpp"
#include "Collision.hpp"
#include "AssetManager.hpp"
#include "EnemyComponent.hpp"
#include <sstream>
#include <cstdlib>
#include <ctime>

Manager manager;

AssetManager* Game::assets = new AssetManager(&manager);
SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

Mix_Music *gMusic = NULL;
Mix_Music *bgmMusic = NULL;
Mix_Chunk *playerDie = NULL;
Mix_Chunk *shoot = NULL;

auto& Player(manager.addEntity());
auto& Enemy(manager.addEntity());
auto& bullet(manager.addEntity());
auto& Layout(manager.addEntity());
auto& Background(manager.addEntity());
auto& label(manager.addEntity());
auto& enemyBullet(manager.addEntity());

std::vector<ColliderComponent*> Game::colliders;
std::vector<Entity*> Enemies;

Uint32 timeNow = SDL_GetTicks();
float Game::deltaTime = 0.0f;
Uint32 fireRate = 2000;
Uint32 lastFireTime = 0;
Uint32 invulnerableTime = 0;
int playerLives = 99;
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
        MainMenu mainMenu;
        mainMenu.show(*this);
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
                Mix_PlayMusic( gMusic, 1 );
            }
        playerDie = Mix_LoadWAV( "assets/playerdie.mp3" );
	    if( playerDie == NULL )
	    {
		printf( "Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
		isRunning = false;
	    }   
        shoot = Mix_LoadWAV( "assets/damage00.wav" );
	    if( shoot == NULL )
	    {
		printf( "Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
		isRunning = false;
	    }
	    
    if (TTF_Init() == -1)
    {
        std::cout << "font error" << std::endl;
    }

    assets->AddTexture("mybullet", "assets/playerbullet.png");
    assets->AddTexture("enemy", "assets/fairy.png");
    assets->AddTexture("enemyBullet", "assets/red2.png");
    assets->AddTexture("enemy1", "assets/mob2.png");
    assets->AddTexture("enemy2", "assets/mob3.png");
    assets->AddTexture("player", "assets/reimu.png");
    assets->AddTexture("layout", "assets/gameplaylayout.png");
    assets->AddTexture("background","assets/temp.jpg");
    assets->AddFont("visby", "assets/visby.ttf", 16);

    Player.addComponent<TransformComponent>(285,500,49,32,1);
    Player.addComponent<SpriteComponent>("player", true);
    Player.addComponent<KeyboardController>();
    Player.addComponent<ColliderComponent>("player");
    Player.addGroup(groupPlayers);

    SDL_Color white = {255,255,255,255};
    label.addComponent<UILabel>(618,95, "727 wysi", "visby", white);

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
    
    enemyBullet.addComponent<TransformComponent>(NULL,NULL,12,12,1);
    enemyBullet.addComponent<SpriteComponent>("enemyBullet",false);
    enemyBullet.addComponent<ColliderComponent>("enemybullet");
    enemyBullet.addGroup(groupEnemyBullets);

    Layout.addComponent<TransformComponent>(0.0f,0.0f,600,800,1);
    Layout.addComponent<SpriteComponent>("layout",false);
    Layout.addComponent<ColliderComponent>("layout");
    Layout.addGroup(groupLayouts);

    Background.addComponent<TransformComponent>(15.0f,18.0f,562,562,1);
    Background.addComponent<SpriteComponent>("background",false);
    Background.addComponent<ColliderComponent>("background");
    Background.addGroup(groupLayouts);
    
    assets->createEnemy(Vector2D(50, 50), 29, 23, "enemy","enemy");
    assets->createEnemy(Vector2D(100, 100), 29, 23, "enemy1","enemy1");
    assets->createEnemy(Vector2D(150, 150), 29, 23, "enemy2","enemy2");
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
auto& enemybullets(manager.getGroup(Game::groupEnemyBullets));

void Game::quit() {
    isRunning = false;
}

void Game::respawnPlayer() {
    if (playerLives > 0) {
        --playerLives;
        Player.getComponent<TransformComponent>().position = Vector2D(283, 500); // set the default position
        invulnerableTime = SDL_GetTicks() + 4000; // make the player invulnerable for 2 seconds
    } else {
        // handle game over
    }
}
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
            Mix_PlayChannel(-1,shoot,0); 
        }
        break;
    }
}

void Game::update() {
    SDL_Rect playerCol = Player.getComponent<ColliderComponent>().collider;
    Vector2D playerPos = Player.getComponent<TransformComponent>().position;
    srand(time(NULL));
    std::stringstream ss;
    ss << "Player position: " << playerPos;
    label.getComponent<UILabel>().SetLabelText(ss.str(), "visby");

    manager.refresh();
    manager.update();
    deltaTime = SDL_GetTicks();
    std::vector<Entity*> Enemies(manager.getGroup(Game::groupEnemies).begin(), manager.getGroup(Game::groupEnemies).end());
    if (SDL_GetTicks() - lastFireTime >= fireRate){
    for (auto& enemy : Enemies) {
    auto& transform = enemy->getComponent<TransformComponent>();
    Vector2D bulletPos(transform.position.x + transform.width / 2, transform.position.y + transform.height / 2);
    assets->CreateEnemyBullet(bulletPos, Vector2D(0, 1),1000,2, "enemyBullet");
    // assets->CreateFlowerPattern(bulletPos,20,4,1000,2,"enemyBullet");
    std::cout << "bullet fired" << std::endl;
    lastFireTime = SDL_GetTicks();
            }   
        }
    for (auto& enemy : Enemies) {
        for (auto& b : bullets) {
            if (Collision::AABB(enemy->getComponent<ColliderComponent>().collider, b->getComponent<ColliderComponent>().collider)) {
                std::cout << "Hit enemy!" << std::endl;
                b->destroy();
                enemy->getComponent<EnemyComponent>().hitByBullet();
            }
        }
    }
    for (auto& eb : enemybullets)
    {
        if (Collision::AABB(Player.getComponent<ColliderComponent>().collider, eb->getComponent<ColliderComponent>().collider)) {
                if (SDL_GetTicks() > invulnerableTime) {
                std::cout << "Hit player!" << std::endl;
                Mix_PlayChannel(-1,playerDie,0);
                eb->destroy();
                respawnPlayer();
                std::cout << playerLives << std::endl;
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
    for (auto& eb : enemybullets)
    {
        eb->getComponent<SpriteComponent>().draw();
    }
    Layout.draw();
    label.draw();
    SDL_RenderPresent(renderer);
}

void Game::clean()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    Mix_FreeMusic(gMusic);
    Mix_FreeChunk(playerDie);
    Mix_FreeChunk(shoot);
    playerDie = NULL;
    gMusic = NULL;
    shoot = NULL;
    Mix_Quit();
    SDL_Quit();
    std::cout << "cweaned!" << std::endl;
}
