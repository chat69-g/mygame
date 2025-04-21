#include "Farm.hpp"
#include "TextureManager.hpp"
#include <algorithm> 

Farm::Farm() {
    texture = TextureManager::getInstance().get("farm");
}

void Farm::Update() {
    for (auto animal : animals) {
        animal->Update();  // Sedaj lahko kličemo brez parametra
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
    animals.erase(std::remove_if(animals.begin(), animals.end(),
        [&collected](Animal* a) {
            if (a->CanBeCollected()) {  // Uporabimo CanBeCollected namesto IsRescued
                collected += a->GetValue();  // Popravljeno iz GetScoreValue
                delete a;
                return true;
            }
            return false;
        }), animals.end());
    return collected;
}

Farm::~Farm() {
    for (auto animal : animals) {
        delete animal;
    }
    animals.clear();
}