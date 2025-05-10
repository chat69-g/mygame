#include "Game.hpp"
#include "TextureManager.hpp"
#include "Player.hpp"
#include "Enemy.hpp"
#include "Animal.hpp"
#include "Farm.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>

Game* Game::sInstance = nullptr; // Definicija statičnega člana

Game::Game() : player(nullptr), window(nullptr), renderer(nullptr), isRunning(false) {
    player = new Player(10, 10); // Inicializacija igralca
}

Game& Game::Instance() {
    if (!sInstance) {
        sInstance = new Game();
    }
    return *sInstance;
}

bool Game::Init(const char* title, int width, int height) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        return false;
    }
    window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
    if (!window) {
        return false;
    }
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        return false;
    }
    isRunning = true;
    return true;
}

void Game::Run() {
    while (isRunning) {
        Update(0.016f); // 60 FPS
        Render();
    }
    Clean();
}

void Game::Update(float /*deltaTime*/) {
    // Posodobitev logike igre
}

void Game::Render() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Risanje igralca
    SDL_Rect playerRect = { player->getX() * 20, player->getY() * 20, 20, 20 };
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_RenderFillRect(renderer, &playerRect);

    SDL_RenderPresent(renderer);
}

void Game::Clean() {
    delete player;
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

bool Game::IsRunning() const {
    return isRunning;
}