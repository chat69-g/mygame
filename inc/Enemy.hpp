#pragma once
#include <SDL2/SDL.h>

class Enemy {
private:
    int x, y;
    Uint32 lastMoveTime; // Čas zadnjega premika
    Uint32 speed;        // Hitrost premikanja v milisekundah

public:
    Enemy(int maxX, int maxY);
    void update(int playerX, int playerY);
    bool isNearPlayer(int playerX, int playerY) const;
    int getX() const { return x; }
    int getY() const { return y; }
};