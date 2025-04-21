#include "TextureManager.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

bool TextureManager::load(const std::string& id, const std::string& path, SDL_Renderer* renderer) {
    std::string fullPath = "../assets/images/" + path;
    SDL_Texture* texture = IMG_LoadTexture(renderer, fullPath.c_str());
    
    if (!texture) {
        std::cerr << "Failed to load texture " << id << " from " << fullPath 
                  << ": " << IMG_GetError() << std::endl;
        return false;
    }

    textures[id] = texture;
    return true;
}

SDL_Texture* TextureManager::get(const std::string& id) const {
    auto it = textures.find(id);
    if (it == textures.end()) {
        std::cerr << "Texture " << id << " not found!" << std::endl;
        return nullptr;
    }
    return it->second;
}

void TextureManager::clean() {
    for (auto& pair : textures) {
        SDL_DestroyTexture(pair.second);
    }
    textures.clear();
}