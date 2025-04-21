#pragma once
#include <SDL2/SDL.h>
#include <vector>
#include "Animal.hpp"

class Farm {
public:
    Farm();
    ~Farm();
    
    void Update();
    void Render(SDL_Renderer* renderer);
    void AddAnimal(Animal* animal);
    int CollectAnimals();

private:
    std::vector<Animal*> animals;
    SDL_Texture* texture;
};