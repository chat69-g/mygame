// src/Player.cpp
#include "Player.hpp"
#include <iostream>

Player::Player(float x, float y) 
    : GameObject(x, y, Constants::TILE_SIZE, Constants::TILE_SIZE * 2),
      velocityX(0), velocityY(0),
      facingRight(true), isJumping(false) {}

void Player::update() {
    Physics::applyGravity(y, velocityY, isGrounded());
    Physics::handleMovement(x, y, velocityX, velocityY);
}

void Player::render() {
    std::cout << "Player at: " << x << "," << y 
              << " Velocity: " << velocityX << "," << velocityY << std::endl;
}

void Player::handleInput() {
    // Input handling bo premaknjen v Game.cpp
}

void Player::jump() {
    if (isGrounded()) {
        velocityY = Constants::JUMP_FORCE;
        isJumping = true;
    }
}

bool Player::isGrounded() const {
    // Preverjanje tal bo v map kolizijah
    return false;
}