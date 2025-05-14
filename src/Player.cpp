#include "Player.hpp"
#include <cstdlib>

Player::Player(int maxX, int maxY) : lives(3), lastMoveTime(0), speed(200) {
    x = rand() % maxX;
    y = rand() % maxY;
    if (x < 0) x = 0;
    if (y < 0) y = 0;
    if (x >= maxX) x = maxX - 1;
    if (y >= maxY) y = maxY - 1;
}

void Player::update(const Uint8* keyState) {
    Uint32 currentTime = SDL_GetTicks();
    if (currentTime - lastMoveTime < speed) {
        return;
    }
    lastMoveTime = currentTime;

    if (keyState[SDL_SCANCODE_W] && y > 0) --y;
    if (keyState[SDL_SCANCODE_S] && y < 29) ++y; // Omejitev na 30 vrstic
    if (keyState[SDL_SCANCODE_A] && x > 0) --x;
    if (keyState[SDL_SCANCODE_D] && x < 39) ++x; // Omejitev na 40 stolpcev
}

void Player::move(char direction) {
    switch (direction) {
        case 'w': --y; break;
        case 's': ++y; break;
        case 'a': --x; break;
        case 'd': ++x; break;
    }
}

void Player::loseLife() {
    if (lives > 0) {
        --lives;
    }
}

bool Player::isAlive() const {
    return lives > 0;
}

bool Player::hasExitedFarm() const {
    return x < 0 || y < 0 || x >= 40 || y >= 30;
}