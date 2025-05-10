#include "Animal.hpp"

Animal::Animal(int maxX, int maxY) : rescued(false) {
    x = rand() % maxX;
    y = rand() % maxY;
}

bool Animal::isRescued() const {
    return rescued;
}

void Animal::checkRescue(int playerX, int playerY) {
    if (playerX == x && playerY == y) {
        rescued = true;
    }
}

void Animal::render() const {
    if (!rescued) {
        std::cout << "Animal is at (" << x << ", " << y << ")" << std::endl;
    } else {
        std::cout << "Animal has been rescued!" << std::endl;
    }
}