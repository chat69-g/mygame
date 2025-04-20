#include "Map.hpp"
#include <fstream>
#include <iostream>
#include "Constants.hpp"
#include <SDL2/SDL.h>

Map::Map() : width(0), height(0) {}

Map::~Map() {
    // Čiščenje virov, če je potrebno
}

bool Map::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open map file: " << filename << std::endl;
        return false;
    }
    
    std::string line;
    while (std::getline(file, line)) {
        tileMap.push_back(line);
    }
    
    height = tileMap.size();
    width = height > 0 ? tileMap[0].size() : 0;
    
    return true;
}

void Map::render(SDL_Renderer* renderer) {
    // Preverimo, ali imamo veljavno mapo in renderer
    if (!renderer || tileMap.empty()) return;

    // Risanje vseh elementov mape
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            SDL_Rect tileRect = {
                x * Constants::TILE_SIZE,
                y * Constants::TILE_SIZE,
                Constants::TILE_SIZE,
                Constants::TILE_SIZE
            };

            switch (tileMap[y][x]) {
                case Constants::WALL:  // Stene
                    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // Bela
                    SDL_RenderFillRect(renderer, &tileRect);
                    break;
                    
                case Constants::GOAL:  // Cilj
                    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // Zelena
                    SDL_RenderFillRect(renderer, &tileRect);
                    break;
                    
                case Constants::SPIKE:  // Ostrije (če so v vaši igri)
                    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Rdeča
                    SDL_RenderFillRect(renderer, &tileRect);
                    break;
                    
                case Constants::PLATFORM:  // Platforme (če so v vaši igri)
                    SDL_SetRenderDrawColor(renderer, 139, 69, 19, 255); // Rjava
                    SDL_RenderFillRect(renderer, &tileRect);
                    break;
                    
                // Dodajte dodatne tipe tilov po potrebi
            }
        }
    }

    // Risanje vseh GameObjectov na mapi
    for (const auto& obj : gameObjects) {
        obj->render(renderer);
    }
}

bool Map::isColliding(const GameObject& obj) const {
    // Implementacija preverjanja trkov
    return false;
}

bool Map::isSpike(const GameObject& obj) const {
    // Implementacija preverjanja, če je objekt na spike ploščici
    return false;
}

bool Map::isGoal(const GameObject& obj) const {
    // Implementacija preverjanja, če je objekt na cilju
    return false;
}

void Map::update() {
    // Implementacija posodabljanja mape
    // Na primer: posodabljanje premikajočih se objektov
}

int Map::getWidth() const { return width; }
int Map::getHeight() const { return height; }
