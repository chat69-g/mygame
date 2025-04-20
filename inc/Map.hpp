// include/Map.hpp
#pragma once
#include <vector>
#include <string>
#include <memory>
#include "GameObject.hpp"
#include "Constants.hpp"

class Map {
public:
    Map();
    bool loadFromFile(const std::string& filename);
    void update();
    void render() const;
    
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