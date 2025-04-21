// Enemy.cpp
#include "Enemy.hpp"
#include <cmath>

void Enemy::Update(float deltaTime, Vec2 playerPos) {
    // Preprost AI za sledenje igralcu
    Vec2 direction = {
        playerPos.x - position.x,
        playerPos.y - position.y
    };
    
    float distance = sqrt(direction.x*direction.x + direction.y*direction.y);
    
    if(distance < detectionRange && distance > 0) {
        direction.x /= distance;
        direction.y /= distance;
        
        position.x += direction.x * speed * deltaTime;
        position.y += direction.y * speed * deltaTime;
    }
}