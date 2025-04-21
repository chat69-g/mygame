#pragma once
#include <SDL2/SDL.h>
#include <vector>

class Map {
public:
    Map();
    ~Map();
    
    void Render(SDL_Renderer* renderer);
    bool IsWall(int x, int y) const;

private:
    std::vector<std::vector<int>> tiles;
    std::vector<SDL_Texture*> tileTextures;
};