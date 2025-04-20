// src/Map.cpp
#include "Map.hpp"
#include "Player.hpp"
#include <fstream>
#include <iostream>

Map::Map() : width(0), height(0) {}

bool Map::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) return false;
    
    std::string line;
    while (std::getline(file, line)) {
        tileMap.push_back(line);
    }
    
    height = tileMap.size();
    width = height > 0 ? tileMap[0].size() : 0;
    
    // Tukaj bi dodali inicializacijo GameObjectov iz mape
    return true;
}

void Map::update() {
    for (auto& obj : gameObjects) {
        obj->update();
    }
}

void Map::render() const {
    for (const auto& row : tileMap) {
        std::cout << row << std::endl;
    }
}

bool Map::isColliding(const GameObject& obj) const {
    // Implementacija kolizij s tilovimi
    return false;
}

bool Map::isSpike(const GameObject& obj) const {
    // Preverjanje spike tilov
    return false;
}

bool Map::isGoal(const GameObject& obj) const {
    // Preverjanje ciljnih tilov
    return false;
}