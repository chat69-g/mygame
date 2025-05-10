#include "Enemy.hpp"

Enemy::Enemy(int maxX, int maxY) : active(true) {
    x = rand() % maxX;
    y = rand() % maxY;
}

void Enemy::update(int playerX, int playerY) {
    if (isNearPlayer(playerX, playerY)) {
        if (playerX > x) x++;
        if (playerX < x) x--;
        if (playerY > y) y++;
        if (playerY < y) y--;
    }
}

bool Enemy::isNearPlayer(int playerX, int playerY) const {
    return std::abs(playerX - x) < 10 && std::abs(playerY - y) < 10;
}

void Enemy::render() const {
    std::cout << "Enemy is at (" << x << ", " << y << ")" << std::endl;
}