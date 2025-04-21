#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "TextureManager.hpp"

class Player;
class Map;
class Menu;

class Game {
public:
    enum GameState { MENU, PLAYING, GAME_OVER };
    
    static Game& Instance();
    
    bool Init(const char* title, int width, int height);
    void Run();
    void Clean();
    void Reset();  // Dodana deklaracija za Reset
    
    SDL_Renderer* GetRenderer() const;
    bool IsRunning() const;

private:
    Game();
    ~Game();

    void HandleEvents();
    void Update();
    void Render();
    void RenderGameOver();

    static Game* sInstance;
    SDL_Window* window;
    SDL_Renderer* renderer;
    bool isRunning;
    GameState currentState;
    
    TextureManager& textureManager;
    Player* player;
    Map* map;
    Menu* menu;
    float currentLevelTime = 0.0f;
    const float levelTimeLimit = 120.0f; // 2 minuti
    int currentLevel = 1;
    std::string playerName;
    
    // Sistemi
    ScoreManager scoreManager;
    ReplaySystem replaySystem;
    Menu menu;
    
    // Komponente
    std::vector<Enemy> enemies;
    std::vector<std::unique_ptr<Farm>> farms;
    
    // Pomožne metode
    void SaveReplayFrame();
    void CheckLevelCompletion();
    void RenderUI();
    void RenderPauseMenu();
    void RenderGameOver();
    void RenderLevelComplete();
    void LoadLevel(int level);
    
};