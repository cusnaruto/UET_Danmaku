#include "ECS.hpp"
#include "Component.hpp"
#include "../Vector2D.hpp"

class PlayerComponent : public Component {
public:
    Vector2D position;
    Vector2D velocity;
    int lives;
    int speed;

    PlayerComponent(Vector2D pos, int spd, int lvs)
        : position(pos), speed(spd), lives(lvs), velocity(Vector2D(0, 0)) {}

    void update() override {
        position += velocity * speed;

        // Check horizontal boundaries
        if (position.x < 36) {
            position.x = 36;
        } else if (position.x + 37 > 530) {  //38,18,485,565
            position.x = 530 - 37;
        }

        // Check vertical boundaries
        if (position.y < 18) {
            position.y = 18;
        } else if (position.y + 19 > 555) {
            position.y = 555 - 19;
        }
    }

    void takeDamage() {
        lives--;
    }

    void draw() override {
        // TODO: Draw the player on the screen
    }
};