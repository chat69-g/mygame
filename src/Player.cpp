#include "Player.hpp"
#include "Physics.hpp"
#include "Constants.hpp"  // Dodano
#include <iostream>       // Dodano za std::cout
#include <SDL2/SDL.h>

Player::Player(float x, float y) 
    : GameObject(x, y, Constants::TILE_SIZE, Constants::TILE_SIZE * 2),
      velocityX(0), velocityY(0),
      facingRight(true), isJumping(false) {}

      void Player::update() {
        // Uporabite manjšo gravitacijo za boljši občutek
        velocityY += 0.2f;  // Namesto Constants::GRAVITY za testiranje
        
        // Limitirajte maksimalno hitrost
        if (velocityY > 10.0f) velocityY = 10.0f;
        
        // Posodobite pozicijo
        x += velocityX;
        y += velocityY;
        
        // Preprost "collision" s spodnjim robom ekrana
        if (y > Constants::SCREEN_HEIGHT - height) {
            y = Constants::SCREEN_HEIGHT - height;
            velocityY = 0;
        }
    }

void Player::render(SDL_Renderer* renderer) {
    SDL_Rect playerRect = {
        static_cast<int>(x),
        static_cast<int>(y),
        static_cast<int>(width),
        static_cast<int>(height)
    };
    
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Rdeča barva
    SDL_RenderFillRect(renderer, &playerRect);
}

bool Player::isGrounded() const {
    // Preverjanje, če je igralec na tleh
    // Vrnite true, če je na tleh, false sicer
    return false;  // Začasna implementacija
}

void Player::jump() {
    if (isGrounded()) {
        velocityY = Constants::JUMP_FORCE;
        isJumping = true;
    }
}

void Player::move(float dx, float dy) {
    velocityX = dx * Constants::PLAYER_SPEED;
    if (dy != 0 && isGrounded()) {
        jump();
    }
}

// Odstranite nepotrebne metode, ki niso deklarirane v Player.hpp
// ali pa jih dodajte v header, če jih potrebujete