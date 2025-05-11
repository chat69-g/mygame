#pragma once

class Enemy {
private:
    int x, y;

public:
    Enemy(int maxX, int maxY);
    void update(int playerX, int playerY);
    bool isNearPlayer(int playerX, int playerY) const;
    int getX() const { return x; }
    int getY() const { return y; }
};