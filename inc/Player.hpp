#pragma once
#include "GameObject.hpp"

class Player : public GameObject {
public:
    Player(float x, float y);
    void update() override;
    void render(SDL_Renderer* renderer) override;  // Popravljeno da se ujema z GameObject
    
private:
    float velocityX, velocityY;
    bool facingRight;
    bool isJumping;
};