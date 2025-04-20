#pragma once
#include <memory>
#include <SDL2/SDL.h>
#include "Player.hpp"
#include "Map.hpp"

class Game {
public:
    Game();
    ~Game();
    
    bool init();
    void run();
    void cleanup();
    
private:
    void handleEvents();
    void update();
    void render();
    
    bool running;
    SDL_Window* window;      // Premaknjeno navzgor
    SDL_Renderer* renderer;  // Premaknjeno navzgor
    Map* map;
    std::unique_ptr<Player> player;
};