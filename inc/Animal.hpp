#pragma once
using namespace std; // Da lahko uporabljamo standardne funkcije brez std::

class Animal {
private:
    int x, y; // Koordinate živali
    bool rescued; // Ali je žival rešena

public:
    Animal(int maxX, int maxY); // Konstruktor za inicializacijo živali
    bool isRescued() const; // Preveri, ali je žival rešena
    void moveRandomly(int maxX, int maxY); // Premakni žival na naključno mesto
    bool checkRescue(int playerX, int playerY); // Preveri, ali je igralec rešil žival
    int getX() const { return x; } // Vrni trenutno X koordinato
    int getY() const { return y; } // Vrni trenutno Y koordinato
};