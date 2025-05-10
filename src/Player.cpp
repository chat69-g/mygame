#include "Player.hpp"

Player::Player(int maxX, int maxY) : lives(3) {
    x = rand() % maxX;
    y = rand() % maxY;
}

void Player::move(char direction) {
    switch (direction) {
        case 'w': y--; break;
        case 's': y++; break;
        case 'a': x--; break;
        case 'd': x++; break;
    }
}

void Player::loseLife() {
    lives--;
}

bool Player::isAlive() const {
    return lives > 0;
}

void Player::render() const {
    std::cout << "Player is at (" << x << ", " << y << ") with " << lives << " lives left." << std::endl;
}