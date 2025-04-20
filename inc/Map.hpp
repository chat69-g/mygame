#pragma once
#include "common.hpp"
#include <vector>
#include <string>

struct Tile {
    int type;
    bool walkable;
    bool hasFarm;
    bool hasAnimal;
};

class Map {
public:
    Map();
    ~Map();
    
    void Generate(int level);
    void Render(SDL_Renderer* renderer);
    Vec2 GetRandomWalkablePosition() const;
    bool IsPositionWalkable(const Vec2& pos) const;
    bool HasFarmAtPosition(const Vec2& pos) const;
    bool HasAnimalAtPosition(const Vec2& pos) const;
    
    int width;
    int height;
    std::vector<std::vector<Tile>> tiles;
    
private:
    void LoadFromFile(const std::string& filename);
    void GenerateProcedural(int level);
    SDL_Texture* tileTextures[5];
};