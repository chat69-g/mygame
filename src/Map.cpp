#include "Map.hpp"
#include "TextureManager.hpp"
#include <vector>

Map::Map() {
    // Initialize tile textures
    TextureManager& tm = TextureManager::getInstance();
    for (int i = 0; i < 5; ++i) {
        tileTextures.push_back(tm.get("tile" + std::to_string(i)));
    }

    // Simple map layout (0 = empty, 1-4 = different tiles)
    tiles = {
        {1,1,1,1,1,1,1,1,1,1},
        {1,0,0,0,0,0,0,0,0,1},
        {1,0,2,0,3,0,4,0,0,1},
        {1,0,0,0,0,0,0,0,0,1},
        {1,1,1,1,1,1,1,1,1,1}
    };
}

Map::~Map() {
    // Textures are managed by TextureManager
}

void Map::Render(SDL_Renderer* renderer) {
    const int tileSize = 64;
    for (size_t y = 0; y < tiles.size(); ++y) {
        for (size_t x = 0; x < tiles[y].size(); ++x) {
            int tileType = tiles[y][x];
            if (tileType > 0) {
                SDL_Rect destRect = {
                    static_cast<int>(x) * tileSize,
                    static_cast<int>(y) * tileSize,
                    tileSize,
                    tileSize
                };
                SDL_RenderCopy(renderer, tileTextures[tileType-1], nullptr, &destRect);
            }
        }
    }
}

bool Map::IsWall(int x, int y) const {
    int tileX = x / 64;
    int tileY = y / 64;
    if (tileY >= 0 && tileY < static_cast<int>(tiles.size()) {
        if (tileX >= 0 && tileX < static_cast<int>(tiles[tileY].size())) {
            return tiles[tileY][tileX] != 0;
        }
    }
    return true;
}