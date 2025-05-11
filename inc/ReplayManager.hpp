#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <vector>
#include <string>

class ReplayManager {
private:
    std::vector<std::pair<int, int>> movements;

public:
    void recordMovement(int x, int y);
    void saveReplay(const std::string& filename) const;
    void loadReplay(const std::string& filename);
    void displayReplay(SDL_Renderer* renderer, TTF_Font* font) const; // Posodobljeno
};