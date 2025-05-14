#include "Farm.hpp"
#include <cmath>
#include <cstdlib>
#include <iostream>

Farm::Farm(int maxX, int maxY) : visible(false), exitVisible(false) {
    x = rand() % maxX;
    y = rand() % maxY;
    std::cout << "Farm created at (" << x << ", " << y << ")" << std::endl;
}

bool Farm::activate(int playerX, int playerY) {
    if (visible && playerX == x && playerY == y) {
        std::cout << "Farm activated at (" << x << ", " << y << ")" << std::endl;
        visible = false; // Skrijemo vrata, ko igralec vstopi
        return true;
    }
    return false;
}

void Farm::checkProximity(int playerX, int playerY) {
    // Vrata se prikažejo, ko je igralec na razdalji 5 enote
    if (std::abs(playerX - x) <= 5 && std::abs(playerY - y) <= 5) {
        visible = true;
    }
}
bool Farm::activateExit(int playerX, int playerY) {
    if (exitVisible && playerX == exitX && playerY == exitY) {
        exitVisible = false; // Skrijemo izhod
        return true;
    }
    return false;
}

void Farm::generateExit(int maxX, int maxY, int playerX, int playerY) {
    do {
        exitX = rand() % maxX;
        exitY = rand() % maxY;
    } while (std::abs(exitX - playerX) <= 3 && std::abs(exitY - playerY) <= 3); // Preverimo razdaljo
    exitVisible = true;
}

bool Farm::isVisible() const {
    return visible;
}