// include/Player.hpp
#pragma once
#include "GameObject.hpp"
#include "Physics.hpp"

class Player : public GameObject {
public:
    Player(float x, float y);
    
    void update() override;
    void render() override;
    void handleInput();
    
    void jump();
    bool isGrounded() const;
    
private:
    float velocityX, velocityY;
    bool facingRight;
    bool isJumping;
};