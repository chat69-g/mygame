#pragma once

#include <iostream>
#include <cmath>

class Enemy {
private:
    int x, y;
    bool active;

public:
    Enemy(int maxX, int maxY);
    void update(int playerX, int playerY);
    bool isNearPlayer(int playerX, int playerY) const;
    void render() const;
    int getX() const { return x; }
    int getY() const { return y; }
};