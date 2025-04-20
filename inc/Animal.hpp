#pragma once
#include "common.hpp"

class Animal {
public:
    Animal(const Vec2& position, int type);
    
    void Update(float deltaTime);
    void Render(SDL_Renderer* renderer);
    void Rescue();
    
    Vec2 position;
    bool isRescued;
    int type;
    
private:
    float rescueTime;
    SDL_Texture* texture;
};