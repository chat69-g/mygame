// Farm.cpp
#include "Farm.hpp"
#include "Game.hpp"

Farm::Farm(Vec2 position) : position(position) {
    // Naključno določi ali vsebuje glavnega bika
    if(rand() % 3 == 0) { // 33% verjetnost
        animals.push_back(new Animal(position, 2)); // Tip 2 = glavni bik
    } else {
        animals.push_back(new Animal(position, 1)); // Običajna žival
    }
}

void Farm::Update(float deltaTime, const Vec2& playerPos) {
    // Preveri razdaljo do igralca
    float dist = sqrt(pow(playerPos.x - position.x, 2) + 
                pow(playerPos.y - position.y, 2));
    if(dist < discoveryRadius) {
        isDiscovered = true;
    }
}

void Farm::Render(SDL_Renderer* renderer) {
    if(isDiscovered) {
        // Uporabite parameter renderer namesto Game::Instance().GetRenderer()
        SDL_Rect farmRect = {position.x, position.y, 64, 64};
        SDL_SetRenderDrawColor(renderer, 139, 69, 19, 255); // Rjava barva
        SDL_RenderFillRect(renderer, &farmRect);
    }
}