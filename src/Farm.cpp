
#include "Farm.hpp"
#include <cmath>
#include <cstdlib>
#include <iostream>

using namespace std; // Da lahko uporabljamo standardne funkcije brez std::

Farm::Farm(int maxX, int maxY) : visible(true), exitVisible(false) {
    // Inicializacija farme na naključnih koordinatah
    x = rand() % maxX;
    y = rand() % maxY;
}

void Farm::checkProximity(int playerX, int playerY) {
    // Preveri, ali je igralec blizu farme in jo naredi vidno
    if (abs(playerX - x) <= 3 && abs(playerY - y) <= 3) {
        visible = true;
    }
}

bool Farm::activate(int playerX, int playerY) {
    // Aktiviraj farmo, če je igralec na vratih
    if (visible && playerX == x && playerY == y) {
        visible = false; // Skrij vrata, ko igralec vstopi
        return true;
    }
    return false;
}

void Farm::generateExit(int maxX, int maxY, int playerX, int playerY) {
    // Ustvari izhod na varni razdalji od igralca
    do {
        exitX = rand() % maxX;
        exitY = rand() % maxY;
    } while (abs(exitX - playerX) <= 3 && abs(exitY - playerY) <= 3);
    exitVisible = true;
}
