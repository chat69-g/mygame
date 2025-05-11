#pragma once
#include <SDL2/SDL.h>

class Player {
private:
    int x, y;
    int lives;
    Uint32 lastMoveTime;
    Uint32 speed;

public:
    Player(int maxX, int maxY);
    void update(const Uint8* keyState);
    void move(char direction);
    void loseLife();
    bool isAlive() const;
    int getX() const { return x; }
    int getY() const { return y; }
    bool hasExitedFarm() const;
};