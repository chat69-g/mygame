#pragma once
#include <SDL2/SDL.h>

class Animal {
public:
    Animal(int x, int y);
    ~Animal();
    
    void Update();
    void Render(SDL_Renderer* renderer);
    bool CanBeCollected() const;
    bool IsRescued() const;
    int GetValue() const;

    // Dodano za premikanje bika
    void MoveRandomly();

private:
    int x, y;
    bool isRescued;
    SDL_Texture* texture;
    int moveCounter;
    int moveDirection; // 0=gor, 1=desno, 2=dol, 3=levo
};