#pragma once
#include "common.hpp"
#include "Map.hpp"
#include <vector>

class Player;  // Forward declaration

class Enemy {
public:
    Enemy(const Vec2& startPos);
    
    void Update(float deltaTime, const Player& player, const Map& map);
    void Render(SDL_Renderer* renderer);
    void AttackPlayer(Player& player);
    
    Vec2 position;
    Vec2 velocity;
    int health;
    bool isActive;
    
private:
    void CalculatePath(const Vec2& target, const Map& map);  // Added Map parameter
    void MoveAlongPath(float deltaTime);
    
    float speed;
    float attackRange;
    float detectionRange;
    std::vector<Vec2> currentPath;
    SDL_Texture* texture;
};