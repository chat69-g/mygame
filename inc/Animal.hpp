#pragma once
#include <SDL2/SDL.h>

class Animal {
public:
    Animal(int x, int y);
    virtual ~Animal();
    
    void Update(float deltaTime = 0.0f);  // Dodan privzeti parameter
    void Render(SDL_Renderer* renderer);
    bool CanBeCollected() const;
    int GetValue() const;
    bool IsRescued() const;  // Dodana javna metoda za dostop

protected:
    int x, y;
    bool isRescued;
    SDL_Texture* texture;

private:
    void MoveRandomly();
    int moveCounter;
    int moveDirection;
};