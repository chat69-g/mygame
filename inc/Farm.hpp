// Farm.hpp
#pragma once
#include "common.hpp"
#include "Animal.hpp"
#include <vector>

class Farm {
public:
    Farm(Vec2 position);
    void Update(float deltaTime, const Vec2& playerPos);
    void Render(SDL_Renderer* renderer);
    bool IsDiscovered() const;
    bool HasMainBull() const;
    std::vector<Animal*>& GetAnimals();

private:
    Vec2 position;
    bool isDiscovered = false;
    std::vector<Animal*> animals;
    float discoveryRadius = 200.0f;
};