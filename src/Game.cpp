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
    player(nullptr),
    map(nullptr),
    menu(nullptr),
    textureManager(TextureManager::getInstance()) {
}

Game::~Game() {
    Clean();
}

Game& Game::Instance() {
    if (!sInstance) {
        sInstance = new Game();
    }
    return *sInstance;
}

bool Game::Init(const char* title, int width, int height) {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return false;
    }

    window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
    if (!window) {
        std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
if (!renderer) {
    std::cerr << "Renderer creation failed: " << SDL_GetError() << std::endl;
    return;
}

    if (TTF_Init() == -1) {
        std::cerr << "TTF_Init Error: " << TTF_GetError() << std::endl;
        return false;
    }

    if (!textureManager.load("player", "images/player.png", renderer) ||
        !textureManager.load("enemy", "images/enemy.png", renderer) ||
        !textureManager.load("tile0", "images/tile0.png", renderer) ||
        !textureManager.load("tile1", "images/tile1.png", renderer) ||
        !textureManager.load("tile2", "images/tile2.png", renderer) ||
        !textureManager.load("tile3", "images/tile3.png", renderer) ||
        !textureManager.load("tile4", "images/tile4.png", renderer) ||
        !textureManager.load("animal1", "images/animal1.png", renderer) ||
        !textureManager.load("animal3", "images/animal3.png", renderer) ||
        !textureManager.load("farm", "images/farm.png", renderer) ||
        !textureManager.load("menu_bg", "images/menu_bg.png", renderer)) {
        return false;
    }

    map = new Map();
    player = new Player();
    menu = new Menu();

    isRunning = true;
    return true;
}

void Game::Run() {
    while (isRunning) {
        HandleEvents();
        Update();
        Render();
        SDL_Delay(16);
    }
}

void Game::HandleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            isRunning = false;
        }

        switch (currentState) {
            case MENU:
                menu->HandleEvents(event);
                break;
            case PLAYING:
                player->HandleEvent(event);
                break;
            case GAME_OVER:
                if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_r) {
                    Reset();
                }
                break;
        }
    }
}

void Game::Update() {
    switch (currentState) {
        case MENU:
            if (menu->StartGame()) {
                currentState = PLAYING;
            }
            break;
        case PLAYING:
            player->Update();
            if (player->IsDead()) {
                currentState = GAME_OVER;
            }
            break;
        case GAME_OVER:
            break;
    }
}

void Game::Render() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

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
    TTF_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

