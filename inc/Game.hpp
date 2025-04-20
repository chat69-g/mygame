// include/Game.hpp
#pragma once
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
    void handleInput();
    void update();
    void render();
    
    bool running;
    Player* player;
    Map* map;
};