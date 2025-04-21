#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <vector>
#include <string>

struct ScoreEntry {
    std::string name;
    int score;
    time_t time;
    int level;
};

class Menu {
public:
    Menu();
    ~Menu();
    
    void HandleEvents(SDL_Event& event);
    void Render(SDL_Renderer* renderer);
    bool StartGame() const;
    
    void AddHighScore(const std::string& name, int score);

private:
    SDL_Texture* background;
    SDL_Texture* titleTexture;
    std::vector<ScoreEntry> highScores;
    bool startGame;
};