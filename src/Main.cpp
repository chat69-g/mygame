#include <SDL2/SDL.h>
#include <iostream>
#include <vector>
#include "Player.hpp"
#include "Enemy.hpp"
#include "Farm.hpp"
#include "Animal.hpp"
#include "ScoreManager.hpp"
#include "ReplayManager.hpp"
#include "Timer.hpp"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

void renderPlayer(SDL_Renderer* renderer, const Player& player) {
    SDL_Rect rect = { player.getX() * 20, player.getY() * 20, 20, 20 };
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // Green for player
    SDL_RenderFillRect(renderer, &rect);
}

void renderEnemy(SDL_Renderer* renderer, const Enemy& enemy) {
    SDL_Rect rect = { enemy.getX() * 20, enemy.getY() * 20, 20, 20 };
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Red for enemy
    SDL_RenderFillRect(renderer, &rect);
}

void renderFarm(SDL_Renderer* renderer, const Farm& farm) {
    if (farm.isVisible()) {
        SDL_Rect rect = { farm.getX() * 20, farm.getY() * 20, 20, 20 };
        SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255); // Yellow for farm
        SDL_RenderFillRect(renderer, &rect);
    }
}

void renderAnimal(SDL_Renderer* renderer, const Animal& animal) {
    if (!animal.isRescued()) {
        SDL_Rect rect = { animal.getX() * 20, animal.getY() * 20, 20, 20 };
        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255); // Blue for animal
        SDL_RenderFillRect(renderer, &rect);
    }
}

int main(int /*argc*/, char* /*argv*/[]) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "Failed to initialize SDL: " << SDL_GetError() << std::endl;
        return -1;
    }

    SDL_Window* window = SDL_CreateWindow("My Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window) {
        std::cerr << "Failed to create window: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return -1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << "Failed to create renderer: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    // Initialize game objects
    Player player(SCREEN_WIDTH / 20, SCREEN_HEIGHT / 20);
    Farm farm(SCREEN_WIDTH / 20, SCREEN_HEIGHT / 20);
    Animal animal(SCREEN_WIDTH / 20, SCREEN_HEIGHT / 20);
    std::vector<Enemy> enemies = { Enemy(SCREEN_WIDTH / 20, SCREEN_HEIGHT / 20), Enemy(SCREEN_WIDTH / 20, SCREEN_HEIGHT / 20) };
    Timer timer(120); // 2-minute timer

    bool running = true;
    SDL_Event event;

    while (running) {
        // Event handling
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            } else if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    case SDLK_w: player.move('w'); break;
                    case SDLK_s: player.move('s'); break;
                    case SDLK_a: player.move('a'); break;
                    case SDLK_d: player.move('d'); break;
                }
            }
        }

        // Game logic
        farm.checkProximity(player.getX(), player.getY());
        animal.checkRescue(player.getX(), player.getY());
        for (auto& enemy : enemies) {
            enemy.update(player.getX(), player.getY());
            if (enemy.isNearPlayer(player.getX(), player.getY())) {
                player.loseLife();
                if (!player.isAlive()) {
                    running = false;
                    std::cout << "Game Over! You lost all your lives." << std::endl;
                }
            }
        }

        if (animal.isRescued()) {
            running = false;
            std::cout << "You win! You rescued the animal!" << std::endl;
        }

        if (timer.isTimeUp()) {
            running = false;
            std::cout << "Game Over! Time is up." << std::endl;
        }

        // Rendering
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Black background
        SDL_RenderClear(renderer);

        renderPlayer(renderer, player);
        renderFarm(renderer, farm);
        renderAnimal(renderer, animal);
        for (const auto& enemy : enemies) {
            renderEnemy(renderer, enemy);
        }

        SDL_RenderPresent(renderer);

        SDL_Delay(16); // ~60 FPS
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}