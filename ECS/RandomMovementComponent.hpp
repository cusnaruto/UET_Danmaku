#include "ECS.hpp"
#include "Component.hpp"
#include "../Vector2D.hpp"
#include "SDL2/SDL.h"

class RandomMovementComponent : public Component {
public:
    RandomMovementComponent(int moveSpeed, int leftBoundary, int rightBoundary, int delay) :
        speed(moveSpeed), left(leftBoundary), right(rightBoundary), moveInterval(delay) {}

    void update() override {
        if (SDL_GetTicks() - lastTimeMoved > moveInterval) {
            int xDir = (rand() % 3) - 1; 
            int yDir = 0;
            Vector2D velocity(xDir, yDir);
            velocity.normalize();
            velocity.x *= speed;

            auto& transform = entity->getComponent<TransformComponent>();
            int newX = transform.position.x + velocity.x;
            if (transform.position.x <= left) {
            transform.position.x = left;
            transform.velocity.x *= -1;
        }
        else if (transform.position.x > right - transform.width) {
            transform.position.x = right - transform.width;
            transform.velocity.x *= -1;
        }
            transform.velocity = velocity;

            lastTimeMoved = SDL_GetTicks();
        }
    }

private:
    int speed;
    Uint32 lastTimeMoved = 0;
    int moveInterval = 1000; // Move every 1 second
    int left, right; // Boundary to move within
};