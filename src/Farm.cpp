#include "Farm.hpp"
#include "TextureManager.hpp"
#include <algorithm> 
#include <SDL2/SDL.h>

Farm::Farm() {
    texture = TextureManager::getInstance().get("farm");
}

Farm::~Farm() {
    for (auto animal : animals) {
        delete animal;
    }
}

void Farm::Update() {
    for (auto animal : animals) {
        animal->Update();
    }
}

void Farm::Render(SDL_Renderer* renderer) {
    SDL_Rect destRect = {400, 300, 200, 200};
    SDL_RenderCopy(renderer, texture, nullptr, &destRect);
    
    for (auto animal : animals) {
        animal->Render(renderer);
    }
}

void Farm::AddAnimal(Animal* animal) {
    animals.push_back(animal);
}

int Farm::CollectAnimals() {
    int collected = 0;
    
    // Uporabi std::remove_if iz algorithm
    auto it = std::remove_if(animals.begin(), animals.end(),
        [&collected](Animal& animal) {
            if (animal.IsReadyForCollection()) {
                collected += animal.GetValue();
                return true;
            }
            return false;
        });
    
    animals.erase(it, animals.end());
    return collected;
}