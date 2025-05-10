#include "Farm.hpp"

Farm::Farm(int maxX, int maxY) : visible(false) {
    x = rand() % maxX;
    y = rand() % maxY;
}

bool Farm::isVisible() const {
    return visible;
}

void Farm::checkProximity(int playerX, int playerY) {
    if (std::abs(playerX - x) < 5 && std::abs(playerY - y) < 5) {
        visible = true;
    }
}

void Farm::render() const {
    if (visible) {
        std::cout << "Farm is at (" << x << ", " << y << ")" << std::endl;
    }
}