#include "Animal.hpp"
#include "TextureManager.hpp"
#include <cstdlib>
#include <ctime>

Animal::Animal(int x, int y) : 
    x(x), y(y), isRescued(false), 
    moveCounter(0), moveDirection(0) {
    texture = TextureManager::getInstance().get("bull");
    std::srand(std::time(0));
}

Animal::~Animal() {
    // Texture je upravljan s TextureManagerjem
}

void Animal::Update(float deltaTime) {
    (void)deltaTime;  // Izognemo se opozorilu o neuporabljenem parametru
    MoveRandomly();
}

void Animal::Render(SDL_Renderer* renderer) {
    SDL_Rect destRect = {x, y, 64, 64};
    SDL_RenderCopy(renderer, texture, nullptr, &destRect);
}

void Animal::MoveRandomly() {
    if (moveCounter <= 0) {
        moveDirection = std::rand() % 4;
        moveCounter = 30 + std::rand() % 50;
    }
    
    switch (moveDirection) {
        case 0: y -= 1; break;
        case 1: x += 1; break;
        case 2: y += 1; break;
        case 3: x -= 1; break;
    }
    
    moveCounter--;
}

bool Animal::CanBeCollected() const {
    return !isRescued;
}

int Animal::GetValue() const {
    return 50;
}

bool Animal::IsRescued() const {
    return isRescued;
}