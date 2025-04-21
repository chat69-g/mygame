#include "Animal.hpp"
#include "TextureManager.hpp"

Animal::Animal(int x, int y, int type) : x(x), y(y), type(type) {
    texture = TextureManager::getInstance().get(type == 1 ? "animal1" : "animal3");
}

Animal::~Animal() {
    // Texture managed by TextureManager
}

void Animal::Update() {
    // Random movement would go here
}

void Animal::Render(SDL_Renderer* renderer) {
    SDL_Rect destRect = {x, y, 40, 40};
    SDL_RenderCopy(renderer, texture, nullptr, &destRect);
}

bool Animal::CanBeCollected() const {
    return true; // Additional conditions would go here
}