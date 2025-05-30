#include "ScoreManager.hpp"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <SDL2/SDL_ttf.h>

using namespace std; // Da lahko uporabljamo standardne funkcije brez std::

void ScoreManager::addScore(const string& name, double time) {
    // Dodaj rezultat in ohrani samo top 5
    scores.emplace_back(name, time);
    sort(scores.begin(), scores.end(), [](const auto& a, const auto& b) {
        return a.second < b.second; // Sortiraj po času
    });
    if (scores.size() > 5) {
        scores.resize(5); // Ohranimo samo top 5 rezultatov
    }
}

void ScoreManager::saveScores(const string& filename) const {
    // Shrani rezultate v datoteko
    ofstream file(filename);
    if (!file) {
        cerr << "Error: Could not open file for writing: " << filename << endl;
        return;
    }
    for (const auto& score : scores) {
        file << score.first << " " << score.second << "\n";
    }
}

void ScoreManager::loadScores(const string& filename) {
    // Naloži rezultate iz datoteke
    ifstream file(filename);
    if (!file) {
        cerr << "Error: Could not open file for reading: " << filename << endl;
        return;
    }
    scores.clear();
    string name;
    double time;
    while (file >> name >> time) {
        scores.emplace_back(name, time);
    }
}

void ScoreManager::displayTopScores(SDL_Renderer* renderer, TTF_Font* font) const {
    // Prikaži top 5 rezultatov na zaslonu
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_Color white = {255, 255, 255, 255};
    SDL_Surface* titleSurface = TTF_RenderText_Solid(font, "Top 5 Scores", white);
    SDL_Texture* titleTexture = SDL_CreateTextureFromSurface(renderer, titleSurface);
    SDL_Rect titleRect = {200, 50, titleSurface->w, titleSurface->h};
    SDL_RenderCopy(renderer, titleTexture, nullptr, &titleRect);
    SDL_FreeSurface(titleSurface);
    SDL_DestroyTexture(titleTexture);

    int yOffset = 150;
    for (const auto& score : scores) {
        string text = score.first + ": " + to_string(score.second) + " seconds";
        SDL_Surface* scoreSurface = TTF_RenderText_Solid(font, text.c_str(), white);
        SDL_Texture* scoreTexture = SDL_CreateTextureFromSurface(renderer, scoreSurface);
        SDL_Rect scoreRect = {200, yOffset, scoreSurface->w, scoreSurface->h};
        SDL_RenderCopy(renderer, scoreTexture, nullptr, &scoreRect);
        SDL_FreeSurface(scoreSurface);
        SDL_DestroyTexture(scoreTexture);
        yOffset += 50;
    }

    SDL_RenderPresent(renderer);
}