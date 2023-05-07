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
Mix_Chunk *enemyDie = NULL;
Mix_Chunk *shoot = NULL;

TTF_Font* font = NULL;

auto& Player(manager.addEntity());
auto& Layout(manager.addEntity());
auto& Background(manager.addEntity());
auto& label(manager.addEntity());


UILabel Lives(618,85, " ");
UILabel Killed(625,132, " ");
UILabel Left(610,175, " ");
UILabel FPS(700,20," ");

std::vector<ColliderComponent*> Game::colliders;
std::vector<Entity*> Enemies;

Uint32 timeNow = SDL_GetTicks();
float lastTime = 0;
float Game::deltaTime = 0.0f;
Uint32 fireRate = 2000;
Uint32 fasterFireRate = 900;
Uint32 lastFireTime = 0;
Uint32 invulnerableTime = 0;
const Uint32 spawnDelay = 2000;
Uint32 lastSpawnTime = 0;

int x1 = -5;
int x2 = 5;

float speed = 1;

int playerLives = 20;
int Game::enemiesKilled = 0;

bool BossIsSpawned = false;

Game::Game()
{
}
Game::~Game(){
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
		printf( "Failed to load playerDie sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
		isRunning = false;
	    }   
        enemyDie = Mix_LoadWAV( "assets/tan01.wav" );
        if( enemyDie == NULL )
	    {
		printf( "Failed to load enemyDie sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
		isRunning = false;
	    }   
        shoot = Mix_LoadWAV( "assets/damage00.wav" );
	    if( shoot == NULL )
	    {
		printf( "Failed to load damage sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
		isRunning = false;
	    }
	    
    if (TTF_Init() == -1)
    {
        std::cout << "font error" << std::endl;
    }
    font = TTF_OpenFont("assets/visby.ttf", 16);
    Lives.SetLabelText(font);
    Lives.setColor(255,255,255,255);

    assets->AddTexture("mybullet", "assets/playerbullet.png");
    assets->AddTexture("enemy", "assets/fairy.png");
    assets->AddTexture("mokou","assets/mokou.png");
    assets->AddTexture("koishi", "assets/koishi.png");
    assets->AddTexture("cirno", "assets/cirno.png");
    assets->AddTexture("chen", "assets/chen.png");
    assets->AddTexture("flan","assets/flan.png");
    assets->AddTexture("enemyBullet", "assets/red2.png");
    assets->AddTexture("chenBullet", "assets/greenknife.png");
    assets->AddTexture("mokouBullet", "assets/mokoubullet.png");
    assets->AddTexture("koishiBullet", "assets/koishiBullet.png");
    assets->AddTexture("koishiBullet2", "assets/koishibullet2.png");
    assets->AddTexture("cirnoBullet", "assets/cirnoBullet.png");
    assets->AddTexture("flanBullet", "assets/flanBullet.png");
    assets->AddTexture("flanBullet2", "assets/flanbullet2.png");
    assets->AddTexture("enemy1", "assets/mob2.png");
    assets->AddTexture("enemy2", "assets/mob3.png");
    assets->AddTexture("enemy3", "assets/fairy4.png");
    assets->AddTexture("enemy4", "assets/fairy5.png");
    assets->AddTexture("player", "assets/reimu.png");
    assets->AddTexture("layout", "assets/gameplaylayout.png");
    assets->AddTexture("background","assets/background.png");

    Player.addComponent<TransformComponent>(285,500,49,32,1);
    Player.addComponent<SpriteComponent>("player", true);
    Player.addComponent<KeyboardController>();
    Player.addComponent<ColliderComponent>("player");
    Player.addGroup(groupPlayers);


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
auto& enemybullets(manager.getGroup(Game::groupEnemyBullets));
auto& bosses(manager.getGroup(Game::groupBosses));

void Game::quit() {
    isRunning = false;
}

void Game::respawnPlayer() {
    if (playerLives > 0) {
        --playerLives;
        Player.getComponent<TransformComponent>().position = Vector2D(283, 500);
        invulnerableTime = SDL_GetTicks() + 3000;
    } 
}
void Game::handleEvent()
{
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
    if (isRunning == true){

    float currentTime = SDL_GetTicks() / 1000.0f;
    deltaTime = currentTime - lastTime;
    int fps = static_cast<int>(1 / deltaTime);
    FPS.destroy();
    FPS.SetLabelText(font);
    Lives.destroy();
    Lives.SetLabelText(font);
    Killed.destroy();
    Killed.SetLabelText(font);
    Left.destroy();
    Left.SetLabelText(font);
    std::stringstream ss,ss1,ss2,ss3;
    ss << playerLives;
    ss1 << enemiesKilled;
    ss2 << 55 - enemiesKilled;
    ss3 << "FPS: " << fps;
    Lives.SetText(ss.str());
    Killed.SetText(ss1.str());
    Left.SetText(ss2.str());
    FPS.SetText(ss3.str());
    if (enemiesKilled == 55){
    Mix_PauseMusic();
    YouWin youWin;
    youWin.show(*this);
    isRunning = false;
    }
    if (playerLives == 0){
        Mix_PauseMusic();
        GameOver GameOver;
        GameOver.show(*this);
        isRunning = false;
    }
    SDL_Rect playerCol = Player.getComponent<ColliderComponent>().collider;
    Vector2D playerPos = Player.getComponent<TransformComponent>().position;
    srand(time(NULL));
    
    manager.refresh();
    manager.update();

    std::vector<Entity*> Enemies(manager.getGroup(Game::groupEnemies).begin(), manager.getGroup(Game::groupEnemies).end());
    if (enemiesKilled == 10 && BossIsSpawned == false) 
    {
    auto& Mokou(manager.addEntity());
    Mokou.addComponent<TransformComponent>(250,100,72,41,1);
    Mokou.addComponent<SpriteComponent>("mokou");
    Mokou.addComponent<ColliderComponent>("enemy");
    Mokou.addComponent<RandomMovementComponent>(1,100,435,0);
    Mokou.addComponent<EnemyComponent>(0, 50, Vector2D(0, 0),"mokou");
    Mokou.addGroup(groupBosses);
    BossIsSpawned = true;
    }
    if (enemiesKilled == 21 && BossIsSpawned == false) {
    auto& Koishi(manager.addEntity());
    Koishi.addComponent<TransformComponent>(250,100,65,38,1);
    Koishi.addComponent<SpriteComponent>("koishi", false);
    Koishi.addComponent<ColliderComponent>("enemy");
    Koishi.addComponent<RandomMovementComponent>(1,100,435,0);
    Koishi.addComponent<EnemyComponent>(0, 50, Vector2D(0, 0),"koishi");
    Koishi.addGroup(groupBosses);
    BossIsSpawned = true;
    }
    if (enemiesKilled == 32 && BossIsSpawned == false) {
    auto& Cirno(manager.addEntity());
    Cirno.addComponent<TransformComponent>(250,100,52,29,1);
    Cirno.addComponent<SpriteComponent>("cirno", false);
    Cirno.addComponent<ColliderComponent>("enemy");
    Cirno.addComponent<RandomMovementComponent>(1,100,435,0);
    Cirno.addComponent<EnemyComponent>(0, 75, Vector2D(0, 0),"cirno");
    Cirno.addGroup(groupBosses);
    BossIsSpawned = true;
    }
    if (enemiesKilled == 43 && BossIsSpawned == false) {
    auto& Chen(manager.addEntity());
    Chen.addComponent<TransformComponent>(250,100,61,43,1);
    Chen.addComponent<SpriteComponent>("chen", false);
    Chen.addComponent<ColliderComponent>("enemy");
    Chen.addComponent<RandomMovementComponent>(1,100,435,0);
    Chen.addComponent<EnemyComponent>(0, 75, Vector2D(0, 0),"chen");
    Chen.addGroup(groupBosses);
    BossIsSpawned = true;
    }
    if (enemiesKilled == 54 && BossIsSpawned == false) {
    auto& Flan(manager.addEntity());
    Flan.addComponent<TransformComponent>(250,100,69,43,1);
    Flan.addComponent<SpriteComponent>("flan", false);
    Flan.addComponent<ColliderComponent>("enemy");
    Flan.addComponent<RandomMovementComponent>(1,100,435,0);
    Flan.addComponent<EnemyComponent>(0, 100, Vector2D(0, 0),"flan");
    Flan.addGroup(groupBosses);
    BossIsSpawned = true;
    }
    if (Enemies.empty() && BossIsSpawned == false ) {
    for (int i = 0; i < 5 && enemiesKilled < 10; i++) {
        assets->createEnemy(Vector2D(50 + i * 100, 100), 29,23,"enemy",10,0,"enemy");
    }
    for (int j = 0; j < 5 && enemiesKilled < 21 && enemiesKilled >= 11; j++) {
        assets->createEnemy(Vector2D(50 + j * 100, 100), 29,23,"enemy1",15,0,"enemy");
    }
    for (int j = 0; j < 5 && enemiesKilled < 32 && enemiesKilled >= 22; j++) {
        assets->createEnemy(Vector2D(50 + j * 100, 100), 28,25,"enemy2",20,0,"enemy");
        fireRate = 1850;
        speed = 1.5;
    }
    for (int j = 0; j < 5 && enemiesKilled < 43 && enemiesKilled >= 33; j++) {
        assets->createEnemy(Vector2D(50 + j * 100, 100), 32,20,"enemy3",25,0,"enemy");
        fireRate = 1700;
        speed = 2;
    }
    for (int j = 0; j < 5 && enemiesKilled < 54 && enemiesKilled >= 44; j++) {
        assets->createEnemy(Vector2D(50 + j * 100, 100), 24,25,"enemy4",35,0,"enemy");
        fireRate = 1500;
        speed = 2;
    }
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
        assets->CreateFlowerPattern(bulletPos, 15,4,1000,1, "mokouBullet",16,16);}
        else if (bs->getComponent<EnemyComponent>().getID() == "koishi"){
        assets->CreateConePattern(bulletPos,dir,35,30,1000,1,"koishiBullet",16,10,1);
        assets->CreateFlowerPattern(bulletPos, 5,2,1000,1, "koishiBullet2",12,12);}
        else if (bs->getComponent<EnemyComponent>().getID() == "cirno"){
        for (int i = -5; i < 5; i++)
        {
            assets->CreateEnemyBullet(bulletPos,Vector2D(dir.x+i,std::abs(dir.y+1)),1000,2,"cirnoBullet",18,10,2);
        }
        }
        else if (bs->getComponent<EnemyComponent>().getID() == "chen"){
            fireRate = fasterFireRate;
            assets->CreateEnemyBullet(bulletPos,Vector2D(dir.x, dir.y+0.5),1000,1,"chenBullet",29,19,2);
            }
        else if (bs->getComponent<EnemyComponent>().getID() == "flan"){
            fireRate = 200;
            
            assets->CreateEnemyBullet(bulletPos,Vector2D(x1, 2),1000,2,"flanBullet2",17,10,2);
            assets->CreateEnemyBullet(bulletPos,Vector2D(x2, 2),1000,2,"flanBullet2",17,10,2);
            x1+=1;
            x2-=1;
            if (x1 == 5)
            {
                x1 = -5;
            }
            if (x2 == -5)
            {
                x2 = 5;
            }
            assets->CreateBulletPattern(bulletPos,30,1,8,"flanBullet",16,16,1);
            }
        lastFireTime = SDL_GetTicks();
            }   
        }
    for (auto& enemy : Enemies) {
        for (auto& b : bullets) {
            if (Collision::AABB(enemy->getComponent<ColliderComponent>().collider, b->getComponent<ColliderComponent>().collider)) {
                b->destroy();
                if (enemy->getComponent<EnemyComponent>().getHealth() == 1)
                {
                    Mix_PlayChannel(-1,enemyDie,0);
                }
                enemy->getComponent<EnemyComponent>().hitByBullet();
            }
        }
    }
    for (auto& Bosses : bosses) {
        for (auto& b : bullets) {
            if (Collision::AABB(Bosses->getComponent<ColliderComponent>().collider, b->getComponent<ColliderComponent>().collider)) {
                b->destroy();
                if (Bosses->getComponent<EnemyComponent>().getHealth() == 1)
                {
                    Mix_PlayChannel(-1,enemyDie,0);
                }
                Bosses->getComponent<EnemyComponent>().hitByBullet();
                if (Bosses->getComponent<EnemyComponent>().getHealth() <= 0)
                {
                    BossIsSpawned = false;
                    fireRate = 2000;
                }
            }
        }
    }
    lastTime = currentTime;
    if (SDL_GetTicks() - lastFireTime >= fireRate){
    for (auto& enemy : Enemies) {
    auto& transform = enemy->getComponent<TransformComponent>();
    auto& playerTransform = Player.getComponent<TransformComponent>();
    Vector2D tempPos(playerTransform.position.x + playerTransform.width / 2, playerTransform.position.y + playerTransform.height / 2);
    auto enemyPos = Vector2D(transform.position.x + transform.width / 2, transform.position.y + transform.height / 2);
    Vector2D dir = (tempPos - enemyPos).normalize();
    Vector2D bulletPos(transform.position.x + transform.width / 2 - 3, transform.position.y + transform.height / 2);
    assets->CreateEnemyBullet(bulletPos, dir ,1000,speed, "enemyBullet",12,12,1);
    lastFireTime = SDL_GetTicks();
             }   
        }
    for (auto& eb : enemybullets)
    {
        if (Collision::AABB(Player.getComponent<ColliderComponent>().collider, eb->getComponent<ColliderComponent>().collider)) {
                if (SDL_GetTicks() > invulnerableTime) {
                Mix_PlayChannel(-1,playerDie,0);
                eb->destroy();
                respawnPlayer();
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
        e->draw();
    }
    for (auto& boss : bosses)
    {
        boss->draw();
    }
    for (auto& eb : enemybullets)
    {
        eb->getComponent<SpriteComponent>().draw();
    }

    Layout.draw();
    FPS.draw();
    Lives.draw();
    Killed.draw();
    Left.draw();
    SDL_RenderPresent(renderer);
}

void Game::clean()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    Mix_FreeMusic(gMusic);
    Mix_FreeChunk(playerDie);
    Mix_FreeChunk(shoot);
    Mix_FreeChunk(enemyDie);
    playerDie = NULL;
    enemyDie = NULL;
    gMusic = NULL;
    shoot = NULL;
    Mix_Quit();
    SDL_Quit();
    std::cout << "cweaned!" << std::endl;
}
