#pragma once
#include <SDL2/SDL.h>
using namespace std; // Da lahko uporabljamo standardne funkcije brez std::

class Player {
private:
    int x, y; // Koordinate igralca
    int lives; // Število življenj
    Uint32 lastMoveTime; // Čas zadnjega premika
    Uint32 speed; // Hitrost premikanja

public:
    Player(int maxX, int maxY); // Konstruktor za inicializacijo igralca
    void update(const Uint8* keyState); // Posodobi pozicijo igralca glede na tipke
    void move(char direction); // Premakni igralca v določeno smer
    void loseLife(); // Zmanjšaj število življenj
    bool isAlive() const; // Preveri, ali je igralec še živ
    int getX() const { return x; } // Vrni trenutno X koordinato
    int getY() const { return y; } // Vrni trenutno Y koordinato
    bool hasExitedFarm() const; // Preveri, ali je igralec zapustil farmo
};