#include "Animal.hpp"
#include "TextureManager.hpp"
#include <SDL2/SDL.h>

Animal::Animal(Vec2 position, int value) : 
    position(position), value(value) {}

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

bool Animal::isReadyForCollection() const {
    return rescued;
}

int Animal::getValue() const {
    return value;
}