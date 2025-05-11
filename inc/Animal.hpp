#pragma once

class Animal {
private:
    int x, y;
    bool rescued;

public:
    Animal(int maxX, int maxY);
    bool isRescued() const;
    void moveRandomly(int maxX, int maxY);
    bool checkRescue(int playerX, int playerY);
    int getX() const { return x; }
    int getY() const { return y; }
};