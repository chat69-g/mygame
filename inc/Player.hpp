#pragma once

#include <iostream>

class Player {
private:
    int x, y;
    int lives;

public:
    Player(int maxX, int maxY);
    void move(char direction);
    void loseLife();
    bool isAlive() const;
    void render() const;
};