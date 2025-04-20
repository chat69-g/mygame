#pragma once
#include "GameObject.hpp"
#include "Physics.hpp"  // Dodano

class Player : public GameObject {
public:
    Player(float x, float y);
    void update() override;
    void render(SDL_Renderer* renderer) override;
    
    // Dodajte samo metode, ki jih boste dejansko uporabljali
    void jump();
    bool isGrounded() const;
    void handleInput();
    
private:
    float velocityX, velocityY;
    bool facingRight;
    bool isJumping;
};