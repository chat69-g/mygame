#include "Enemy.hpp"
#include <cmath>
#include <cstdlib>

Enemy::Enemy(int maxX, int maxY) : lastMoveTime(0), speed(400) { // Hitrost: 400 ms
    do {
        x = rand() % maxX;
        y = rand() % maxY;
    } while (std::abs(x - maxX / 2) <= 3 && std::abs(y - maxY / 2) <= 3); // Preverimo razdaljo
}

void Enemy::update(int playerX, int playerY) {
    Uint32 currentTime = SDL_GetTicks();
    if (currentTime - lastMoveTime < speed) {
        return; // Nasprotnik se premakne le, če je preteklo dovolj časa
    }
    lastMoveTime = currentTime;

    if (playerX > x) ++x;
    else if (playerX < x) --x;

    if (playerY > y) ++y;
    else if (playerY < y) --y;
}

bool Enemy::isNearPlayer(int playerX, int playerY) const {
    return std::abs(playerX - x) <= 1 && std::abs(playerY - y) <= 1;
}