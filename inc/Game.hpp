#pragma once
#include "common.hpp"
#include "Player.hpp"
#include "Map.hpp"
#include "Enemy.hpp"
#include "Animal.hpp"
#include "Farm.hpp"
#include "Score.hpp"
#include <vector>

class Game {
public:
    static Game& Instance();
    
    TextureManager& textureManager;

    void Init(const char* title, int width, int height);
    void HandleEvents();
    void Update(float deltaTime);
    void Render();
    void Clean();
    bool Running() const { return isRunning; }
    
    void ChangeState(GameState newState);
    void LoadLevel(int level);
    void SaveGame();
    void LoadGame();

    SDL_Renderer* GetRenderer() const { return renderer; }
    
    // Game components
    std::unique_ptr<Player> player;
    std::unique_ptr<Map> map;
    std::vector<std::unique_ptr<Enemy>> enemies;
    std::vector<std::unique_ptr<Animal>> animals;
    std::vector<std::unique_ptr<Farm>> farms;
    
private:
    Game();
    ~Game() = default;
    
    bool isRunning;
    SDL_Window* window;
    SDL_Renderer* renderer;
    GameState currentState;
    int currentLevel;
    float levelTime;
    float maxLevelTime;
    ScoreManager scoreManager;
};