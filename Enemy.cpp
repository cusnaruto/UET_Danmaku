#include "Enemy.hpp"

Enemy::Enemy(SDL_Renderer* renderer, int initialHealth, float speed) {
    // Create the sprite component
    spriteComponent = new SpriteComponent(renderer, "enemy.png");

    // Get the sprite dimensions
    frameWidth = spriteComponent->getTextureWidth() / frameCount;
    frameHeight = spriteComponent->getTextureHeight();

    // Create the transform component
    transformComponent = new TransformComponent(0, 0, frameWidth, frameHeight);

    // Create the health bar component
    healthBar = new HealthBar(initialHealth);

    // Create the animation component
    animation = new Animation(frameCount, 100);

    // Set the initial health and speed
    health = initialHealth;
    this->speed = speed;

    // Set the initial animation frame
    currentFrame = 0;
}

void Enemy::spawn() {
    // Randomly set the enemy's initial position on either the left or right side of the screen
    int randomX = rand() % 2 == 0 ? -transformComponent->getWidth() : Game::SCREEN_WIDTH;
    int randomY = rand() % Game::SCREEN_HEIGHT;
    transformComponent->setPosition(randomX, randomY);
}

void Enemy::shootBullet(SDL_Point playerPosition) {
    // Create a new bullet instance aimed at the player's position
    Bullet* bullet = new Bullet(transformComponent->getPosition(), playerPosition);
    Game::getInstance()->addEntity(bullet);
}

void Enemy::update(float deltaTime) {
    // Update the animation
    animation->update(deltaTime);
    currentFrame = animation->getCurrentFrame();

    // Move the enemy
    int dx = speed * deltaTime;
    if (transformComponent->getPosition().x < -transformComponent->getWidth()) {
        delete();
    }