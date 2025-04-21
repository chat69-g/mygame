#include "Game.hpp"
#include <SDL2/SDL_image.h>
#include <iostream>
#include <memory>   // For smart pointers
#include <cmath>    // For math functions

using namespace std;

Game& Game::Instance() {
    static Game instance;
    return instance;
}

Game::Game() : isRunning(false), window(nullptr), renderer(nullptr), 
               currentState(GameState::MENU), currentLevel(1) {}

void Game::Init(const char* title, int width, int height) {
    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        cerr << "SDL could not initialize! Error: " << SDL_GetError() << endl;
        return;
    }

    window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, 
                             SDL_WINDOWPOS_CENTERED, width, height, 0);
    if(!window) {
        cerr << "Window could not be created! Error: " << SDL_GetError() << endl;
        return;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(!renderer) {
        cerr << "Renderer could not be created! Error: " << SDL_GetError() << endl;
        return;
    }

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    isRunning = true;

    // Initialize game components
    player = make_unique<Player>();
    map = make_unique<Map>();
    scoreManager = ScoreManager();
    scoreManager.LoadFromFile("scores.json");

    LoadLevel(currentLevel);
}

void Game::HandleEvents() {
    SDL_Event event;
    while(SDL_PollEvent(&event)) {
        if(event.type == SDL_QUIT) {
            isRunning = false;
        }

        if(currentState == GameState::MENU) {
            // Menu handles its own events
            continue;
        }

        if(event.type == SDL_KEYDOWN) {
            switch(event.key.keysym.sym) {
                case SDLK_ESCAPE:
                    if(currentState == GameState::PLAYING) {
                        ChangeState(GameState::PAUSED);
                    } else {
                        ChangeState(GameState::PLAYING);
                    }
                    break;
                case SDLK_F5:
                    SaveGame();
                    break;
                case SDLK_F9:
                    LoadGame();
                    break;
            }
        }
    }

    if(currentState == GameState::PLAYING) {
        player->HandleInput(SDL_GetKeyboardState(nullptr));
    }
}

void Game::Update(float deltaTime) {
    if(currentState != GameState::PLAYING) return;

    levelTime += deltaTime;
    if(levelTime > maxLevelTime) {
        player->score -= 10; // Penalty for taking too long
        levelTime = 0;
    }

    player->Update(deltaTime);
    
    for(auto& enemy : enemies) {
        enemy->Update(deltaTime, *player, *map);
    }

    for(auto& animal : animals) {
        animal->Update(deltaTime);
    }

    for(auto& farm : farms) {
        farm->Update(deltaTime);
    }

    // Check win/lose conditions
    if(player->health <= 0) {
        ChangeState(GameState::GAME_OVER);
    }

    bool allAnimalsRescued = all_of(animals.begin(), animals.end(), 
        [](const unique_ptr<Animal>& a) { return a->isRescued; });
    
    if(allAnimalsRescued) {
        ChangeState(GameState::LEVEL_COMPLETE);
    }
}

void Game::Render() {
    SDL_RenderClear(renderer);

    map->Render(renderer);
    
    for(auto& farm : farms) {
        farm->Render(renderer);
    }
    
    for(auto& animal : animals) {
        animal->Render(renderer);
    }
    
    for(auto& enemy : enemies) {
        enemy->Render(renderer);
    }
    
    player->Render(renderer);

    SDL_RenderPresent(renderer);
}

void Game::Clean() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Game::ChangeState(GameState newState) {
    currentState = newState;
    
    if(newState == GameState::LEVEL_COMPLETE) {
        currentLevel++;
        if(currentLevel > 2) { // Only 2 levels in this example
            // Game completed
            ScoreEntry entry{player->name, player->score, levelTime, currentLevel};
            scoreManager.AddScore(entry);
            scoreManager.SaveToFile("scores.json");
            ChangeState(GameState::MENU);
        } else {
            LoadLevel(currentLevel);
            ChangeState(GameState::PLAYING);
        }
    }
}

void Game::LoadLevel(int level) {
    levelTime = 0;
    maxLevelTime = 120.0f - (level * 20); // Less time for higher levels
    
    map->Generate(level);
    player->position = map->GetRandomWalkablePosition();
    player->health = 3;

    // Clear existing entities
    enemies.clear();
    animals.clear();
    farms.clear();

    // Create enemies based on level
    int enemyCount = 2 + level;
    for(int i = 0; i < enemyCount; i++) {
        Vec2 pos = map->GetRandomWalkablePosition();
        enemies.push_back(make_unique<Enemy>(pos));
    }

    // Create animals to rescue
    int animalCount = 3 + level;
    for(int i = 0; i < animalCount; i++) {
        Vec2 pos = map->GetRandomWalkablePosition();
        animals.push_back(make_unique<Animal>(pos, rand() % 3));
    }

    // Create hidden farms
    int farmCount = 1 + level;
    for(int i = 0; i < farmCount; i++) {
        Vec2 pos = map->GetRandomWalkablePosition();
        farms.push_back(make_unique<Farm>(pos));
    }
}

void Game::SaveGame() {
    // Implementation would save player, map, and entities state
    cout << "Game saved!" << endl;
}

void Game::LoadGame() {
    // Implementation would load saved state
    cout << "Game loaded!" << endl;
}