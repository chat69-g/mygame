#pragma once
#include "common.hpp"
#include "Score.hpp"
#include <string>
#include <vector>

struct MenuItem {
    std::string text;
    SDL_Rect rect;
    bool isSelected;
};

class Menu {
public:
    Menu();
    
    void HandleEvents(SDL_Event& event);
    void Render(SDL_Renderer* renderer);
    void AddHighScore(const std::string& name, int score);
    
    std::string playerName;
    bool startGame;
    bool loadGame;
    bool showHighScores;
    bool exitGame;
    
private:
    void RenderHighScores(SDL_Renderer* renderer);
    
    std::vector<MenuItem> mainMenuItems;
    std::vector<ScoreEntry> highScores;
    SDL_Texture* background;
    SDL_Texture* titleTexture;
};