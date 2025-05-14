#pragma once
#include <SDL2/SDL.h>
using namespace std; // Da lahko uporabljamo standardne funkcije brez std::

class Enemy {
private:
    int x, y; // Koordinate nasprotnika
    Uint32 lastMoveTime; // Čas zadnjega premika
    Uint32 speed; // Hitrost premikanja

public:
    Enemy(int maxX, int maxY); // Konstruktor za inicializacijo nasprotnika
    void update(int playerX, int playerY); // Posodobi pozicijo nasprotnika glede na igralca
    bool isNearPlayer(int playerX, int playerY) const; // Preveri, ali je nasprotnik blizu igralca
    int getX() const { return x; } // Vrni trenutno X koordinato
    int getY() const { return y; } // Vrni trenutno Y koordinato
};