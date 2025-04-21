#include "Animal.hpp"
#include "TextureManager.hpp"
#include <cstdlib>
#include <ctime>

Animal::Animal(int x, int y) : 
    x(x), y(y), isRescued(false), moveCounter(0), moveDirection(0) {
    texture = TextureManager::getInstance().get("bull"); // Preimenujte sliko v bull.png
    std::srand(std::time(0));
}

Animal::~Animal() {
    // Texture je upravljan s TextureManagerjem
}

void Animal::Update() {
    MoveRandomly();
}

void Animal::Render(SDL_Renderer* renderer) {
    SDL_Rect destRect = {x, y, 64, 64}; // Večja velikost za bika
    SDL_RenderCopy(renderer, texture, nullptr, &destRect);
}

void Animal::MoveRandomly() {
    if (moveCounter <= 0) {
        moveDirection = std::rand() % 4;
        moveCounter = 30 + std::rand() % 50;
    }
    
    switch (moveDirection) {
        case 0: y -= 1; break; // Gor
        case 1: x += 1; break; // Desno
        case 2: y += 1; break; // Dol
        case 3: x -= 1; break; // Levo
    }
    
    moveCounter--;
}

bool Animal::CanBeCollected() const {
    return !isRescued;
}

bool Animal::IsRescued() const {
    return isRescued;
}

int Animal::GetValue() const {
    return 50; // Vrednost bika
}