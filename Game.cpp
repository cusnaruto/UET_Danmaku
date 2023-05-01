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
#include <cmath>

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
const Uint32 spawnDelay = 2000;
Uint32 lastSpawnTime = 0;

int playerLives = 99;
int Game::enemiesKilled = 0;

bool BossIsSpawned = false;

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
    assets->AddTexture("enemy3", "assets/fairy4.png");
    assets->AddTexture("player", "assets/reimu.png");
    assets->AddTexture("layout", "assets/gameplaylayout.png");
    assets->AddTexture("background","assets/temp.jpg");
    assets->AddTexture("mokou","assets/mokou.png");
    assets->AddTexture("koishi", "assets/koishi.png");
    assets->AddTexture("cirno", "assets/cirno.png");
    assets->AddTexture("chen", "assets/chen.png");
    assets->AddFont("visby", "assets/visby.ttf", 16);

    Player.addComponent<TransformComponent>(285,500,49,32,1);
    Player.addComponent<SpriteComponent>("player", true);
    Player.addComponent<KeyboardController>();
    Player.addComponent<ColliderComponent>("player");
    Player.addGroup(groupPlayers);

    SDL_Color white = {255,255,255,255};
    label.addComponent<UILabel>(618,95, "727 wysi", "visby", white);

    bullet.addComponent<TransformComponent>(NULL,NULL,23,21,1);
    bullet.addComponent<SpriteComponent>("bullet",true);
    bullet.addComponent<ColliderComponent>("mybullet");
    bullet.addGroup(groupBullets);
    
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

    
    // assets->createEnemy(Vector2D(50, 50), 29, 23, "enemy","enemy");
    // assets->createEnemy(Vector2D(100, 100), 29, 23, "enemy1","enemy1");
    // assets->createEnemy(Vector2D(150, 150), 29, 23, "enemy2","enemy2");

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
auto& bosses(manager.getGroup(Game::groupBosses));
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

// assets->CreateSineWaveBulletPattern(bulletPos,20,2,1000,"enemyBullet");
// assets->CreateFlowerPattern(bulletPos,20,4,1000,2,"enemyBullet");

void Game::update() {
    SDL_Rect playerCol = Player.getComponent<ColliderComponent>().collider;
    Vector2D playerPos = Player.getComponent<TransformComponent>().position;
    // Vector2D tempPos(playerPos.x,playerPos.y);
    srand(time(NULL));
    std::stringstream ss;
    ss << "Enemies killed: " << enemiesKilled;
    label.getComponent<UILabel>().SetLabelText(ss.str(), "visby");

    manager.refresh();
    manager.update();
    deltaTime = SDL_GetTicks();

    std::vector<Entity*> Enemies(manager.getGroup(Game::groupEnemies).begin(), manager.getGroup(Game::groupEnemies).end());
    if (enemiesKilled == 10 && BossIsSpawned == false) {
    auto& Mokou(manager.addEntity());
    Mokou.addComponent<TransformComponent>(250,100,72,41,1);
    Mokou.addComponent<SpriteComponent>("mokou", false);
    Mokou.addComponent<ColliderComponent>("enemy");
    Mokou.addComponent<EnemyComponent>(0, 50, Vector2D(0, 0),"mokou");
    Mokou.addGroup(groupBosses);
    BossIsSpawned = true;
    }
    if (enemiesKilled == 21 && BossIsSpawned == false) {
    auto& Koishi(manager.addEntity());
    Koishi.addComponent<TransformComponent>(250,100,65,38,1);
    Koishi.addComponent<SpriteComponent>("koishi", false);
    Koishi.addComponent<ColliderComponent>("enemy");
    Koishi.addComponent<EnemyComponent>(0, 50, Vector2D(0, 0),"koishi");
    Koishi.addGroup(groupBosses);
    BossIsSpawned = true;
    }
    if (enemiesKilled == 32 && BossIsSpawned == false) {
    auto& Cirno(manager.addEntity());
    Cirno.addComponent<TransformComponent>(250,100,52,29,1);
    Cirno.addComponent<SpriteComponent>("cirno", false);
    Cirno.addComponent<ColliderComponent>("enemy");
    Cirno.addComponent<EnemyComponent>(0, 50, Vector2D(0, 0),"cirno");
    Cirno.addGroup(groupBosses);
    BossIsSpawned = true;
    }
    if (enemiesKilled == 43 && BossIsSpawned == false) {
    auto& Chen(manager.addEntity());
    Chen.addComponent<TransformComponent>(250,100,61,43,1);
    Chen.addComponent<SpriteComponent>("chen", false);
    Chen.addComponent<ColliderComponent>("enemy");
    Chen.addComponent<EnemyComponent>(0, 50, Vector2D(0, 0),"chen");
    Chen.addGroup(groupBosses);
    BossIsSpawned = true;
    }
    if (Enemies.empty() && BossIsSpawned == false && SDL_GetTicks() - lastSpawnTime >= spawnDelay) {
    for (int i = 0; i < 5 && enemiesKilled < 10; i++) {
        assets->createEnemy(Vector2D(50 + i * 100, 100), 29,23,"enemy",10,0,"enemy");
    }
    for (int j = 0; j < 5 && enemiesKilled < 21 && enemiesKilled >= 11; j++) {
        assets->createEnemy(Vector2D(50 + j * 100, 100), 29,23,"enemy1",15,0,"enemy");
    }
    for (int j = 0; j < 5 && enemiesKilled < 32 && enemiesKilled >= 22; j++) {
        assets->createEnemy(Vector2D(50 + j * 100, 100), 29,23,"enemy2",20,0,"enemy");
    }
    for (int j = 0; j < 5 && enemiesKilled < 43 && enemiesKilled >= 33; j++) {
        assets->createEnemy(Vector2D(50 + j * 100, 100), 29,23,"enemy2",20,0,"enemy");
    }
    lastSpawnTime = SDL_GetTicks();
    }
        if (SDL_GetTicks() - lastFireTime >= fireRate){
        for (auto& bs : bosses) {
        auto& transform = bs->getComponent<TransformComponent>();
        auto& playerTransform = Player.getComponent<TransformComponent>();
        Vector2D tempPos(playerTransform.position.x + playerTransform.width / 2, playerTransform.position.y + playerTransform.height / 2);
        auto enemyPos = Vector2D(transform.position.x + transform.width / 2, transform.position.y + transform.height / 2);
        Vector2D dir = (tempPos - enemyPos).normalize();
        Vector2D bulletPos(transform.position.x + transform.width / 2 - 3, transform.position.y + transform.height / 2);
        if (bs->getComponent<EnemyComponent>().getID() == "mokou"){
        assets->CreateFlowerPattern(bulletPos, 20,5,1000,2, "enemyBullet");}
        else if (bs->getComponent<EnemyComponent>().getID() == "koishi"){
        assets->CreateConePattern(bulletPos,dir,60,20,1000,2,"enemyBullet");}
        else if (bs->getComponent<EnemyComponent>().getID() == "cirno"){
        for (int i = -5; i < 5; i++)
        {
            assets->CreateEnemyBullet(bulletPos,Vector2D(dir.x+i,std::abs(dir.y+3)),1000,2,"enemyBullet");
        }
        }
        else if (bs->getComponent<EnemyComponent>().getID() == "chen"){
        // Calculate the rotation angle for each bullet
        
            }
        // assets->CreateFlowerPattern(bulletPos,20,4,1000,2,"enemyBullet");
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
    for (auto& Bosses : bosses) {
        for (auto& b : bullets) {
            if (Collision::AABB(Bosses->getComponent<ColliderComponent>().collider, b->getComponent<ColliderComponent>().collider)) {
                std::cout << "Hit enemy!" << std::endl;
                b->destroy();
                if (Bosses->getComponent<EnemyComponent>().getHealth() == 1)
                {
                    BossIsSpawned = false;
                }
                Bosses->getComponent<EnemyComponent>().hitByBullet();
            }
        }
    }
    if (SDL_GetTicks() - lastFireTime >= fireRate){
    for (auto& enemy : Enemies) {
    auto& transform = enemy->getComponent<TransformComponent>();
    auto& playerTransform = Player.getComponent<TransformComponent>();
    Vector2D tempPos(playerTransform.position.x + playerTransform.width / 2, playerTransform.position.y + playerTransform.height / 2);
    auto enemyPos = Vector2D(transform.position.x + transform.width / 2, transform.position.y + transform.height / 2);
    Vector2D dir = (tempPos - enemyPos).normalize();
    Vector2D bulletPos(transform.position.x + transform.width / 2 - 3, transform.position.y + transform.height / 2);
    assets->CreateEnemyBullet(bulletPos, dir ,1000,2, "enemyBullet");
    std::cout << "bullet fired" << std::endl;
    lastFireTime = SDL_GetTicks();
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
    for (auto& b : bullets)
    {
        b->getComponent<SpriteComponent>().draw();
    }
    for (auto& e : enemies)
    {
        e->getComponent<SpriteComponent>().draw();
    }
    for (auto& eb : enemybullets)
    {
        eb->getComponent<SpriteComponent>().draw();
    }
    for (auto& boss : bosses)
    {
        boss->draw();
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
