#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <vector>
#include <string>

class Menu {
    private:
        std::string playerName;
        bool nameEntered;
    
    public:
        Menu();
        void displayMenu();
        void handleInput();
        std::string getPlayerName() const;
        bool isNameEntered() const;
    };