#include "Enemy.hpp"
#include <cmath>
#include <cstdlib>
#include <iostream>

Enemy::Enemy(int maxX, int maxY) : lastMoveTime(0), speed(400) {
    do {
        x = rand() % maxX;
        y = rand() % maxY;
    } while (std::abs(x - maxX / 2) <= 3 && std::abs(y - maxY / 2) <= 3);
    std::cout << "Enemy created at (" << x << ", " << y << ")" << std::endl;
}

void Enemy::update(int playerX, int playerY) {
    Uint32 currentTime = SDL_GetTicks();
    if (currentTime > lastMoveTime + speed) {
        if (playerX > x && x < 39) x++; // Omejitev na 40 stolpcev
        else if (playerX < x && x > 0) x--;
        if (playerY > y && y < 29) y++; // Omejitev na 30 vrstic
        else if (playerY < y && y > 0) y--;
        lastMoveTime = currentTime;
    }
}

bool Enemy::isNearPlayer(int playerX, int playerY) const {
    return std::abs(playerX - x) <= 1 && std::abs(playerY - y) <= 1;
}