#include "ReplayManager.hpp"
#include <fstream>
#include <iostream>
#include <SDL2/SDL_ttf.h>
using namespace std; // Da lahko uporabljamo standardne funkcije brez std::

void ReplayManager::recordMovement(int x, int y) {
    // Zabeleži premik igralca
    movements.emplace_back(x, y);
}

void ReplayManager::saveReplay(const string& filename) const {
    // Shrani replay v datoteko
    ofstream file(filename);
    if (!file) {
        cerr << "Error: Could not open file for writing: " << filename << endl;
        return;
    }
    for (const auto& move : movements) {
        file << move.first << " " << move.second << "\n";
    }
}

void ReplayManager::loadReplay(const string& filename) {
    // Naloži replay iz datoteke
    ifstream file(filename);
    if (!file) {
        cerr << "Error: Could not open file for reading: " << filename << endl;
        return;
    }
    movements.clear();
    int x, y;
    while (file >> x >> y) {
        movements.emplace_back(x, y);
    }
}

void ReplayManager::displayReplay(SDL_Renderer* renderer, [[maybe_unused]] TTF_Font* font) const {
    // Prikaži replay na zaslonu
    SDL_Event event;
    for (const auto& move : movements) {
        // Preverimo, ali je bil pritisnjen ESC
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) {
                return; // Prekinemo replay in se vrnemo v meni
            }
        }

        // Počistimo zaslon z črno barvo
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Izrišemo igralca na trenutni poziciji
        SDL_Rect playerRect = {move.first * 20, move.second * 20, 20, 20};
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // Bela barva za igralca
        SDL_RenderFillRect(renderer, &playerRect);

        // Posodobimo zaslon
        SDL_RenderPresent(renderer);

        // Skrajšamo čas med premiki za hitrejši replay
        SDL_Delay(30); // 30 ms za hitrejši replay
    }
}