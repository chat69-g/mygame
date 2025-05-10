#pragma once

#include <iostream>
#include <cmath>

class Farm {
private:
    int x, y; // Lokacija farme
    bool visible; // Ali je farma vidna

public:
    Farm(int maxX, int maxY);
    bool isVisible() const;
    void checkProximity(int playerX, int playerY);
    void render() const;
    bool HasMainBull() const;
    std::vector<Animal> GetAnimals() const;
};