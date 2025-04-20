#include "Physics.hpp"
#include "Constants.hpp"

bool Physics::checkCollision(float x1, float y1, float w1, float h1,
                           float x2, float y2, float w2, float h2) {
    return x1 < x2 + w2 &&
           x1 + w1 > x2 &&
           y1 < y2 + h2 &&
           y1 + h1 > y2;
}

void Physics::applyGravity(float& y, float& velocity, bool isGrounded) {
    if (!isGrounded) {
        velocity += Constants::GRAVITY;
        y += velocity;
    } else {
        velocity = 0;
    }
}

void Physics::handleMovement(float& x, float& y, float& velX, float& velY) {
    x += velX;
    y += velY;
    velX *= 0.9f;  // Friction
    velY *= 0.95f;
}