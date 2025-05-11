#pragma once
#include <SDL2/SDL.h>       // Za SDL_Renderer
#include <SDL2/SDL_ttf.h>   // Za TTF_Font
#include <vector>
#include <string>

class ScoreManager {
    private:
        std::vector<std::pair<std::string, double>> scores;
    
    public:
        void addScore(const std::string& name, double time);
        void saveScores(const std::string& filename) const;
        void loadScores(const std::string& filename);
        void displayTopScores(SDL_Renderer* renderer, TTF_Font* font) const; // Pravilno definirano
    };