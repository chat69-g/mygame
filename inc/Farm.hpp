#pragma once

class Farm {
private:
    int x, y;
    bool visible;
    int exitX, exitY; // Koordinate izhoda
    bool exitVisible; // Ali je izhod viden

public:
    Farm(int maxX, int maxY);
    bool isVisible() const;
    void checkProximity(int playerX, int playerY);
    bool activate(int playerX, int playerY);
    int getX() const { return x; }
    int getY() const { return y; }
    bool activateExit(int playerX, int playerY);
    void generateExit(int maxX, int maxY, int playerX, int playerY);
    bool isExitVisible() const { return exitVisible; }
    int getExitX() const { return exitX; }
    int getExitY() const { return exitY; }
};