#pragma once
#include "Constants.hpp"

class Physics {
public:
    static bool checkCollision(float x1, float y1, float w1, float h1,
                             float x2, float y2, float w2, float h2);
    
    static void applyGravity(float& y, float& velocity, bool isGrounded);
    static void handleMovement(float& x, float& y, float& velocityX, float& velocityY);
};