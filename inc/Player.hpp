#pragma once
#include <SDL2/SDL.h>
#include "GameObject.hpp"

class Player : public GameObject {
public:
    Player(float x, float y);
    void update() override;
    void render(SDL_Renderer* renderer) override;
    
private:
    float velocityX, velocityY;
    bool facingRight;
    bool isJumping;
};