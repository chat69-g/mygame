#include "Game.h"
#include "states/MenuState.h"

Game& Game::getInstance() {
    static Game instance;
    return instance;
}

void Game::init(const char* title, int width, int height) {
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, 
                            SDL_WINDOWPOS_CENTERED, width, height, 0);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    changeState(std::make_unique<MenuState>());
}

void Game::run() {
    Uint32 lastTime = SDL_GetTicks();
    while (currentState) {
        // Delta time za gladke animacije
        Uint32 currentTime = SDL_GetTicks();
        float deltaTime = (currentTime - lastTime) / 1000.0f;
        lastTime = currentTime;

        currentState->handleEvents();
        currentState->update(deltaTime);
        currentState->render();
    }
}