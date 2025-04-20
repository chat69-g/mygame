#pragma once
#include "GameObject.hpp"
#include "Physics.hpp"

class Player : public GameObject {
public:
    Player(float x, float y);
    void update() override;
    void render(SDL_Renderer* renderer) override;
    
    // Dodane metode za upravljanje z igralcem
    void jump();
    void move(float dx, float dy);
    bool isGrounded() const;
    
private:
    float velocityX, velocityY;
    bool facingRight;
    bool isJumping;
};