#include "Menu.hpp"
#include "TextureManager.hpp"
#include <SDL2/SDL_ttf.h>
#include <ctime>
#include <algorithm>
#include <iostream>  // Dodano za std::cout
#include <ostream>   // Dodano za std::endl

Menu::Menu() : startGame(false) {
    TextureManager& tm = TextureManager::getInstance();
    background = tm.get("menu_bg");
    
    // Inicializacija naslova in high scores
    highScores = {
        {"Player1", 1000, time(nullptr), 1},
        {"Player2", 800, time(nullptr), 1},
        {"Player3", 600, time(nullptr), 1}
    };
}

Menu::~Menu() {
    // Textures managed by TextureManager
}

void Menu::HandleEvents(SDL_Event& event) {
    if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RETURN) {
        startGame = true;
        std::cout << "ENTER pressed - startGame set to true" << std::endl;
    }
}

bool Menu::StartGame() const {
    std::cout << "Checking startGame: " << startGame << std::endl;
    return startGame;
}

void Menu::Render(SDL_Renderer* renderer) {
    SDL_RenderCopy(renderer, background, nullptr, nullptr);
    
    // Render high scores
    TTF_Font* font = TTF_OpenFont("assets/fonts/arial.ttf", 24);
    if (font) {
        SDL_Color white = {255, 255, 255, 255};
        for (size_t i = 0; i < highScores.size(); ++i) {
            std::string scoreText = highScores[i].name + ": " + std::to_string(highScores[i].score);
            SDL_Surface* surface = TTF_RenderText_Solid(font, scoreText.c_str(), white);
            SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
            
            SDL_Rect destRect = {100, 200 + static_cast<int>(i) * 30, surface->w, surface->h};
            SDL_RenderCopy(renderer, texture, nullptr, &destRect);
            
            SDL_FreeSurface(surface);
            SDL_DestroyTexture(texture);
        }
        TTF_CloseFont(font);
    }
}

void Menu::AddHighScore(const std::string& name, int score) {
    highScores.push_back({name, score, time(nullptr), 1});
    std::sort(highScores.begin(), highScores.end(), 
        [](const ScoreEntry& a, const ScoreEntry& b) { return a.score > b.score; });
    if (highScores.size() > 10) {
        highScores.resize(10);
    }
}