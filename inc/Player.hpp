#pragma once
#include "common.hpp"
#include <string>

enum class PlayerState {
    IDLE,
    MOVING,
    ATTACKING,
    RESCUING,
    DEAD
};

class Player {
public:
    Player();
    
    void HandleInput(const Uint8* keystate);
    void Update(float deltaTime);
    void Render(SDL_Renderer* renderer);
    
    void TakeDamage(int amount);
    void RescueAnimal();
    void DestroyFarm();
    
    Vec2 position;
    Vec2 velocity;
    int health;
    int score;
    std::string name;
    PlayerState currentState;
    
private:
    float speed;
    float attackCooldown;
    SDL_Texture* texture;
};