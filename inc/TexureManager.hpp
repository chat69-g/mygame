#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <map>
#include <string>
#include <iostream>

class TextureManager {
public:
    static TextureManager& getInstance() {
        static TextureManager instance;
        return instance;
    }

    // Prepoved kopiranja
    TextureManager(const TextureManager&) = delete;
    void operator=(const TextureManager&) = delete;

    bool load(const std::string& id, const std::string& path, SDL_Renderer* renderer);
    SDL_Texture* get(const std::string& id) const;
    void clean();

private:
    TextureManager() {}
    std::map<std::string, SDL_Texture*> textures;
};