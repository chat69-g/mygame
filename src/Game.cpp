#include "Game.hpp"
#include "TextureManager.hpp"
#include "Player.hpp"
#include "Map.hpp"
#include "Enemy.hpp"
#include "Animal.hpp"
#include "Farm.hpp"
#include "Menu.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>

Game* Game::sInstance = nullptr;

Game::Game() :
    window(nullptr),
    renderer(nullptr),
    isRunning(false),
    currentState(MENU),
    textureManager(TextureManager::getInstance()),  // Matches declaration order
    player(nullptr),
    map(nullptr),
    menu(nullptr) {
}

Game& Game::Instance() {
    if (!sInstance) {
        sInstance = new Game();
    }
    return *sInstance;
}

bool Game::Init(const char* title, int width, int height) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return false;
    }

    window = SDL_CreateWindow(title, 
                            SDL_WINDOWPOS_CENTERED, 
                            SDL_WINDOWPOS_CENTERED, 
                            width, 
                            height, 
                            SDL_WINDOW_SHOWN);
    if (!window) {
        std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer) {
        std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        return false;
    }

    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        std::cerr << "SDL_image could not initialize! Error: " << IMG_GetError() << std::endl;
        return false;
    }

    if (TTF_Init() == -1) {
        std::cerr << "SDL_ttf could not initialize! Error: " << TTF_GetError() << std::endl;
        return false;
    }

    // Nalaganje tekstur
    if (!textureManager.load("player", "player.png", renderer) ||
        !textureManager.load("enemy", "enemy.png", renderer) ||
        !textureManager.load("tile0", "tile0.png", renderer) ||
        !textureManager.load("tile1", "tile1.png", renderer) ||
        !textureManager.load("tile2", "tile2.png", renderer) ||
        !textureManager.load("tile3", "tile3.png", renderer) ||
        !textureManager.load("tile4", "tile4.png", renderer) ||
        !textureManager.load("animal1", "animal1.png", renderer) ||
        !textureManager.load("animal3", "animal3.png", renderer) ||
        !textureManager.load("farm", "farm.png", renderer) ||
        !textureManager.load("menu_bg", "menu_bg.png", renderer)) {
        return false;
    }

    map = new Map();
    player = new Player();
    menu = new Menu();

    isRunning = true;
    return true;
}

void Game::Run() {
    Uint32 lastTime = SDL_GetTicks();
    
    while (IsRunning()) {
        Uint32 currentTime = SDL_GetTicks();
        (void)lastTime;  // Izognemo se opozorilu o neuporabljeni spremenljivki
        lastTime = currentTime;

        HandleEvents();
        Update();
        Render();

        Uint32 frameTime = SDL_GetTicks() - currentTime;
        if (frameTime < 16) {
            SDL_Delay(16 - frameTime);
        }
    }
}

void Game::HandleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            isRunning = false;
            return;
        }

        if (currentState == MENU) {
            menu->HandleEvents(event);
            if (menu->StartGame()) {
                std::cout << "Switching to PLAYING state" << std::endl; // Debug
                currentState = PLAYING;
            }
        }
        else if (currentState == PLAYING) {
            player->HandleEvent(event);
        }
    }
}



void Game::Update() {
    if (currentState == PLAYING && player) {
        player->Update();  // Posodabljamo igralca
    }
}

void Game::Render() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    std::cout << "Current state: " << currentState << std::endl;
    switch (currentState) {
        case MENU:
            menu->Render(renderer);
            break;
        case PLAYING:
            map->Render(renderer);
            player->Render(renderer);
            break;
        case GAME_OVER:
            RenderGameOver();
            break;
    }

    SDL_RenderPresent(renderer);
}

void Game::RenderGameOver() {
    map->Render(renderer);
    player->Render(renderer);
    
    TTF_Font* font = TTF_OpenFont("fonts/arial.ttf", 24);
    if (!font) {
        return;
    }

    SDL_Color white = {255, 255, 255, 255};
    SDL_Surface* surface = TTF_RenderText_Solid(font, "Game Over! Press R to restart", white);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    
    SDL_Rect rect = {200, 300, surface->w, surface->h};
    SDL_RenderCopy(renderer, texture, NULL, &rect);
    
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
    TTF_CloseFont(font);
}

void Game::Reset() {
    delete player;
    player = new Player();
    currentState = PLAYING;
}

void Game::Clean() {
    delete menu;
    delete player;
    delete map;

    textureManager.clean();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}
bool Game::IsRunning() const {
    return isRunning;
}