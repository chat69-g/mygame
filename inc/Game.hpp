#pragma once
#include "common.hpp"
#include "Player.hpp"
#include "Enemy.hpp"
#include "Farm.hpp"
#include "ScoreManager.hpp"
#include <vector>
#include <memory>
#include "TextureManager.hpp" 
#include "Menu.hpp" 


class Game {
    public:
        Game();
        static Game& Instance();
        bool Init(const char* title, int width, int height);
        void Run();
        void Update(float deltaTime);
        void Render();
        void Clean();
        bool IsRunning() const;
        Player* GetPlayer();
    
    private:
        static Game* sInstance; // Deklaracija statičnega člana
        Player* player;
        SDL_Window* window;
        SDL_Renderer* renderer;
        bool isRunning;
    };