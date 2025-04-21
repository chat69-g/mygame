// Enemy.cpp
#include "Enemy.hpp"
#include <cmath>

void Enemy::Update(float deltaTime, Vec2 playerPos) {
    // Izračunaj smer do igralca
    Vec2 direction = {
        playerPos.x - position.x,
        playerPos.y - position.y
    };
    
    float distance = sqrt(direction.x*direction.x + direction.y*direction.y);
    
    // Če je igralec v dosegu, zasleduj
    if(distance < detectionRange) {
        if(distance > 0) {
            direction.x /= distance;
            direction.y /= distance;
        }
        
        position.x += direction.x * speed * deltaTime;
        position.y += direction.y * speed * deltaTime;
    }
}