#include "Enemy.hpp"
#include <cmath>
#include <cstdlib>

Enemy::Enemy(int maxX, int maxY) {
    x = rand() % maxX;
    y = rand() % maxY;
}

void Enemy::update(int playerX, int playerY) {
    if (playerX > x) ++x;
    else if (playerX < x) --x;

    if (playerY > y) ++y;
    else if (playerY < y) --y;
}

bool Enemy::isNearPlayer(int playerX, int playerY) const {
    return std::abs(playerX - x) <= 1 && std::abs(playerY - y) <= 1;
}