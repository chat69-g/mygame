#pragma once
#include <SDL2/SDL.h>
#include <memory>
#include "states/State.h"

class Game {
public:
    static Game& getInstance();
    
    void init(const char* title, int width, int height);
    void run();
    void cleanup();
    void changeState(std::unique_ptr<State> newState);

    SDL_Renderer* getRenderer() const { return renderer; }
    SDL_Window* getWindow() const { return window; }

private:
    Game() = default;  // Preprečimo ustvarjanje novega objekta
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    std::unique_ptr<State> currentState;
};