#include "Farm.hpp"
#include "TextureManager.hpp"
#include <algorithm> 
#include <SDL2/SDL.h>
#include <memory>

Farm::Farm() {
    texture = TextureManager::getInstance().get("farm");
}

Farm::~Farm() {
    for (auto animal : animals) {
        delete animal;
    }
    animals.clear();
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

void Farm::AddAnimal(int x, int y) {
    animals.push_back(new Animal(x, y));
}

int Farm::CollectAnimals() {
    int collected = 0;
    
    // Uporabi remove-erase idiom kot v GameRPA-13
    animals.erase(
        std::remove_if(animals.begin(), animals.end(),
            [&collected](Animal* animal) {  // Uporabi Animal* namesto Animal&
                if (animal->isReadyForCollection()) {  // Uporabi -> za kazalce
                    collected += animal->getValue();
                    delete animal;  // Pomni zbiranje smeti!
                    return true;
                }
                return false;
            }),
        animals.end());
    
    return collected;
}