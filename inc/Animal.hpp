#pragma once

#include <iostream>

class Animal {
private:
    int x, y;
    bool rescued;

public:
    Animal(int maxX, int maxY);
    bool isRescued() const;
    void checkRescue(int playerX, int playerY);
    void render() const;
};