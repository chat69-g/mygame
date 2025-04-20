#include "Player.hpp"
#include "Physics.hpp"
#include "Constants.hpp"  // Dodano
#include <iostream>       // Dodano za std::cout

Player::Player(float x, float y) 
    : GameObject(x, y, Constants::TILE_SIZE, Constants::TILE_SIZE * 2),
      velocityX(0), velocityY(0),
      facingRight(true), isJumping(false) {}

void Player::update() {
    Physics::applyGravity(y, velocityY, isGrounded());
    Physics::handleMovement(x, y, velocityX, velocityY);
}

void Player::render(SDL_Renderer* renderer) {  // Popravljeno da se ujema z deklaracijo
    // Tukaj dodajte kodo za risanje igralca z uporabo SDL_Rendererja
    // Za zdaj samo izpis v konzolo za debug namene
    std::cout << "Player at: " << x << "," << y << std::endl;
}

// Odstranite nepotrebne metode, ki niso deklarirane v Player.hpp
// ali pa jih dodajte v header, če jih potrebujete