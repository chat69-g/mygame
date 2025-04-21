#include "Map.hpp"
#include "Game.hpp"
#include <SDL2/SDL_image.h>
#include <iostream>
#include <random>
#include <memory>   // For smart pointers
#include <cmath>    // For math functions

using namespace std;

Map::Map() : width(20), height(15) {
    // Initialize tiles
    tiles.resize(height, vector<Tile>(width));
    
    // Load textures
    for(int i = 0; i < 5; i++) {
        string path = "assets/tile" + to_string(i) + ".png";
        tileTextures[i] = IMG_LoadTexture(Game::Instance().GetRenderer(), path.c_str());
        if(!tileTextures[i]) {
            cerr << "Failed to load tile texture " << i << ": " << IMG_GetError() << endl;
        }
    }
}

Map::~Map() {
    for(auto tex : tileTextures) {
        if(tex) SDL_DestroyTexture(tex);
    }
}

void Map::Generate(int level) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, 100);
    
    width = 15 + (level * 5);
    height = 10 + (level * 3);
    tiles.resize(height, vector<Tile>(width));
    
    for(int y = 0; y < height; y++) {
        for(int x = 0; x < width; x++) {
            int roll = dis(gen);
            tiles[y][x].type = (roll < 80) ? 0 : (roll < 90) ? 1 : 2;
            tiles[y][x].walkable = (tiles[y][x].type != 2);
            tiles[y][x].hasFarm = false;
            tiles[y][x].hasAnimal = false;
        }
    }
    
    // Ensure path from start to exit
    for(int y = 1; y < height-1; y++) {
        tiles[y][1].type = 0;
        tiles[y][1].walkable = true;
    }
}

void Map::Render(SDL_Renderer* renderer) {
    for(int y = 0; y < height; y++) {
        for(int x = 0; x < width; x++) {
            SDL_Rect dest = {x * 32, y * 32, 32, 32};
            SDL_RenderCopy(renderer, tileTextures[tiles[y][x].type], nullptr, &dest);
        }
    }
}

Vec2 Map::GetRandomWalkablePosition() const {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> xdis(0, width-1);
    uniform_int_distribution<> ydis(0, height-1);
    
    while(true) {
        int x = xdis(gen);
        int y = ydis(gen);
        if(tiles[y][x].walkable) {
            return {static_cast<float>(x * 32), static_cast<float>(y * 32)};
        }
    }
}

bool Map::IsPositionWalkable(const Vec2& pos) const {
    int x = static_cast<int>(pos.x) / 32;
    int y = static_cast<int>(pos.y) / 32;
    if(x < 0 || y < 0 || x >= width || y >= height) return false;
    return tiles[y][x].walkable;
}

bool Map::HasFarmAtPosition(const Vec2& pos) const {
    int x = static_cast<int>(pos.x) / 32;
    int y = static_cast<int>(pos.y) / 32;
    if(x < 0 || y < 0 || x >= width || y >= height) return false;
    return tiles[y][x].hasFarm;
}

bool Map::HasAnimalAtPosition(const Vec2& pos) const {
    int x = static_cast<int>(pos.x) / 32;
    int y = static_cast<int>(pos.y) / 32;
    if(x < 0 || y < 0 || x >= width || y >= height) return false;
    return tiles[y][x].hasAnimal;
}