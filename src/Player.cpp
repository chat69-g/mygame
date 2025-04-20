#include "Player.hpp"
#include "Game.hpp"
#include <SDL2/SDL_image.h>
#include <iostream>  // Add this

using namespace std;


Player::Player() : position{0,0}, velocity{0,0}, health(3), score(0), 
                  currentState(PlayerState::IDLE), speed(200.0f), 
                  attackCooldown(0) {
    // Use GetRenderer()
    texture = IMG_LoadTexture(Game::Instance().GetRenderer(), "assets/player.png");
    if(!texture) {
        cerr << "Failed to load player texture: " << IMG_GetError() << endl;
    }
}

void Player::HandleInput(const Uint8* keystate) {
    velocity = {0,0};
    
    if(keystate[SDL_SCANCODE_W]) velocity.y = -1;
    if(keystate[SDL_SCANCODE_S]) velocity.y = 1;
    if(keystate[SDL_SCANCODE_A]) velocity.x = -1;
    if(keystate[SDL_SCANCODE_D]) velocity.x = 1;
    
    // Normalize diagonal movement
    if(velocity.x != 0 && velocity.y != 0) {
        velocity.x *= 0.7071f;
        velocity.y *= 0.7071f;
    }
    
    if(velocity.x != 0 || velocity.y != 0) {
        currentState = PlayerState::MOVING;
    } else {
        currentState = PlayerState::IDLE;
    }
    
    if(keystate[SDL_SCANCODE_SPACE] && attackCooldown <= 0) {
        currentState = PlayerState::ATTACKING;
        attackCooldown = 0.5f;
    }
}

void Player::Update(float deltaTime) {
    if(attackCooldown > 0) {
        attackCooldown -= deltaTime;
    }
    
    // Move player
    position.x += velocity.x * speed * deltaTime;
    position.y += velocity.y * speed * deltaTime;
    
    // Check bounds
    auto& map = Game::Instance().map;
    if(position.x < 0) position.x = 0;
    if(position.y < 0) position.y = 0;
    if(position.x >= map->width * 32) position.x = map->width * 32 - 1;
    if(position.y >= map->height * 32) position.y = map->height * 32 - 1;
    
    // Check for animal rescue
    if(map->HasAnimalAtPosition(position)) {
        RescueAnimal();
    }
    
    // Check for farm destruction
    if(map->HasFarmAtPosition(position) && currentState == PlayerState::ATTACKING) {
        DestroyFarm();
    }
}

void Player::Render(SDL_Renderer* renderer) {
    SDL_Rect dest = {static_cast<int>(position.x), 
                   static_cast<int>(position.y), 32, 32};
    SDL_RenderCopy(renderer, texture, nullptr, &dest);
}

void Player::TakeDamage(int amount) {
    health -= amount;
    if(health <= 0) {
        currentState = PlayerState::DEAD;
    }
}

void Player::RescueAnimal() {
    score += 100;
    // Mark animal at current position as rescued
    // Implementation would find and update the specific animal
}

void Player::DestroyFarm() {
    score += 50;
    // Mark farm at current position as destroyed
    // Implementation would find and update the specific farm
}