#include "ReplayManager.hpp"
#include <fstream>
#include <iostream>
#include <SDL2/SDL_ttf.h>

void ReplayManager::recordMovement(int x, int y) {
    movements.emplace_back(x, y);
}

void ReplayManager::saveReplay(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file) {
        std::cerr << "Error: Could not open file for writing: " << filename << std::endl;
        return;
    }
    for (const auto& move : movements) {
        file << move.first << " " << move.second << "\n";
    }
}

void ReplayManager::loadReplay(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Error: Could not open file for reading: " << filename << std::endl;
        return;
    }
    movements.clear();
    int x, y;
    while (file >> x >> y) {
        movements.emplace_back(x, y);
    }
}

void ReplayManager::displayReplay(SDL_Renderer* renderer, TTF_Font* font) const {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_Color white = {255, 255, 255, 255};
    SDL_Surface* titleSurface = TTF_RenderText_Solid(font, "Replay of Last Game", white);
    SDL_Texture* titleTexture = SDL_CreateTextureFromSurface(renderer, titleSurface);
    SDL_Rect titleRect = {200, 50, titleSurface->w, titleSurface->h};
    SDL_RenderCopy(renderer, titleTexture, nullptr, &titleRect);
    SDL_FreeSurface(titleSurface);
    SDL_DestroyTexture(titleTexture);

    int yOffset = 150;
    for (const auto& move : movements) {
        std::string text = "Player moved to (" + std::to_string(move.first) + ", " + std::to_string(move.second) + ")";
        SDL_Surface* moveSurface = TTF_RenderText_Solid(font, text.c_str(), white);
        SDL_Texture* moveTexture = SDL_CreateTextureFromSurface(renderer, moveSurface);
        SDL_Rect moveRect = {200, yOffset, moveSurface->w, moveSurface->h};
        SDL_RenderCopy(renderer, moveTexture, nullptr, &moveRect);
        SDL_FreeSurface(moveSurface);
        SDL_DestroyTexture(moveTexture);
        yOffset += 50;
    }

    SDL_RenderPresent(renderer);

    bool waiting = true;
    SDL_Event waitEvent;
    while (waiting) {
        while (SDL_PollEvent(&waitEvent)) {
            if (waitEvent.type == SDL_KEYDOWN && waitEvent.key.keysym.sym == SDLK_ESCAPE) {
                waiting = false;
            }
        }
    }
}