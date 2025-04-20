#include "Map.hpp"
#include <fstream>
#include <iostream>
#include "Constants.hpp"

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
    // Implementacija renderiranja z uporabo SDL_Rendererja
    // Tukaj dodajte kodo za risanje mape
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

int Map::getWidth() const { return width; }
int Map::getHeight() const { return height; }