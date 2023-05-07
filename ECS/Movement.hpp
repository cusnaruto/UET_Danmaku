#include "ECS.hpp"
#include "Component.hpp"
#include "../Vector2D.hpp"
#include "SDL2/SDL.h"

class MovementComponent : public Component {
public:
    MovementComponent(int moveSpeed, int leftBoundary, int rightBoundary, int delay) :
        speed(moveSpeed), left(leftBoundary), right(rightBoundary), moveInterval(delay) {}

    void update() override {
        if (SDL_GetTicks() - lastTimeMoved > moveInterval) {
            auto& transform = entity->getComponent<TransformComponent>();
            Vector2D velocity(1, 0);

            if (transform.position.x <= left) {
                velocity.x = speed;
            }
            else if (transform.position.x > right - transform.width) {
                velocity.x = -speed;
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
