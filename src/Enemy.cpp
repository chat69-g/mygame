// Enemy.cpp
#include "Enemy.hpp"
#include <cmath>
#include "Game.hpp"

Enemy::Enemy(Vec2 startPos) : position(startPos) {}

void Enemy::Update(float deltaTime) {
    const Player& player = Game::Instance().GetPlayer();
    Vec2 direction = {
        player.position.x - position.x,
        player.position.y - position.y
    };
    
    float distance = std::sqrt(direction.x*direction.x + direction.y*direction.y);
    
    if (distance < detectionRange && distance > 0) {
        direction.x /= distance;
        direction.y /= distance;
        
        position.x += direction.x * speed * deltaTime;
        position.y += direction.y * speed * deltaTime;
    }
}