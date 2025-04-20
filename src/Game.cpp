#include "Game.hpp"
#include <iostream>  // Dodano
#include <memory>    // Dodano
#include "Constants.hpp"

Game::Game() : running(false), window(nullptr), renderer(nullptr), map(nullptr) {}

bool Game::init() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! Error: " << SDL_GetError() << std::endl;
        return false;
    }
    
    window = SDL_CreateWindow(Constants::WINDOW_TITLE,
                            SDL_WINDOWPOS_CENTERED,
                            SDL_WINDOWPOS_CENTERED,
                            Constants::SCREEN_WIDTH,
                            Constants::SCREEN_HEIGHT,
                            SDL_WINDOW_SHOWN);
    
    if (!window) {
        std::cerr << "Window could not be created! Error: " << SDL_GetError() << std::endl;
        return false;
    }
    
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << "Renderer could not be created! Error: " << SDL_GetError() << std::endl;
        return false;
    }
    
    player = std::make_unique<Player>(100, 100);
    map = new Map();
    if (!map->loadFromFile("assets/map.txt")) {
        std::cerr << "Failed to load map!" << std::endl;
        return false;
    }
    
    running = true;
    return true;
}


void Game::run() {
    while (running) {
        handleEvents();
        update();
        render();
        SDL_Delay(16); // ~60 FPS
    }
}
#include "Game.hpp"
#include <iostream>
#include <memory>
#include "Constants.hpp"

Game::Game() : running(false), window(nullptr), renderer(nullptr), map(nullptr) {}

Game::~Game() {
    cleanup();
}

bool Game::init() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! Error: " << SDL_GetError() << std::endl;
        return false;
    }
    
    window = SDL_CreateWindow(Constants::WINDOW_TITLE,
                            SDL_WINDOWPOS_CENTERED,
                            SDL_WINDOWPOS_CENTERED,
                            Constants::SCREEN_WIDTH,
                            Constants::SCREEN_HEIGHT,
                            SDL_WINDOW_SHOWN);
    
    if (!window) {
        std::cerr << "Window could not be created! Error: " << SDL_GetError() << std::endl;
        return false;
    }
    
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << "Renderer could not be created! Error: " << SDL_GetError() << std::endl;
        return false;
    }
    
    player = std::make_unique<Player>(100, 100);
    map = new Map();
    if (!map->loadFromFile("assets/map.txt")) {
        std::cerr << "Failed to load map!" << std::endl;
        return false;
    }
    
    running = true;
    return true;
}

void Game::run() {
    while (running) {
        handleEvents();
        update();
        render();
        SDL_Delay(16); // ~60 FPS
    }
}

void Game::handleEvents() {
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) {
            running = false;
        }
        // Tukaj dodajte input handling za igralca
    }
}

void Game::update() {
    player->update();
    map->update();
}

void Game::render() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    
    map->render(renderer);
    player->render(renderer);
    
    SDL_RenderPresent(renderer);
}

void Game::cleanup() {
    delete map;
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
void Game::handleEvents() {
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) {
            running = false;
        }
        // Tukaj dodaj input handling za igralca
    }
}

void Game::update() {
    player->update();
    map.update();
    
    // Tukaj dodaj collision detection
}

void Game::render() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    
    map.render(renderer);
    player->render(renderer);
    
    SDL_RenderPresent(renderer);
}

void Game::cleanup() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}