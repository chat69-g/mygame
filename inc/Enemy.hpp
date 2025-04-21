#pragma once
#include "common.hpp"
#include "Vec2.hpp"

class Enemy {
public:
    Enemy(Vec2 startPos);
    void Update(float deltaTime, Vec2 playerPos);
    void Render(SDL_Renderer* renderer);
    Vec2 GetPosition() const;

private:
    Vec2 position;
    Vec2 velocity;
    float speed = 120.0f;
    float detectionRange = 300.0f;
};