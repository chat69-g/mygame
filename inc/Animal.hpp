#pragma once
#include "common.hpp"

class Animal {
public:
    Animal(Vec2 position, int value);
    
    bool isReadyForCollection() const;  // camelCase po vzoru GameRPA-13
    int getValue() const;               // camelCase po vzoru GameRPA-13
    void update(float deltaTime);
    void render(SDL_Renderer* renderer);
    
    Vec2 position;
    bool rescued = false;
    
private:
    int value;
    float rescueTime = 0.0f;
    float rescueDuration = 2.0f;  // 2 sekunde za rešitev
};