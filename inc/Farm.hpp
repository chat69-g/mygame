
#pragma once

using namespace std; // Da lahko uporabljamo standardne funkcije brez std::

class Farm {
private:
    int x, y; // Koordinate farme
    int exitX, exitY; // Koordinate izhoda
    bool visible; // Ali so vrata farme vidna
    bool exitVisible; // Ali je izhod viden

public:
    Farm(int maxX, int maxY); // Konstruktor za inicializacijo farme
    void checkProximity(int playerX, int playerY); // Preveri, ali je igralec blizu farme
    bool activate(int playerX, int playerY); // Aktiviraj farmo, če je igralec na vratih
    void generateExit(int maxX, int maxY, int playerX, int playerY); // Ustvari izhod na varni razdalji od igralca
    bool isVisible() const { return visible; } // Preveri, ali so vrata farme vidna
    bool isExitVisible() const { return exitVisible; } // Preveri, ali je izhod viden
    int getX() const { return x; } // Vrni trenutno X koordinato farme
    int getY() const { return y; } // Vrni trenutno Y koordinato farme
    int getExitX() const { return exitX; } // Vrni trenutno X koordinato izhoda
    int getExitY() const { return exitY; } // Vrni trenutno Y koordinato izhoda
};