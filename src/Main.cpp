#define SDL_MAIN_HANDLED

#ifdef _WIN32
#undef main  // Fix for Windows
#endif

#include "Game.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <memory>   // For smart pointers
#include <cmath>    // For math functions

using namespace std;

int main(int /*argc*/, char* /*argv*/[]) {
    // Inicializacija igre
    if (!Game::Instance().Init("My Farm Game", 800, 600)) {
        return -1;  // Napaka pri inicializaciji
    }

    // Poenostavljena glavna zanka
    Game::Instance().Run();

    // Čiščenje
    Game::Instance().Clean();
    return 0;
}