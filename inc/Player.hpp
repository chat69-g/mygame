#pragma once

#include <iostream>

class Player {
private:
    int x, y;
    int lives;
   
public:
    Player(int maxX, int maxY);
    Player() : x(0), y(0), lives(3) {}
    void TakeDamage(int damage);
    void move(char direction);
    void loseLife();
    bool isAlive() const;
    void render() const;
    int getX() const { return x; }
    int getY() const { return y; }
};