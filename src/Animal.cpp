#include "Animal.hpp"
#include <cstdlib>

Animal::Animal(int maxX, int maxY) : rescued(false) {
    x = rand() % maxX;
    y = rand() % maxY;
}

bool Animal::isRescued() const {
    return rescued;
}

void Animal::moveRandomly(int maxX, int maxY) {
    x = rand() % maxX;
    y = rand() % maxY;
}

bool Animal::checkRescue(int playerX, int playerY) {
    if (playerX == x && playerY == y) {
        rescued = true;
        return true;
    }
    return false;
}