
#include "Enemy.hpp"
#include <cmath>
#include <cstdlib>
#include <iostream>

using namespace std; // Da lahko uporabljamo standardne funkcije brez std::

Enemy::Enemy(int maxX, int maxY) : lastMoveTime(0), speed(300) {
    // Inicializacija nasprotnika na naključnih koordinatah
    x = rand() % maxX;
    y = rand() % maxY;
}

void Enemy::update(int playerX, int playerY) {
    // Posodobi pozicijo nasprotnika glede na igralca
    Uint32 currentTime = SDL_GetTicks();
    if (currentTime > lastMoveTime + speed) {
        if (playerX > x) ++x; // Premik desno proti igralcu
        else if (playerX < x) --x; // Premik levo proti igralcu
        if (playerY > y) ++y; // Premik dol proti igralcu
        else if (playerY < y) --y; // Premik gor proti igralcu
        lastMoveTime = currentTime;
    }
}

bool Enemy::isNearPlayer(int playerX, int playerY) const {
    // Preveri, ali je nasprotnik na isti poziciji kot igralec
    return (x == playerX && y == playerY);
}