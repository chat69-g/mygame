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
    std::unique_ptr<Player> player;
    Map* map;
    SDL_Window* window;
    SDL_Renderer* renderer;
};