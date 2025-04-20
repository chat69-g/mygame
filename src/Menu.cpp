#include "Menu.hpp"
#include "Game.hpp"
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

using namespace std;

Menu::Menu() : playerName("Player"), startGame(false), 
              loadGame(false), showHighScores(false), exitGame(false) {
    
    // Initialize menu items
    mainMenuItems = {
        {"Start Game", {300, 200, 200, 50}, false},
        {"Load Game", {300, 260, 200, 50}, false},
        {"High Scores", {300, 320, 200, 50}, false},
        {"Exit", {300, 380, 200, 50}, false}
    };
    
    // Load textures
    background = IMG_LoadTexture(Game::Instance().renderer, "assets/menu_bg.png");
    
    TTF_Font* font = TTF_OpenFont("assets/font.ttf", 24);
    if(font) {
        SDL_Color white = {255, 255, 255, 255};
        SDL_Surface* surf = TTF_RenderText_Solid(font, "Animal Rescue", white);
        titleTexture = SDL_CreateTextureFromSurface(Game::Instance().renderer, surf);
        SDL_FreeSurface(surf);
        TTF_CloseFont(font);
    }
}

void Menu::HandleEvents(SDL_Event& event) {
    if(event.type == SDL_MOUSEMOTION) {
        for(auto& item : mainMenuItems) {
            SDL_Point mouse = {event.motion.x, event.motion.y};
            item.isSelected = SDL_PointInRect(&mouse, &item.rect);
        }
    }
    
    if(event.type == SDL_MOUSEBUTTONDOWN) {
        for(auto& item : mainMenuItems) {
            if(item.isSelected) {
                if(item.text == "Start Game") startGame = true;
                else if(item.text == "Load Game") loadGame = true;
                else if(item.text == "High Scores") showHighScores = true;
                else if(item.text == "Exit") exitGame = true;
            }
        }
    }
    
    if(event.type == SDL_KEYDOWN && showHighScores) {
        if(event.key.keysym.sym == SDLK_ESCAPE) {
            showHighScores = false;
        }
    }
    
    if(event.type == SDL_TEXTINPUT && !showHighScores) {
        playerName += event.text.text;
    }
    
    if(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_BACKSPACE && !playerName.empty()) {
        playerName.pop_back();
    }
}

void Menu::Render(SDL_Renderer* renderer) {
    // Render background
    if(background) {
        SDL_RenderCopy(renderer, background, nullptr, nullptr);
    }
    
    if(showHighScores) {
        RenderHighScores(renderer);
        return;
    }
    
    // Render title
    if(titleTexture) {
        SDL_Rect titleRect = {250, 100, 300, 80};
        SDL_RenderCopy(renderer, titleTexture, nullptr, &titleRect);
    }
    
    // Render menu items
    SDL_Color normal = {200, 200, 200, 255};
    SDL_Color selected = {255, 255, 0, 255};
    
    TTF_Font* font = TTF_OpenFont("assets/font.ttf", 24);
    if(font) {
        for(auto& item : mainMenuItems) {
            SDL_Color color = item.isSelected ? selected : normal;
            SDL_Surface* surf = TTF_RenderText_Solid(font, item.text.c_str(), color);
            SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, surf);
            
            SDL_Rect textRect = {
                item.rect.x + (item.rect.w - surf->w) / 2,
                item.rect.y + (item.rect.h - surf->h) / 2,
                surf->w,
                surf->h
            };
            
            SDL_RenderCopy(renderer, tex, nullptr, &textRect);
            SDL_FreeSurface(surf);
            SDL_DestroyTexture(tex);
        }
        
        // Render player name input
        SDL_Color white = {255, 255, 255, 255};
        string prompt = "Enter name: " + playerName;
        SDL_Surface* nameSurf = TTF_RenderText_Solid(font, prompt.c_str(), white);
        SDL_Texture* nameTex = SDL_CreateTextureFromSurface(renderer, nameSurf);
        SDL_Rect nameRect = {300, 450, nameSurf->w, nameSurf->h};
        SDL_RenderCopy(renderer, nameTex, nullptr, &nameRect);
        SDL_FreeSurface(nameSurf);
        SDL_DestroyTexture(nameTex);
        
        TTF_CloseFont(font);
    }
}

void Menu::RenderHighScores(SDL_Renderer* renderer) {
    // Render background
    SDL_SetRenderDrawColor(renderer, 0, 0, 50, 255);
    SDL_Rect bgRect = {200, 100, 400, 400};
    SDL_RenderFillRect(renderer, &bgRect);
    
    // Render title
    TTF_Font* font = TTF_OpenFont("assets/font.ttf", 32);
    if(font) {
        SDL_Color white = {255, 255, 255, 255};
        SDL_Surface* surf = TTF_RenderText_Solid(font, "High Scores", white);
        SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, surf);
        SDL_Rect rect = {300, 120, surf->w, surf->h};
        SDL_RenderCopy(renderer, tex, nullptr, &rect);
        SDL_FreeSurface(surf);
        SDL_DestroyTexture(tex);
    }
    
    // Render scores
    font = TTF_OpenFont("assets/font.ttf", 24);
    if(font) {
        int y = 180;
        for(const auto& entry : highScores) {
            string text = entry.name + ": " + to_string(entry.score);
            SDL_Color white = {255, 255, 255, 255};
            SDL_Surface* surf = TTF_RenderText_Solid(font, text.c_str(), white);
            SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, surf);
            SDL_Rect rect = {250, y, surf->w, surf->h};
            SDL_RenderCopy(renderer, tex, nullptr, &rect);
            SDL_FreeSurface(surf);
            SDL_DestroyTexture(tex);
            y += 40;
        }
        
        // Render back prompt
        SDL_Color yellow = {255, 255, 0, 255};
        SDL_Surface* backSurf = TTF_RenderText_Solid(font, "Press ESC to return", yellow);
        SDL_Texture* backTex = SDL_CreateTextureFromSurface(renderer, backSurf);
        SDL_Rect backRect = {300, 450, backSurf->w, backSurf->h};
        SDL_RenderCopy(renderer, backTex, nullptr, &backRect);
        SDL_FreeSurface(backSurf);
        SDL_DestroyTexture(backTex);
        
        TTF_CloseFont(font);
    }
}

void Menu::AddHighScore(const string& name, int score) {
    highScores.push_back({name, score});
    sort(highScores.begin(), highScores.end(), 
        [](const ScoreEntry& a, const ScoreEntry& b) {
            return a.score > b.score;
        });
    
    if(highScores.size() > 5) {
        highScores.resize(5);
    }
}