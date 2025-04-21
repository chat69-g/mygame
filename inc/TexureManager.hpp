#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <map>
#include <string>

class TextureManager {
public:
    static TextureManager& getInstance();
    
    bool load(const std::string& id, const std::string& path, SDL_Renderer* renderer);
    SDL_Texture* get(const std::string& id) const;
    void clean();

    TextureManager(const TextureManager&) = delete;
    void operator=(const TextureManager&) = delete;

private:
    TextureManager() = default;
    std::map<std::string, SDL_Texture*> textures;
};