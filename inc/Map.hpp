#pragma once
#include <vector>  // Dodano
#include <string>  // Dodano
#include <memory>  // Dodano
#include "GameObject.hpp"

class Map {
public:
    Map();
    ~Map();
    
    bool loadFromFile(const std::string& filename);
    void update();
    void render(SDL_Renderer* renderer);
    
private:
    std::vector<std::string> tileMap;
    std::vector<std::unique_ptr<GameObject>> gameObjects;
    int width, height;
};