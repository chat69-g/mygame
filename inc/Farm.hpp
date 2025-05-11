#pragma once

class Farm {
private:
    int x, y;
    bool visible;

public:
    Farm(int maxX, int maxY);
    bool isVisible() const;
    void checkProximity(int playerX, int playerY);
    bool activate(int playerX, int playerY);
    int getX() const { return x; }
    int getY() const { return y; }
};