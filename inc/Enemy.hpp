#pragma once
#include <SDL2/SDL.h>

class Enemy {
public:
    Enemy(int x, int y);
    ~Enemy();
    
    void Update();
    void Render(SDL_Renderer* renderer);
    void TakeDamage(int amount);
    bool IsDead() const;

private:
    int x, y;
    int health;
    int damage;
    SDL_Texture* texture;
};