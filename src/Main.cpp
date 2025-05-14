#include "Game.hpp"
#include <SDL2/SDL.h>
#include <iostream> // Dodano za std::cerr in std::endl
using namespace std; // Da lahko uporabljamo standardne funkcije brez std::

int main() {
    // Inicializacija SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        cerr << "Failed to initialize SDL: " << SDL_GetError() << endl;
        return 1;
    }

    // Ustvarimo okno
    SDL_Window* window = SDL_CreateWindow("My Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
    if (!window) {
        cerr << "Failed to create window: " << SDL_GetError() << endl;
        SDL_Quit();
        return 1;
    }

    // Ustvarimo renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer) {
        cerr << "Failed to create renderer: " << SDL_GetError() << endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Inicializacija igre
    Game game(renderer);
    game.run();

    // Počistimo SDL vire
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}