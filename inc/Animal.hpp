#pragma once
#include <SDL2/SDL.h>

class Animal {
public:
    Animal(int x, int y, int type);
    ~Animal();
    
    void Update();
    void Render(SDL_Renderer* renderer);
    bool CanBeCollected() const;

private:
    int x, y;
    int type;
    SDL_Texture* texture;
};