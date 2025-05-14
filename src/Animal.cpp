#include "Animal.hpp"
#include <cstdlib>
using namespace std; // Da lahko uporabljamo standardne funkcije brez std::

Animal::Animal(int maxX, int maxY) : rescued(false) {
    // Inicializacija živali na naključnih koordinatah
    x = rand() % maxX;
    y = rand() % maxY;
}

bool Animal::isRescued() const {
    // Preveri, ali je žival rešena
    return rescued;
}

void Animal::moveRandomly(int maxX, int maxY) {
    // Premakni žival na naključno mesto
    x = rand() % maxX;
    y = rand() % maxY;
}

bool Animal::checkRescue(int playerX, int playerY) {
    // Preveri, ali je igralec na isti poziciji kot žival
    if (playerX == x && playerY == y) {
        rescued = true;
        return true;
    }
    return false;
}