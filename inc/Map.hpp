#pragma once
#include <vector>
#include <string>
#include <memory>
#include "GameObject.hpp"

class Map {
public:
    Map();
    ~Map();
    
    bool loadFromFile(const std::string& filename);
    void update();
    void render(SDL_Renderer* renderer);  // Odstranjeno const
    
    // Dodajte manjkajoče deklaracije metod
    bool isColliding(const GameObject& obj) const;
    bool isSpike(const GameObject& obj) const;
    bool isGoal(const GameObject& obj) const;
    
    int getWidth() const;
    int getHeight() const;
    
private:
    std::vector<std::string> tileMap;
    std::vector<std::unique_ptr<GameObject>> gameObjects;
    int width, height;
};