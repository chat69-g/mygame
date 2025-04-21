#include "Animal.hpp"
#include "Game.hpp"
#include <SDL2/SDL_image.h>
#include <iostream>
#include <cmath>
#include <memory>   // For smart pointers

using namespace std;

Animal::Animal(const Vec2& pos, int type) : 
    position(pos), isRescued(false), type(type), rescueTime(2.0f) {
    
    string paths[] = {
        "assets/animal1.png",
        "assets/animal2.png",
        "assets/animal3.png"
    };
    
    texture = IMG_LoadTexture(Game::Instance().GetRenderer(), paths[type].c_str());
    if(!texture) {
        cerr << "Failed to load animal texture: " << IMG_GetError() << endl;
    }
}

void Animal::Update(float deltaTime) {
    if(isRescued) return;
    
    // Check if player is rescuing this animal
    auto& player = Game::Instance().player;
    float dist = sqrt(pow(player->position.x - position.x, 2) + 
                 pow(player->position.y - position.y, 2));
    
    if(dist < 30.0f) {
        rescueTime -= deltaTime;
        if(rescueTime <= 0) {
            Rescue();
        }
    } else {
        rescueTime = 2.0f; // Reset rescue timer
    }
}

void Animal::Render(SDL_Renderer* renderer) {
    if(isRescued) return;
    
    SDL_Rect dest = {static_cast<int>(position.x), 
                   static_cast<int>(position.y), 32, 32};
    SDL_RenderCopy(renderer, texture, nullptr, &dest);
    
    // Show rescue progress if in progress
    if(rescueTime < 2.0f) {
        SDL_Rect progressBg = {static_cast<int>(position.x), 
                             static_cast<int>(position.y) - 10, 32, 5};
        SDL_Rect progressFg = {static_cast<int>(position.x), 
                             static_cast<int>(position.y) - 10, 
                             static_cast<int>(32 * (1 - rescueTime/2.0f)), 5};
        
        SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
        SDL_RenderFillRect(renderer, &progressBg);
        
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        SDL_RenderFillRect(renderer, &progressFg);
    }
}

void Animal::Rescue() {
    isRescued = true;
    Game::Instance().player->RescueAnimal();
}