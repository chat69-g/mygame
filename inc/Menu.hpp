#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <vector>
#include <string>

class Menu {
    private:
        SDL_Renderer* renderer;
        TTF_Font* font;
        std::string playerName;
        bool nameEntered;
    
    public:
        Menu(SDL_Renderer* renderer);
        ~Menu();
        void displayMenu();
        void handleInput(SDL_Event& event);
        std::string getPlayerName() const;
        bool isNameEntered() const;
    };