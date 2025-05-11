#include "Farm.hpp"
#include <cmath>
#include <cstdlib>

Farm::Farm(int maxX, int maxY) : visible(false) {
    x = rand() % maxX;
    y = rand() % maxY;
}

bool Farm::isVisible() const {
    return visible;
}

void Farm::checkProximity(int playerX, int playerY) {
    if (std::abs(playerX - x) <= 5 && std::abs(playerY - y) <= 5) { // Povečana razdalja
        visible = true;
    }
}

bool Farm::activate(int playerX, int playerY) {
    return visible && playerX == x && playerY == y; // Aktivacija, če je igralec na farmi
}