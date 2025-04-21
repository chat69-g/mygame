#pragma once
#include <SDL2/SDL.h>

class Player {
public:
    Player();
    ~Player();
    
    void HandleEvent(SDL_Event& event);
    void Update();
    void Render(SDL_Renderer* renderer);
    
    bool IsDead() const;
    void TakeDamage(int amount);

private:
    int x, y;
    int width, height;
    int health;
    int speed;
    SDL_Texture* texture;
};