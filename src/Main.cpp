// src/main.cpp
#include "Game.hpp"
#include <iostream>

int main() {
    Game game;
    if (!game.init()) {
        std::cerr << "Failed to initialize game!" << std::endl;
        return -1;
    }
    
    game.run();
    return 0;
}