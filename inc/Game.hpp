#pragma once
#include "common.hpp"
#include "Player.hpp"
#include "Enemy.hpp"
#include "Farm.hpp"
#include "ScoreManager.hpp"
#include <vector>
#include <memory>

class Game {
    public:
        static Game& Instance();
        
        bool Init(const char* title, int width, int height);
        void Run();
        void Clean();
        
        SDL_Renderer* GetRenderer() const { return renderer; }
        void ChangeState(GameState newState);
        
        // Dodane metode za upravljanje igralca in nasprotnikov
        Player& GetPlayer() { return player; }
        const std::vector<Enemy>& GetEnemies() const { return enemies; }
        
    private:
        Game();
        void HandleEvents();
        void Update(float deltaTime);
        void Render();
        void LoadLevel(int level);
        
        SDL_Window* window = nullptr;
        SDL_Renderer* renderer = nullptr;
        bool isRunning = false;
        GameState currentState = GameState::MENU;
        
        Player player;
        std::vector<Enemy> enemies;
        std::vector<std::unique_ptr<Farm>> farms;
        ScoreManager scoreManager;
    };