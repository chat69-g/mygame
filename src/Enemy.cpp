#include "Enemy.hpp"
#include <cmath>
#include "Game.hpp"

Enemy::Enemy(Vec2 startPos) : position(startPos) {}

void Enemy::Update(float deltaTime, Vec2 playerPos) {
    const Player& player = Game::Instance().GetPlayer();
    Vec2 direction = {
        playerPos.x - position.x,
        playerPos.y - position.y
    };
    
    float length = sqrt(direction.x * direction.x + direction.y * direction.y);
    if (length > 0) {
        direction.x /= length;
        direction.y /= length;
    }
    
    velocity.x = direction.x * speed;
    velocity.y = direction.y * speed;
    
    position.x += velocity.x * deltaTime;
    position.y += velocity.y * deltaTime;
}
