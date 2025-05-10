#include "Menu.hpp"
#include <SDL2/SDL_ttf.h>
#include <ctime>
#include <algorithm>
#include <iostream>  // Dodano za std::cout
#include <ostream>   // Dodano za std::endl

Menu::Menu(SDL_Renderer* renderer) : renderer(renderer), nameEntered(false) {
    if (TTF_Init() == -1) {
        std::cerr << "Failed to initialize SDL_ttf: " << TTF_GetError() << std::endl;
    }
    font = TTF_OpenFont("assets/fonts/font.ttf", 24); // Pot do pisave
    if (!font) {
        std::cerr << "Failed to load font: " << TTF_GetError() << std::endl;
    }
}

Menu::~Menu() {
    TTF_CloseFont(font);
    TTF_Quit();
}

void Menu::displayMenu() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Črno ozadje
    SDL_RenderClear(renderer);

    SDL_Color white = {255, 255, 255, 255};

    // Prikaz naslova menija
    SDL_Surface* titleSurface = TTF_RenderText_Solid(font, "=== MENU ===", white);
    SDL_Texture* titleTexture = SDL_CreateTextureFromSurface(renderer, titleSurface);
    SDL_Rect titleRect = {200, 50, titleSurface->w, titleSurface->h};
    SDL_RenderCopy(renderer, titleTexture, nullptr, &titleRect);
    SDL_FreeSurface(titleSurface);
    SDL_DestroyTexture(titleTexture);

    // Prikaz možnosti menija
    const char* options[] = {"1. View Top 5 Scores", "2. Start Game", "3. Replay Last Game"};
    for (int i = 0; i < 3; ++i) {
        SDL_Surface* optionSurface = TTF_RenderText_Solid(font, options[i], white);
        SDL_Texture* optionTexture = SDL_CreateTextureFromSurface(renderer, optionSurface);
        SDL_Rect optionRect = {200, 150 + i * 50, optionSurface->w, optionSurface->h};
        SDL_RenderCopy(renderer, optionTexture, nullptr, &optionRect);
        SDL_FreeSurface(optionSurface);
        SDL_DestroyTexture(optionTexture);
    }

    SDL_RenderPresent(renderer);
}

void Menu::handleInput(SDL_Event& event) {
    if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
            case SDLK_1:
                std::cout << "Top 5 Scores:\n";
                // Prikaz rezultatov (implementirano v ScoreManager)
                break;
            case SDLK_2:
                if (!nameEntered) {
                    std::cout << "Enter your name: ";
                    std::cin >> playerName;
                    nameEntered = true;
                }
                break;
            case SDLK_3:
                std::cout << "Replaying last game...\n";
                // Replay logika (implementirano v ReplayManager)
                break;
            default:
                std::cout << "Invalid choice. Try again.\n";
                break;
        }
    }
}

std::string Menu::getPlayerName() const {
    return playerName;
}

bool Menu::isNameEntered() const {
    return nameEntered;
}